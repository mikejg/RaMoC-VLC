<?php
$id_movie     = $_POST['id_movie'];
$id_actor     = $_POST['id_actor'];
$portrait     = $_POST['portrait'];
$character        = $_POST['character'];

error_log('updateActor.php');
/*
  Mit dem MySQL-Server verbinden und Datenbank anwählen
*/
$link=mysql_connect("localhost","ramocuser","ramoc");
if (!$link)
{
    die('Verbindung schlug fehl: ' . mysql_error());
}

$db_selected = mysql_select_db('ramoc', $link);
if (!$db_selected)
{
    die ('Kann ramoc nicht benutzen : ' . mysql_error());
}


mysql_query("SET NAMES 'utf8'", $link);
//der Eintrag existiert noch nicht
//naechst freie ID ermitteln
$query= "SELECT id + 1 available_id FROM  t_Person_Film t ";
$query.="WHERE NOT EXISTS ( SELECT * FROM t_Person_Film ";
$query.=" WHERE id = t.id + 1 ) order by id LIMIT 1";

$result = mysql_query($query);
if(!$result)
{
  error_log($query);
  error_log(mysql_error());
  die;
}

$rows = mysql_num_rows($result);
if($rows)
{
  while ($row = mysql_fetch_assoc($result)) 
  {
    $id_actor_film = $row['available_id'];
  }
}
else
{
  $id_actor_film = 1;
}
mysql_free_result($result);

$query= "INSERT INTO t_Person_Film (id, film, person, rolle) VALUES(";
$query.=$id_actor_film . ", ";
$query.=$id_movie . ", ";
$query.=$id_actor . ", ";
$query.="'" . $character . "')";

if(!mysql_query($query))
{
  error_log($query);
  error_log(mysql_error());
}

$query= "UPDATE t_Person SET cover = '" . $portrait . "' ";
$query.="WHERE id = " . $id_actor;

if(!mysql_query($query))
{
  error_log($query);
  error_log(mysql_error());
}

mysql_close();

?>
