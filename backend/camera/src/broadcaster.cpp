#include "../include/broadcaster.hpp"

//
//

int Broadcaster::_broadcast_fd = -1;

uint16_t Broadcaster::_broadcast_port = 6666;

sockaddr_in Broadcaster::_broadcast_addr = { 0 };

time_t Broadcaster::_last_broadcast = 0;

//
//

bool Broadcaster::initialize() {
    _broadcast_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (_broadcast_fd == -1) {
        return false;
    }

    int broadcast = 1;
    
    if (setsockopt(_broadcast_fd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(int)) == -1) {
        return false;
    }

    _broadcast_addr.sin_family = AF_INET;
    _broadcast_addr.sin_port = htons(_broadcast_port);
    _broadcast_addr.sin_addr.s_addr = INADDR_BROADCAST;

    return true;
}

time_t Broadcaster::dtime() {
    return time(nullptr) - _last_broadcast;
}

void Broadcaster::broadcast() {
    _last_broadcast = time(nullptr);

    //ssize_t result = sendto(_broadcast_fd, )
}