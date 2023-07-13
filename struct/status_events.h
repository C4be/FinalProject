#ifndef STATUS_EVENTS_H
#define STATUS_EVENTS_H

typedef struct {
    int id;
    int id_module;
    int new_id_module;
    // format: "dd.mm.yyyy\0"
    char date_of_change[10 + 1];
    // format: "hh:mm:ss\0"
    char time_of_time[8 + 1];
} status_events;

#endif //STATUS_EVENTS_H
