
<?php
$albumID=$_REQUEST['albumID'];
error_log('getCover.php');
exec('../wakeup.sh');

/*
  Mit dem MySQL-Server verbinden und Datenbank anwählen
*/
$link=mysql_connect("localhost","ramocuser","ramoc");
if (!$link)
{
    die('Verbindung schlug fehl: ' . mysql_error());
}
//else
//    error_log('Verbindung aufgebaut');

$db_selected = mysql_select_db('ramoc', $link);
if (!$db_selected)
{
    die ('Kann ramoc nicht benutzen : ' . mysql_error());
}
//else
//    error_log('Datenbank offen');


mysql_query("SET NAMES 'utf8'", $link);

$query="SELECT m_album.hasImage, m_album.image, m_album.id FROM m_album  ";
$query.="WHERE ";
$query.="m_album.id = " . $albumID;

$q=mysql_query($query);

if(strcmp(mysql_error(),"" ))
{
  error_log('mysql error ' . mysql_error());
  error_log($query);
}

while($row=mysql_fetch_assoc($q))
{
   $array=$row;
   $out[]=$array;
}

print(json_encode($out));
mysql_close();

?>
