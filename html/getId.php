<?php
$table=$_REQUEST['table'];
$column=$_REQUEST['column'];
$value=$_REQUEST['value'];

error_log('getId.php' . $table . ' ' . $column . ' ' . $value);
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

//gibt es den Eintrag schon?
$query= "SELECT id FROM " . $table . " WHERE " . $column . " = '" . $value . "'";

$result=mysqli_query($link, $query);
$rows = mysqli_num_rows($result);
error_log("rows: " . $rows); 
if($rows)
{
  //Ja es gibt ihn schon und wird zurückgegeben
  while ($row = mysqli_fetch_assoc($result)) 
  {
    print("[{\"id\":\"" . $row['id'] . "\"}]");
    mysqli_close($link);
    die();
  }
}
mysqli_free_result($result);

//der Eintrag existiert noch nicht
//naechst freie ID ermitteln
$query= "SELECT id + 1 available_id FROM " . $table . " t ";
$query.="WHERE NOT EXISTS ( SELECT * FROM " . $table . " WHERE id = t.id + 1 ) order by id LIMIT 1";

$result=mysqli_query($link, $query);
$rows = mysqli_num_rows($result);
error_log("rows: " . $rows); 
if($rows)
{
  while ($row = mysqli_fetch_assoc($result)) 
  {
    $id = $row['available_id'];
  }
}
else
{
  $id = 1;
}
mysqli_free_result($result);

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
  if(!mysqli_query($link, $query))
  {
    error_log($query);
    error_log(mysqli_error($link));
  }
}

else
{
  $query= "INSERT INTO " . $table . " (id, " . $column . ") ";
  $query.="VALUES(" . $id  . ", '" . $value . "')";
  if(!mysqli_query($link, $query))
  {
    error_log($query);
    error_log(mysqli_error($link));
  }
}

print("[{\"id\":\"" . $id . "\"}]");


//
//if(strcmp(mysql_error(),"" ))
//{
//  error_log('mysql error ' . mysql_error());
//  error_log($query);
//}

mysqli_close($link);

?>
