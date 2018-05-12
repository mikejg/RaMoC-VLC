<?php
$artistName=$_REQUEST['artistName'];
error_log('getAlben.php');
exec('./wakeup.sh');

/*
  Mit dem MySQL-Server verbinden und Datenbank anwählen
*/
$link=mysql_connect("localhost","ramocuser","ramoc");
if (!$link)
{
    die('Verbindung schlug fehl: ' . mysql_error());
}
//else
//    error_log('Verbindung aufgebaut');

$db_selected = mysql_select_db('ramoc', $link);
if (!$db_selected)
{
    die ('Kann ramoc nicht benutzen : ' . mysql_error());
}
//else
//    error_log('Datenbank offen');


mysql_query("SET NAMES 'utf8'", $link);

$query="SELECT DISTINCT m_artist.name, m_album.name FROM m_title ";
$query.="INNER JOIN m_artist ON m_title.artist = m_artist.id ";
$query.="INNER JOIN m_album ON m_title.album = m_album.id ";
$query.="WHERE ";
$query.="m_artist.name = '" . $artistName;
$query.="'";

$q=mysql_query($query);

if(strcmp(mysql_error(),"" ))
{
  error_log('mysql error ' . mysql_error());
  error_log($query);
}

while($row=mysql_fetch_assoc($q))
{
   $array=$row;
   $output[]=$array;

   //$output[]=$row;
}

print(json_encode($output));

mysql_close();

?>
