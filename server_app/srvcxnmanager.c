
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>


#include "src/gameArray.h"
#include "src/controller.h"
#include "srvcxnmanager.h"
#include "../protocol/protocol.h"
#include "../config/gameConfig/gameConfig.h"
#include "../config/config.h"

connection_t* connections[MAXSIMULTANEOUSCLIENTS];

/**
 * @brief Init socket array where are save the player 
 * @return
**/
void init_sockets_array() {
    for (int i = 0; i < MAXSIMULTANEOUSCLIENTS; i++) {
        connections[i] = NULL;
    }
    init_array_games();
}

/**
 * @brief Function called when it's the first connection to init a protocol
 * @param id
 * @return protocol send to player
 **/
char* firstConection(int id){
    InputProtocol inputClient;
    // init protocol to default value
    inputClient = init_client(inputClient, id);
    return deserialize(inputClient);
}

/**
 * @brief Function for adding thread connection to connections
 * @param connection
 * @return
 **/
void connection_add(connection_t *connection) {
    // Searching connection who is null to init it
    for (int i = 0; i < MAXSIMULTANEOUSCLIENTS; i++) {
        if (connections[i] == NULL) {
            connections[i] = connection;
            return;
        }
    }
    perror("Too much simultaneous connections");
    exit(-5);
}

/**
 * @brief Function to delete connection to connections
 * @param connection
 * @return 
 **/
void connection_del(connection_t *connection) {
    // Searching connection to del
    for (int i = 0; i < MAXSIMULTANEOUSCLIENTS; i++) {
        if (connections[i] == connection) {
            connections[i] = NULL;
            return;
        }
    }
    perror("Connection not in pool ");
    exit(-5);
}

/**
 * Thread allowing server to handle multiple client connections
 * @param ptr connection_t 
 * @return 
 */
void *threadProcess(void *ptr) {
    char inputClient[BUFFERSIZE];
    char outputServer[BUFFERSIZE];

    int len;
    connection_t *connection;

    if (!ptr) pthread_exit(0);
    connection = (connection_t *) ptr;

    connection_add(connection);

    //Welcome the new client
    InputProtocol conenctionProtocol;
    conenctionProtocol = init_client(conenctionProtocol, connection->index);
    printf("Welcome client new client id : %d \n", conenctionProtocol.player_id);
    controller_main(conenctionProtocol, connection);

    while ((len = read(connection->sockfd, inputClient, BUFFERSIZE)) > 0) {

        if (strncmp(inputClient, "bye", 3) == 0) {
            break;
        }

        InputProtocol inputProtocol = serialize(inputClient);
        controller_main(inputProtocol, connection);
      
    }
    printf("\nConnection to client %i ended \n", connection->index);
    close(connection->sockfd);
    connection_del(connection);
    free(connection);
    pthread_exit(0);

}

/**
 * @brief init socket when server started 
 * @param setting
 * @return
 **/
int create_server_socket(Settings setting) {

    
    int sockfd = -1;
    struct sockaddr_in address;
    int port =  atoi(settings_getOption(&setting, "port")); //atoi=conversion string en int voila

    /* create socket */
    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd <= 0) {
        fprintf(stderr, "%s: error: cannot create socket\n");
        return -3;
    }


    /* bind socket to port */
    address.sin_family = AF_INET;
    //bind to all ip : 
    //address.sin_addr.s_addr = INADDR_ANY;
    //ou 0.0.0.0 
    //Sinon  127.0.0.1
    address.sin_addr.s_addr = inet_addr(settings_getOption(&setting, "ip_address"));
    address.sin_port = htons(port);

    /* prevent the 60 secs timeout */
    int reuse = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char*) &reuse, sizeof (reuse));
    /* bind */
    if (bind(sockfd, (struct sockaddr *) &address, sizeof (struct sockaddr_in)) < 0) {
        fprintf(stderr, "error: cannot bind socket to port %d\n", port);
        return -4;
    }

    return sockfd;
}
