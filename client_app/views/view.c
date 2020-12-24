#include <gtk/gtk.h>
#include <time.h>
#include <string.h>
#include "../controller/controller.h"
#include "../socket/socket.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include "../../config/gameConfig/gameConfig.h"

GtkBuilder *builder = NULL;
int elapsed_time = 0;
int timer_id = 0;
int sockfd;
InputProtocol cli_protocol;

/**
 * @brief Function to update the client status
 * @param status
 * @return 
 **/
void set_status(int status){
    cli_protocol.status = status;
}

/**
 * @brief Function to leave the game and disconnect
 * @param
 * @return 
 **/
void on_window_main_destroy() {
    printf("\nDisconnect..\n ");
    set_status(GAME_STATUS_DISCONNECT);
    player_action(0,sockfd,cli_protocol); 
    gtk_main_quit();
}

/**
 * @brief Function to update timer of client
 * @param
 * @return 1
 **/
int timer_handler() {
    elapsed_time++;
    char txt[100];
    GtkLabel *timelabel = GTK_LABEL(gtk_builder_get_object(builder, "time_display"));
    snprintf(txt, 100, "%04i", elapsed_time);
    gtk_label_set_text(timelabel, txt);
    return 1;
}

/**
 * @brief Function to update message labels on interface
 * @param label
 * @return 
 **/
void set_message(int label){
    char *message = malloc(100);
    GtkLabel *gtk_label;
    if(label == GAME_STATUS_MESSAGE){
        label = cli_protocol.status;
        gtk_label = GTK_LABEL(gtk_builder_get_object(builder, "status"));
    } else if(label == GAME_ACTION_MESSAGE) {
        label = cli_protocol.action;
        gtk_label = GTK_LABEL(gtk_builder_get_object(builder, "action"));
    }
    message = get_message(label, cli_protocol);
    gtk_label_set_text (gtk_label, message);
}

/**
 * @brief Function to update the client round on interface
 * @param
 * @return 
 **/
void set_round(){
    GtkLabel *label_round = GTK_LABEL(gtk_builder_get_object(builder, "round_display"));
    gchar *display;
    display = g_strdup_printf("%d", cli_protocol.round); 
    gtk_label_set_text (label_round, display);
}

/**
 * @brief Function to update the client amount on interface
 * @param
 * @return 
 **/
void set_amount(){
    char txt[100];
    GtkLabel *label_montant = GTK_LABEL(gtk_builder_get_object(builder, "montant_display"));
    snprintf(txt, 100,"%.1f", cli_protocol.montant);
    gtk_label_set_text (label_montant, txt);
}

/**
 * @brief Function to update the visual of the interface
 * @param
 * @return 
 **/
void refresh_view(){
    GtkButton *btn_coop = GTK_BUTTON(gtk_builder_get_object(builder, "coop"));
    GtkButton *btn_trahir = GTK_BUTTON(gtk_builder_get_object(builder, "trahir"));
    if(cli_protocol.status == GAME_STATUS_END){
        gtk_widget_hide(GTK_WIDGET(btn_coop));
        gtk_widget_hide(GTK_WIDGET(btn_trahir));
    } else if(cli_protocol.status == GAME_STATUS_START){
        timer_id = g_timeout_add(1000, (GSourceFunc) timer_handler, NULL);
    }

    set_round();
    set_amount();
    set_message(GAME_STATUS_MESSAGE);
    set_message(GAME_ACTION_MESSAGE);
}

/**
 * @brief Function to update data of the interface
 * @param input_protocol
 * @return 
 **/
void update_view_data(InputProtocol input_protocol){
    cli_protocol.game_id = input_protocol.game_id;
    cli_protocol.round = input_protocol.round;
    cli_protocol.player_id = input_protocol.player_id;
    cli_protocol.action = input_protocol.action;
    cli_protocol.status = input_protocol.status;
    cli_protocol.montant = input_protocol.montant;
    refresh_view();
}

/**
 * @brief Function for the selection of betray choice
 * @param
 * @return 
 **/
void on_button_betray() {
    if(cli_protocol.status == GAME_STATUS_START){
        printf("\nbutton betray\n"); 
        cli_protocol.time = elapsed_time; 
        g_source_remove(timer_id);
        elapsed_time = 0;
        set_status(GAME_STATUS_WAITING_RESULT_PLAYER);
        player_action(GAME_CHOICE_BETRAY,sockfd,cli_protocol);  
        set_message(GAME_STATUS_MESSAGE);
    }
}

/**
 * @brief Function for the selection of cooperate choice
 * @param
 * @return 
 **/
void on_button_cooperate() {
    if(cli_protocol.status == GAME_STATUS_START) {
        printf("\nbutton cooperate\n");
        cli_protocol.time = elapsed_time;
        g_source_remove(timer_id);
        elapsed_time = 0;
        set_status(GAME_STATUS_WAITING_RESULT_PLAYER);
        player_action(GAME_CHOICE_COLLABORATE,sockfd,cli_protocol); 
        set_message(GAME_STATUS_MESSAGE);
    }        
}

/**
 * @brief Function to leave the game and disconnect
 * @param
 * @return 
 **/
void on_cancel() {
    GtkWidget *message_dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK_CANCEL,
            "This action will cause the universe to stop existing.");
    unsigned int pressed = gtk_dialog_run(GTK_DIALOG(message_dialog));
    if (pressed == GTK_RESPONSE_OK) {
        printf("\nDisconnect.. \n");
        set_status(GAME_STATUS_DISCONNECT);
        player_action(0,sockfd,cli_protocol); 
        gtk_widget_destroy(message_dialog);
        gtk_main_quit();
    } else {
        gtk_widget_destroy(message_dialog);
    }
}

/**
 * @brief Function to initialize the client interface with reading thread
 * @param argc
 * @param argv
 * @param sockfdd
 * @param thread
 * @return 
 **/
void init_view(int argc, char** argv, int sockfdd, pthread_t thread){
    GtkWidget *win;
    sockfd = sockfdd;
    
    gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("glade/Interface.glade");
    win = GTK_WIDGET(gtk_builder_get_object(builder, "app_win"));
    g_object_set(gtk_settings_get_default(), "gtk-application-prefer-dark-theme", TRUE, NULL);
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(win);

    pthread_create(&thread, 0, thread_process, &sockfd);
    pthread_detach(thread);

    gtk_main();
}