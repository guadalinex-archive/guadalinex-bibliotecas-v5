#!/bin/bash

logs=/var/log/installer/debug

exec > $logs 2>&1

function error() {
	echo "Error: $*"
}

cp -v /usr/share/gbiblio-ubiquity/templates/hosts /target/etc/hosts || error "copying hosts"

cp -v /usr/share/gbiblio-ubiquity/templates/resolv.conf /target/etc/resolv.conf || error "copying resolv.conf"

cp -v /tmp/interfaces /target/etc/network/interfaces  || error "copying interfaces"

dev=$(awk -F: '/:/ {gsub(" ","",$1); print $1}' /proc/net/wireless)
if [ "$dev" != "ath0" ]; then
        sed -i 's|ath0|'$dev'|g' /target/etc/network/interfaces
fi

if ( grep -q client /proc/cmdline ) ; then
	line='servidor:/var/nfs/compartido /var/Compartido  nfs        rw,hard,intr,auto,user      0 0'
         echo $line >> /target/etc/fstab || error "Adding nfs line to fstab"
fi

exit 0
