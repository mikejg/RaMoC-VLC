<?php

$order=$_REQUEST['order'];
exec('./wakeup.sh');
error_log('getArchive.php');

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
$query= "SELECT t_Film.id, serie, titel, fsk, laufzeit, g1.genre1, g2.genre2, g3.genre3, g4.genre4 FROM t_Film ";
$query.="INNER JOIN t_Genre AS g1 ON t_Film.genre1 = g1.id ";
$query.="INNER JOIN t_Genre AS g2 ON t_Film.genre2 = g2.id ";
$query.="INNER JOIN t_Genre AS g3 ON t_Film.genre3 = g3.id ";
$query.="INNER JOIN t_Genre AS g4 ON t_Film.genre4 = g4.id ";
$query.="WHERE serie = 0 ";
$query.="AND archives = 1 ";
if (strcmp($order, "6") == 0) 
{
  $query.="AND fsk = 6 ";
  $query.="OR fsk = 0 ";
}
$query.="ORDER BY titel";

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
