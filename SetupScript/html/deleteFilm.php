<?php
$id=$_REQUEST['id_movie'];
error_log('deleteFilm.php');

/*
  Mit dem MySQL-Server verbinden und Datenbank anwählen
*/
$link=mysql_connect("localhost","ramocuser","ramoc");
if (!$link)
{
    die('Verbindung schlug fehl: ' . mysql_error());
}

$db_selected = mysql_select_db('ramoc', $link);
if (!$db_selected)
{
    die ('Kann ramoc nicht benutzen : ' . mysql_error());
}

//--- Dateien löschen---
mysql_query("SET NAMES 'utf8'", $link);
$query= "DELETE ab, b FROM t_Film AS a ";
$query.="INNER JOIN t_Datei_Film AS ab ON a.id=ab.film ";
$query.="INNER JOIN t_Datei AS b ON ab.datei=b.id ";
$query.="WHERE a.id = " . $id;

if(!mysql_query($query))
{
  error_log($query);
  error_log(mysql_error());
}

//--- Verknuepfung Film Actor loeschen ---
$query= "DELETE FROM t_Person_Film ";
$query.="WHERE t_Person_Film.film = " . $id;

if(!mysql_query($query))
{
  error_log($query);
  error_log(mysql_error());
}

//--- ActorBackdrop loeschen ---
$query= "DELETE FROM t_ActorBackdrop ";
$query.="WHERE t_ActorBackdrop.film = " . $id;

if(!mysql_query($query))
{
  error_log($query);
  error_log(mysql_error());
}

//--- Film loeschen ---
$query= "DELETE FROM t_Film ";
$query.="WHERE t_Film.id = " . $id;

if(!mysql_query($query))
{
  error_log($query);
  error_log(mysql_error());
}

mysql_close();

?>
