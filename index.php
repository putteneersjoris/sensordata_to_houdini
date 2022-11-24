<?php
$servername = "localhost";
$username = "root";
$password = "Ikegcasen72.";
$dbname = "data";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
	die("Connection failed: " . $conn->connect_error);
}
// // get
// $sql = "SELECT sensorID, value, time FROM sensordata";
// $result = $conn->query($sql);
// 
// if ($result->num_rows > 0) {
	// // output data of each row
	// while($row = $result->fetch_assoc()) {
	   	// echo "<br> id: ". $row["sensorID"]. " - Name: ". $row["value"]. " " . $row["time"] . "<br>";
	    	// }
	// }
// else {
// echo "0 results";
// }

if ('PUT' === $_SERVER['REQUEST_METHOD']) {
 echo "this is a put request\n";
 
    parse_str(file_get_contents("php://input"),$post_vars);
    $test = json_decode(file_get_contents('php://input'), true);

	echo "\n\n\n\n";
	echo gettype($test)."\n";
	echo $test."\n";
	echo $test['sensorID']."\n";
	echo $test['value']."\n";
	echo $test['time']."\n";

	//command curl to put json object into mysql db
	// curl -X PUT http://hasdata.xyz/ -H 'Content-Type: application/json' -d '{"sensorID":19,"value":"my_password","time":"sonmjgb"}'


if (array_key_exists("sensorID",$test) && array_key_exists("value",$test) && array_key_exists("time",$test))
{  	    
	    $sql = "INSERT INTO sensordata VALUES ({$test['sensorID']},'{$test['value']}', '{$test['time']}')";
		if ($conn->query($sql) === TRUE) {
			echo "New record created successfully";
		}
		else {
			echo "Error: " . $sql . "<br>" . $conn->error;
		}
	}
}
			                  	          


if ('GET' === $_SERVER['REQUEST_METHOD']) {
	$queries = array();
	parse_str($_SERVER['QUERY_STRING'], $queries);
	$sql = "SELECT * FROM sensordata";

	// if(array_key_exists('last', $queries)){
		// $sql = $sql. " ORDER BY id DESC LIMIT 1";
	// }

	$res = $conn->query($sql);
	$rows = $res->fetch_all(MYSQLI_ASSOC);

	if(array_key_exists('last', $queries)){
		echo json_encode($rows[0]);
	}
	else{
		echo json_encode($rows);
	}
	$conn->close();
}

?>	
	
