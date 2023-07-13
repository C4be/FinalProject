#define ENTITY
#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////
ENTITY int *select(FILE *db, int id);
int delete(FILE *db, int id);
int insert(FILE *db, ENTITY *entity);
int update(FILE *db, int id, ENTITY *entity);
//////////////////////////////////////////////////////
