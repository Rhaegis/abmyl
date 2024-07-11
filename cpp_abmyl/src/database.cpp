#include "database.h"
#include <iostream>

void initializeDatabase(sqlite3* db) {
    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS Users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            email TEXT UNIQUE NOT NULL
        );
        CREATE TABLE IF NOT EXISTS Games (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT UNIQUE NOT NULL
        );
        CREATE TABLE IF NOT EXISTS Users_Games (
            user_id INTEGER,
            game_id INTEGER,
            FOREIGN KEY(user_id) REFERENCES Users(id),
            FOREIGN KEY(game_id) REFERENCES Games(id),
            PRIMARY KEY(user_id, game_id)
        );
    )";

    char* errMsg = 0;
    if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
        std::cerr << "Error initializing database: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

void associateGameToUser(sqlite3* db, const std::string& userEmail, const std::string& gameName) {
    sqlite3_stmt* stmt;
    const char* findUserId = "SELECT id FROM Users WHERE email = ?;";
    const char* findGameId = "SELECT id FROM Games WHERE name = ?;";
    int userId, gameId;

    if (sqlite3_prepare_v2(db, findUserId, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, userEmail.c_str(), -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            userId = sqlite3_column_int(stmt, 0);
        } else {
            std::cerr << "User not found" << std::endl;
            sqlite3_finalize(stmt);
            return;
        }
    } else {
        std::cerr << "Failed to prepare SQL statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return;
    }
    sqlite3_finalize(stmt);

    if (sqlite3_prepare_v2(db, findGameId, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, gameName.c_str(), -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            gameId = sqlite3_column_int(stmt, 0);
        } else {
            std::cerr << "Game not found" << std::endl;
            sqlite3_finalize(stmt);
            return;
        }
    } else {
        std::cerr << "Failed to prepare SQL statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return;
    }
    sqlite3_finalize(stmt);

    const char* insertAssoc = "INSERT INTO Users_Games (user_id, game_id) VALUES (?, ?);";
    if (sqlite3_prepare_v2(db, insertAssoc, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, userId);
        sqlite3_bind_int(stmt, 2, gameId);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Error executing SQL: " << sqlite3_errmsg(db) << std::endl;
        } else {
            std::cout << "Association added successfully" << std::endl;
        }
    } else {
        std::cerr << "Failed to prepare SQL statement: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
}

void listAssociations(sqlite3* db) {
    sqlite3_stmt* stmt;
    const char* sql = R"(
        SELECT Users.name, Users.email, Games.name
        FROM Users
        JOIN Users_Games ON Users.id = Users_Games.user_id
        JOIN Games ON Games.id = Users_Games.game_id;
    )";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            const char* userName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            const char* userEmail = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            const char* gameName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            std::cout << "User: " << userName << ", Email: " << userEmail << ", Game: " << gameName << std::endl;
        }
    } else {
        std::cerr << "Failed to prepare SQL statement: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
}

void searchByUser(sqlite3* db, const std::string& userEmail) {
    sqlite3_stmt* stmt;
    const char* sql = R"(
        SELECT Users.name, Users.email, Games.name
        FROM Users
        JOIN Users_Games ON Users.id = Users_Games.user_id
        JOIN Games ON Games.id = Users_Games.game_id
        WHERE Users.email = ?;
    )";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, userEmail.c_str(), -1, SQLITE_STATIC);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            const char* userName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            const char* gameName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            std::cout << "User: " << userName << ", Email: " << userEmail << ", Game: " << gameName << std::endl;
        }
    } else {
        std::cerr << "Failed to prepare SQL statement: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
}

void searchByGame(sqlite3* db, const std::string& gameName) {
    sqlite3_stmt* stmt;
    const char* sql = R"(
        SELECT Users.name, Users.email, Games.name
        FROM Users
        JOIN Users_Games ON Users.id = Users_Games.user_id
        JOIN Games ON Games.id = Users_Games.game_id
        WHERE Games.name = ?;
    )";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, gameName.c_str(), -1, SQLITE_STATIC);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            const char* userName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            const char* userEmail = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            std::cout << "User: " << userName << ", Email: " << userEmail << ", Game: " << gameName << std::endl;
        }
    } else {
        std::cerr << "Failed to prepare SQL statement: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
}
