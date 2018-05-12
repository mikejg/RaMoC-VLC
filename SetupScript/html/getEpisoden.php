<?php

exec('./wakeup.sh');

$id=$_REQUEST['filmId'];
error_log('getEpisoden.php');

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

$query= "SELECT film, t_Datei.dateiname, t_Datei.played from t_Datei_Film ";
$query.="INNER JOIN t_Datei on t_Datei_Film.datei = t_Datei.id ";
$query.="WHERE film = " . $id;
$query.=" ORDER BY t_Datei.dateiname";

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
