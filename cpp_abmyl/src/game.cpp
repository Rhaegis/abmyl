#include "game.h"
#include <iostream>

void addGame(sqlite3* db, const std::string& name) {
    sqlite3_stmt* stmt;
    const char* sql = "INSERT INTO Games (name) VALUES (?);";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Error executing SQL: " << sqlite3_errmsg(db) << std::endl;
        } else {
            std::cout << "Game added successfully" << std::endl;
        }
    } else {
        std::cerr << "Failed to prepare SQL statement: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
}

void updateGame(sqlite3* db, int gameId, const std::string& name) {
    sqlite3_stmt* stmt;
    const char* sql = "UPDATE Games SET name = ? WHERE id = ?;";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, gameId);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Error executing SQL: " << sqlite3_errmsg(db) << std::endl;
        } else {
            std::cout << "Game updated successfully" << std::endl;
        }
    } else {
        std::cerr << "Failed to prepare SQL statement: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
}

void deleteGame(sqlite3* db, int gameId) {
    sqlite3_stmt* stmt;
    const char* sql = "DELETE FROM Games WHERE id = ?;";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, gameId);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Error executing SQL: " << sqlite3_errmsg(db) << std::endl;
        } else {
            std::cout << "Game deleted successfully" << std::endl;
        }
    } else {
        std::cerr << "Failed to prepare SQL statement: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
}

void listGames(sqlite3* db) {
    sqlite3_stmt* stmt;
    const char* sql = "SELECT id, name FROM Games;";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const char* name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            std::cout << "ID: " << id << ", Name: " << name << std::endl;
        }
    } else {
        std::cerr << "Failed to prepare SQL statement: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
}
