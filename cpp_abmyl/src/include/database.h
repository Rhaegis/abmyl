#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>

void initializeDatabase(sqlite3* db);
void associateGameToUser(sqlite3* db, const std::string& userEmail, const std::string& gameName);
void listAssociations(sqlite3* db);
void searchByUser(sqlite3* db, const std::string& userEmail);
void searchByGame(sqlite3* db, const std::string& gameName);

#endif // DATABASE_H
