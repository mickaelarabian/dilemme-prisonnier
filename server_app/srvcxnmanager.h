/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File: srvcxnmanager.h
 *
 */
#include <sys/socket.h>
#ifndef SRVCXNMANAGER_H
#define SRVCXNMANAGER_H

// Structure of connection socket
typedef struct {
    int sockfd;
    struct sockaddr address;
    int addr_len;
    int index;
} connection_t;


void init_sockets_array();
char* firstConection(int id);
void connection_add(connection_t *connection);
void connection_del(connection_t *connection);
void *threadProcess(void *ptr);
int create_server_socket() ;

#endif /* SRVCXNMANAGER_H */

