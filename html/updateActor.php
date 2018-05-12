<?php
$id_movie     = $_POST['id_movie'];
$id_actor     = $_POST['id_actor'];
$portrait     = $_POST['portrait'];
$character        = $_POST['character'];

error_log('updateActor.php id_actor = ' . $id_actor);
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

//der Eintrag existiert noch nicht
//naechst freie ID ermitteln
$query= "SELECT id + 1 available_id FROM  t_Person_Film t ";
$query.="WHERE NOT EXISTS ( SELECT * FROM t_Person_Film ";
$query.=" WHERE id = t.id + 1 ) order by id LIMIT 1";

$result = mysqli_query($link, $query);
if(!$result)
{
  error_log($query);
  error_log(mysqli_error($link));
  die;
}

$rows = mysqli_num_rows($result);
if($rows)
{
  while ($row = mysqli_fetch_assoc($result)) 
  {
    $id_actor_film = $row['available_id'];
  }
}
else
{
  $id_actor_film = 1;
}
mysqli_free_result($result);

$query= "INSERT INTO t_Person_Film (id, film, person, rolle) VALUES(";
$query.=$id_actor_film . ", ";
$query.=$id_movie . ", ";
$query.=$id_actor . ", ";
$query.="'" . $character . "')";

if(!mysqli_query($link, $query))
{
  error_log($query);
  error_log(mysqli_error($link));
}

$query= "UPDATE t_Person SET profilehash = '" . $portrait . "' ";
$query.="WHERE id = " . $id_actor;

if(!mysqli_query($link, $query))
{
  error_log($query);
  error_log(mysqli_error($link));
}

mysqli_close($link);

?>
