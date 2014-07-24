#define switch_off_thelog
#include <thelog/logger.hpp>
#include <igloo/igloo_alt.h>
using namespace igloo;

Describe( a_switched_off_logger )
{
  It( still_compiles )
  {
    thelog( 1 )( "something" );
  }
};

