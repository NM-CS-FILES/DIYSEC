#include "../include/auth.hpp"

//
//
//

time_t Auth::_last_prune = 0;

Auth::token_map_t Auth::_token_map = { };

//
//
//

void Auth::prune() {
    time_t now = time(nullptr);

    auto iter = _token_map.begin();

    while (iter != _token_map.end()) {

        auto next = std::next(iter);

        if (now >= iter->second) {
            _token_map.erase(iter);
        } 

        iter = next;
    }

    _last_prune = now;
}


std::string Auth::generate_token() {
    static const char chars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890";
    std::string token(20, ' ');

    for (size_t i = 0; i != token.size(); i++) {
        token[i] = chars[rand() % sizeof(chars)];
    }

    // 30 min from now
    _token_map[token] = time(nullptr) + (30 * 60); 

    return token;
}


bool Auth::is_token_valid(
    const std::string& token
) {
    time_t now = time(nullptr);

    // prune every 3 minutes
    if (now - _last_prune > (3 * 60)) {
        prune();
    }

    auto iter = _token_map.find(token);

    if (iter == _token_map.end()) {
        return false;
    }

    if (now >= iter->second) {
        return false;
    }

    return true;
}