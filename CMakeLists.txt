cmake_minimum_required(VERSION 3.25)
project(FinalProject C)

set(CMAKE_C_STANDARD 11)

add_executable(FinalProject modules_db.c masters/master_levels.c masters/master_levels.h masters/master_modules.c masters/master_modules.h masters/master_status_events.c masters/master_status_events.h shared.h shared.c struct/modules.h struct/levels.h struct/status_events.h)
