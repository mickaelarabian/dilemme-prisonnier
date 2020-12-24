/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: aurelio
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include "socket/socket.h"
#include "controller/controller.h"

/**
 * @brief Main function of client
 * @return
**/
void main(int argc, char** argv) {
    info_client();
    start_thread_socket(argc, argv);
}

