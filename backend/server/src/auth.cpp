#include "../include/auth.hpp"

//
//

Auth::token_set Auth::_token_set = { };

//
//

std::string Auth::generate_token() {
    static const char chars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890";
    std::string token(20, ' ');

    for (size_t i = 0; i != token.size(); i++) {
        token[i] = chars[rand() % sizeof(chars)];
    }

    _token_set.insert(token);

    return token;
}


bool Auth::is_token_valid(
    const std::string& token
) {
    auto iter = _token_set.find(token);

    if (iter == _token_set.end()) {
        return false;
    }

    return true;
}