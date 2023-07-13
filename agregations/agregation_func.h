//
// Created by lifefire1 on 13.07.23.
//

#ifndef FINALPROJECT_AGREGATION_FUNC_H
#define FINALPROJECT_AGREGATION_FUNC_H
#include <stdio.h>
#include <stdlib.h>

int agr_count_modules(FILE *db,char *field, int value);
int agr_count_modules_module_name(FILE *db,char *field, char *value);
int agr_sum_modules(FILE *db,char *field, int value);
int agr_sum_modules_name(FILE *db,char *field, int value);

#endif  // FINALPROJECT_AGREGATION_FUNC_H
