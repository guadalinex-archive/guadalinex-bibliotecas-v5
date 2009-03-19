#!/usr/bin/python
# -*- coding: utf-8 -*-

#######################################################################################################
#Autor:         J. Felix Ontañón <fontanon@emergya.es>
#Fecha:         2009/02/04
#Versión:       0.1
#Licencia:      GNU GPL (http://www.gnu.org/licenses/gpl.txt)
#Descripcion:   Genera ejecutable en C ofuscado capaz de reemplazar las claves de los usuarios definidos
#		por la constante USERNAME. 
#		Recibe como argumento el nombre del binario resultante.
#
#Uso:           python claves.py [nombre_binario]
#
#Ejemplo: 	python claves.py cambia_clave
#		Genera binario cambia_clave que, ejecutado como root, modifica las claves de los
#		usuario definidos por 
#
#Dependencias:	gcc, pwgen, mkpasswd
#
######################################################################################################

import os
import sys
import subprocess

# Plantilla del codigo del binario a generar
C_CODE='#include <stdio.h>\n\
#include <string.h>\n\
#include <stdlib.h>\n\
#include <unistd.h>\n\
#include <sys/types.h>\n\
\n\
#define SLICES //REPLACE_SLICES//\n\
#define SIZE //REPLACE_SIZE//\n\
#define USERS //REPLACE_USERS_SIZE//\n\
\n\
\n\
int main() {\n\
       	int i=0, j=0;\n\
	char *arg1[4], *arg2[3];\n\
\n\
	pid_t pid1,pid2;\n\
	int pipefd[2];\n\
\n\
        char claves[SLICES][SIZE]={//REPLACE_HASHES//};\n\
       	char usuarios[USERS][11]={//REPLACE_USERS//};\n\
\n\
        arg1[0]=\"echo\";\n\
        arg1[1]=\"-n\";\n\
        arg1[2]=malloc(1024);\n\
        arg1[3]=0;\n\
\n\
        arg2[0]=\"chpasswd\";\n\
        arg2[1]=\"-e\";\n\
        arg2[2]=0;\n\
\n\
       	for(i=0;i<USERS;i++)\n\
        {\n\
		strcat(arg1[2], usuarios[i]);\n\
		strcat(arg1[2], \":\");\n\
\n\
\n\
		for(j=i;j<SLICES;j+=USERS)\n\
			strcat(arg1[2], claves[j]);\n\
		strcat(arg1[2], \"\\n\");\n\
        }\n\
\n\
        pipe(pipefd);\n\
        if(!(pid1=fork()))\n\
        {\n\
                dup2(pipefd[1],STDOUT_FILENO);\n\
                close(pipefd[0]);\n\
                execvp(arg1[0],arg1);\n\
                return(1);\n\
        }\n\
        else\n\
        {\n\
                waitpid(pid1,NULL,0);\n\
                dup2(pipefd[0],STDIN_FILENO);\n\
                close(pipefd[1]);\n\
                execvp(arg2[0],arg2);\n\
                return(2);\n\
        }\n\
\n\
        return 0;\n\
}\n'

# Lista de usuarios sobre los que actuar
USERNAMES=["biblio", "cau", "catalogo", "usuario"]

# Longitud de la clave en texto plano
PASS_LENGTH=6

# Longitud del hash md5 de la clave. Suele ser 34
HASH_LENGTH=34

# Los trozos en los que se dividen los hashes md5 de las claves son de esta longitud
HASH_SLICE=2 # Cuidado con cambiar este valor, depende de HASH_LENGTH

# Nombre del ejecutable de salida 
if len(sys.argv) == 2:
	BINARY_NAME=sys.argv[1]
else:
	BINARY_NAME="chpwd"

# Ruta del ejecutable de salida
OUTPUT_PATH="./"

# Devuelve lo obtenido por la salida estandar tras ejecutar un comando de shell
def execute(command):
	p = subprocess.Popen([command], shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE, close_fds=True)
	(child_stdout, child_stdin) = (p.stdout, p.stdin)
	return child_stdout.read()

# Divide cada passwod md5 en trozos y revuelve una lista de trozos mezclados
def format_hashes(hashes, num_users):
	hash_slices = []
	i=0
	while (i + HASH_SLICE) <= HASH_LENGTH:
		for index in range(0, num_users):
			hash_slices.append(hashes[index][i:i+HASH_SLICE])

		i = i + HASH_SLICE
	
	return hash_slices

hashes = []
# Crea passwords y hashes md5, los imprime por pantalla y guarda en fichero
os.system("rm -f claves_`date +%d%m%Y`")
for username in USERNAMES:
	try:
		plain = execute("pwgen -n -A %s 1" % PASS_LENGTH)[:-1]
		hash = execute("mkpasswd -H md5 %s" % plain)[:-1]
	except:
		sys.exit(1)

	hashes.append(hash)

	hash_string = "%s: %s %s" % (username, plain, hash)
	print "	%s" % hash_string
	os.system("echo '" + hash_string + "' >> claves_`date +%d%m%Y`")

# Comenzamos a sustituir los valores en el codigo C
users_replacement = str(USERNAMES).replace("'",'"').replace('[','').replace(']','')
hash_slices = format_hashes(hashes, len(USERNAMES))
hashes_replacement = str(hash_slices).replace("'",'"').replace('[','').replace(']','')

C_CODE = C_CODE.replace("//REPLACE_SLICES//", str(len(hash_slices)))
C_CODE = C_CODE.replace("//REPLACE_SIZE//", str(HASH_SLICE+1))
C_CODE = C_CODE.replace("//REPLACE_USERS_SIZE//", str(len(USERNAMES)))
C_CODE = C_CODE.replace("//REPLACE_USERS//", users_replacement)
C_CODE = C_CODE.replace("//REPLACE_HASHES//", hashes_replacement)

# Escribimos el fichero fuente
try:
	f = open(BINARY_NAME+".c","w")
	f.write(C_CODE)
	f.close()
except:
	sys.exit(2)

# Y lo compilamos
try:
	os.system("gcc -c %s.c" % BINARY_NAME)
	os.system("gcc -o %s %s.o" % ((OUTPUT_PATH+BINARY_NAME), BINARY_NAME))
except:
	sys.exit(3)

# Acciones de limpieza
#os.system("rm %s.c %s.o" %  (BINARY_NAME,  BINARY_NAME))
sys.exit(0)
