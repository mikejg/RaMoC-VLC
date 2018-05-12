#!/bin/bash
set -e
#mysqldump -u root -pramoc-mysql --add-drop-table ramoc > database.sql
BACKUPDIR="/media/ramoc/Backup/DataBase/"

#lösche alle alten Einträge
cd "${BACKUPDIR}"
rm -f *.sql

mysqldump -v -u root -pramoc-mysql ramoc m_artist > "${BACKUPDIR}m_artist.sql"
mysqldump -v -u root -pramoc-mysql ramoc m_genre > "${BACKUPDIR}m_genre.sql"
mysqldump -v -u root -pramoc-mysql ramoc m_title > "${BACKUPDIR}m_title.sql"
mysqldump -v -u root -pramoc-mysql ramoc m_year > "${BACKUPDIR}m_year.sql"

mysqldump -v -u root -pramoc-mysql ramoc t_Datei > "${BACKUPDIR}t_Datei.sql"
mysqldump -v -u root -pramoc-mysql ramoc t_Datei_Film > "${BACKUPDIR}t_Datei_Film.sql"
mysqldump -v -u root -pramoc-mysql ramoc t_Datei_Film > "${BACKUPDIR}t_Datei_Film.sql"
mysqldump -v -u root -pramoc-mysql ramoc t_Genre > "${BACKUPDIR}t_Genre.sql"
mysqldump -v -u root -pramoc-mysql ramoc t_Person_Film > "${BACKUPDIR}t_Person_Film.sql"
mysqldump -v -u root -pramoc-mysql ramoc t_Regie > "${BACKUPDIR}t_Regie.sql"

#wenn das Verzeichnis Person nicht existiert wird es erstellt
if [ ! -d "${BACKUPDIR}Person" ]
then
  mkdir "${BACKUPDIR}Person"
fi
#lösche alle alten Einträge
cd "${BACKUPDIR}Person/"
rm -f *.sql

#Hol mir die letzte id
id=$(mysql ramoc -u ramocuser -pramoc -se "select id from t_Person order by id desc limit 0,1")

#Beim ersten dump wird mit DROP TABLE und CREATE TABLE geschrieben, bei den restlich nichtmehr
mysqldump -v -u root -pramoc-mysql ramoc t_Person --where "id<100" > "${BACKUPDIR}Person/t_Person0001.sql"
LOWCOUNTER=-1
HIGHCOUNTER=100
COUNT=0
while [ $HIGHCOUNTER -lt $id ]
do
    let LOWCOUNTER=LOWCOUNTER+100
    let HIGHCOUNTER=HIGHCOUNTER+100
    let COUNT=COUNT+1
    INDEX=$COUNT

    if [ $COUNT -lt 1000 ]
    then
      INDEX="0${COUNT}"
    fi

    if [ $COUNT -lt 100 ]
    then
      INDEX="00${COUNT}"
    fi

    if [ $COUNT -lt 10 ]
    then
      INDEX="000${COUNT}"
    fi

    mysqldump --skip-add-drop-table -t -v -u root -pramoc-mysql ramoc t_Person --where "id>$LOWCOUNTER and id<$HIGHCOUNTER" >"${BACKUPDIR}Person/t_Person${INDEX}.sql"
done

#wenn das Verzeichnis Person nicht existiert wird es erstellt
if [ ! -d "${BACKUPDIR}Film" ]
then
  mkdir "${BACKUPDIR}Film"
fi
#lösche alle alten Einträge
cd "${BACKUPDIR}Film/"
rm -f *.sql

#Hol mir die letzte id
id=$(mysql ramoc -u ramocuser -pramoc -se "select id from t_Film order by id desc limit 0,1")

#Beim ersten dump wird mit DROP TABLE und CREATE TABLE geschrieben, bei den restlich nichtmehr
mysqldump -v -u root -pramoc-mysql ramoc t_Film --where "id<10" > "${BACKUPDIR}Film/t_Film0001.sql"
LOWCOUNTER=-1
HIGHCOUNTER=10
COUNT=0
while [ $HIGHCOUNTER -lt $id ]
do
    let LOWCOUNTER=LOWCOUNTER+10
    let HIGHCOUNTER=HIGHCOUNTER+10
    let COUNT=COUNT+1
    INDEX=$COUNT

    if [ $COUNT -lt 1000 ]
    then
      INDEX="0${COUNT}"
    fi

    if [ $COUNT -lt 100 ]
    then
      INDEX="00${COUNT}"
    fi

    if [ $COUNT -lt 10 ]
    then
      INDEX="000${COUNT}"
    fi

    mysqldump --skip-add-drop-table -t -v -u root -pramoc-mysql ramoc t_Film --where "id>$LOWCOUNTER and id<$HIGHCOUNTER" >"${BACKUPDIR}Film/t_Film${INDEX}.sql"
done
exit

if [ "$count" -gt "1" ] 
then
  mysqldump -v -u root -pramoc-mysql ramoc t_Person --where id='1' > "${BACKUPDIR}Person/t_Person1.sql"

  for i in `seq 2 $count`
  do
    mysqldump --skip-add-drop-table -t -v -u root -pramoc-mysql ramoc t_Person --where id=$i >"${BACKUPDIR}Person/t_Person${i}.sql"
  done    
fi
