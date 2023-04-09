//
// created by Pavel Kosteckij 26.03.2023
//
#define _XOPEN_SOURCE
#define _CRT_SECURE_NO_WARNIN
#include <stdio.h>
#include <string.h>
#include "../include/interface.h"
#include "../include/structures.h"

void string_concat(char* destination, int index);

void create_insert_query(char* query);

static int callback(void* data, int argc, char** argv, char** azColName);

void create_select_query(char* query);

void create_delete_query(char* query);

int open_database(char* path, sqlite3* db) {
	int rc = sqlite3_open("db/lab4.db", &db);
	if (rc){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	}
	else {
		fprintf(stderr, "Opened database successfully\n");
	}
	return rc;
}

void string_concat(char* destination, int index) {
	strcat(destination, query_parts[index]);
}

static int callback(void* data, int argc, char** argv, char** azColName) {
	fprintf(stderr, "%s: ", (const char*)data);
	for (int i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "null");
	}
	printf("\n");
	return 0;
}

void input_str_field(char* query,char* buffer, int what_to_enter) {
	printf("%s: ", query_parts[what_to_enter]);
	scanf("%s", buffer);
	strcat(query, "'");
	strcat(query, buffer);
	strcat(query, "'");
	string_concat(query, COMMA);
}

void input_int_field(char* query, int what_to_enter) {
	int buffer = 0;
	printf("%s: ", query_parts[what_to_enter]);
	scanf("%d", &buffer);
	int length = snprintf(NULL, 0, "%d", buffer);
	char* str = malloc(length + 1);
	snprintf(str, length + 1, "%d", buffer);
	strcat(query, str);
	free(str);
	if (what_to_enter != DEPARTMENT_ID) {
		string_concat(query, COMMA);
	}
}

void create_insert_query(char* query) {
	string_concat(query, INSERT);
	char* str_buffer = malloc(sizeof(char) * 50);
	printf("Enter the insert values:\n");
	string_concat(query, STR_NULL);
	string_concat(query, COMMA);

	input_str_field(query, str_buffer, LASTNAME);
	input_str_field(query, str_buffer, FIRSTNAME);
	input_str_field(query, str_buffer, SURNAME);
	input_str_field(query, str_buffer, ADDRESS);
	input_str_field(query, str_buffer, NATIONALITY);
	input_str_field(query, str_buffer, BIRTHDAY);

	input_int_field(query, ACCOUNT_NUMBER);

	input_str_field(query, str_buffer, EDUCATION);

	input_int_field(query, YEAR_OF_EMPLOYMENT);
	input_int_field(query, SALARY);
	input_int_field(query, DEPARTMENT_ID);

	string_concat(query, END_INSERT);

	printf("%s\n", query);
}

void create_select_query(char* query) {
	printf("Choose condition type:\n"
		"0 - no condition\n"
		"1 - like\n"
		"2 - simple condition\n");
	int global = 0;
	scanf("%d", &global);
	if (global == 0) {
		return;
	}
	else {
		int choice = 0;
		strcat(query, " ");
		string_concat(query, WHERE);
		strcat(query, " ");
		printf("Choose the field:\n"
			"1 - id\n"
			"2 - last name"
			"3 - first name");
		scanf("%d", &choice);
		switch (choice) {
		case (1):
			printf("Enter the target id: ");
			int id;
			scanf("%d", &id);
			strcat(query, " ");
			string_concat(query, ID);
			strcat(query, " = ");
			int length = snprintf(NULL, 0, "%d", id);
			char* str = malloc(length + 1);
			snprintf(str, length + 1, "%d", id);
			strcat(query, str);
			free(str);
			break;
		case(2):
			printf("Enter the target last name: ");
			char* lastname = malloc(20 * sizeof(char));
			scanf("%s", lastname);
			strcat(query, " ");
			string_concat(query, LASTNAME);
			if (global == 2) {
				strcat(query, " = '%");
			}
			else {
				strcat(query, " = '");
			}
			strcat(query, lastname);
			strcat(query, "'");
			free(lastname);
			break;
		case(3):
			printf("Enter the target first name: ");
			char* name = malloc(20 * sizeof(char));
			scanf("%s", name);
			strcat(query, " ");
			string_concat(query, FIRSTNAME);
			if (global == 2) {
				strcat(query, " = '%");
			}
			else {
				strcat(query, " = '");
			}
			strcat(query, name);
			strcat(query, "'");
			free(name);
			break;
		default:
			return;
		}
	}
}

int process_menu_actions(sqlite3* db) {
	char* zErrMsg = 0;
	int rc;
	const char* data = "Callback function called";
	int transaction_mode = 0;
	while (1) {
		char* query = malloc(sizeof(char) * 400);
		printf("1 - transaction mode\n"
			"0 - autocommit mode\n");
		scanf("%d", &transaction_mode);
		if (transaction_mode < 0 || transaction_mode > 1) {
			printf("Wrong input. Try again\n");
			free(query);
			continue;
		}
		else if (transaction_mode) {
			string_concat(query, BEGIN_TRANSACTION);
		}
		printf("Menu:\n"
			"1 - SELECT\n"
			"2 - INSERT\n"
			"3 - DELETE\n"
			"4 - exit\n");

		int input;
		scanf("%d", &input);
		switch (input) {
		case (1):
			string_concat(query, SELECT);
			create_select_query(query);
			string_concat(query, END);
			printf("%s", query);
			break;
		case (2):
			create_insert_query(query);
			break;
		case (3):
			strcat(query, query_parts[DELETE]);
			create_delete_query(query);
			break;
		case (4):
			free(query);
			return -1;
		default:
			printf("Wrong input. Try again\n");
			free(query);
			continue;
		}
		if (transaction_mode) {
			string_concat(query, COMMIT);
		}
		rc = sqlite3_exec(db, query, callback, (void*)data, &zErrMsg);
		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
		else {
			printf(stdout, "Operation mode successfully\n");
		}
		free(query);
	}
}