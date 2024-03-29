
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "db.h"

//tests the functions for correctness

static int is_empty(const char *data);
int DB_save(const Database *db);

int test(Database *db, char *data)
{
	assert(db);
	assert(data);
	
	/*
	Entry ent;
	memset(&ent.data, 'A', MAX_DATA);
	ent.data[56] = '\0';
	printf("is_empty_entry: %d\n", is_empty_entry(&ent));
	DB_print(db);
	*/
	//printf("DB_find: %d\n", DB_find(db, data));
	//printf("the first entry in the db is %s\n", db->entries[0].data);
	
	DB_print(db);
	DB_save(db);
	
	return 1;
}

//loads entries from database file

int load_entries(Entry *ent, const char *filename)
{
	FILE *fp = fopen(filename, "r");
	if(!fp) fp = fopen(filename, "w+");
	if(!fp) {
		fprintf(stderr, "Database file could not be loaded.\n");
		return -1;
	}
	
	char temp[MAX_DATA] = {'\0'};
	while(!feof(fp)) {
		char *rc = fgets(temp, MAX_DATA, fp);
		if (!rc) break;	//if rc is NULL, fgets reached EOF
		if (!is_empty(temp)) {
			temp[strlen(temp)-1] = '\0';	//trim trailing newline
			memcpy(ent->data, temp, MAX_DATA);
			ent++;
		}
	}
	
	fclose(fp);
	return 1;
}

//allocates memory for a Database, initializes the variables and returns a pointer to it

Database *DB_create(const char *filename)
{
	assert(filename);
	
	Database *db = (Database *)malloc(sizeof(Database));
	db->filename = strdup(filename);
	load_entries(db->entries, filename);
	db->entry_num = 0;
	
	return db;
}

//checks if the Database has an entry with the given data

int DB_find(const Database *db, const char *data)
{
	assert(db);
	assert(data);
	
	for (int i = 0; i < MAX_ENTRIES; i++) {
		if (strcmp(data, db->entries[i].data) == 0) return 1;
	}
	return 0;
}

//checks if an Entry is filled with NULL

static int is_empty(const char *data)
{
	assert(data);
	for (int i = 0; i < MAX_DATA; i++) {
		if (data[i] != '\0') return 0;
	}
	return 1;
}

//adds an entry to a Database

int DB_add(Database *db, const char *data)
{
	assert(db);
	assert(data);
	
	if(DB_find(db, data)) return 0;
	for (int i = 0; i < MAX_ENTRIES; i++) {
		if (is_empty(db->entries[i].data)) {
			memcpy(&db->entries[i], data, MAX_DATA);
			db->entry_num++;
			return 1;
		}
	}
	return 1;
}

//prints the entry data in a list

void DB_print(const Database *db)
{
	assert(db);
	
	printf("Database at %s\n", db->filename);
	for (int i = 0; i < MAX_ENTRIES; i++) {
		if (is_empty(db->entries[i].data)) continue;
		printf("- %s\n", db->entries[i].data);
	}
}

//saves Database to a file

int DB_save(const Database *db)
{
	FILE *fp = fopen(db->filename, "w");
	assert(fp);
	printf("saving database...");
	for (int i = 0; i < MAX_ENTRIES; i++) {
		if (!is_empty(db->entries[i].data)) {
			fputs(db->entries[i].data, fp);
			fputs("\n", fp);
		}
	}
	fclose(fp);
	printf("database saved!\n");
	return 1;
}
