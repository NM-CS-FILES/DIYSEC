#include "../include/api.hpp"
#include <crow/common.h>
#include <crow/json.h>
#include <utility>

//
//
//

crow::SimpleApp API::_restful_app;

//
//
//

void API::initialize() {
    _restful_app.port(8080);

    // GET routes

    // POST routes
    CROW_ROUTE(_restful_app, "/login").methods("POST"_method)(login);
}

template <typename... VarArgs>
crow::response API::error(
    crow::status status,
    const std::string &fmt,
    VarArgs &&...args
) {
    return crow::response(status, crow::json::wvalue({{"message", fmt::format(fmt, std::forward<VarArgs>(args)...)}}));
}

//
//  GET handlers
//

crow::response API::cameras() {
    // if (!Auth::is_token_valid(/*token*/)) {
    //     return error(crow::status::UNAUTHORIZED, "Invalid Token");
    // }

    return crow::response(crow::status::BAD_REQUEST);
}

//
//  POST handlers
//

crow::response API::login(
    const crow::request &req
) {
    // TODO: security: (D)DOS protection

    auto json = crow::json::load(req.body);

    // validate json

    if (!json) {
        return error(crow::status::BAD_REQUEST, "Invalid Data");
    }

    if (!json.has("username")) {
        return error(crow::status::BAD_REQUEST, "Missing Username");
    }

    if (!json.has("password")) {
        return error(crow::status::BAD_REQUEST, "Missing Password");
    }

    auto username_rstr = json["username"].s();
    auto password_rstr = json["password"].s();

    // fetch user information

    auto username = std::string(username_rstr.begin(), username_rstr.end());
    auto password = std::string(password_rstr.begin(), password_rstr.end());

    Database::User user;

    // TODO: security: hashing

    if (!Database::get_user(username, user) || user.password != password) {
        return error(crow::status::UNAUTHORIZED, "Invalid Login Details");
    }

    // generate and send auth token

    return crow::json::wvalue({
        { "authorization", Auth::generate_token() }
    });
}
