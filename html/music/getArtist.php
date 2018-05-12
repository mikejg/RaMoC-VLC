<?php

exec('./wakeup.sh');
error_log('getArtist.php');

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
$query= "SELECT name FROM m_artist order by name";

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
}

print(json_encode($output));

mysql_close();

?>
