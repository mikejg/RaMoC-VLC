# mysql -u ramocuser -pramo < delete-database.sql

use ramoc;

delete from t_Datei_Film where film = 247;
delete from t_Person_Film where film = 247;
#delete from t_Datei;
delete from t_Film where id = 247;
#delete from t_Genre;
#delete from t_Person;

