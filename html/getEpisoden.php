<?php

exec('./wakeup.sh');

$id=$_REQUEST['filmId'];
error_log('getEpisoden.php');

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

$query= "SELECT film, t_Datei.dateiname, t_Datei.played from t_Datei_Film ";
$query.="INNER JOIN t_Datei on t_Datei_Film.datei = t_Datei.id ";
$query.="WHERE film = " . $id;
$query.=" ORDER BY t_Datei.dateiname";

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
