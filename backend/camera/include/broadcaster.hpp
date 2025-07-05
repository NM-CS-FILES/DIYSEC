#include <ctime>

#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#pragma once

class Broadcaster {

    static int _broadcast_fd;
    static uint16_t _broadcast_port;
    static sockaddr_in _broadcast_addr;
    static time_t _last_broadcast;

public:

    static bool initialize();    

    static time_t dtime();

    static void broadcast();

};