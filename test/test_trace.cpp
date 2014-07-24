#include <thelog/trace.hpp>
#include <thelog/logger.hpp>
#include <igloo/igloo_alt.h>
using namespace igloo;

namespace
{

  void traced_function( std::function<void()> checker )
  {
    thelog_trace( 10 );
    checker();
  }

}

Describe( a_trace )
{
  void SetUp()
  {
    the::log::Logger::drop_channels();
    the::log::Logger::set_loglevel( 0 );
    log_stream.str( "" );
    the::log::Logger::add_channel( log_stream );
  }

  It( logs_ENTER_when_entering_the_function )
  {
    traced_function(
        [ this ]()
        {
          AssertThat( log_stream.str(), Contains( "ENTER" ) );
        } );
  }

  It( logs_LEAVE_when_leaving_the_function )
  {
    traced_function(
        [ this ]()
        {
          AssertThat( log_stream.str(), Is().Not().Containing( "LEAVE" ) );
        } );
    AssertThat( log_stream.str(), Contains( "LEAVE" ) );
  }

  std::stringstream log_stream;
};

