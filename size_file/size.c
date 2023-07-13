//
// Created by lifefire1 on 13.07.23.
//

#include "size.h"


int get_file_size_in_bytes(FILE *pfile) {
    int size;
    fseek(pfile, 0, SEEK_END);
    size = ftell(pfile);
    rewind(pfile);
    return size;
}


int get_records_count_in_file(FILE *pfile) {
    return get_file_size_in_bytes(pfile) / sizeof(modules);
}