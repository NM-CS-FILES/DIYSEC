#include <crow/app.h>
#include <iostream>
#include <cstdio>
#include <crow.h>
#include "../include/uuid.hpp"
#include "../include/database.hpp"
#include "../include/api.hpp"

void initialize() {
    Database::initialize();
    API::initialize();
}

int main() {
    initialize();

    Database::User user;
    //std::cout << Database::get_user("admin", user) << std::endl;
    //std::cout << user.password << std::endl;

    API::_restful_app.run();
}
