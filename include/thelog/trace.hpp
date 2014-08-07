#pragma once

#include <thelog/logger.hpp>

namespace the
{

namespace log
{

class Trace
{
  public:
    Trace( const LogDetails& details, const char* message )
      : m_details( details )
      , m_message( message )
    {
      the::log::Logger::log( m_details, "ENTER", m_message );
    }

    ~Trace()
    {
      the::log::Logger::log( m_details, "LEAVE", m_message );
    }

  private:
    const LogDetails m_details;
    const std::string m_message;
};

}

}

#define thelog_trace( loglevel, message ) the::log::Trace __thelog_trace_iwer92398uweir( { loglevel, __FILE__, __LINE__ }, message );

