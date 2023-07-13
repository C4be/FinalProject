// точка входа
#include <stdio.h>
#include "crud/shared.h"
#define MAX_NAME_DB 1000
#define MAX_FIELD_NAME 100
#define MAX_FIELD_LENGTH 100

int menu(int choose)    {
    switch (choose) {
        case 1:{
            // select
            printf("Был выбран запрос SELECT\n"
                "Какую базу данных вы хотите вывести?\n"
                "Примечание:\n"
                "Сейчас доступны следующие базы данных:\n"
                "- master_levels.db\n"
                "- master_modules.db\n"
                "- master_status_events.db\n");
            char db_name[MAX_NAME_DB];
            scanf("%s", db_name);
            char res_path[MAX_NAME_DB + MAX_NAME_DB];
            sprintf(res_path, "../materials/%s", db_name);
            FILE *db = fopen(res_path,"r");
            printf("Хотите ли вы провести выборку по равенству поля каккому-либо значению?\n"
                "Введите y/n:\n");
            fflush(stdin);
            char acc[2];
            scanf("%1s", acc);
            if(strcmp(acc,"y") == 0){
                printf("Структура базы данных master_levels.db\n"
                    "id int\n"
                    "module_name string\n"
                    "level_memory_number\n"
                    "ceil_number\n"
                    "flag_delete\n");
                char field_name[MAX_FIELD_NAME];
                scanf("%s", field_name);
                if (strcmp(field_name,"module_name") == 0){
                    printf("Введите значение:\n");
                    char value_field[MAX_FIELD_LENGTH];
                    scanf("%s", value_field);
                    select_modules_by_module_name(db,value_field);
                }
                else{
                    printf("Введите значение:\n");
                    int value;
                    scanf("%d", &value);
                    select_modules_by(db,field_name, value);
                }
            }
            else{
                select_all_modules(db);
            }
            fclose(db);
            break;
        }
        case 2:{
            printf("Был выбран запрос INSERT\n"
                "В какую базу данных вы хотите добавить запись?\n"
                "Примечание:\n"
                "Сейчас доступны следующие базы данных:\n"
                "- master_levels.db\n"
                "- master_modules.db\n"
                "- master_status_events.db\n");
                char db_path[MAX_NAME_DB];
                scanf("%s", db_path);
                char res_path[MAX_NAME_DB + MAX_NAME_DB];
                sprintf(res_path, "../materials/%s", db_path);
                FILE *db = fopen(res_path, "a");
                modules mod;
                printf("Введите id:");
                scanf("%d", &mod.id);
                printf("Введите module_name:");
                scanf("%s", mod.module_name);
                printf("Введите level_memory_number:");
                scanf("%d", &mod.level_memory_number);
                printf("Введите ceil_number:");
                scanf("%d", &mod.ceil_number);
                printf("Введите flag_delete:");
                scanf("%d", &mod.flag_delete);
                insert_modules(db,&mod);
                fclose(db);
            break ;
        }
        case 3:{
            //update
            printf("Был выбран запрос UPDATE\n"
                "В какой базе данных вы хотите обновить запись?\n"
                "Примечание:\n"
                "Сейчас доступны следующие базы данных:\n"
                "- master_levels.db\n"
                "- master_modules.db\n"
                "- master_status_events.db\n");
            char db_path[MAX_NAME_DB];
            scanf("%s", db_path);
            char res_path[MAX_NAME_DB + MAX_NAME_DB];
            sprintf(res_path, "../materials/%s", db_path);
            FILE *db = fopen(res_path, "a");
            modules mod;
            printf("Введите id:");
            scanf("%d", &mod.id);
            printf("Введите module_name:");
            scanf("%s", mod.module_name);
            printf("Введите level_memory_number:");
            scanf("%d", &mod.level_memory_number);
            printf("Введите ceil_number:");
            scanf("%d", &mod.ceil_number);
            printf("Введите flag_delete:");
            scanf("%d", &mod.flag_delete);
            select_all_modules(db);
            printf("\nвведите id той записи, которую хотите изменить:\n");
            int id = 0;
            scanf("%d", &id);
            update_modules(db, id, &mod);
            fclose(db);
            break;
        }
        case 4:{
            // delete
            break ;
        }
        case 5:{
            // modules
            break ;
        }
        case 6:{
            // help
            break;
        }
        case 7:{
            // exit
            break ;
        }
    }
    return 0;
}

int main() {
    int choose = 0;
    while (choose != 7){
        printf(
            "Добро пожаловать в Систему Управления Базами Данных!\n"
            "Доступные команды:\n"
            "1. select - Получить записи из указанной таблицы.\n"
            "2. insert - Вставить новую запись в указанную таблицу.\n"
            "3. update - Обновить запись в указанной таблице.\n"
            "4. delete - Удалить запись из указанной таблицы.\n"
            "5. modules - Вывести все модули в базе данных\n"
            "6. help - Показать доступные команды и инструкции по использованию\n"
            "7. exit - Выйти из программы\n"
            "\n"
            "Введите команду: ");
        scanf("%d", &choose);
        menu(choose);
    }
    return 0;
}
