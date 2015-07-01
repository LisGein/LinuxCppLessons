#pragma once
#include "point_t.h"

struct BaseConnection
{
    virtual ~BaseConnection() {}
    virtual bool first_turn() = 0;
    void send_step(point_t const &pos) ;
    point_t recv_step();

protected:
    int sock_;
};
