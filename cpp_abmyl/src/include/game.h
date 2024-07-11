#ifndef GAME_H
#define GAME_H

#include <sqlite3.h>
#include <string>

void addGame(sqlite3* db, const std::string& name);
void updateGame(sqlite3* db, int gameId, const std::string& name);
void deleteGame(sqlite3* db, int gameId);
void listGames(sqlite3* db);

#endif // GAME_H
