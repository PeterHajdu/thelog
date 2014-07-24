#include <thelog/logger.hpp>
#include <memory>
#include <iomanip>
#include <chrono>

namespace
{
  std::unique_ptr< the::log::Logger > logger_instance;

  std::stringstream local_time_in_string_format()
  {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    return ss;
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
Logger::drop_channels()
{
  instance().m_channels.clear();
}

AutoLogger
Logger::log()
{
  return AutoLogger( instance().m_channels );
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
  std::string time( local_time_in_string_format().str() );
  for ( auto& channel : m_channels )
  {
    channel.get() << time << " " << m_stream.str() << std::endl;
  }
}

}
}

