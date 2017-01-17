#include "runtimeerror.h"

RunTimeError::RunTimeError(const std::string& what_arg, const std::string& message)
   : std::runtime_error(what_arg)
   , arg_(what_arg)
   , message_(message)
{

}

std::string RunTimeError::arg() const
{
   return arg_;
}

std::string RunTimeError::message() const
{
   return message_;
}
