#include <iostream>
#include <string>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
int main() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
 
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    //127.0.0.1 (localhost)
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
 
    char message[] = "Hello from client";
    sendto(sockfd, message, strlen(message), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    char buffer[1024];
    // waiting to answer message with max len 1024
    ssize_t n = recvfrom(sockfd, buffer, 1024, 0, NULL, NULL);
    buffer[n] = '\0';
    std::cout << "Server: " << buffer << std::endl;
    close(sockfd);
    return 0;
}