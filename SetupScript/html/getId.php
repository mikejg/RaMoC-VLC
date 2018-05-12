<?php
$table=$_REQUEST['table'];
$column=$_REQUEST['column'];
$value=$_REQUEST['value'];

error_log('getId.php' . $table . ' ' . $column . ' ' . $value);
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
//gibt es den Eintrag schon?
$query= "SELECT id FROM " . $table . " WHERE " . $column . " = '" . $value . "'";

$result=mysql_query($query);
$rows = mysql_num_rows($result);
if($rows)
{
  //Ja es gibt ihn schon und wird zurückgegeben
  while ($row = mysql_fetch_assoc($result)) 
  {
    print("[{\"id\":\"" . $row['id'] . "\"}]");
    mysql_close();
    die();
  }
}
mysql_free_result($result);

//der Eintrag existiert noch nicht
//naechst freie ID ermitteln
$query= "SELECT id + 1 available_id FROM " . $table . " t ";
$query.="WHERE NOT EXISTS ( SELECT * FROM " . $table . " WHERE id = t.id + 1 ) order by id LIMIT 1";

$result=mysql_query($query);
$rows = mysql_num_rows($result);
if($rows)
{
  while ($row = mysql_fetch_assoc($result)) 
  {
    $id = $row['available_id'];
  }
}
else
{
  $id = 1;
}
mysql_free_result($result);

//Eintrag erstelle, Genre ist ein Sonderfall
if($table == "t_Genre")
{
  $query= "INSERT INTO t_Genre (id, genre1, genre2, genre3, genre4) ";
  $query.="VALUES (" . $id;
  $query.=", '" . $value;
  $query.="', '" .$value;
  $query.="', '" .$value;
  $query.="', '" .$value;
  $query.="')";
  if(!mysql_query($query))
  {
    error_log($query);
    error_log(mysql_error());
  }
}

else
{
  $query= "INSERT INTO " . $table . " (id, " . $column . ") ";
  $query.="VALUES(" . $id  . ", '" . $value . "')";
  if(!mysql_query($query))
  {
    error_log($query);
    error_log(mysql_error());
  }
}


print("[{\"id\":\"" . $id . "\"}]");


//
//if(strcmp(mysql_error(),"" ))
//{
//  error_log('mysql error ' . mysql_error());
//  error_log($query);
//}

mysql_close();

?>
