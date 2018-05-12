<?php
$titel=$_REQUEST['titel'];

error_log('tvShowExist.php');
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
$query= "SELECT t_Film.id, titel FROM t_Film ";
$query.=" WHERE ";
$query.="titel = '" . $titel . "'";

$result=mysql_query($query);
$rows = mysql_num_rows($result);
error_log($query);
error_log(mysql_error());
if($rows)
{
  //Ja es gibt ihn schon und wird zurückgegeben
    print("[{\"exist\":\"true\"}]");
}
else
{
  //Ja es gibt ihn schon und wird zurückgegeben
    print("[{\"exist\":\"false\"}]");
}

mysql_close();

?>
