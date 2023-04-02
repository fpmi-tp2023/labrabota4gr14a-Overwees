//
// created by Pavel Kosteckij 26.03.2023
//

#include <sqlite3.h>

#ifndef DBPROJECT_TASK6_INTERFACE_H
#define DBPROJECT_TASK6_INTERFACE_H


int open_database(char* path, sqlite3* db);
int process_menu_actions(sqlite3* db);

#endif // DBPROJECT_TASK6_INTERFACE_H