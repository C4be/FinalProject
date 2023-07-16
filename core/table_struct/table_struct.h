//
// Created by lifefire1 on 16.07.23.
//

#ifndef FINALPROJECT_TABLE_STRUCT_H
#define FINALPROJECT_TABLE_STRUCT_H
#include "field_struct.h"
#define MAX_FIELDS 10

typedef struct {
    char *table_name;
    TableField fields[MAX_FIELDS];
    int field_count;
} Table;

#endif  // FINALPROJECT_TABLE_STRUCT_H
