#ifndef MENU_OPTIONS_C
#define MENU_OPTIONS_C

#include "menu_options.h"

void display_main_menu(void)
{
    printf("--------------------------------------------------------\n");
    printf("\t    Can Data Emulation -HMI Test Client \n\n");
    printf("-------------------------Main Menu----------------------\n");
    printf("\t q) HIGH BEAM \n");
    printf("\t w) LOW BEAM \n");
    printf("\t e) OPTICAL HORN \n");
    printf("\t r) TURN RIGHT \n");
    printf("\t t) TURN LEFT \n");
    printf("\t y) HAZARD WARINING LIGHT \n");
    printf("\t u) ABS BREAK \n");
    printf("\t i) AIRBAG\n");
    printf("\t o) KEY STATUS \n");
    printf("\t p) LOW BATTERY \n");
    printf("\t a) LOW FUEL \n");
    printf("\t s) CHECK ENGINE \n");
    printf("\t d) SEATBELT \n");
    printf("\t f) HANDBRAKE \n");
    printf("\t g) SATTELITAL NOTIFICATION \n");
    printf("\t h)OIL \n");
    printf("\t j) DOOR WANING LIGHT \n");
    printf("\t k) MOTOR TEMPERATURE WARNING \n");
    printf("\t l) BATTERY \n");
    printf("\t z) ENV TEMP \n");
    printf("\t x) SPEED \n");
    printf("\t c) FUEL \n");
    printf("\t v) EFFICIENCY \n");
    printf("\t b) RPMs \n");
    printf("\t n) TIREPRESURE_1 \n");
    printf("\t m) LOW PRESURE 1 Warning \n");
    printf("\t 1) TIREPRESURE_2 \n");
    printf("\t 2) LOW PRESURE 2 Warning \n");
    printf("\t 3) TIREPRESURE_3 \n");
    printf("\t 4) LOW PRESURE 3 Warning \n");
    printf("\t5) TIREPRESURE_4 \n");
    printf("\t 6) LOW PRESURE 4 Warning \n");
    printf("\t 7) ODOMETER\n");
    printf("\t 8) GEAR \n");
    printf("\t 9) COMPAS \n");
    printf("--------------------------------------------------\n");
    printf("\t Q) Exit \n");
    printf("--------------------------------------------------\n");
    printf("\t Select option to change:");
}

uint8_t display_boolean_sub_menu(void)
{
    uint8_t new_value;
    char option;
    printf("--------------------------------------------------\n");
    printf("\t    Boolean Options \n\n");
    printf("-------------------------Sub-Menu-----------------\n");
    printf("\t 0) OFF \n");printf("\t 1) ON \n");
    printf("--------------------------------------------------\n");
    printf("\t Select value:");
    getchar();
    scanf("%c",&option);
    if(option =='0'){
        new_value =OFF;
    }else{
        new_value =ON;
    }
    return new_value;
}

float display_float_sub_menu(void)
{
    float new_value;
    printf("--------------------------------------------------\n");
    printf("\t      Float Options \n\n");
    printf("----------------------Sub-Menu--------------------\n");
    printf("\t Before enter the new value, please check \n");
    printf("\t range values for each option. \n");
    printf("--------------------------------------------------\n");
    printf("\tEnter new value:");
    getchar();
    scanf("%f",&new_value);
    return new_value;
}

int display_int_sub_menu(void)
{
    int new_value;
    printf("--------------------------------------------------\n");
    printf("\t      Integer Options \n\n");
    printf("----------------------Sub-Menu--------------------\n");
    printf("\t Before enter the new value, please check \n");
    printf("\t range values for each option. \n");
    printf("--------------------------------------------------\n");
    printf("\t Enter new value:");
    getchar();
    scanf("%i",&new_value);
    return new_value;
}

