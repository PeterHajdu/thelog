#include <thelog/logger.hpp>
#include <memory>
#include <ctime>
#include <iostream>

namespace
{
  std::unique_ptr< the::log::Logger > logger_instance;
}

namespace the
{
namespace log
{


std::string
trim_file_name( std::string&& filename )
{
  const std::size_t slash_position( filename.find_last_of( "/\\" ) );
  if ( slash_position != std::string::npos )
  {
    filename = filename.substr( slash_position + 1 );
  }

  return filename;
}


std::ostream&
operator<<( std::ostream& output, const LogDetails& details )
{
  output << details.file << " +" << details.line;
  return output;
}

std::string local_time_in_string_format()
{
  std::time_t t( std::time( nullptr ) );
  char buffer[ 100 ];
  std::strftime( buffer, sizeof( buffer ), "%Y-%m-%d %X", std::localtime( &t ) );
  return buffer;
}

Logger&
Logger::instance()
{
  if ( !logger_instance )
  {
    logger_instance.reset( new Logger() );
    logger_instance->add_channel( std::cout );
  }

  return *logger_instance;
}


void
Logger::add_channel( std::ostream& stream )
{
  instance().m_channels.emplace_back( stream );
}

void
Logger::set_loglevel( int loglevel )
{
  instance().m_loglevel = loglevel;
}

void
Logger::drop_channels()
{
  instance().m_channels.clear();
}


AutoLogger::AutoLogger( const LogDetails& details )
  : m_details( details )
{
}


AutoLogger::~AutoLogger()
{
}

}
}

