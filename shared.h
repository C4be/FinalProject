#ifndef SHARED_H
#define SHARED_H

#include "./struct/modules.h"
#include "./struct/levels.h"
#include "./struct/status_events.h"

// files work
int get_file_size_in_bytes(FILE *pfile);
int get_records_count_in_file(FILE *pfile);

// select
int select_modules_by(FILE *db, const char *field, int value);
int select_modules_by_module_name(FILE *db, char *value);

// insertion Warning: не возвращают указатель файла на начало
int insert_modules(FILE *db, modules *entity);
int insert_levels(FILE *db, levels *entity);
int insert_status_events(FILE *db, status_events *entity);

// delete
int delete_modules(FILE *db, int id);
int delete_levels(FILE *db, int id);
int delete_status_events(FILE *db, int id);

// update
int update_modules(FILE *db, int id, modules *entity);
int update_levels(FILE *db, int id, levels *entity);
int update_status_events(FILE *db, int id, status_events *entity);


#endif //SHARED_H
