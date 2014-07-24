#include <thelog/logger.hpp>
#include <memory>
#include <ctime>

namespace
{
  std::unique_ptr< the::log::Logger > logger_instance;
}

namespace the
{
namespace log
{

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

