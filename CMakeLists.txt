cmake_minimum_required(VERSION 3.25)
project(FinalProject C)

set(CMAKE_C_STANDARD 11)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra")

add_executable(
        db
        core/db_manipulation/db_man.c
        core/db_manipulation/db_man.h
        core/db_manipulation/db_helper.c
        core/global_var.h
        core/global_var.c
        core/table_struct/table_struct.h
        core/crud/create_table.c
        core/crud/insert.c
        core/crud/select.c
        core/crud/delete.c
        core/crud/delete.h
        core/crud/update.c
        core/crud/update.h
        modules_db.c)
