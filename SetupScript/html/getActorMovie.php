<?php
$actorName=$_REQUEST['actorName'];
error_log('getActorMovie.php');
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

$query="select t_Person.name, t_Film.id, t_Film.titel, person, film FROM t_Person_Film ";
$query.="INNER JOIN t_Person ON t_Person_Film.person = t_Person.id ";
$query.="INNER JOIN t_Film ON t_Person_Film.film = t_Film.id ";
$query.="WHERE ";
$query.="t_Person.name = '" . $actorName;
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
