#include <unordered_map>
#include <string>
#include <list>
#include <ctime>

#pragma once

class Auth {

    using token_map_t = std::unordered_map<std::string, time_t>;

    static time_t _last_prune;

    static token_map_t _token_map;

public:

    static void prune();

    static std::string generate_token();

    static bool is_token_valid(
        const std::string& token
    );

};