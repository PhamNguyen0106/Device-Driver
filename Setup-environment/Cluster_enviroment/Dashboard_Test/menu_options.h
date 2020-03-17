#ifndef MENU_OPTIONS_H
#define MENU_OPTIONS_H

#include <stdio.h>
#include <stdint.h>
#include "types_definitions.h"
#include "shared_memory.h"
void display_main_menu(void);
uint8_t display_boolean_sub_menu(void);
float display_float_sub_menu(void);
int display_int_sub_menu(void);
void change_option_value(char option);

#endif // MENU_OPTIONS_H
