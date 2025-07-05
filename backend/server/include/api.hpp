#include <crow.h>
#include <crow/app.h>
#include <crow/common.h>
#include <crow/logging.h>
#include <ctime>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <tuple>
#include <fmt/core.h>
#include "auth.hpp"
#include "database.hpp"
#include "camera.hpp"
#include "message.hpp"

#pragma once

class API {
public: // TODO: REMOVE!!!

    static crow::SimpleApp _restful_app;
    static std::unordered_map<crow::websocket::connection*, bool> _streamers;
    static bool _is_initd;

public:

    static void initialize();

    static bool is_request_authorized(
        const crow::request& req
    );

    //
    //  Web Sockets
    //

    static void stream_onopen(
        crow::websocket::connection& conn
    );

    static void stream_onmessage(
        crow::websocket::connection& conn,
        const std::string& data,
        bool is_binary
    );

    static void stream_onclose(
        crow::websocket::connection& conn, 
        const std::string& reason,
        uint16_t with_status_code
    );

    static void camera_onopen(
        crow::websocket::connection& conn
    );

    static void camera_onmessage(
        crow::websocket::connection& conn,
        const std::string& data,
        bool is_binary
    );

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
