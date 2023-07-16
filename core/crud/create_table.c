//
// Created by lifefire1 on 16.07.23.
//
#include "../table_struct/table_struct.h"
#include "../table_struct/field_struct.h"
#include "create_table.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

char *get_table_name(char *query){
    char *delim = " ";
    char *tb_name = strtok(query, delim);
    for(int i = 0; i < 2 ; ++i){
        tb_name = strtok(NULL, " ");
    }
    return tb_name;
}

int get_field_count(const char *query){
    int index = 0;
    int count = 1;
    while (*(query + index) != '\0'){
        if(*(query + index) == ','){
            count++;
        }
        index++;
    }
    return count;
}

void fill_table_fields(char *query, Table *table){
    char* token;
    char* delimiter = " (,)";
//    printf("%d\n", table->field_count);
    // Пропускаем "create", "table" и название таблицы
    strtok(query, delimiter);
    strtok(NULL, delimiter);
    token = strtok(NULL, delimiter);

    int index = 0;
    while (token != NULL) {
        token = strtok(NULL, delimiter);
        if(token == NULL){
            break ;
        }
        if(strcmp(token,"int") == 0){
            table->fields[index].field_type = 1;
        }
        else if(strcmp(token,"string") == 0){
            table->fields[index].field_type = 2;
        }
        token = strtok(NULL, delimiter);
        table->fields[index].field_name = token;
        index++;
    }

}

int create_table(char *query){
    Table table;
    char *tmp_str = (char *)malloc(sizeof(char ) * (strlen(query) + 1));
    char *tmp_field_count = (char *)malloc(sizeof(char ) * (strlen(query) + 1));
    char *tmp_fill_field = (char *)malloc(sizeof(char ) * (strlen(query) + 1));
    strcpy(tmp_str, query);
    strcpy(tmp_fill_field, query);
    strcpy(tmp_field_count,query);
    tmp_str[strlen(query)] = '\0';
    tmp_field_count[strlen(query)] = '\0';
    table.table_name = get_table_name(tmp_str);
    table.field_count = get_field_count(tmp_field_count);
    fill_table_fields(tmp_fill_field, &table);
    for (int i = 0; i < table.field_count; ++i) {
        printf("%d %s\n", table.fields[i].field_type, table.fields[i].field_name);
    }

    return 0;
}

int main() {
    char buffer[] = "create table test (int id, string name, int age, string value, int salary)";
    create_table(buffer);
    return 0;
}
