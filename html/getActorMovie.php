<?php
$actorName=$_REQUEST['actorName'];
error_log('getActorMovie.php');
exec('./wakeup.sh');

mysql_query("SET NAMES 'utf8'", $link);

$link=mysqli_connect("localhost","ramocuser","ramoc", "ramoc");
/* check connection */
if (mysqli_connect_errno())
{
    die('Verbindung schlug fehl: ' . mysqli_connect_error());
}

mysqli_set_charset($link, "utf8");

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
