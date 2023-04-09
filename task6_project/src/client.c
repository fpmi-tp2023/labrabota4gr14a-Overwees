//
// created by Pavel Kosteckij 26.03.2023
//

//client file
#include <stdio.h>
#include "../include/interface.h"
#include <sqlite3.h>

int main(void)
{
	sqlite3* db;

	if (open_database("db/lab4.db", db) != 0) {
		sqlite3_close(db);
		return 1;
	}

	while(1) {
		if (process_menu_actions(db) == -1) {
			break;
		}
	}
	
	sqlite3_close(db);
	printf("\nThanks for using our service\n");
	return 0;
}
