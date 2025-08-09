#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/SQLiteCpp.h>

#pragma once

class Database {

    static const char* _sqlite_path;
    static SQLite::Database _instance;

public:
    struct User {
        int id;
        std::string username;
        std::string password;
        int is_admin;
    };

    static void initialize();

    static int user_count();

    static int admin_user_count();

    static void add_user(const User& user);

    static bool get_user(
        const std::string& username,
        User& user
    );
};
