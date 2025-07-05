#include "../include/api.hpp"
#include <crow/common.h>
#include <crow/json.h>
#include <utility>

//
//
//

crow::SimpleApp API::_restful_app;
std::unordered_map<crow::websocket::connection*, bool> API::_streamers;

//
//
//

void API::initialize() {
    _restful_app.port(8888);

    // Websocket routes

    CROW_ROUTE(_restful_app, "/wss/stream")
        .websocket(&_restful_app)
        .onopen(stream_onopen)
        .onmessage(stream_onmessage)
        .onclose(stream_onclose);

    CROW_ROUTE(_restful_app, "/wss/camera")
        .websocket(&_restful_app)
        .onopen(camera_onopen)
        .onmessage(camera_onmessage);

    // GET routes

    CROW_ROUTE(_restful_app, "/api/cameras")(cameras);
    //CROW_ROUTE(_restful_app, "/api/")

    // POST routes

    CROW_ROUTE(_restful_app, "/api/login").methods("POST"_method)(login);
}

bool API::is_request_authorized(
    const crow::request& req
) {
    auto iter = req.headers.find("Authorization");
    return !(iter == req.headers.end() || !Auth::is_token_valid(iter->second));
}

//
//
//

template <typename... VarArgs>
crow::response API::error(
    crow::status status,
    const std::string &fmt,
    VarArgs &&...args
) {
    return crow::response(status, crow::json::wvalue({{"message", fmt::format(fmt, std::forward<VarArgs>(args)...)}}));
}

//
//  WSS
//

void API::stream_onopen(
    crow::websocket::connection& conn
) {
    CROW_LOG_INFO << "Streamer Connected: " << conn.get_remote_ip();
    _streamers.insert(std::make_pair(&conn, false));
}

void API::stream_onmessage(
    crow::websocket::connection& conn,
    const std::string& data,
    bool is_binary
) {
    if (!is_binary) {
        CROW_LOG_ERROR << "Recieved Non Binary Stream Message";
        return;
    }

    // TODO: fix potential buffer overread

    const Message* pmsg = reinterpret_cast<const Message*>(data.data());

    if (pmsg->type != MSG_TYPE_AUTH) {
        CROW_LOG_ERROR << "Recieved Non Auth Message";
        return;
    }

    std::string token(
        pmsg->data.auth_msg.token,
        pmsg->data.auth_msg.token_len 
    );

    if (!Auth::is_token_valid(token)) {
        // TODO: tell streamer they're unauthorized
        conn.close();
        return;
    }

    _streamers[&conn] = true;
}

void API::stream_onclose(
    crow::websocket::connection& conn, 
    const std::string& reason,
    uint16_t with_status_code
) {
    CROW_LOG_INFO << "Streamer Disconnected: " << conn.get_remote_ip() << " Reason: " << reason;
    _streamers.erase(&conn);
}

void API::camera_onopen(
    crow::websocket::connection& conn
) {
    CROW_LOG_INFO << "Camera Connected: " << conn.get_remote_ip();
}

void API::camera_onmessage(
    crow::websocket::connection& conn,
    const std::string& data,
    bool is_binary
) {
    if (!is_binary) {
        CROW_LOG_ERROR << "Recieved Non Binary Camera Message";
        return;
    }

    const FrameMessage* pmsg = reinterpret_cast<const FrameMessage*>(data.data());

    Camera* pcam = CameraManager::get_camera(pmsg->camera_id);

    if (pcam == nullptr) {
        CROW_LOG_ERROR << "Recieved Camera Message For Nonexistant Camera Id: " << pmsg->camera_id;
        return;
    }

    pcam->update_frame(pmsg->frame, pmsg->frame + pmsg->frame_len);

    for (auto entry : _streamers) {
        // is authorized
        if (entry.second) {
            entry.first->send_binary(data);
        }
    }
}

//
//  GET handlers
//

crow::response API::cameras(
    const crow::request& req
) {
    if (!is_request_authorized(req)) {
        return error(crow::status::UNAUTHORIZED, "Invalid Token");
    }

    auto camera_ids = CameraManager::camera_ids();

    return crow::json::wvalue({
        { "camera_ids", crow::json::wvalue::list(camera_ids.begin(), camera_ids.end()) } 
    });
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
        { "Authorization", Auth::generate_token() }
    });
}
