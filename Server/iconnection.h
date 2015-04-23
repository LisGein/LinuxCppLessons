#pragma once
#include "point_t.h"

struct IConnection
{

public:
  virtual ~IConnection(){};
  virtual bool first_step() = 0;
  virtual void send_step(point_t const & pos) = 0;
  virtual point_t revc_step() = 0;
};

