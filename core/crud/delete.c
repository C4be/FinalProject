#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_header(const char *header, char *fields[]) {
    char *line_copy = strdup(header);
    char *token = strtok(line_copy, " ");
    int field_count = 0;

    while (token != NULL) {
        fields[field_count++] = strdup(token);
        token = strtok(NULL, " ");
    }

    free(line_copy);
    return field_count;
}

// Функция для освобождения памяти, занятой массивом названий полей
void free_fields(char *fields[], int field_count) {
    for (int i = 0; i < field_count; i++) {
        free(fields[i]);
    }
}

// Функция для удаления строк из файла таблицы, удовлетворяющих условию
// Функция для получения имени таблицы из запроса
char *get_table_name_th(char *query) {
    char *tmp = strdup(query);
    char *from_keyword = "from";
    char *table_name = NULL;
    char *token = strtok(tmp, " ,");

    while (token != NULL) {
        if (strcmp(token, from_keyword) == 0) {
            // Найдено ключевое слово "from"
            token = strtok(NULL, " ,"); // Переходим к следующему токену после "from"
            if (token != NULL) {
                table_name = strdup(token);
                break;
            }
        }
        token = strtok(NULL, " ,"); // Переходим к следующему токену
    }

    free(tmp);
    return table_name;
}

// Функция для полного удаления таблицы
int delete_all(char *table_name) {
    char file_path[100];
    sprintf(file_path, "../table/%s", table_name);

    // Открываем файл таблицы для чтения
    FILE *tb = fopen(file_path, "r");
    if (tb == NULL) {
        printf("Ошибка: не удалось открыть файл таблицы\n");
        return -1;
    }

    // Создаем временный файл
    FILE *temp_file = tmpfile();
    if (temp_file == NULL) {
        printf("Ошибка: не удалось создать временный файл\n");
        fclose(tb);
        return -1;
    }

    // Копируем только первую строку из файла таблицы во временный файл
    char line[100];
    if (fgets(line, sizeof(line), tb)) {
        fputs(line, temp_file);
    }

    // Закрываем и удаляем исходный файл
    fclose(tb);
    remove(file_path);

    // Переименовываем временный файл в исходный
    FILE *new_tb = fopen(file_path, "w");
    if (new_tb == NULL) {
        printf("Ошибка: не удалось создать новый файл таблицы\n");
        fclose(temp_file);
        return -1;
    }

    rewind(temp_file);
    while (fgets(line, sizeof(line), temp_file)) {
        fputs(line, new_tb);
    }

    fclose(new_tb);
    fclose(temp_file);

    return 0;
}

int delete(char *query) {
    char *table_name = get_table_name_th(query);
    if (table_name == NULL) {
        printf("Ошибка: не удалось получить имя таблицы из запроса\n");
        return -1;
    }

    // Получаем условие для удаления строк
    char *delete_keyword = "delete from";
    char *where_keyword = "where";
    char *condition = NULL;

    char *delete_pos = strstr(query, delete_keyword);
    if (delete_pos != NULL) {
        delete_pos += strlen(delete_keyword);
        char *where_pos = strstr(delete_pos, where_keyword);
        if (where_pos != NULL) {
            size_t condition_len = strlen(where_pos + strlen(where_keyword));
            condition = (char *)malloc(sizeof(char) * (condition_len + 1));
            strncpy(condition, where_pos + strlen(where_keyword), condition_len);
            condition[condition_len] = '\0';
        }
    }

    if (condition == NULL) {
        // Если нет условия, удаляем всю таблицу
        int result = delete_all(table_name);
        free(table_name);
        return result;
    }

    // Открываем файл таблицы для чтения
    char file_path[100];
    sprintf(file_path, "../table/%s", table_name);
    FILE *tb = fopen(file_path, "r");
    if (tb == NULL) {
        printf("Ошибка: не удалось открыть файл таблицы\n");
        free(table_name);
        free(condition);
        return -1;
    }

    // Создаем временный файл
    FILE *temp_file = tmpfile();
    if (temp_file == NULL) {
        printf("Ошибка: не удалось создать временный файл\n");
        free(table_name);
        free(condition);
        fclose(tb);
        return -1;
    }

    // Получаем заголовок таблицы (названия столбцов) и записываем его во временный файл
    char header[100];
    if (fgets(header, sizeof(header), tb)) {
        fputs(header, temp_file);
    }

    // Парсим первую строку для получения названий полей
    char *fields[10];
    int field_count = parse_header(header, fields);

    // Разбиваем условие на отдельные части: поле, оператор сравнения и значение
    char *field = strtok(condition, "=<> ");
    char *operator_str = strtok(NULL, " "); // Changed variable name to operator_str
    char *value = strtok(NULL, "=<> ");

    // Парсим каждую строку таблицы и проверяем, удовлетворяет ли она условию
    char line[100];
    while (fgets(line, sizeof(line), tb)) {
        // Очищаем строку от символа переноса строки
        size_t line_len = strlen(line);
        if (line[line_len - 1] == '\n') {
            line[line_len - 1] = '\0';
        }

        // Создаем копию строки, чтобы не потерять данные при токенизации
        char *line_copy = strdup(line);

        int meets_condition = 0;
        char *token = strtok(line_copy, " "); // Разделитель - пробел
        int current_field = 0; // Индекс текущего поля
        while (token != NULL && current_field < field_count) {
            // Если нашли поле, которое соответствует условию, проверяем значение
            if (strcmp(fields[current_field], field) == 0) {
//                token = strtok(NULL, " "); // Разделитель - пробел
                if (strcmp(operator_str, "=") == 0 && strcmp(token, value) == 0) {
                    meets_condition = 1;
                } else if (strcmp(operator_str, "<") == 0 && atoi(token) < atoi(value)) {
                    meets_condition = 1;
                } else if (strcmp(operator_str, ">") == 0 && atoi(token) > atoi(value)) {
                    meets_condition = 1;
                }
                break;
            }

            token = strtok(NULL, " "); // Разделитель - пробел
            current_field++;
        }

        free(line_copy);

        // Записываем строки, которые не удовлетворяют условию, во временный файл
        if (!meets_condition) {
            fputs(line, temp_file);
            fputs("\n", temp_file); // Добавляем символ переноса строки после каждой строки
        }
    }

    // Закрываем и удаляем исходный файл
    fclose(tb);
    remove(file_path);

    // Переименовываем временный файл в исходный
    FILE *new_tb = fopen(file_path, "w");
    if (new_tb == NULL) {
        printf("Ошибка: не удалось создать новый файл таблицы\n");
        free(table_name);
        free(condition);
        fclose(temp_file);
        return -1;
    }

    rewind(temp_file);
    while (fgets(line, sizeof(line), temp_file)) {
        fputs(line, new_tb);
    }

    fclose(new_tb);
    fclose(temp_file);

    // Освобождаем память, занятую массивом названий полей
    free_fields(fields, field_count);

    free(table_name);
    free(condition);

    return 0;
}
