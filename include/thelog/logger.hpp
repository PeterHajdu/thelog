#pragma once
#include <ostream>
#include <vector>
#include <functional>
#include <string>

namespace the
{

namespace log
{

class LogDetails;

std::string local_time_in_string_format();
std::ostream& operator<<( std::ostream& output, const LogDetails& details );

std::string trim_file_name( std::string&& );

class LogDetails
{
  public:
    LogDetails(
        int loglevel,
        const char* file,
        int line )
      : loglevel( loglevel )
      , file( trim_file_name( file ) )
      , line( line )
    {
    }

    const int loglevel;
    const std::string file;
    const int line;
};


class Logger
{
  public:
    static void drop_channels();
    static void add_channel( std::ostream& );
    static void set_loglevel( int loglevel );

    template < typename...Args >
    static void log( const LogDetails& details, Args&&...args )
    {
      Logger& logger( instance() );
      if ( details.loglevel < logger.m_loglevel )
      {
        return;
      }

      logger.to_all_channels( local_time_in_string_format() );
      logger.to_all_channels( details );
      logger.print( std::forward< Args >( args )... );
      logger.end_of_message();
    }

    Logger( const Logger& ) = delete;
    Logger& operator=( const Logger& ) = delete;

    static const int default_loglevel{ 1000 };
  private:
    template< typename Head, typename...Tail >
    void print( Head&& head, Tail&&...tail )
    {
      to_all_channels( head );
      print( std::forward< Tail >( tail )... );
    }

    void print() {}

    void end_of_message()
    {
      for ( auto& channel : m_channels )
      {
        channel.get() << std::endl;
      }
    }

    template < typename T >
    void to_all_channels( const T& message )
    {
      for ( auto& channel : m_channels )
      {
        channel.get() << message << " ";
      }
    }

    Logger() = default;

    static Logger& instance();

    typedef std::vector< std::reference_wrapper< std::ostream > > ChannelContainer;
    ChannelContainer m_channels;
    int m_loglevel{ default_loglevel };
};

class AutoLogger
{
  public:
    AutoLogger( const LogDetails& details );

    template < typename...Args >
    void operator()( Args&&...args )
    {
      Logger::log( m_details, std::forward<Args>( args )... );
    }

    ~AutoLogger();

  private:
    const LogDetails m_details;
};

}

}

#if defined switch_off_thelog
  #define thelog(...) (void)
#else
  #define thelog( loglevel ) the::log::AutoLogger( { loglevel, __FILE__, __LINE__ } )
#endif

