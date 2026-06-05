#!/bin/bash

Memoire_totale=$(free --giga | grep Mem | awk '{print $2}')
Memoire_libre=$(free --giga | grep Mem | awk '{print $4}')
Nombre_coeur=$(nproc)
Architecture=$(getconf LONG_BIT)
Mem_disk=$(lsblk | grep disk | head -1 |awk '{print $4}')
ip=$(hostname -I | awk '{print $1}')


echo "Memoire totale: $Memoire_totale G"
echo "Memoire_libre: $Memoire_libre G"
echo "Nombre de coeur : $Nombre_coeur coeurs"
echo "Architecture : $Architecture bits"
echo "Taille du disque interne : $Mem_disk"
echo "Ip reseau : $ip"

dpkg -l > /dev/null 2>&1

if [ $? -eq 0 ]; then
    Nombre_paquet=$(dpkg -l | grep ^ii | wc -l )
else
    Nombre_paquet=$(rpm -qa | wc -l)
fi
echo "Nombre de paquets installes : $Nombre_paquet paquets"