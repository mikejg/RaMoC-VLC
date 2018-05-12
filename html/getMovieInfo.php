<?php
$id=$_REQUEST['filmId'];
error_log('getMovieInfo.php');
exec('./wakeup.sh');

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

$query= "SELECT t_Film.beschreibung, t_Film.fsk, t_Film.laufzeit, t_Film.trailer, t_Film.backdrophash FROM t_Film ";
$query.="WHERE t_Film.id = " . $id;

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
