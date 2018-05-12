<?php
error_log('getActor.php');
$id=$_REQUEST['filmId'];

/*
  Mit dem MySQL-Server verbinden und Datenbank anwählen
*/
$link=mysqli_connect("localhost","ramocuser","ramoc", "ramoc");
/* check connection */
if (mysqli_connect_errno())
{
    die('Verbindung schlug fehl: ' . mysqli_connect_error());
}

mysqli_set_charset($link, "utf8");

$query= "SELECT t_Person.id, t_Person.name, rolle, profilehash FROM t_Person_Film ";
$query.="INNER JOIN t_Person ON t_Person_Film.person = t_Person.id ";
$query.="WHERE t_Person_Film.film = " . $id;

$q=mysqli_query($link, $query);

if(strcmp(mysqli_error($link),"" ))
{
  error_log('mysql error ' . mysqli_error($link));
  error_log($query);
}

while($row=mysqli_fetch_assoc($q))
{
   $array=$row;
   $output[]=$array;
}

print(json_encode($output));

mysqli_close($link);

?>
