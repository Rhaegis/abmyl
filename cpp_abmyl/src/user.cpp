#include "user.h"
#include <iostream>

void addUser(sqlite3* db, const std::string& name, const std::string& email) {
    sqlite3_stmt* stmt;
    const char* sql = "INSERT INTO Users (name, email) VALUES (?, ?);";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, email.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Error executing SQL: " << sqlite3_errmsg(db) << std::endl;
        } else {
            std::cout << "User added successfully" << std::endl;
        }
    } else {
        std::cerr << "Failed to prepare SQL statement: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
}

void updateUser(sqlite3* db, int userId, const std::string& name, const std::string& email) {
    sqlite3_stmt* stmt;
    const char* sql = "UPDATE Users SET name = ?, email = ? WHERE id = ?;";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, email.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 3, userId);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Error executing SQL: " << sqlite3_errmsg(db) << std::endl;
        } else {
            std::cout << "User updated successfully" << std::endl;
        }
    } else {
        std::cerr << "Failed to prepare SQL statement: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
}

void deleteUser(sqlite3* db, int userId) {
    sqlite3_stmt* stmt;
    const char* sql = "DELETE FROM Users WHERE id = ?;";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, userId);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Error executing SQL: " << sqlite3_errmsg(db) << std::endl;
        } else {
            std::cout << "User deleted successfully" << std::endl;
        }
    } else {
        std::cerr << "Failed to prepare SQL statement: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
}

void listUsers(sqlite3* db) {
    sqlite3_stmt* stmt;
    const char* sql = "SELECT id, name, email FROM Users;";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const char* name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            const char* email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            std::cout << "ID: " << id << ", Name: " << name << ", Email: " << email << std::endl;
        }
    } else {
        std::cerr << "Failed to prepare SQL statement: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
}
