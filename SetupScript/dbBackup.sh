#!/bin/bash
set -e

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
#es werden noch ein paar versteckte Ordner sichtbar gemacht
TODAY=$(/bin/date +%y%m%d)

cd /var/www/html
rsync -avR  Pictures /mnt/smb/dbBackup
mysqldump -u ramocuser -pramoc ramoc > /mnt/smb/dbBackup/$TODAY.sql
#DAILY=(workspace ConfigFiles Skripte Projekte)
#for DAILY in "${DAILY[@]}"
#do
#	rsync -e /usr/bin/ssh -avR $DAILY 192.168.2.100:/Backup/$TODAY
#done

#RaMoc Datenbank sichern
#ssh 192.168.2.100 "mysqldump -u ramocuser -pramoc --databases ramoc > /Backup/RaMoC.sql"

#Tagesverzeichnis packen & loeschen
#ssh 192.168.2.100 "tar --directory /Backup -czf /Backup/\"$TODAY\".tgz \"$TODAY\""
#ssh 192.168.2.100 "rm -rf /Backup/\"$TODAY\""

logger "AutoBackup: done"

### Git Backup ###
#cd /home/drue/workspace/RaMoC-L
#
#git add -A
#git commit -a -m "`date`"
#
#git push origin master
#
#SOURCES=(/home/drue/workspace/RaMoC /home/drue/Projekte/RaMoC/RaMoc-Client )

#for SOURCE in "${SOURCES[@]}"
#do
#		cd $SOURCE
#		git add -A
#		git commit -a -m "`date`"
#
#		git push origin master
#		
#done 
#sudo /sbin/shutdown -h now
#sudo systemctl suspend


