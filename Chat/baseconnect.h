#pragma once

struct BaseConnection
{
    virtual ~BaseConnection() {}
    virtual void step() = 0;

protected:
    int sock_;
};
