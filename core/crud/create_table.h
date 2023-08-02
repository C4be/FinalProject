//
// Created by lifefire1 on 16.07.23.
//

#ifndef FINALPROJECT_CREATE_TABLE_H
#define FINALPROJECT_CREATE_TABLE_H
#include "../table_struct/table_struct.h"
char *get_table_name(char *query);
Table *deserrializable_table(FILE *tb);
int create_table(char *query);
#endif  // FINALPROJECT_CREATE_TABLE_H
