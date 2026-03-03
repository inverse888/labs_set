#include <iostream>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
int main() {
    // sockfd - socket descriptor
    // AF_INET - ipv4 addresses
    // TYPE: SOCK_DGRAM - UDP (SOCK_STREAM - TCP)
    // 0 - default protocol for this sock TYPE
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
    sockaddr_in serverAddr; // struct for storing server address
    serverAddr.sin_family = AF_INET; // TYPE: ipv4 address
    // htons - host_to_network  (transform byte order)
    serverAddr.sin_port = htons(8080); // port greater than 1000, so user can use it
    serverAddr.sin_addr.s_addr = INADDR_ANY; // we can receive data(bytes) from any network interface
    // bind socket to address+port
    bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    sockaddr_in clientAddr;// struct for storing client address (client's port usuall is random )
    char buffer[1024];
    socklen_t addrLen = sizeof(clientAddr); // get size of allocaed memory
    // receive datagramm from client with max size 1024 byte
    // and save info about client IP+PORT to clientAddr
    // and return count of received bytes
    ssize_t n = recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&clientAddr, &addrLen);
    // add string terminator
    buffer[n] = '\0';
    char ip[INET_ADDRSTRLEN];
    //clientAddr.sin_addr is type of uint32_t. So if we want to see string address => 
    inet_ntop(AF_INET, &(clientAddr.sin_addr), ip, sizeof(ip));
    int port = ntohs(clientAddr.sin_port); // transform byte order: network => host
    std::cout << "Client " << ip << ":" << port << " -> " << buffer << std::endl;
    sendto(sockfd, buffer, n, 0, (struct sockaddr*)&clientAddr, sizeof(clientAddr));
    close(sockfd);
    return 0;
}