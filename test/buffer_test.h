#pragma once

#include <vector>
#include "xo/geometry/vec3.h"
#include "xo/system/log.h"
#include "xo/utility/interpolation.h"
#include "xo/container/label_vector.h"
#include "xo/container/circular_frame_buffer.h"
#include "xo/container/circular_deque.h"
#include "xo/container/storage.h"
#include "xo/diagnose/test_framework.h"

namespace xo
{
	void buffer_test()
	{
		// circular_deque test
		circular_deque< int > cd( 10 );
		for ( int i = 0; i < 30; ++i )
		{
			cd.push_back( i );
			if ( cd.size() == 10 )
			{
				XO_TEST( cd.front() == i - 9 );
				cd.pop_front();
			}
		}

		// circular_deque test
		cd.clear();
		cd.reserve( 0 );
		for ( int i = 0; i < 30; ++i )
		{
			cd.push_front( i );
			if ( cd.size() == 20 )
			{
				XO_TEST( cd.back() == i - 19 );
				cd.pop_back();
			}
		}

		// regular buffer test
		storage< float, string > buf( 0 );

		//regular_ring_buffer< double, 100, void > ringbuf( 20 );
		for ( int i = 0; i < 10; ++i )
			buf.add_channel( stringf( "channel%d", i ) );

		// more tests
		std::vector< std::pair< double, vec3 > > buf_test;
		buf_test.push_back( std::make_pair( 0, vec3( 1, 0, 0 ) ) );
		buf_test.push_back( std::make_pair( 1, vec3( 0, 1, 0 ) ) );
		buf_test.push_back( std::make_pair( 3, vec3( 0, 1, 2 ) ) );
		for ( int d = -10; d < 40; ++d )
			log::trace( 0.1 * d, ": ", interpolated_value( buf_test, 0.1 * d ) );

		// more tests
		std::vector< vec3 > buf_test2;
		buf_test2.push_back( vec3( 1, 0, 0 ) );
		buf_test2.push_back( vec3( 0, 1, 0 ) );
		buf_test2.push_back( vec3( 0, 1, 2 ) );
		for ( int d = -10; d < 40; ++d )
			log::trace( 0.1 * d, ": ", interpolated_value( buf_test2, 0.1 * d ) );
	}
}
