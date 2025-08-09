#include <unordered_set>
#include <string>
#include <list>
#include <ctime>

#pragma once

class Auth {

    using token_set = std::unordered_set<std::string, std::pair<User, time_t>>;

    static token_set _token_set;

public:

    static std::string generate_token();

    static bool is_token_valid(
        const std::string& token
    );

};