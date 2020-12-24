

#ifndef UTILS_H
#define UTILS_H

#include "../../protocol/protocol.h"
#include "../srvcxnmanager.h"

char *getReponse(int response_player);
void console_log_protocol(InputProtocol input_protocol);
void infoServer(char* ip, char* port);
void sendMessage(InputProtocol outputProtocol, connection_t* connection);

#endif 
