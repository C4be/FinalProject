#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUERY_LENGTH 1000

void update(char *query) {
    char table_name[MAX_QUERY_LENGTH];
    char new_table_name[MAX_QUERY_LENGTH];
    char update_params[MAX_QUERY_LENGTH];
    int id;

    // Используем sscanf для разбора входной строки и получения необходимых значений
    sscanf(query, "update %s set %[^w] where id = %d", table_name, update_params, &id);


    // Создаем новое имя таблицы
    snprintf(new_table_name, sizeof(new_table_name), "../table/%s", table_name);

    FILE *file = fopen(new_table_name, "r+");
    if (file == NULL) {
        printf("Ошибка при открытии файла.\n");
        return;
    }

    char line[MAX_QUERY_LENGTH];
    char header[MAX_QUERY_LENGTH];
    fgets(header, sizeof(header), file); // Читаем строку с названиями столбцов и пропускаем ее

    int found = 0;
    long int position = ftell(file); // Сохраняем текущую позицию указателя файла

    while (fgets(line, sizeof(line), file)) {
        int record_id;
        sscanf(line, "%d", &record_id);

        if (record_id == id) {
            found = 1;
            fseek(file, position, SEEK_SET); // Переходим к исходной позиции

            // Получаем предыдущие значения параметров
            char old_params[MAX_QUERY_LENGTH];
            sscanf(line, "%*d \"%[^\"]\"", old_params);

            // Обновляем параметры
            char new_line[MAX_QUERY_LENGTH];
            snprintf(new_line, sizeof(new_line), "%d \"%s %s\"\n", id, old_params, update_params);
            fprintf(file, "%s", new_line);

            break;
        }

        position = ftell(file); // Сохраняем позицию для следующей строки
    }

    fclose(file);

    if (!found) {
        printf("Запись с ID %d не найдена.\n", id);
    } else {
        printf("Запись с ID %d успешно обновлена в таблице %s.\n", id, new_table_name);
    }
}

//int main() {
//    char query[] = "update madi set name = \"vasyan\",surname = \"bulkin\", salary = 100 where id = 3";
//
//    update(query);
//
//    return 0;
//}
