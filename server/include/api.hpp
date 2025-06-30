#include <crow.h>
#include <crow/app.h>
#include <crow/common.h>
#include <crow/logging.h>
#include <ctime>
#include <unordered_map>
#include <list>
#include <tuple>
#include <fmt/core.h>
#include "auth.hpp"
#include "database.hpp"
#include "camera.hpp"

#pragma once

class API {
public:

    static crow::SimpleApp _restful_app;
    static std::list<crow::websocket::connection*> _streamers;
    static bool _is_initd;

public:

    static void initialize();

    //
    //  Responses
    //

    template<typename ...VarArgs>
    static crow::response error(
        crow::status status,
        const std::string& fmt,
        VarArgs&& ...args
    );

    //
    //  GET handlers
    //

    static crow::response cameras(
        const crow::request& req
    );

    //
    //  POST handlers
    //

    static crow::response login(
        const crow::request& req
    );
};
