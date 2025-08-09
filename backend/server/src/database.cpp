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
    _instance.exec("CREATE TABLE IF NOT EXISTS cameras (id INTEGER PRIMARY KEY, name TEXT)");
}

int Database::user_count() {
    SQLite::Statement query(_instance, "SELECT COUNT(*) FROM users");

    if (!query.executeStep()) {
        return -1;
    }

    return query.getColumn(0);
}

int Database::admin_user_count() {
    SQLite::Statement query(_instance, "SELECT COUNT(*) FROM users WHERE is_admin = 1");

    if (!query.executeStep()) {
        return -1;
    }

    return query.getColumn(0);
}


void Database::add_user(const User& user) {
    SQLite::Statement query(_instance, "INSERT INTO users (username, password, is_admin) VALUES (?, ?, ?)");

    query.bind(1, user.username);
    query.bind(2, user.password);
    query.bind(3, user.is_admin);

    query.exec();
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