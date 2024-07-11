#include <iostream>
#include <sqlite3.h>
#include "database.h"
#include "user.h"
#include "game.h"

int main() {
    sqlite3* db;
    int rc = sqlite3_open("example.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return 0;
    } else {
        std::cout << "Opened database successfully" << std::endl;
    }

    initializeDatabase(db);

    // Llamadas de prueba a las funciones CRUD y de asociación
    addUser(db, "John Doe", "john@example.com");
    addGame(db, "Game 1");
    associateGameToUser(db, "john@example.com", "Game 1");

    listUsers(db);
    listGames(db);
    listAssociations(db);
    searchByUser(db, "john@example.com");
    searchByGame(db, "Game 1");

    sqlite3_close(db);
    return 0;
}
