#pragma once

#include <thelog/logger.hpp>

namespace the
{

namespace log
{

class Trace
{
  public:
    Trace( const LogDetails& details )
      : m_details( details )
    {
      the::log::Logger::log( m_details, "ENTER" );
    }

    ~Trace()
    {
      the::log::Logger::log( m_details, "LEAVE" );
    }

  private:
    LogDetails m_details;
};

}

}

#define thelog_trace( loglevel ) the::log::Trace __thelog_trace_iwer92398uweir( { loglevel, __FILE__, __LINE__ } );

