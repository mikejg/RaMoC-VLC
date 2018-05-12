use ramoc;

CREATE TABLE t_Person (id INTEGER NOT NULL, 
                       tmdb_ID VARCHAR(255), 
                       name VARCHAR(255), 
                       profilehash VARCHAR(255), 
                       PRIMARY KEY (id));
CREATE TABLE t_Regie (id INTEGER NOT NULL, regie  VARCHAR(255), PRIMARY KEY (id));
CREATE TABLE t_Genre (id INTEGER NOT NULL, genre1 VARCHAR(255),genre2 VARCHAR(255),genre3 VARCHAR(255),genre4 VARCHAR(255), PRIMARY KEY (id));
CREATE TABLE t_Datei (id INTEGER NOT NULL, 
             dateiname  VARCHAR(255), 
             PRIMARY KEY (id), 
             played TINYINT DEFAULT 0);

CREATE TABLE t_Film(id INTEGER NOT NULL, 
             tmdb_ID VARCHAR(255), 
             titel VARCHAR(255), 
             trailer VARCHAR(255), 
             beschreibung VARCHAR(4048), 
             regie INTEGER, 
             fsk INTEGER, 
             jahr INTEGER, 
             genre1 INTEGER, 
             genre2 INTEGER, 
             genre3 INTEGER, 
             genre4 INTEGER, 
             coverhash VARCHAR(255),
             backdrophash VARCHAR(255),
             laufzeit INTEGER, 
             note INTEGER, 
             stimmen INTEGER, 
             serie TINYINT default 0, 
             archives TINYINT default 0, 
             played INTEGER default 0,
             FOREIGN KEY (regie) REFERENCES t_Regie (id), 
             FOREIGN KEY (genre1) REFERENCES t_Genre (id), 
             FOREIGN KEY (genre2) REFERENCES t_Genre (id), 
             FOREIGN KEY (genre3) REFERENCES t_Genre (id), 
             FOREIGN KEY (genre4) REFERENCES t_Genre (id), 
             PRIMARY KEY (id));

CREATE TABLE t_Datei_Film(id INTEGER NOT NULL, 
             film INTEGER, 
             datei INTEGER, 
             FOREIGN KEY (film) REFERENCES t_Film (id), 
             FOREIGN KEY (datei) REFERENCES t_Datei (id), 
             PRIMARY KEY (id));

CREATE TABLE t_Person_Film(id INTEGER NOT NULL, film INTEGER, person INTEGER, rolle VARCHAR(255), FOREIGN KEY (film) REFERENCES t_Film (id), FOREIGN KEY (person) REFERENCES t_Person (id), PRIMARY KEY (id));

