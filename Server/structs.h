
#ifndef STRUCTS_H
#define STRUCTS_H
struct Person
{
  QString name;
  QString character;
  QString profile_Path;
  QString tmdb_ID;
  QString profile_Hash;
};

struct Movie
{
  QString ramoc_ID;
  QString title;
  QString file_Path;
  QString tmdb_ID;
  QString year;
  QString poster_Path;
  QString backdrop_Path;
  QString overview;
  QString vote_Average;
  QString vote_Count;
  QString poster_Hash;
  QString backdrop_Hash;
  QString trailer;
  QString runtime;
  QString serie;
  QString fsk;
  QString archive;

  QStringList strList_Genres;
  QList<Person> list_Person;
};

struct Track
{
  QString ramoc_ID;
  QString album_ID;
  QString artist_ID;
  QString title;
  QString album;
  QString artist;
  QString path;
  QString playlistPos;
  QString favorite;
  QString sampler;
};

struct MetaPaket
{
  int id;
  QString title;
  QString artist;
  QString album;
  QString genre;
  QString year;
  uint tracknr;
  int playcounter;
  uint erfasst;
  uint gespielt;
  int wertung;
  QString pfad;
  QString coverPfad;
  QString coverData;
  QString sampler;
};

#endif
