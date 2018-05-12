<?php
$id_movie     = $_POST['id_movie'];
$id_file     = $_POST['id_file'];

error_log('insertTVShow.php');
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
$query = "INSERT INTO t_Datei_Film (id, film, datei) VALUES(";
$query.= $id_file . ", ";
$query.= $id_movie . ", ";
$query.= $id_file . ")";

if(!mysqli_query($link, $query))
{
  error_log($query);
  error_log(mysqli_error($link));
}

mysqli_close($link);
?>
