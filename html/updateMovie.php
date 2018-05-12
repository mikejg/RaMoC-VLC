<?php
$beschreibung = $_POST['beschreibung'];
//$tmdb_ID =      $_POST['tmdb_ID'];
$genre1 =       $_POST['genre1'];
$genre2 =       $_POST['genre2'];
$genre3 =       $_POST['genre3'];
$genre4 =       $_POST['genre4'];
$trailer =      $_POST['trailer'];
$laufzeit =     $_POST['laufzeit'];
$note =         $_POST['note'];
$stimmen =      $_POST['stimmen'];
$serie =        $_POST['serie'];
$fsk =          $_POST['fsk'];
$cover =        $_POST['cover'];
$jahr =         $_POST['jahr'];
$backdrop =     $_POST['backdrop'];
$id_film=       $_POST['id'];
$id_file=       $_POST['id_file'];
$archive=       $_POST['archive'];
error_Log('updateMovie.php ID:' . $id_film);

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

$query= "UPDATE t_Film SET beschreibung = '" . $beschreibung . "', ";
$query.="genre1 = " . $genre1 . ", ";
$query.="genre2 = " . $genre2 . ", ";
$query.="genre3 = " . $genre3 . ", ";
$query.="genre4 = " . $genre4 . ", ";
$query.="trailer = '" . $trailer . "', ";
$query.="laufzeit = " . $laufzeit . ", ";
$query.="note = " . $note . ", ";
$query.="stimmen = " . $stimmen . ", ";
$query.="serie = " . $serie . ", ";
$query.="fsk = " . $fsk . ", ";
$query.="jahr = " . $jahr . ", ";
$query.="archives = " . $archive . ", ";
$query.="coverhash = '" . $cover . "', ";
$query.="backdrophash = '" . $backdrop . "' ";
$query.="WHERE id = " .$id_film;

if(!mysqli_query($link, $query))
{
  error_log($query);
  error_log(mysqli_error($link));
}
//mysqli_free_result($result);

$query= "INSERT INTO t_Datei_Film (id, film, datei) VALUES(";
$query.= $id_file . ", ";
$query.= $id_film . ", ";
$query.= $id_file . ")";

if(!mysqli_query($link, $query))
{
  error_log($query);
  error_log(mysqli_error($link));
}

mysqli_close($link);

?>
