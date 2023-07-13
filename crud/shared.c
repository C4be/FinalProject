#include "shared.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../struct/modules.h"
//////////////////////////////////////////////////////
#include "../size_file/size.h"

int select_modules_by(FILE *db, const char *field, int value) {
    int struct_count = get_records_count_in_file(db);
    modules *modules1 = (modules *)malloc(sizeof(modules));
    printf("--------------------------------------------------------------------------------------------------------------------------\n");
    printf("|                                                  MODULES_TABLE                                                        |\n");
    printf("--------------------------------------------------------------------------------------------------------------------------\n");
    printf("|\tid\t|\tmodule_name\t|\tlevel_memory_number\t|\tceil_number\t|\tflag_delete\t|\n");
    printf("--------------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < struct_count; ++i) {
        fread(modules1, 1, sizeof(modules), db);
        if (strcmp(field, "id") == 0 && modules1->id == value) {
            printf("|%14d | %22s | %29d | %21d | %22d|\n",
                   modules1->id,
                   modules1->module_name,
                   modules1->level_memory_number,
                   modules1->ceil_number,
                   modules1->flag_delete
            );
        } else if (strcmp(field, "level_memory_number") == 0 && modules1->level_memory_number == value) {
            printf("|%14d | %22s | %29d | %21d | %22d|\n",
                   modules1->id,
                   modules1->module_name,
                   modules1->level_memory_number,
                   modules1->ceil_number,
                   modules1->flag_delete
            );
        } else if (strcmp(field, "ceil_number") == 0 && modules1->ceil_number == value) {
            printf("|%14d | %22s | %29d | %21d | %22d|\n",
                   modules1->id,
                   modules1->module_name,
                   modules1->level_memory_number,
                   modules1->ceil_number,
                   modules1->flag_delete
            );
        } else if (strcmp(field, "flag_delete") == 0 && modules1->flag_delete == value) {
            printf("|%14d | %22s | %29d | %21d | %22d|\n",
                   modules1->id,
                   modules1->module_name,
                   modules1->level_memory_number,
                   modules1->ceil_number,
                   modules1->flag_delete
            );
        }
        printf("--------------------------------------------------------------------------------------------------------------------------\n");
    }

    free(modules1);
    return 0;
}

int select_modules_by_module_name(FILE *db, char *value){
    int struct_count = get_records_count_in_file(db);
    modules *modules1 = (modules *)malloc(sizeof(modules));
    printf("--------------------------------------------------------------------------------------------------------------------------\n");
    printf("|                                                  MODULES_TABLE                                                        |\n");
    printf("--------------------------------------------------------------------------------------------------------------------------\n");
    printf("|\tid\t|\tmodule_name\t|\tlevel_memory_number\t|\tceil_number\t|\tflag_delete\t|\n");
    printf("--------------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < struct_count; ++i) {
        fread(modules1, 1, sizeof(modules), db);
        if (strcmp(modules1->module_name,value) == 0) {
            printf("|%14d | %22s | %29d | %21d | %22d|\n",
                   modules1->id,
                   modules1->module_name,
                   modules1->level_memory_number,
                   modules1->ceil_number,
                   modules1->flag_delete
            );
        }
        else{
            printf("|               |                       |                               |                       |                       |\n");
        }
        printf("--------------------------------------------------------------------------------------------------------------------------\n");
    }
    return 0;
}

