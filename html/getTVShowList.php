<?php
exec('./wakeup.sh');
error_log('getTVShowList.php');

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

$query= "SELECT t_Film.id, serie, titel, fsk, laufzeit, coverhash, g1.genre1, g2.genre2, g3.genre3, g4.genre4 FROM t_Film ";
$query.="INNER JOIN t_Genre AS g1 ON t_Film.genre1 = g1.id ";
$query.="INNER JOIN t_Genre AS g2 ON t_Film.genre2 = g2.id ";
$query.="INNER JOIN t_Genre AS g3 ON t_Film.genre3 = g3.id ";
$query.="INNER JOIN t_Genre AS g4 ON t_Film.genre4 = g4.id ";
$query.="WHERE serie = 1 ";
$query.="AND archives = 0 ";
$query.="ORDER BY titel ";

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
