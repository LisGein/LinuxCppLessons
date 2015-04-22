#include "iconnection.h"


IConnection::IConnection(){}
IConnection::~IConnection(){}
virtual bool IConnection::first_step() = 0;
virtual void IConnection::send_step()= 0;
virtual point_t IConnection::revc_step()= 0;
