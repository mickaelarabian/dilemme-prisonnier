#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "srvcnmanager.test.h"
#include "../../srvcxnmanager.h"
#include "../../../config/gameConfig/gameConfig.h"
#include "../fixtures/fixtures.h"

connection_t* connections_test[MAXSIMULTANEOUSCLIENTS];
/**
 * @brief test_init_sockets_array
 * @return 
 **/ 
void test_init_sockets_array(){
    init_sockets_array();
    for (int i = 0; i < MAXSIMULTANEOUSCLIENTS; i++) {
       assert(connections_test[i] == NULL);
    }
}
/**
 * @brief test_first_connection
 * @return 
 **/ 
void test_first_connection(){
    int id = 600;
    char* some_protocol_char = get_some_protocol_first_connection();
    char* first_connection_char = firstConection(id);
    assert(strcmp(some_protocol_char, first_connection_char) == 0);
}
/**
 * @brief test_srvcnmanager
 * @return 
 **/ 
void test_srvcnmanager(){
    test_init_sockets_array();
    test_first_connection();
}