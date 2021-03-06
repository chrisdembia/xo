#pragma once

#include "xo/utility/types.h"
#include "xo/system/system_tools.h"
#include "xo/time/timer.h"
#include "xo/container/prop_node.h"

#ifdef XO_COMP_MSVC
#	pragma warning( push )
#	pragma warning( disable: 4251 )
#endif

namespace xo
{
	class XO_API profiler
	{
	public:
		using tick_t = nanoseconds_t;

		struct section
		{
			section( const char* n, size_t i, size_t pi ) : name( n ), id( i ), parent_id( pi ), total_time( 0 ), overhead( 0 ), count( 0 ) {}
			const char* name;
			size_t id;
			size_t parent_id;
			tick_t total_time;
			tick_t overhead;
			size_t count;
			tick_t epoch;
		};

		void reset();
		section* start_section( const char* name );
		void end_section();
		tick_t now() const { return timer_.nanoseconds(); }
		prop_node report();
		static profiler& instance() { return instance_; }

	private:
		profiler();
		void clear();

		void report_section( section* s, prop_node& pn );
		tick_t exclusive_time( section* s );
		tick_t total_overhead( section* s );
		section* root() { return &sections_.front(); }
		section* find_section( size_t id );
		section* find_section( const char* name, size_t parent_id );
		section* acquire_section( const char* name, size_t parent_id );
		section* add_section( const char* name, size_t parent_id );
		std::vector< section* > get_children( size_t parent_id );

		std::vector< section > sections_;
		timer timer_;
		static profiler instance_;
		section* current_section_;
		tick_t overhead_estimate;

		void init_overhead_estimate();
	};

	struct XO_API scoped_section_profiler
	{
		scoped_section_profiler( const char* name ) { profiler::instance().start_section( name ); }
		~scoped_section_profiler() { profiler::instance().end_section(); }
	};
}

#ifdef XO_COMP_MSVC
#	pragma warning( pop )
#endif
