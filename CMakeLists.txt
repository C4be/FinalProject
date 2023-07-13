cmake_minimum_required(VERSION 3.25)
project(FinalProject C)

set(CMAKE_C_STANDARD 11)

add_executable(FinalProject modules_db.c crud/shared.c crud/shared.h master_levels.c master_levels.h master_modules.c master_modules.h master_status_events.c master_status_events.h database.h struct/modules.h agregations/agregation_func.c agregations/agregation_func.h size_file/size.c size_file/size.h)
