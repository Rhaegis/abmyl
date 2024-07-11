#ifndef USER_H
#define USER_H

#include <sqlite3.h>
#include <string>

void addUser(sqlite3* db, const std::string& name, const std::string& email);
void updateUser(sqlite3* db, int userId, const std::string& name, const std::string& email);
void deleteUser(sqlite3* db, int userId);
void listUsers(sqlite3* db);

#endif // USER_H
