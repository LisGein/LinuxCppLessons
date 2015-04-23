#pragma once
#include "point_t.h"

struct IConnection
{
  virtual ~IConnection() {}
  virtual bool first_turn() = 0;
  virtual void send_step(point_t const &input_pos) = 0;
  virtual point_t recv_step() = 0;
};
