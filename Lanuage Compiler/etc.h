#ifndef ETC_H
#define ETC_H

char *strremove(char *str, const char *sub);

void helpscrn();

int unknown_argument_error();

void remove_spaces(char *str);

void space_to_newline(char *str);

int is_blank(const char *line);

void rand_usleep(int min, int max);

#endif