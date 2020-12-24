
#ifndef PROTOCOL_H
#define PROTOCOL_H

typedef struct {
    int game_id;
    int status;
    int player_id;
    int action;
    double time;
    int round;
    double montant;
} InputProtocol;

InputProtocol serialize(char *buffer_in);
InputProtocol init_client(InputProtocol input_protocol, int client_id);
char* deserialize(InputProtocol inputProtocol);
InputProtocol relaod_protocol(InputProtocol input_protocol);

#endif