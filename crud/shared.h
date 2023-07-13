#ifndef SHARED_H
#define SHARED_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../struct/modules.h"
#include "../struct/levels.h"
#include "../struct/status_events.h"
//////////////////////////////////////////////////////
#include "../size_file/size.h"
// ОБЩИЕ ОПЕРАЦИИ НАД ТАБЛИЦАМИ

int select_modules_by(FILE *db, const char *field, int value);
int select_modules_by_module_name(FILE *db, char *value);
int select_all_modules(FILE *db);
int insert_modules(FILE *db, modules *entity);
int update_modules(FILE *db, int id, modules *entity);

#endif //SHARED_H
