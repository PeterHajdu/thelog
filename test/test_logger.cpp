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
    the::log::Logger::set_loglevel( 0 );
    log_stream.str( "" );
    second_log_stream.str( "" );
    the::log::Logger::add_channel( log_stream );
    the::log::Logger::add_channel( second_log_stream );
    thelog( 1 )( log_message );
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

  It( cuts_off_full_path_and_keeps_only_the_filename )
  {
    AssertThat( log_stream.str(), Contains( " test_logger.cpp +" ) );
  }

  It( logs_the_line_number_in_vim_format )
  {
    AssertThat( log_stream.str(), Contains( "+20" ) );
  }

  It( should_not_log_messages_under_the_loglevel )
  {
    thelog( lower_loglevel )( another_log_message );
    AssertThat( log_stream.str(), Is().Not().Containing( another_log_message ) );
  }

  It( should_set_loglevels_runtime )
  {
    the::log::Logger::set_loglevel( lower_loglevel );
    thelog( lower_loglevel )( another_log_message );
    AssertThat( log_stream.str(), Contains( another_log_message ) );
  }

  It( can_log_containers )
  {
    std::vector< int > int_container{ 10, 123 };
    thelog( 1 )( int_container );
    AssertThat( log_stream.str(), Contains( "10" ) );
    AssertThat( log_stream.str(), Contains( "123" ) );
  }

  const int lower_loglevel{ -10 };
  const std::string log_message{ "some log message" };
  const std::string another_log_message{ "some other log message" };
  std::stringstream log_stream;
  std::stringstream second_log_stream;
};

