
<?php
$albumID=$_REQUEST['albumID'];
error_log('getCover.php');
exec('../wakeup.sh');

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

$query="SELECT m_album.hasImage, m_album.image, m_album.id FROM m_album  ";
$query.="WHERE ";
$query.="m_album.id = " . $albumID;

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
