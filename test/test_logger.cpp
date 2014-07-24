#include <thelog/logger.hpp>
#include <igloo/igloo_alt.h>
using namespace igloo;

/*
 * Do not edit the first part of the file. If line numbers get modified before the thelog() call
 * line number tests are going to fail.
 */

Describe( a_logger )
{
  void SetUp()
  {
    the::log::Logger::drop_channels();
    log_stream.str( "" );
    second_log_stream.str( "" );
    the::log::Logger::add_channel( log_stream );
    the::log::Logger::add_channel( second_log_stream );
    thelog( 1 ) << log_message;
  }

  It( logs_messages )
  {
    AssertThat( log_stream.str(), Contains( log_message ) );
  }

  It( logs_messages_to_all_registered_channels )
  {
    AssertThat( log_stream.str(), Contains( log_message ) );
    AssertThat( second_log_stream.str(), Contains( log_message ) );
  }

  It( logs_the_file_name )
  {
    AssertThat( log_stream.str(), Contains( "test_logger.cpp" ) );
  }

  It( logs_the_line_number_in_vim_format )
  {
    AssertThat( log_stream.str(), Contains( "+19" ) );
    std::cout << log_stream.str() << std::endl;
  }

  const std::string log_message{ "some log message" };
  std::stringstream log_stream;
  std::stringstream second_log_stream;
};
