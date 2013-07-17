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
		$devices[$i]['time'] = time();
	}
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
<!doctype html>
<html>
	<head>
		<meta charset="UTF-8" />
		<title>Battery Status</title>
		<style type="text/css">
td.number {
text-align: right;
}
td, th {
padding: 2px 15px;
}
</style>
	</head>
	<body>
<table>
<tr>
<th>Gerät</th>
<th>Ladestand</th>
<th>Aktualisierungszeitpunkt</th>
<th>Aktualisierung vor / Minuten</th>
</tr>
<?php for ($i = 0; $i < count($devices); $i++): ?>
<tr>
<td>
<?= $devices[$i]['name'] ?>
</td>
<td class="number">
<?= round($devices[$i]['charge']) ?>
</td>
<td>
<?= date("Y-m-d H:i:s", $devices[$i]['time']) ?>
</td>
<td class="number">
<?= round((time() - $devices[$i]['time'])/60) ?>
</td>
</tr>
<?php endfor; ?>
</table>
	</body>
</html>
