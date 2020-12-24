#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "config.h"

/**
 * @brief Initialize the settings of configuration file
 * @param setting
 * @param file_name
 * @return boolean for check if the settings have been initialized
 **/
bool settings_initialize(Settings *setting, char *file_name){

    //Setup filename
    setting->filename = file_name;

    //Setup file pointer
    setting->settings_file = fopen(file_name, "r");

    //check if file exists
    if (setting->settings_file == NULL){
        printf("Le fichier %s n'existe pas", file_name);
        printf("\nEchec de connexion au serveur");
        return false;
    }

    //read line by line
    char* line = malloc(SETTINGS_LINE_SIZE);
    int i = 0;

    //for each lines
    while (fgets(line, SETTINGS_LINE_SIZE, setting->settings_file) != NULL)  {

        //Ignore lines too big
        if(i == SETTINGS_MAX_SETTINGS)
            break;

        // Returns first token
        char *value = strtok(line, "=");

        setting->settings_label[i] = malloc(sizeof(value));

        strncpy (setting->settings_label[i] , value, sizeof(setting->settings_value[i]) + 2);

        //Return second token
        value = strtok(NULL, "=");
        setting->settings_value[i] = malloc(sizeof(value));

        strncpy (setting->settings_value[i] , value, sizeof(setting->settings_value[i]) + 2);

        i++;
    }

    return true;
}

/**
 * @brief Get the different options in the config file
 * @param settings
 * @param option
 * @return option selected from the config file
 **/
char* settings_getOption(Settings* settings, char* option){
    for(int i = 0; i <= SETTINGS_MAX_SETTINGS; i++){

        if(settings->settings_label[i] != NULL && strcmp(settings->settings_label[i], option) == 0){
            return settings->settings_value[i];
        }
    }
    printf("\nError, option %s not found", option);
    return "ERROR";
}