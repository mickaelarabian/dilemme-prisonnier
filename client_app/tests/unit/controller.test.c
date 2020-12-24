#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "controller.test.h"
#include "../fixtures/fixtures.h"

/**
 * @brief get_reponse_test
 * @return 
 **/ 
void get_message_test(){
    
    int gui_label = GAME_STATUS_WAITING_GAME;
    InputProtocol input_protocol = get_some_protocol_struct_1();
    char *result = malloc(50);
    result = get_message(gui_label, input_protocol);
    assert(strcmp(result, "En attente d'un autre joueur") == 0);
    result = "";

    gui_label = GAME_STATUS_WAITING_RESULT_PLAYER;
    input_protocol = get_some_protocol_struct_1();
    result = get_message(gui_label, input_protocol);
    assert(strcmp(result, "En attente du resultat") == 0);
    result = "";

    gui_label = GAME_STATUS_START;
    input_protocol = get_some_protocol_struct_1();
    result = get_message(gui_label, input_protocol);
    assert(strcmp(result, "A vous de jouer") == 0);
    result = "";

    gui_label = GAME_STATUS_END;
    input_protocol = get_some_protocol_struct_1();
    result = get_message(gui_label, input_protocol);
    assert(strcmp(result, "Partie terminée") == 0);
    result = "";

    gui_label = GAME_CHOICE_BOTH_COLLAB;
    input_protocol = get_some_protocol_struct_1();
    result = get_message(gui_label, input_protocol);
    assert(strcmp(result, "Vous avez tous les deux colaboré") == 0);
    result = "";

    gui_label = GAME_CHOICE_BOTH_BETRAY;
    input_protocol = get_some_protocol_struct_1();
    result = get_message(gui_label, input_protocol);
    assert(strcmp(result, "Vous avez tous les deux trahi") == 0);
    result = "";

    gui_label = GAME_CHOICE_PLAYER2_WIN;
    input_protocol = get_some_protocol_struct_2();
    result = get_message(gui_label, input_protocol);
    assert(strcmp(result, "Vous avez perdu la partie !") == 0);
    result = "";

    gui_label = GAME_CHOICE_PLAYER1_WIN;
    input_protocol = get_some_protocol_struct_2();
    result = get_message(gui_label, input_protocol);
    assert(strcmp(result, "Vous avez gagné la partie !") == 0);
    result = "";

    gui_label = GAME_CHOICE_EQUALITY;
    input_protocol = get_some_protocol_struct_2();
    result = get_message(gui_label, input_protocol);
    assert(strcmp(result, "Égalité !") == 0);
    result = "";

}

/**
 * @brief test_controller
 * @return 
 **/ 
void test_controller(){
    get_message_test();
}