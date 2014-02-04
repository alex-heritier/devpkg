
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "db.h"

char *get_zip_name(char *URL)
{
	int nslashes = 0;
	int last_slash = 0;
	for (int i = 0; i < strlen(URL); i++) {
		if (URL[i] == '/') {
			nslashes++;
			last_slash = i;
		}
	}
	assert(nslashes);
	
	return strdup(URL+last_slash+1);
}

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
	//DB_print(db);
	DB_save(db);
	
	//get .zip file name
	char shell_command[128];
	char *zip_name = get_zip_name(URL);
	
	//make a folder for the project
	char project_name[strlen(zip_name)+1];	//remove .zip from zip name
	memcpy(project_name, zip_name, strlen(zip_name)+1);
	project_name[strlen(project_name)-4] = '\0';
	sprintf(shell_command, "mkdir projects/%s", project_name);
	system(shell_command);
	
	//download project .zip file to folder
	sprintf(shell_command, "curl %s > projects/%s/%s", URL, project_name, zip_name);
	system(shell_command);
	
	//unzip .zip file
	sprintf(shell_command, "unzip projects/%s/%s", project_name, zip_name);
	system(shell_command);
	
	//./configure
	sprintf(shell_command, "./projects/%s/%s/configure", project_name, zip_name);
	system(shell_command);
	
	//make
	sprintf(shell_command, "cd projects/%s/%s", project_name, zip_name);
	system(shell_command);
	sprintf(shell_command, "make");
	system(shell_command);
	
	//make install
	sprintf(shell_command, "make install");
	system(shell_command);
	
	return 0;
}

