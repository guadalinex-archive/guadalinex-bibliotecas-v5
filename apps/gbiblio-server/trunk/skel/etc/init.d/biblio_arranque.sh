#!/bin/bash

# Actualizaciones automáticas
# ===========================

echo "Actualizando base de datos de paquetes..."
 ( dpkg --configure -a 
   apt-get update

# Instalacion del metapaquete de actualizacion del servidor
  echo "Actualizando sistema..."
  DEBCONF_PRIORITY=critical apt-get -f install -o APT::Get::Assume-Yes="true" -o APT::Get::Remove="true" -o APT::Get::Show-Upgraded="true" -o APT::Quiet="true" -o DPkg::Options="--force-confmiss --force-confold" -o DPkg::Pre-Install-Pkgs="/usr/sbin/dpkg-preconfigure --apt" -y -qq --force-yes

  DEBCONF_PRIORITY=critical apt-get install -o APT::Get::Assume-Yes="true" -o APT::Get::Remove="true" -o APT::Get::Show-Upgraded="true" -o APT::Quiet="true" -o DPkg::Options="--force-confmiss --force-confold" -o DPkg::Pre-Install-Pkgs="/usr/sbin/dpkg-preconfigure --apt" -y -qq --force-yes gbiblio-v5-servidor-actualizacion

 ) &


# Quota
# =====

#/usr/local/bin/cambiar_quota_usuario.sh usuario 1000

# Borrado del directorio /home/usuario en cada arranque
# (No se borra el usuario del servidor)
#echo "Borrando contenido de directorio de usuario /home/usuario..."
#rm -rf /home/usuario/*

# Se pone el volumen general al 20% en cada arranque
amixer sset Master 20% 

# HACKS
# =====
# Fichero de logs
LOG=/var/log/biblio_arranque_log
