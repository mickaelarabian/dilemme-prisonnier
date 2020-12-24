#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define SETTINGS_LINE_SIZE 300
#define SETTINGS_MAX_SETTINGS 10

typedef struct {
    FILE* settings_file;
    char *filename;

    char* settings_label[SETTINGS_MAX_SETTINGS];
    char* settings_value[SETTINGS_MAX_SETTINGS];
} Settings;

bool settings_initialize(Settings *setting, char *filename);
char* settings_getOption(Settings* settings, char* option);