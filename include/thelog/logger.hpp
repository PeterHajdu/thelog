#pragma once
#include <ostream>
#include <vector>
#include <functional>
#include <sstream>

namespace the
{

namespace log
{

typedef std::vector< std::reference_wrapper< std::ostream > > ChannelContainer;

class AutoLogger
{
  public:
    AutoLogger( const ChannelContainer& channels );
    AutoLogger( const AutoLogger& other );
    std::stringstream& stream();
    ~AutoLogger();

  private:
    const ChannelContainer& m_channels;
    std::stringstream m_stream;
};

class Logger
{
  public:
    static void drop_channels();
    static void add_channel( std::ostream& );
    static AutoLogger log();

    Logger( const Logger& ) = delete;
    Logger& operator=( const Logger& ) = delete;

  private:
    Logger() = default;

    static Logger& instance();

    ChannelContainer m_channels;
};

#define thelog( loglevel ) the::log::Logger::log().stream() << __FILE__ << " +" << __LINE__ << " "

}

}

