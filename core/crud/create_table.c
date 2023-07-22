//
// Created by lifefire1 on 16.07.23.
//
#include "../table_struct/table_struct.h"
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

void serrializable_table(FILE *tb, const Table *table) {
    // Записываем имя таблицы
    size_t table_name_len = strlen(table->table_name);
    fwrite(&table_name_len, sizeof(size_t), 1, tb);
    fwrite(table->table_name, sizeof(char), table_name_len, tb);

    // Записываем количество полей
    fwrite(&table->field_count, sizeof(int), 1, tb);

    // Записываем каждое поле
    for (int i = 0; i < table->field_count; i++) {
        // Записываем имя поля
        size_t field_name_len = strlen(table->fields[i].field_name);
        fwrite(&field_name_len, sizeof(size_t), 1, tb);
        fwrite(table->fields[i].field_name, sizeof(char), field_name_len, tb);

        // Записываем тип поля (или другие данные структуры TableField)
        fwrite(&table->fields[i].field_type, sizeof(int), 1, tb);
    }
}


void fill_table_fields(char *query, Table *table){
    char* token;
    char* delimiter = " (,)";
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

void free_table(Table *table) {
    if (table == NULL) {
        return;
    }

    // Освобождаем память для имени таблицы
    free(table->table_name);

    // Освобождаем память для имени и типа каждого поля
    for (int i = 0; i < table->field_count; i++) {
        free(table->fields[i].field_name);
    }

    // Освобождаем память для массива полей и самой структуры Table
    free(table);
}

Table *deserrializable_table(FILE *tb) {
    Table *table = (Table *)malloc(sizeof(Table));
    if (table == NULL) {
        printf("Ошибка при выделении памяти для структуры Table\n");
        return NULL;
    }

    // Читаем имя таблицы
    size_t table_name_len;
    fread(&table_name_len, sizeof(size_t), 1, tb);
    table->table_name = (char *)malloc(sizeof(char) * (table_name_len + 1));
    if (table->table_name == NULL) {
        printf("Ошибка при выделении памяти для имени таблицы\n");
        free(table);
        return NULL;
    }
    fread(table->table_name, sizeof(char), table_name_len, tb);
    table->table_name[table_name_len] = '\0';

    // Читаем количество полей
    fread(&table->field_count, sizeof(int), 1, tb);

    // Выделяем память для массива полей
    for (int i = 0; i < table->field_count; i++) {
        size_t field_name_len;
        fread(&field_name_len, sizeof(size_t), 1, tb);
        table->fields[i].field_name = (char *)malloc(sizeof(char) * (field_name_len + 1));
        if (table->fields[i].field_name == NULL) {
            printf("Ошибка при выделении памяти для имени поля\n");
            free_table(table);
            return NULL;
        }
        fread(table->fields[i].field_name, sizeof(char), field_name_len, tb);
        table->fields[i].field_name[field_name_len] = '\0';

        // Читаем тип поля (или другие данные структуры TableField)
        fread(&table->fields[i].field_type, sizeof(int), 1, tb);
    }

    return table;
}



int create_table(char *query){
    Table *table = (Table *)malloc(sizeof(Table));
    char *tmp_str = (char *)malloc(sizeof(char ) * (strlen(query) + 1));
    char *tmp_field_count = (char *)malloc(sizeof(char ) * (strlen(query) + 1));
    char *tmp_fill_field = (char *)malloc(sizeof(char ) * (strlen(query) + 1));
    strcpy(tmp_str, query);
    strcpy(tmp_fill_field, query);
    strcpy(tmp_field_count,query);
    tmp_str[strlen(query)] = '\0';
    tmp_field_count[strlen(query)] = '\0';
    table->table_name = get_table_name(tmp_str);
    table->field_count = get_field_count(tmp_field_count);
    fill_table_fields(tmp_fill_field, table);
    for (int i = 0; i < table->field_count; ++i) {
        printf("%d %s\n", table->fields[i].field_type, table->fields[i].field_name);
    }
    char res_path[100];
    sprintf(res_path, "../table/%s", table->table_name);
    FILE *table_file = fopen(res_path, "wb");
    for (int i = 0; i < table->field_count; ++i) {
        char line[1000];
        sprintf(line, "%s ", table->fields[i].field_name);
        fwrite(line, strlen(line), 1, table_file);
    }
    fwrite("\n", 1, 1, table_file);
    char str_table_file_path[100];
    sprintf(str_table_file_path,"../table_str/%s.bin", table->table_name);
    FILE *str_table_file = fopen(str_table_file_path, "wb+");
    serrializable_table(str_table_file, table);
    fclose(str_table_file);
    FILE *rb_file = fopen(str_table_file_path, "rb+");
    fclose(rb_file);
    free(tmp_str);
    free(tmp_field_count);
    free(tmp_fill_field);
    return 0;
}

//int main(){
//    create_table("create table test (int id, string name, string surname, int salary)");
//    return 0;
//}
