//
// created by Pavel Kosteckij 26.03.2023
//

#ifndef DBPROJECT_TASK6_STRUCTURES_H
#define DBPROJECT_TASK6_STRUCTURES_H

extern enum Menu {
	SELECT = 0,
	INSERT = 1,
	DELETE = 2,
	WHERE = 3,
	END_INSERT = 21
};

extern enum Columns {
	ID = 4,
	LASTNAME = 5,
	FIRSTNAME = 6,
	SURNAME = 7,
	ADDRESS = 8,
	NATIONALITY = 9,
	BIRTHDAY = 10,
	ACCOUNT_NUMBER = 11,
	EDUCATION = 12,
	YEAR_OF_EMPLOYMENT = 13,
	SALARY = 14,
	DEPARTMENT_ID = 15,
	PHOTO = 16,
	END = 17,
	BEGIN_TRANSACTION = 18,
	COMMIT = 19,
	LIKE = 19,
	STR_NULL = 22,
	COMMA = 23
};

char* query_parts[] = { "SELECT * From Workers","INSERT INTO Workers(id, first_name, last_name,surname, address, nationality, birthday, account_number, education, year_of_employment, salary, department_id, photo)","Delete * From Workers", "WHERE", "id", "first_name", "last_name", "surname", "address", "nationality", "birthday", "account_number", "education", "year_of_employment", "salary", "department_id", "photo", ";", "BEGIN TRANSACTION", "COMMIT", "LIKE", ");","null", ","};

#endif //DBPROJECT_TASK6_STRUCTURES_H