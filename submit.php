<?php
# Copyright © 2013 Martin Ueding <dev@martin-ueding.de>

$datafile = 'devices.js';

$charge = (double) $_GET["charge"];
$token = $_GET["token"];

# Load data.
$devices = array();
if (file_exists($datafile)) {
	$devices = json_decode(file_get_contents($datafile), true);
}

for ($i = 0; $i < count($devices); $i++) {
	if ($devices[$i]['token'] == $token) {
		$devices[$i]['charge'] = $charge;
	}
	echo $devices[$i]['name'].': '.$devices[$i]['charge'].'<br />';
}

# Write data.
$encoded = json_encode($devices);
$h = fopen($datafile, 'w');
if ($h === false) {
	die();
}
fwrite($h, $encoded);
fclose($h);
?>
