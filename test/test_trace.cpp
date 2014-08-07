#include <thelog/trace.hpp>
#include <thelog/logger.hpp>
#include <igloo/igloo_alt.h>
using namespace igloo;

namespace
{
  const char* test_string = "some string";

  void traced_function( std::function<void()> checker )
  {
    thelog_trace( 10, test_string );
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

  It( logs_an_additional_string_along_with_enter_and_leave )
  {
    traced_function(
        [ this ]()
        {
          AssertThat( log_stream.str(), Is().Containing( test_string ) );
          log_stream.str( "" );
        } );
    AssertThat( log_stream.str(), Contains( test_string ) );
  }

  std::stringstream log_stream;
};

