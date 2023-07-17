
#include "db_helper.h"
#include "../global_var.h"


int db_not_exist(char *db_name) {
    if (db_list == NULL) {
        return -1;
    }
    rewind(db_list);
    char db[MAX_DB_NAME];
    while (fgets(db, MAX_DB_NAME, db_list) != NULL) {
        size_t length = strlen(db);
        if (db[length - 1] == '\n') {
            db[length - 1] = '\0';
        }

        if (strcmp(db, db_name) == 0) {
            return 0;
        }
    }
    return 1;
}

int add_db_list(char *db_name){
    if(db_not_exist(db_name)){
        fwrite(db_name, strlen(db_name), 1,db_list);
        fwrite("\n", 1, 1,db_list);
    }
    return 0;
}