void change_option_value(char option)
{
    uint8_t boolean_value;
    float float_value;
    int int_value;
    switch(option)
    {
        case'q':
            boolean_value =display_boolean_sub_menu();
            getchar();
            write_uint8_value(option,boolean_value);
            break;
        case'w':
            boolean_value =display_boolean_sub_menu();
            getchar();
            write_uint8_value(option,boolean_value);
            break;
        case'e':
            boolean_value =display_boolean_sub_menu();
            getchar();
            write_uint8_value(option,boolean_value);
            break;
        case'r':
            boolean_value =display_boolean_sub_menu();
            getchar();
            write_uint8_value(option,boolean_value);
            break;
        case't':
            boolean_value =display_boolean_sub_menu();
            getchar();
            write_uint8_value(option,boolean_value);
            break;
        case'y':
            boolean_value =display_boolean_sub_menu();
            getchar();
            write_uint8_value(option,boolean_value);
            break;
        case'u':
            boolean_value =display_boolean_sub_menu();
            getchar();
            write_uint8_value(option,boolean_value);
            break;
        case'i':
            boolean_value =display_boolean_sub_menu();
            getchar();
            write_uint8_value(option,boolean_value);
            break;
        case'o':
            boolean_value =display_boolean_sub_menu();
            getchar();
            write_uint8_value(option,boolean_value);
            break;
        case'p':
            boolean_value =display_boolean_sub_menu();
            getchar();
            write_uint8_value(option,boolean_value);
            break;
        case'a':
            boolean_value =display_boolean_sub_menu();
            getchar();
            write_uint8_value(option,boolean_value);
            break;
        case's':
            boolean_value =display_boolean_sub_menu();
            getchar();
            write_uint8_value(option,boolean_value);
            break;
        case'd':
            boolean_value =display_boolean_sub_menu();
            getchar();
            write_uint8_value(option,boolean_value);
            break;
        case'f':
            boolean_value =display_boolean_sub_menu();
            getchar();write_uint8_value(option,boolean_value);
            break;
        case'g':
            boolean_value =display_boolean_sub_menu();
            getchar();
            write_uint8_value(option,boolean_value);
            break;
        case'h':
            boolean_value =display_boolean_sub_menu();
            getchar();
            write_uint8_value(option,boolean_value);
            break;
        case'j':
            boolean_value =display_boolean_sub_menu();
            getchar();
            write_uint8_value(option,boolean_value);
            break;
        case'k':
            boolean_value =display_boolean_sub_menu();
            getchar();
            write_uint8_value(option,boolean_value);
            break;
        case'l':
            float_value =display_float_sub_menu();
            getchar();
            write_float_value(option,float_value);
            break;
        case'z':
            float_value =display_float_sub_menu();
            getchar();
            write_float_value(option,float_value);
            break;
        case'x':
            float_value =display_float_sub_menu();
            getchar();
            write_float_value(option,float_value);
            break;
        case'c':
            float_value =display_float_sub_menu();
            getchar();
            write_float_value(option,float_value);
            break;
        case'v':
            float_value =display_float_sub_menu();
            getchar();
            write_float_value(option,float_value);
            break;
        case'b':
            int_value =display_int_sub_menu();
            getchar();
            write_int_value(option,int_value);
            break;
        case'n':
            int_value =display_int_sub_menu();
            getchar();
            write_int_value(option,int_value);
            break;
        case'm':
            boolean_value =display_boolean_sub_menu();
            getchar();
            write_uint8_value(option,boolean_value);
            break;
        case'1':
            int_value =display_int_sub_menu();
            getchar();
            write_int_value(option,int_value);
            break;
        case'2':
            boolean_value =display_boolean_sub_menu();
            getchar();
            write_uint8_value(option,boolean_value);
            break;
        case'3':
            int_value =display_int_sub_menu();
            getchar();
            write_int_value(option,int_value);
            break;
        case'4':
            boolean_value =display_boolean_sub_menu();
            getchar();
            write_uint8_value(option,boolean_value);
            break;
        case'5':
            int_value =display_int_sub_menu();
            getchar();
            write_int_value(option,int_value);
            break;
        case'6':
            boolean_value =display_boolean_sub_menu();
            getchar();
            write_uint8_value(option,boolean_value);
            break;
        case'7':
            int_value =display_int_sub_menu();
            getchar();
            write_int_value(option,int_value);
            break;
        case'8':
            int_value =display_int_sub_menu();
            getchar();
            write_int_value(option,int_value);
            break;
        case'9':
            int_value =display_int_sub_menu();
            getchar();
            write_int_value(option,int_value);
            break;
        default:
            break;
    }
}

#endif // MENU_OPTIONS_C
