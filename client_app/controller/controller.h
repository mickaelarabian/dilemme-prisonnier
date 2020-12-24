#ifndef UTILS_H
#define UTILS_H


#define BUFFERSIZE 2048


#include "../../protocol/protocol.h"

void player_action(int choice, int sockfd, InputProtocol cli_message);
void send_message(char *message, int sockfd);
char *get_message(int label, InputProtocol cli_protocol);
void info_client();
void console_log_protocol(InputProtocol input_protocol);

#endif /* CLIENTCXNMANAGER_H */

