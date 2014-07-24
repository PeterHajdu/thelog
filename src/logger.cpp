#include <thelog/logger.hpp>
#include <memory>
#include <ctime>

namespace
{
  std::unique_ptr< the::log::Logger > logger_instance;

  std::string local_time_in_string_format()
  {
    std::time_t t( std::time( nullptr ) );
    char buffer[ 100 ];
    std::strftime( buffer, sizeof( buffer ), "%Y-%m-%d %X", std::localtime( &t ) );
    return buffer;
  }
}

namespace the
{
namespace log
{

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

AutoLogger
Logger::log( int loglevel )
{
  Logger& logger( instance() );
  return AutoLogger(
      loglevel < logger.m_loglevel ?
      logger.m_no_channels :
      instance().m_channels );
}


AutoLogger::AutoLogger( const ChannelContainer& channels )
  : m_channels( channels )
{
}

  AutoLogger::AutoLogger( const AutoLogger& other )
  : m_channels( other.m_channels )
{
}

std::stringstream&
AutoLogger::stream()
{
  return m_stream;
}

AutoLogger::~AutoLogger()
{
  const std::string time( local_time_in_string_format() );
  for ( auto& channel : m_channels )
  {
    channel.get() << time << " " << m_stream.str() << std::endl;
  }
}

}
}

