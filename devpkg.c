
#include <stdio.h>

#include "devpkg.h"
#include "db.h"

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("ERROR: an argument is expected.\n");
		return -1;
	} else if (argc > 2) {
		printf("ERROR: only 1 argument expected.\n");
		return -1;
	}
	
	char *URL = argv[1];
	
	Database *db = DB_create("db/database.txt");
	
	if (!DB_add(db, URL)) {
		puts("That project has already been added to the database.");
	} else {
		puts("Project added to the database.");
	}
	DB_print(db);
	DB_save(db);
	
	return 0;
}