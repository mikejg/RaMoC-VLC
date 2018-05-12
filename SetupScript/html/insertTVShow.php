<?php
$id_movie     = $_POST['id_movie'];
$id_file     = $_POST['id_file'];

error_log('insertTVShow.php');
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

mysql_query("SET NAMES 'utf8'", $link);
$query = "INSERT INTO t_Datei_Film (id, film, datei) VALUES(";
$query.= $id_file . ", ";
$query.= $id_movie . ", ";
$query.= $id_file . ")";

if(!mysql_query($query))
{
  error_log($query);
  error_log(mysql_error());
}

?>
