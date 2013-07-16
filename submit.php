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
td.charge {
text-align: right;
}
</style>
	</head>
	<body>
<table>
<tr>
<th>Gerät</th>
<th>Ladestand</th>
</tr>
<?php for ($i = 0; $i < count($devices); $i++): ?>
<tr>
<td>
<?= $devices[$i]['name'] ?>
</td>
<td class="charge">
<?= round($devices[$i]['charge']) ?>
</td>
</tr>
<?php endfor; ?>
</table>
	</body>
</html>
