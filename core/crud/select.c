//
// Created by lifefire1 on 16.07.23.
//

#include "select.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "../table_struct/table_struct.h"
#include "create_table.h"

char **get_table_fields(const char *file_path, int *field_count) {
    FILE *tb = fopen(file_path, "r");
    if (tb == NULL) {
        printf("Ошибка: не удалось открыть файл таблицы\n");
        return NULL;
    }

    char line[100];
    if (fgets(line, sizeof(line), tb)) {
        // Первая строка содержит поля таблицы, разделенные пробелами
        // Вычисляем количество полей, подсчитывая пробелы в строке
        *field_count = 1;
        for (int i = 0; line[i] != '\0'; i++) {
            if (line[i] == ' ') {
                (*field_count)++;
            }
        }

        // Выделяем память для массива fields
        char **fields = (char **)malloc(sizeof(char *) * (*field_count));

        // Разделяем строку на отдельные токены (имена полей) и сохраняем их в массив fields
        char *token = strtok(line, " \n");
        int index = 0;
        while (token != NULL) {
            fields[index] = (char *)malloc(strlen(token) + 1);
            strcpy(fields[index], token);
            token = strtok(NULL, " \n");
            index++;
        }

        fclose(tb);
        return fields;
    } else {
        printf("Ошибка: файл таблицы пуст\n");
        fclose(tb);
        return NULL;
    }
}

int get_column_index(char **fields, int field_count, const char *column_name) {
    for (int i = 0; i < field_count; i++) {
        if (strcmp(fields[i], column_name) == 0) {
            return i;
        }
    }
    return -1;
}

int *get_select_columns(char *query, char **fields, int field_count) {
    char *select_keyword = "select";
    char *from_keyword = "from";
    char *columns = NULL;

    // Находим ключевое слово "select" в запросе
    char *select_pos = strstr(query, select_keyword);
    if (select_pos == NULL) {
        printf("Ошибка: запрос не содержит ключевого слова 'select'\n");
        return NULL;
    }

    // Находим ключевое слово "from" в запросе
    char *from_pos = strstr(query, from_keyword);
    if (from_pos == NULL) {
        printf("Ошибка: запрос не содержит ключевого слова 'from'\n");
        return NULL;
    }

    // Выделяем память для строки, в которой будем хранить столбцы
    size_t columns_len = from_pos - (select_pos + strlen(select_keyword));
    columns = (char *)malloc(sizeof(char) * (columns_len + 1));

    // Копируем столбцы в выделенную строку
    strncpy(columns, select_pos + strlen(select_keyword), columns_len);
    columns[columns_len] = '\0';

    // Выделяем память для массива, где будем хранить флаги (0 - столбец не запрошен, 1 - столбец запрошен)
    int *selected_columns = (int *)malloc(sizeof(int) * field_count);
    for (int i = 0; i < field_count; i++) {
        selected_columns[i] = 0; // Изначально все столбцы не запрошены
    }

    // Разделяем столбцы на отдельные токены (имена столбцов)
    char *token = strtok(columns, ", ");
    while (token != NULL) {
        // Проверяем, соответствует ли текущий токен имени одного из столбцов
        int column_index = get_column_index(fields, field_count, token);
        if (column_index != -1) {
            selected_columns[column_index] = 1; // Запрошен текущий столбец
        }
        token = strtok(NULL, ", ");
    }

    free(columns);
    return selected_columns;
}

char *tb_name_selct(char *query) {
    char *tmp = (char *)malloc (sizeof (char) * (strlen(query) + 1));
    strcpy(tmp, query);
    char *from_keyword = "from";
    char *table_name = NULL;
    char *token = strtok(tmp, " ,");

    while (token != NULL) {
        if (strcmp(token, from_keyword) == 0) {
            // Найдено ключевое слово "from"
            token = strtok(NULL, " ,"); // Переходим к следующему токену после "from"
            if (token != NULL) {
                table_name = token;
                break;
            }
        }
        token = strtok(NULL, " ,"); // Переходим к следующему токену
    }
    free(tmp);
    return table_name;
}

char *get_name_for_all(char *query){
    char *name = strtok(query," ");
    name = strtok(NULL," ");
    name = strtok(NULL," ");
    name = strtok(NULL," ");
    return name;
}

int select_all(char *query) {
    char *temp = (char *)malloc(sizeof(char) * (strlen(query) + 1));
    strcpy(temp, query);
    char *tb_name = get_name_for_all(temp);
    char res_path[100];
    sprintf(res_path, "../table/%s", tb_name);

    FILE *tb = fopen(res_path, "r");
    if (tb == NULL) {
        printf("Ошибка: не удалось открыть файл таблицы\n");
        free(temp);
        return -1;
    }

    char line[100];
    while (fgets(line, sizeof(line), tb)) {
        // Обработайте каждую строку здесь, как вам нужно
        printf("%s", line);
    }

    fclose(tb);
    free(temp);
    return 0;
}

int find_char_index(const char *str, char c) {
    int index = -1;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c) {
            index = i;
            break;
        }
    }
    return index;
}


int select_with_params(char *query, char **fields, int field_count) {
    char *tmp = (char *)malloc(sizeof(char) * (strlen(query) + 1));
    strcpy(tmp, query);
    tmp[strlen(query)] = '\0';
    int *selected_columns = get_select_columns(tmp, fields, field_count); // Получаем массив с флагами запрошенных столбцов

    // Открываем файл с таблицей
    char *tb_name = tb_name_selct(tmp);
    char res_path[100];
    sprintf(res_path, "../table/%s", tb_name);
    FILE *tb = fopen(res_path, "r");
    if (tb == NULL) {
        printf("Ошибка: не удалось открыть файл таблицы\n");
        free(tmp);
        free(selected_columns);
        return -1;
    }

    char line[100];
    while (fgets(line, sizeof(line), tb)) {
        // Обработка каждой строки, как вам требуется
        // Для примера, просто выведем значения запрошенных столбцов
        char *token = strtok(line, " ");
        int column_num = 0;
        while (token != NULL) {
            // Проверяем, нужно ли выводить данный столбец
            if (selected_columns[column_num] == 1) {
                printf("%s ", token); // Выводим значение столбца
            }
            token = strtok(NULL, " ");
            column_num++;
        }
        printf("\n");
    }

    fclose(tb);
    free(tmp);
    free(selected_columns);
    return 0;
}

int select_(char *query){
    /*
     * get params
     * * - all
     * ...
     */
    if(find_char_index(query,'*') != -1){
        select_all(query);
    }
    else {
        int field_count;
        char *tmp = (char *)malloc(sizeof (char) * (strlen(query) + 1));
        strcpy(tmp,query);
        char *tb_name = tb_name_selct(tmp);
        char res_path[100];
        sprintf(res_path, "../table/%s", tb_name);
        char **fields = get_table_fields(res_path, &field_count);
//            {"id", "name", "salary", "surname"};
        select_with_params(query, fields, field_count);
    }
    return 0;
}



//int main() {
//    char buffer[] = "select id, salary from test";
//    select_(buffer);
//    return 0;
//}
