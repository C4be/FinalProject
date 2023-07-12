#include <stdio.h>
#include <stdlib.h>

#include "shared.h"

int insert_modules(FILE *db, modules *entity) {
    if (fseek(db, 0, SEEK_END) != 0) {
        return -1;
    }

    if (fwrite(entity, sizeof(modules), 1, db) != 1) {
        return -1;
    }

    return 1;
}

int insert_levels(FILE *db, levels *entity) {
    if (fseek(db, 0, SEEK_END) != 0) {
        return -1;
    }

    if (fwrite(entity, sizeof(levels), 1, db) != 1) {
        return -1;
    }

    return 1;
}

int insert_status_events(FILE *db, status_events *entity) {
    if (fseek(db, 0, SEEK_END) != 0) {
        return -1;
    }

    if (fwrite(entity, sizeof(status_events), 1, db) != 1) {
        return -1;
    }

    return 1;
}

int delete_modules(FILE *db, int id) {
    // Проверка входных параметров
    if (db == NULL) {
        printf("Некорректный указатель на файл.\n");
        return -1;
    }

    // Перемещаем указатель файла в начало
    rewind(db);

    // Поиск модуля с заданным идентификатором и пометка его для удаления
    modules current_module;
    int is_found = 0;

    while (fread(&current_module, sizeof(modules), 1, db) == 1) {
        if (current_module.id == id) {
            current_module.flag_delete = 1;
            fseek(db, -sizeof(modules), SEEK_CUR);  // Возвращаемся назад к найденной записи
            fwrite(&current_module, sizeof(modules), 1, db);
            is_found = 1;
            break;
        }
    }

    // Если модуль с указанным идентификатором не был найден
    if (!is_found) {
        printf("Модуль с идентификатором %d не найден.\n", id);
        return 0;
    }

    return 1;  // Успешное удаление модуля
}

int delete_levels(FILE *db, int id) {
    // Проверка входных параметров
    if (db == NULL) {
        printf("Некорректный указатель на файл.\n");
        return -1;
    }

    // Перемещаем указатель файла в начало
    rewind(db);

    // Поиск уровня с заданным идентификатором и пометка его для удаления
    levels current_level;
    int is_found = 0;

    while (fread(&current_level, sizeof(levels), 1, db) == 1) {
        if (current_level.id == id) {
            current_level.flag_security = 1;
            fseek(db, -sizeof(levels), SEEK_CUR);  // Возвращаемся назад к найденной записи
            fwrite(&current_level, sizeof(levels), 1, db);
            is_found = 1;
            break;
        }
    }

    // Если уровень с указанным идентификатором не был найден
    if (!is_found) {
        printf("Уровень с идентификатором %d не найден.\n", id);
        return 0;
    }

    return 1;  // Успешное удаление уровня
}

int delete_status_events(FILE *db, int id) {
    // Проверка входных параметров
    if (db == NULL) {
        printf("Некорректный указатель на файл.\n");
        return -1;
    }

    // Перемещаем указатель файла в начало
    rewind(db);

    // Поиск статусного события с заданным идентификатором и пометка его для удаления
    status_events current_event;
    int is_found = 0;

    while (fread(&current_event, sizeof(status_events), 1, db) == 1) {
        if (current_event.id == id) {
            current_event.id_module = -1;  // Помечаем модуль как удаленный
            fseek(db, -sizeof(status_events), SEEK_CUR);  // Возвращаемся назад к найденной записи
            fwrite(&current_event, sizeof(status_events), 1, db);
            is_found = 1;
            break;
        }
    }

    // Если статусное событие с указанным идентификатором не было найдено
    if (!is_found) {
        printf("Статусное событие с идентификатором %d не найдено.\n", id);
        return 0;
    }

    return 1;  // Успешное удаление статусного события
}

int update_modules(FILE *db, int id, modules *entity) {
    // Проверка входных параметров
    if (db == NULL || entity == NULL) {
        printf("Некорректные указатели.\n");
        return -1;
    }

    // Перемещаем указатель файла в начало
    rewind(db);

    // Поиск модуля с заданным идентификатором и обновление его данных
    modules current_module;
    int is_found = 0;

    while (fread(&current_module, sizeof(modules), 1, db) == 1) {
        if (current_module.id == id) {
            fseek(db, -sizeof(modules), SEEK_CUR);  // Возвращаемся назад к найденной записи
            fwrite(entity, sizeof(modules), 1, db);
            is_found = 1;
            break;
        }
    }

    // Если модуль с указанным идентификатором не был найден
    if (!is_found) {
        printf("Модуль с идентификатором %d не найден.\n", id);
        return 0;
    }

    return 1;  // Успешное обновление модуля
}

int update_levels(FILE *db, int id, levels *entity) {
    // Проверка входных параметров
    if (db == NULL || entity == NULL) {
        printf("Некорректные указатели.\n");
        return -1;
    }

    // Перемещаем указатель файла в начало
    rewind(db);

    // Поиск уровня с заданным идентификатором и обновление его данных
    levels current_level;
    int is_found = 0;

    while (fread(&current_level, sizeof(levels), 1, db) == 1) {
        if (current_level.id == id) {
            fseek(db, -sizeof(levels), SEEK_CUR);  // Возвращаемся назад к найденной записи
            fwrite(entity, sizeof(levels), 1, db);
            is_found = 1;
            break;
        }
    }

    // Если уровень с указанным идентификатором не был найден
    if (!is_found) {
        printf("Уровень с идентификатором %d не найден.\n", id);
        return 0;
    }

    return 1;  // Успешное обновление уровня
}

int update_status_events(FILE *db, int id, status_events *entity) {
    // Проверка входных параметров
    if (db == NULL || entity == NULL) {
        printf("Некорректные указатели.\n");
        return -1;
    }

    // Перемещаем указатель файла в начало
    rewind(db);

    // Поиск статусного события с заданным идентификатором и обновление его данных
    status_events current_event;
    int is_found = 0;

    while (fread(&current_event, sizeof(status_events), 1, db) == 1) {
        if (current_event.id == id) {
            fseek(db, -sizeof(status_events), SEEK_CUR);  // Возвращаемся назад к найденной записи
            fwrite(entity, sizeof(status_events), 1, db);
            is_found = 1;
            break;
        }
    }

    // Если статусное событие с указанным идентификатором не было найдено
    if (!is_found) {
        printf("Статусное событие с идентификатором %d не найдено.\n", id);
        return 0;
    }

    return 1;  // Успешное обновление статусного события
}