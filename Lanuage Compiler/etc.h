#ifndef ETC_H
#define ETC_H

extern int input_flag;

extern int help_flag;

extern int output_flag;

extern int type_flag;

char *strremove(char *str, const char *sub);

void helpscrn();

void flag_allocations(char *inputs[]);

void no_args_scrn();

#endif