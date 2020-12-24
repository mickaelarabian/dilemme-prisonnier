#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>

#include "socket.h"
#include "../../config/config.h"
#include "../../protocol/protocol.h"
#include "../views/view.h"
#include "../controller/controller.h"

Settings setting;

/**
 * Thread allowing client to handle data reception
 * @param ptr connection_t 
 * @return 
 */
void *thread_process(void * ptr) {
    char buffer_in[BUFFERSIZE];
    int sockfd = *((int *) ptr);
    int len;
  
    while ((len = read(sockfd, buffer_in, BUFFERSIZE)) != 0) {
        if (strncmp(buffer_in, "exit", 4) == 0) {
            break;
        }
        
        InputProtocol input_protocol = serialize(buffer_in);
        printf("\n ###RECEIVE###");
        console_log_protocol(input_protocol);
   
        update_view_data(input_protocol);
    }
    close(sockfd);
    printf("client pthread ended, len=%d\n", len);
}

/**
 * @brief Function for create a socket to comunicate with server
 * @param setting
 * @return sockfd
 **/
int open_connection(Settings setting) {
    settings_initialize(&setting, "../config/configClient.cfg");
    int sockfd;

    struct sockaddr_in serverAddr;

    int port = atoi(settings_getOption(&setting, "port"));

    // Create the socket. 
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    //Configure settings of the server address
    // Address family is Internet 
    serverAddr.sin_family = AF_INET;
    //Set port number, using htons function 
    serverAddr.sin_port = htons(port);
    //Set IP address to localhost
    serverAddr.sin_addr.s_addr = inet_addr(settings_getOption(&setting, "ip_address"));

    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    //Connect the socket to the server using the address
    if (connect(sockfd, (struct sockaddr *) &serverAddr, sizeof (serverAddr)) != 0) {
        printf("Fail to connect to server");
        exit(-1);
    };
    return sockfd;
}

/**
 * @brief Function for create thread socket & start interface
 * @param argc
 * @param argv
 * @return
 **/
void start_thread_socket(int argc, char** argv){
    int sockfd;
    int status = 0;
    char *msg = malloc(100);
    pthread_t thread;
    
    settings_initialize(&setting, "../config/configClient.cfg");
    sockfd = open_connection(setting);

    init_view(argc, argv,sockfd, thread);
}