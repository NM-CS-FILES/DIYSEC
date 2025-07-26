#include "../include/message.hpp"

Message::Message(
    Type t
) : _type(NUL) {
    convert(t);   
}

void Message::convert(Type t) {
    nullify();

    _type = t;

    switch (_type) {
        case FRAME:
            _data.frame = new Frame{ 0 };
            break;

        case AUTH:
            _data.auth = new Auth{ 0 };
            break;

        case STATUS:
            _data.status = new Status{ 0 };
            break;
    
        case BEACON:
            _data.beacon = new Beacon{ 0 };
            break;

        case NUL:
            _data = { 0 };
            break;
    }
}

//
//

Message::Message(
    const Message& msg
) : Message(msg._type) {
    switch (_type) {
        case FRAME:
            *_data.frame = *msg._data.frame;
            break;

        case AUTH:
            *_data.auth = *msg._data.auth;
            break;

        case STATUS:
            *_data.status = *msg._data.status;
            break;
    
        case BEACON:
            *_data.beacon = *msg._data.beacon;
            break;
    }
}

Message::Message(
    Message&& msg
) : _type(msg._type), _data(msg._data) {
    msg._type = NUL;
    msg._data = { 0 };
}

Message::~Message() {
    nullify();
}

//
//

void Message::nullify() {
    switch (_type) {
        case NUL:
            return;

        case FRAME:
            delete _data.frame;
            break;

        case AUTH:
            delete _data.auth;
            break;

        case STATUS:
            delete _data.status;
            break;
    
        case BEACON:
            delete _data.beacon;
            break;
    }

    _type = NUL;
}

//
//

Message& Message::operator=(
    const Message& msg
) {
    convert(msg._type);

    switch (_type) {
        case FRAME:
            *_data.frame = *msg._data.frame;
            break;

        case AUTH:
            *_data.auth = *msg._data.auth;
            break;

        case STATUS:
            *_data.status = *msg._data.status;
            break;
    
        case BEACON:
            *_data.beacon = *msg._data.beacon;
            break;
    }

    return *this;
}

//
//

Message Message::make_frame(
    const std::string& camera_id,
    const cv::Mat& frame
) {
    Message msg(FRAME);

    std::vector<uint8_t> frame_buf;
    cv::imencode(".jpg", frame, frame_buf);

    msg._data.frame->camera_id = camera_id;
    msg._data.frame->frame = cppcodec::base64_rfc4648::encode(frame_buf.data(), frame_buf.size());

    return msg;
}

Message Message::make_auth(
    const std::string& auth
) {
    Message msg(AUTH);

    msg._data.auth->token = auth;

    return msg;
}

Message Message::make_status(
    const std::string& error
) {
    Message msg(STATUS);

    msg._data.status->ok = (error.empty());
    msg._data.status->error = error;

    return msg;
}

Message Message::make_beacon(
    const std::string& address,
    uint16_t port
) {
    Message msg(BEACON);

    msg._data.beacon->addr = address;
    msg._data.beacon->port = port;

    return msg;
}

//
//

bool Message::deserialize(
    const std::string& in,
    Message& out
) {
    using namespace nlohmann;

    json doc = json::parse(in);

    if (!doc.contains("type") || !doc.contains("data") || !doc["type"].is_string()) {
        return false;
    }

    std::string type = doc["type"];

    if (type == "null") {
        out = Message(NUL);
        return true;
    }

    if (!doc["data"].is_object()) {
        return false;
    }

    // TODO: case insensitive comparisons?
    if (type == "null") {
        out = Message(NUL);
    }
    else if (type == "frame") {
        if (!doc["data"].contains("camera_id") || !doc["data"].contains("frame")
            || !doc["data"]["camera_id"].is_string() || !doc["data"]["frame"].is_string()) {
            return false;
        }

        out.convert(FRAME);
        out._data.frame->camera_id = doc["data"]["camera_id"];
        out._data.frame->frame = doc["data"]["frame"];
    }
    else if (type == "auth") {
        if (!doc["data"].contains("token") || !doc["data"]["token"].is_string()) {
            return false;
        }

        out.convert(AUTH);
        out._data.auth->token = doc["data"]["token"];
    }
    else if (type == "status") {
        if (!doc["data"].contains("ok") || !doc.contains("error")
            || !doc["data"]["ok"].is_boolean() || !doc["data"]["error"].is_string()) {
            return false;
        }

        out.convert(STATUS);
        out._data.status->ok = doc["data"]["ok"];
        out._data.status->error = doc["data"]["error"];
    }
    else if (type == "beacon") {
        if (!doc["data"].contains("addr") || !doc["data"].contains("port")
            || !doc["data"]["addr"].is_string() || !doc["data"]["port"].is_number_integer()) {
            return false;
        }

        out.convert(BEACON);
        out._data.beacon->addr = doc["data"]["addr"];
        out._data.beacon->port = doc["data"]["port"];
    }

    return true;
}

bool Message::serialize(
    const Message& in,
    std::string& out
) {
    using namespace nlohmann;

    json doc;

    // Type

    std::string type = nullptr;

    switch (in._type) {
        case NUL:    type = "null";   break;
        case FRAME:  type = "frame";  break;
        case AUTH:   type = "auth";   break;
        case STATUS: type = "status"; break;
        case BEACON: type = "beacon"; break;
    }

    doc["type"] = type;

    // Data

    switch (in._type) {
        case NUL:
            doc["data"] = nullptr;    
            break;

        case FRAME:
            doc["data"]["camera_id"] = in.frame()->camera_id;
            doc["data"]["frame"] = in.frame()->frame;
            break;

        case AUTH:
            doc["data"]["token"] = in.auth()->token;
            break;

        case STATUS:
            doc["data"]["ok"] = in.status()->ok;
            doc["data"]["error"] = in.status()->error;
            break;

        case BEACON:
            doc["data"]["addr"] = in.beacon()->addr;
            doc["data"]["port"] = in.beacon()->port;
            break;
    }

    // stringify DOM

    out = doc.dump();

    return true;
}