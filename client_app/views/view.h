
#ifndef VIEW_H
#define VIEW_H

#include "../../protocol/protocol.h"
#include <pthread.h>

void on_window_main_destroy();
void timer_handler();
void on_clicked_start_stop();
void on_button_trahir();
void on_button_cooperate();
void on_cancel();
void update_view_data(InputProtocol input_protocol);
void on_button_click();
void set_message(int label);
void set_amount();
void set_status(int status);
void set_round();
void init_view(int argc, char** argv, int sockfd, pthread_t thread);

#endif