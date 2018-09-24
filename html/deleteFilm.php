<?php
$id=$_REQUEST['id_movie'];
error_log('deleteFilm.php');

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

$query= "DELETE ab, b FROM t_Film AS a ";
$query.="INNER JOIN t_Datei_Film AS ab ON a.id=ab.film ";
$query.="INNER JOIN t_Datei AS b ON ab.datei=b.id ";
$query.="WHERE a.id = " . $id;

if(!mysqli_query($link, $query))
{
  error_log($query);
  error_log(mysqli_error($link));
}


//--- Verknuepfung Film Actor loeschen ---
$query= "DELETE FROM t_Person_Film ";
$query.="WHERE t_Person_Film.film = " . $id;

if(!mysqli_query($link, $query))
{
  error_log($query);
  error_log(mysqli_error($link));
}
//--- Cover und Backdrop loeschen
$query = "SELECT id, coverhash, backdrophash FROM t_Film WHERE id = " . $id;
  error_log($query);
$result=mysqli_query($link, $query);

if(!mysqli_query($link, $query))
{
  error_log($query);
  error_log(mysqli_error($link));
}

while ($row = mysqli_fetch_array($result)) 
{
  error_log($row[1]);
  error_log($row[2]);

  $poster = "Pictures/Poster/" . $row[1];
  error_log($poster);

  unlink("Pictures/Poster/" . $row[1]);
  unlink("Pictures/Backdrop/" . $row[2]);
              
}


//--- Film loeschen ---
$query= "DELETE FROM t_Film ";
$query.="WHERE t_Film.id = " . $id;

if(!mysqli_query($link, $query))
{
  error_log($query);
  error_log(mysqli_error($link));
}

mysqli_close($link);

?>
