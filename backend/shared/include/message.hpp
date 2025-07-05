#include <cstdint>
#include <string>
#include <strings.h>

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include <opencv2/opencv.hpp>
#include <cppcodec/base64_rfc4648.hpp>

#pragma once

/*
{
    "type": "...",
    "data": {
        "camera_id": "...",
        "frame": "ABCEF..."
    }
}
*/

class Message {
public:
    struct Frame {
        std::string camera_id;
        std::string frame;
    };

    struct Auth {
        std::string token;
    };

    struct Status {
        bool ok;
        std::string error;
    };

    struct Beacon {
        std::string addr;
        uint16_t port;
    };
    
private:
    enum Type {
        NUL,
        FRAME,
        AUTH,
        STATUS,
        BEACON
    };

    Type _type;

    union {
        Frame* frame;
        Auth* auth;
        Status* status;
        Beacon* beacon;
    } _data;

    Message(
        Type t
    );

    void convert(Type t);

public:

    Message(
        const Message& msg
    );

    Message(
        Message&& msg
    );

    ~Message();

    //
    //

    void nullify();

    //
    //

    inline bool is_null()   const { return _type == NUL;    }
    inline bool is_frame()  const { return _type == FRAME;  }
    inline bool is_auth()   const { return _type == AUTH;   }
    inline bool is_status() const { return _type == STATUS; }
    inline bool is_beacon() const { return _type == BEACON; }

    //
    //

    // TODO: error handling
    inline const auto& frame()  const { return _data.frame;  }
    inline const auto& auth()   const { return _data.auth;   }
    inline const auto& status() const { return _data.status; }
    inline const auto& beacon() const { return _data.beacon; }

    //
    //

    Message& operator=(
        const Message& msg
    );

    //
    //

    static Message make_frame(
        const std::string& camera_id,
        const cv::Mat& frame
    );

    static Message make_auth(
        const std::string& auth
    );
    
    static Message make_status(
        const std::string& error = "" // default no error
    );
    
    static Message make_beacon(
        const std::string& address,
        uint16_t port
    );

    //
    //

    static bool deserialize(
        const std::string& in,
        Message& out
    );

    static bool serialize(
        const Message& in,
        std::string& out
    );
};