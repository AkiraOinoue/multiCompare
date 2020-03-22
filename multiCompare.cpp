#include "multiCompare.h"
using namespace locallib::Mcomp;
Exception::Exception( const string& msg ):
    message(msg)
    {}
Exception::~Exception() throw()
{
    ;
}
const char* Exception::what() const throw()
{
    return this->message.c_str();
}
