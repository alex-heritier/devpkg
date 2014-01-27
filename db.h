#ifndef DB_H
#define DB_H

static int const MAX_ENTRIES = 512;
static int const MAX_DATA = 128;

typedef struct Entry {
	char data[MAX_DATA];
} Entry;

typedef struct Database {
	char *filename;
	Entry entries[MAX_ENTRIES];
	unsigned int entry_num;
} Database;

int test(Database *db, char *data);
Database *DB_create(char *filename);
int DB_find(Database *db, char *data);
int DB_add(Database *db, char *data);
void DB_print(Database *db);
int DB_save(Database *db);

#endif	//DB_H