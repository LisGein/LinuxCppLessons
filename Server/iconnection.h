#pragma once
#include "point_t.h"

struct IConnection
{

public:
  IConnection();
  ~IConnection();
  virtual bool first_step();
  virtual void send_step();
  virtual point_t revc_step();
private:
   Point_t point_t;
};

