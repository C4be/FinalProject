#include <stdio.h>
#include "string.h"
#include "core/crud/select.h"
#include "core/crud/create_table.h"
#include "core/crud/delete.h"
#include "core/crud/update.h"
#include "core/crud/insert.h"

int main(){
    char string[100];
//        = "select * from madi";
    // create table niggers (int id, string name, string surname, int salary, int famka)
    fgets(string, 100, stdin);
    string[strlen(string) - 1] = '\0';
    char *str_dup = strdup(string);
    char delim[] = " ";
    char *token = strtok(str_dup, delim); // first word
    if (strcmp(token, "select") == 0){
        //select
        select_(string);
    }
    else if(strcmp(token, "create") == 0){
        // create

        // or table or db
        create_table(string);
    }
    else if(strcmp(token, "delete") == 0){
        // delete
        // delete from niggers where id = 1
        delete (string);
    }
    else if(strcmp(token, "update") == 0){
        // it's not work correctly 
        update(string);
    }
    else if(strcmp(token, "insert") == 0){
        // insert
        // insert into niggers (1, "chlen", "pass", 100, 200)
        insert_(string);
    }
    else{
        printf("incorrect input sql string");
    }
    return 0;
}