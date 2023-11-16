#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_MESSAGE_LEN 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <receiver_ip> <receiver_port>\n", argv[0]);
        exit(1);
    }

    int sockfd;
    struct sockaddr_in receiver_addr;
    char message[MAX_MESSAGE_LEN];

    // Create a UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(1);
    }

    // Initialize the receiver address structure
    memset(&receiver_addr, 0, sizeof(receiver_addr));
    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_port = htons(atoi(argv[2]));
    inet_aton(argv[1], &receiver_addr.sin_addr);

    while (1) {
        printf("Enter message: ");
        fgets(message, MAX_MESSAGE_LEN, stdin);

        // Send the message to the receiver
        sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&receiver_addr, sizeof(receiver_addr));

        // Check if the message is "exit"
        if (strncmp(message, "exit", 4) == 0) {
            printf("Exiting...\n");
            break;
        }
    }

    close(sockfd);
    return 0;
}
