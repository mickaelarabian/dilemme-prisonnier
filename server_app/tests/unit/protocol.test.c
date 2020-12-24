#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "protocol.test.h"
#include <stdio.h>

/**
 * @brief test_serialize
 * @return 
 **/ 
void test_serialize(){
    char some_protocol_char[] = "600;5;1;7;0.000000;0;0.000000";
    InputProtocol some_protocol_struct_1 = serialize(some_protocol_char);
    InputProtocol some_protocol_struct_2 = get_some_protocol_struct_1();
    assert(some_protocol_struct_1.game_id == some_protocol_struct_2.game_id);
    assert(some_protocol_struct_1.player_id == some_protocol_struct_2.player_id);
    assert(some_protocol_struct_1.action == some_protocol_struct_2.action);
    assert(some_protocol_struct_1.status == some_protocol_struct_2.status);
    assert(some_protocol_struct_1.round == some_protocol_struct_2.time);
    assert(some_protocol_struct_1.time == some_protocol_struct_2.round);
}
/**
 * @brief test_deserialize
 * @return 
 **/ 
void test_deserialize(){
    char* some_protocol_char = get_some_protocol_char_1();
    char* some_protocol_struct = deserialize(get_some_protocol_struct_1());
    assert(strcmp(some_protocol_struct, some_protocol_char) == 0);
}
/**
 * @brief test_init_client
 * @return 
 **/ 
void test_init_client(){
    InputProtocol some_protocol_struct = get_some_protocol_struct_1();
    InputProtocol init_client_val = init_client(some_protocol_struct, some_protocol_struct.player_id);
    assert(init_client_val.player_id == some_protocol_struct.player_id);
    assert(init_client_val.status == 5);
    assert(init_client_val.game_id == 0);
    assert(init_client_val.montant == 0);
    assert(init_client_val.time == 0);
    assert(init_client_val.round == 0);
    assert(init_client_val.action == 0);
}
/**
 * @brief test_relaod_protocol
 * @return 
 **/ 
void test_relaod_protocol(){
    InputProtocol some_protocol_struct = get_some_protocol_struct_1();
    InputProtocol init_client_val = relaod_protocol(some_protocol_struct);
    assert(init_client_val.player_id == 0);
    assert(init_client_val.status == 0);
    assert(init_client_val.game_id == 0);
    assert(init_client_val.montant == 0);
    assert(init_client_val.time == 0);
    assert(init_client_val.round == 0);
    assert(init_client_val.action == 0);
}
/**
 * @brief test_protocol
 * @return 
 **/ 
void test_protocol(){
    test_serialize();
    test_deserialize();
    test_init_client();
    test_relaod_protocol();
}