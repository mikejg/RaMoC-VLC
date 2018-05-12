# mysql -u ramocuser -pramo < delete-database.sql

use ramoc;

delete from t_Datei_Film;
delete from t_Person_Film;
delete from t_Datei;
delete from t_Film;
delete from t_Genre;
delete from t_Person;
delete from m_title;
delete from m_album;
delete from m_artist;
delete from m_genre;
delete from m_year;
