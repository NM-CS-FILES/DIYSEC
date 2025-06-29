#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/SQLiteCpp.h>

#pragma once

class Database {

    /*
     *
     */

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

    static void debug_init_users();

    static bool get_user(
        const std::string& username,
        User& user
    );
};
