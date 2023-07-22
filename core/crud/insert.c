//
// Created by lifefire1 on 18.07.23.
//

#include "insert.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "../table_struct/table_struct.h"
#include "create_table.h"

int insert_(char *query){
    char *temp = (char *)malloc(sizeof (char) * (strlen(query) + 1));
    strcpy(temp,query);
    char path[100];
    char *tb_name = get_table_name(temp);
    sprintf(path, "../table_str/%s.bin",tb_name);
    FILE *bin_str = fopen(path, "rb+");
    Table *bin = deserrializable_table(bin_str);
    char *param = strtok(query, "(,)");
    char path_tb[100];
    sprintf(path_tb,"../table/%s", tb_name);
    FILE *tb = fopen(path_tb, "a+");
    for (int i = 0; i < bin->field_count; ++i) {
        param = strtok(NULL, "(,)");
        fwrite(param, strlen(param), 1, tb);
    }
    fwrite("\n", 1, 1, tb);
    fclose(tb);
    fclose(bin_str);
    free(bin);
    return 0;
}
