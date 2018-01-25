#pragma once

#include <vector>
#include <algorithm>

#include "xo/system/assert.h"
#include "xo/utility/types.h"

namespace xo
{
	// TODO: use own implementation, avoid <algorithm> header
	template< typename C > typename C::iterator find( C& cont, typename C::value_type& e )
	{ return std::find( std::begin( cont ), std::end( cont ), e ); }

	// TODO: use own implementation, avoid <algorithm> header
	template< typename C, typename P > typename C::const_iterator find( const C& cont, typename C::value_type& e )
	{ return std::find( std::begin( cont ), std::end( cont ), e ); }

	// TODO: use own implementation, avoid <algorithm> header
	template< typename C, typename P > typename C::iterator find_if( C& cont, P pred )
	{ return std::find_if( std::begin( cont ), std::end( cont ), pred ); }

	// TODO: use own implementation, avoid <algorithm> header
	template< typename C, typename P > typename C::const_iterator find_if( const C& cont, const P pred )
	{ return std::find_if( std::cbegin( cont ), std::cend( cont ), pred ); }

	template< typename C > typename C::iterator min_element( C& cont )
	{ return std::min_element( std::begin( cont ), std::end( cont ) ); }

	template< typename C > typename C::const_iterator min_element( const C& cont )
	{ return std::min_element( std::cbegin( cont ), std::cend( cont ) ); }

	template< typename C > typename C::iterator max_element( C& cont )
	{ return std::max_element( std::begin( cont ), std::end( cont ) ); }

	template< typename C > typename C::const_iterator max_element( const C& cont )
	{ return std::max_element( std::cbegin( cont ), std::cend( cont ) ); }

	template< typename I > typename std::iterator_traits< I >::value_type average( I b, I e )
	{ return std::accumulate( b, e, std::iterator_traits< I >::value_type( 0 ) ) / ( e - b ); }

	template< typename C > typename C::value_type average( const C& cont )
	{ return average( std::cbegin( cont ), std::cend( cont ) ); }

	/// append two containers, currently requires C::reserve()
	template< typename C > C& append( C& c1, const C& c2 )
	{ c1.reserve( c1.size() + c2.size() ); for ( auto& e : c2 ) c1.emplace_back( e ); return c1; }

	template < typename C > std::vector< index_t > sort_indices( const C& cont ) {
		std::vector< size_t > idx_vec( cont.size() );
		for ( index_t i = 0; i < cont.size(); ++i ) idx_vec[ i ] = i;
		sort( idx_vec.begin(), idx_vec.end(), [ &cont ]( size_t i1, size_t i2 ) { return cont[ i1 ] < cont[ i2 ]; } );
		return idx_vec;
	}

	template< typename C > C sorted_copy( const C& cont ) { C res( cont ); std::sort( res.begin(), res.end() ); return res; }

	template< typename I > typename std::iterator_traits< I >::value_type median( I b, I e ) {
		auto s = e - b;
		xo_assert( s > 0 );
		std::vector< std::remove_cv< std::iterator_traits< I >::value_type >::type > v( e - b );
		std::copy( b, e, v.begin() );
		if ( s % 2 == 1 ) return v[ s / 2 ];
		else return ( v[ s / 2 ] + v[ s / 2 - 1 ] ) / std::iterator_traits< I >::value_type( 2 );
	}

	template< typename C > typename C::value_type median( const C& v ) {
		return median( std::cbegin( v ), std::cend( v ) );
	}

	template< typename C > typename C::value_type top_average( const C& vec, size_t count ) {
		C result( count );
		std::partial_sort_copy( vec.begin(), vec.end(), result.begin(), result.end() );
		return average( result );
	}

	template< typename T > index_t find_index( const vector< T >& vec, const T& val ) {
		auto it = std::find( vec.begin(), vec.end(), val );
		if ( it == vec.end() ) return no_index;
		else return it - vec.begin();
	}

	template< typename T > index_t back_index( const vector< T >& vec )
	{ xo_assert( vec.size() > 0 ) return vec.size() - 1; }

	template< typename T > std::ostream& operator<<( std::ostream& str, const vector< T >& vec )
	{
		for ( auto it = vec.begin(); it != vec.end(); ++it ) {
			if ( it != vec.begin() ) str << "\t";
			str << *it;
		}
		return str << std::endl;
	}
}
