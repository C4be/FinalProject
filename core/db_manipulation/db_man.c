//
// Created by lifefire1 on 16.07.23.
//
#include "../global_var.h"
#include "db_helper.h"

int use_db(char *db_name){
    if(db_list == NULL){
        return -1;
    }
    rewind(db_list);
    char db[MAX_DB_NAME];
    while (fgets(db,MAX_DB_NAME, db_list) != NULL){
        if(strcmp(db,db_name) == 0){
            char res_path[MAX_DB_NAME];
            sprintf(res_path, "../database/%s", db_name);
            current_db = fopen(res_path,"a+");
            return 0;
        }
    }
    return -1;
}

FILE *create_database(char *db_name){
    char res_path[1000];
    sprintf(res_path, "../database/%s", db_name);
    if(db_not_exist(db_name)){
        add_db_list(db_name);
        return fopen(res_path, "r+");
    }
    else{
        printf("db %s exist\n", db_name);
        return NULL;
    }
}

int delete_database(char *db_name){
    FILE *tmp_file = fopen("../database/temp.db", "w+");
    char line[MAX_DB_NAME];
    rewind(db_list);
    while (fgets(line,MAX_DB_NAME,db_list) != NULL){
        size_t length = strlen(line);
        if (line[length - 1] == '\n') {
            line[length - 1] = '\0';
        }
        if(strcmp(db_name, line) != 0){
            fwrite(line, strlen(line), 1, tmp_file);
            fwrite("\n", 1, 1,tmp_file);
        }
    }
    fclose(tmp_file);
    fclose(db_list);
    remove("../database/list.db");
    rename("../database/temp.db", "../database/list.db");

    db_list = fopen("../database/list.db", "a+");
    if (db_list == NULL) {
        printf("Ошибка при открытии файла db_list\n");
        return -1;
    }

    return 0;
}


//int main(){
//    db_list = fopen("../database/list.db","a+");
//
//    return 0;
//}