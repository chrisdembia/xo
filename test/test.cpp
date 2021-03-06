#define XO_ENABLE_PROFILER

#include "test.h"
#include "math_test.h"
#include "buffer_test.h"
#include "xo/container/prop_node.h"
#include "xo/system/system_tools.h"
#include "prop_node_test.h"
#include "xo/time/stopwatch.h"
#include "xo/diagnose/test_framework.h"
#include "string_test.h"
#include "xo/string/dictionary.h"
#include "xo/system/log_sink.h"
#include "factory_test.h"
#include "container_test.h"
#include "timer_test.h"
#include "xo/diagnose/profiler.h"
#include "data_test.h"
#include "delay_test.h"
#include "filter_test.h"
#include "math_test.h"
#include "serializer_test.h"
#include "regression_test.h"
#include "alignment_test.h"

using xo::string;

int main( int argc, char* argv[] )
{
	xo::log::stream_sink str( xo::log::info_level, std::cout );
	xo::log::add_sink( &str );

	try
	{
		xo::alignment_test();
		//xo::wrap_test();
		//xo::filter_test();
		//xo::delay_test();

		xo::timer_test();

#ifdef XO_ENABLE_PROFILER
		//xo::profile_test();
#endif

		xo_profiler_reset();
		xo::stopwatch sw;

		xo::serializer_test();
		sw.add_measure( "serializer" );

		xo::container_test();
		sw.add_measure( "container" );

		xo::data_test();
		sw.add_measure( "data" );

		xo::factory_test();
		sw.add_measure( "factory" );

		xo::prop_node_test();
		sw.add_measure( "prop_node" );

		xo::string_test();
		sw.add_measure( "string" );

		xo::buffer_test();
		sw.add_measure( "buffer" );

		xo::regression_test();
		sw.add_measure( "regression" );

		xo::optional_test();
		xo::clamp_test();
		xo::linear_regression_test();
		xo::math_test();
		xo::function_test();
		xo::angle_test();
		sw.add_measure( "math" );

		xo_profiler_log_report( xo::log::info_level );
		auto pn = sw.get_report();
		xo::log::info( pn );
	}
	catch ( std::exception& e )
	{
		std::cout << e.what();				
	}

	int i = xo::test_framework::get_instance().report();

#if XO_IS_DEBUG_BUILD && defined( XO_COMP_MSVC )
	xo::wait_for_key();
#endif

	return i;
}
