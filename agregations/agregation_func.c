//
// Created by lifefire1 on 13.07.23.
//

#include "agregation_func.h"

#include "../size_file/size.h"

int agr_count_modules(FILE *db,char *field, int value){
    int count = 0;
    int struct_count = get_records_count_in_file(db);
    modules *modules1 = (modules *)malloc(sizeof(modules));
    for (int i = 0; i < struct_count; ++i) {
        fread(modules1, 1, sizeof(modules), db);
        if (strcmp(field, "id") == 0 && modules1->id == value) {
            count++;
        } else if (strcmp(field, "level_memory_number") == 0 && modules1->level_memory_number == value) {
            count++;
        } else if (strcmp(field, "ceil_number") == 0 && modules1->ceil_number == value) {
            count++;
        } else if (strcmp(field, "flag_delete") == 0 && modules1->flag_delete == value) {
            count++;
        }
    }

    printf("%d\n", count);

    free(modules1);
    return 0;
}

int agr_count_modules_module_name(FILE *db,char *field, char *value){
    int count = 0;
    int struct_count = get_records_count_in_file(db);
    modules *modules1 = (modules *)malloc(sizeof(modules));
    for (int i = 0; i < struct_count; ++i) {
        fread(modules1, 1, sizeof(modules), db);
        if (strcmp(field, "module_name") == 0 && strcmp(modules1->module_name, value) == 0) {
            count++;
        }
    }

    printf("%d\n", count);

    free(modules1);
    return 0;
}

int agr_sum_modules(FILE *db,char *field, int value){
    int sum = 0;
    int struct_count = get_records_count_in_file(db);
    modules *modules1 = (modules *)malloc(sizeof(modules));
    for (int i = 0; i < struct_count; ++i) {
        fread(modules1, 1, sizeof(modules), db);
        if (strcmp(field, "id") == 0 && modules1->id == value) {
            sum += modules1->id;
        } else if (strcmp(field, "level_memory_number") == 0 && modules1->level_memory_number == value) {
            sum += modules1->level_memory_number;
        } else if (strcmp(field, "ceil_number") == 0 && modules1->ceil_number == value) {
            sum += modules1->ceil_number;
        } else if (strcmp(field, "flag_delete") == 0 && modules1->flag_delete == value) {
            sum += modules1->flag_delete;
        }
    }
    printf("%d\n", sum);
    free(modules1);
    return 0;
}

