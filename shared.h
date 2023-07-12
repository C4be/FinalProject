#ifndef SHARED_H
#define SHARED_H

typedef struct {
    int id;
    char module_name[30];
    int level_memory_number;
    int ceil_number;
    int flag_delete;
} modules;

typedef struct {
    int id;
    int count_ceil_on_level;
    int flag_security;
} levels;

typedef struct {
    int id;
    int id_module;
    int new_id_module;
    // format: "dd.mm.yyyy\0"
    char date_of_change[10 + 1];
    // format: "hh:mm:ss\0"
    char time_of_time[8 + 1];
} status_events;

// insertion TODO: не возвращают указатель файла на начало
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
