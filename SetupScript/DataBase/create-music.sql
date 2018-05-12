use ramoc
DROP TABLE IF EXISTS m_title, m_album, m_artist, m_genre, m_year;

CREATE TABLE m_artist (id INTEGER, 
                      name VARCHAR(128), 
                      image MEDIUMBLOB, 
                      hasImage TINYINT, 
                      PRIMARY KEY (id));

CREATE TABLE m_album (id INTEGER NOT NULL, name VARCHAR(128), 
                      artist INTEGER, FOREIGN KEY (artist) REFERENCES m_artist (id), 
                      imagePath VARCHAR(255), 
                      image MEDIUMBLOB, 
                      hasImage TINYINT, 
                      sampler TINYINT default 0, 
                      PRIMARY KEY (id));

CREATE TABLE m_genre (id INTEGER NOT NULL, 
                      name VARCHAR(128), 
                      PRIMARY KEY (id));

CREATE TABLE m_year (id INTEGER NOT NULL, 
                      name VARCHAR(20), 
                      PRIMARY KEY (id));

CREATE TABLE m_title (id INTEGER NOT NULL, 
                      title VARCHAR(128), 
                      artist INTEGER, 
                      album INTEGER, 
                      genre INTEGER, 
                      year INTEGER, 
                      tracknr INTEGER, 
                      playcounter INTEGER, 
                      erfasst INTEGER, 
                      gespielt INTEGER, 
                      wertung INTEGER, 
                      pfad VARCHAR(255),
                      PRIMARY KEY (id), 
                      FOREIGN KEY (artist) REFERENCES m_artist (id),
                      FOREIGN KEY (album) REFERENCES m_album (id),
                      FOREIGN KEY (genre) REFERENCES m_genre (id),
                      FOREIGN KEY (year) REFERENCES m_year (id));
