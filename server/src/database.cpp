#include "../include/database.hpp"
#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/Statement.h>

const char* Database::_sqlite_path = "database.sqlite3";

SQLite::Database Database::_instance = SQLite::Database(
    Database::_sqlite_path, 
    SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE
);

void Database::initialize() {
    _instance.exec("CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT, password TEXT, is_admin INTEGER)");
}

void Database::debug_init_users() {
    SQLite::Statement query(_instance, "SELECT COUNT(*) FROM users WHERE username = \"admin\"");

    if (!query.executeStep()) {
        return;
    }

    int count = query.getColumn(0);

    if (count == 0) {
        _instance.exec("INSERT INTO users (username, password, is_admin) VALUES (\"admin\", \"password\", 1)");
    }
}

bool Database::get_user(
    const std::string& username,
    User& user
) {
    try {
        SQLite::Statement query(_instance, "SELECT * FROM users WHERE username = ?");

        query.bind(1, username);
    
        if (!query.executeStep()) {
            return false;
        }

        user = { 0 };
        user.id = query.getColumn(0);
        user.username = static_cast<const char*>(query.getColumn(1));
        user.password = static_cast<const char*>(query.getColumn(2));
        user.is_admin = query.getColumn(3);

        return true;

    } catch (...) {
        // TODO error handling
        return false;
    }
}