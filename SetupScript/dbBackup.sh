#!/bin/bash
#set -e

ping -c1 -w1 -q 192.168.0.2 > /dev/null
if [ $? -ne 0 ]
 then
	logger "AutoBackup: Send wake on lan"
	wakeonlan 00:1c:c0:a8:f6:4e
	sleep 60
fi

logger "AutoBackup: Reping Host"
ping -c1 -w1 -q 192.168.0.2 > /dev/null
STATUS=$?
COUNTER=0

#Sollte die NAS beim hochfahren einen HD-Check durchführen kann das schon 
#etwas dauern 
while [ $STATUS -ne 0 ] && [ $COUNTER -lt 100 ];
do
	logger "AutoBackup: Versuch " $COUNTER
	ping -c1 -w1 -q 192.168.0.2 > /dev/null
	STATUS=$?
	COUNTER=$[$COUNTER +1]
	sleep 60
done


if [ $COUNTER -eq 100 ]
then
	logger "AutoBackup: Abbruch nach " $COUNTER " Versuchen " 
	exit
fi

#NAS ist gestartet und gemountet
TODAY=$(/bin/date +%y%m%d)
cd /mnt/smb/dbBackup/Pictures/Actor
rm *
cd /mnt/smb/dbBackup/Pictures/Poster
rm *
cd /mnt/smb/dbBackup/Pictures/Backdrop
rm *

cd /var/www/html/Pictures/Actor
cp -v * /mnt/smb/dbBackup/Pictures/Actor

cd /var/www/html/Pictures/Poster
cp -v * /mnt/smb/dbBackup/Pictures/Poster

cd /var/www/html/Pictures/Backdrop
cp -v * /mnt/smb/dbBackup/Pictures/Backdrop
#rsync -avR --omit-dir-times Pictures /mnt/smb/dbBackup
mysqldump -u ramocuser -pramoc ramoc > /mnt/smb/dbBackup/$TODAY.sql

logger "AutoBackup: done"


