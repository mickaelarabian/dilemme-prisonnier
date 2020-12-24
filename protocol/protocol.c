#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "protocol.h"

/**
 * @brief serialize data for creation of the protocol 
 * @param buffer_in
 * @return InputProtocol protocol to send 
 **/ 
InputProtocol serialize(char *buffer_in){
    InputProtocol input_protocol;
      int input[10];

    char *val = strtok(buffer_in, ";");
    input[0] = atoi(val);
    for(int i = 1; i<= 5; i++){
        val = strtok(NULL, ";");
        if(val == NULL) 
            break;
        input[i] = atoi(val);
    }
    val = strtok(NULL, ";");
    input_protocol.montant = atof(val);
    input_protocol.game_id = input[0];
    input_protocol.status = input[1];
    input_protocol.player_id = input[2];
    input_protocol.action = input[3];
    input_protocol.time = input[4];
    input_protocol.round = input[5];
    return input_protocol;
}
/**
 * @brief deserialize data for read the protocol  
 * @param input_protocol
 * @return char* data of the protocol 
 **/ 
char* deserialize(InputProtocol input_protocol){
    char* output_protocol = malloc(250);
    sprintf(output_protocol, "%d;%d;%d;%d;%f;%d;%f", 
    input_protocol.game_id,  input_protocol.status, input_protocol.player_id,
    input_protocol.action, input_protocol.time ,input_protocol.round, input_protocol.montant);
    return output_protocol;
}
/**
 * @brief init_client protocol client 
 * @param input_protocol
 * @param client_id
 * @return return init client protocol 
 **/ 
InputProtocol init_client(InputProtocol input_protocol, int client_id){
    input_protocol.game_id = 0;
    input_protocol.status = 5;
    input_protocol.player_id = client_id;
    input_protocol.action = 0;
    input_protocol.round = 0;
    input_protocol.montant = 0;
    return input_protocol;
}
/**
 * @brief relaod_protocol protocol 
 * @param input_protocol
 * @return return reloaded protocol 
 **/ 
InputProtocol relaod_protocol(InputProtocol input_protocol){
    input_protocol.game_id = 0;
    input_protocol.status = 0;
    input_protocol.player_id = 0;
    input_protocol.action = 0;
    input_protocol.round = 0;
    input_protocol.montant = 0;
    return input_protocol;
}

