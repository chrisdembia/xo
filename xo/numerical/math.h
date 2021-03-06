#pragma once

#include "xo/utility/types.h"
#include <cmath>

namespace xo
{
	/// min
	template< typename T > const T& min( const T& v1, const T& v2 ) { return v1 < v2 ? v1 : v2; }
	template< typename T > const T& min( const T& v1, const T& v2, const T& v3 ) { return min( v1, min( v2, v3 ) ); }

	/// max
	template< typename T > const T& max( const T& v1, const T& v2 ) { return v1 < v2 ? v2 : v1; }
	template< typename T > const T& max( const T& v1, const T& v2, const T& v3 ) { return max( v1, max( v2, v3 ) ); }

	/// inverse of v (1 / v)
	template< typename T > T inv( T v ) { return T(1) / v; }

	/// inverse of sqrt
	template< typename T > T invsqrt( T v ) { return T(1) / sqrt( v ); }

	/// sqrt based on sign: if v >= 0 sqrt( v ) else -sqrt( -v )
	template< typename T > T signed_sqrt( T v ) { return v >= T() ? sqrt( v ) : -sqrt( -v ); }

	/// squared
	template< typename T > T squared( T v ) { return v * v; }

	/// cubed
	template< typename T > T cubed( T v ) { return v * v * v; }

	/// sign of v: 1 or -1
	template< typename T > T sign( T v ) { return v >= T() ? T( 1 ) : T( -1 ); }

	/// signum of v: 1, 0 or -1
	template< typename T > int signum( T v ) { return ( T(0) < v ) - ( v < T(0) ); }

	/// check if sign of v1 equals sign of v2
	template< typename T > bool same_sign( T v1, T v2 ) { return signum( v1 ) == signum( v2 ); }

	/// set if smaller
	template< typename T > T& set_if_smaller( T& value, const T& other ) { if ( other < value ) value = other; return value; }

	/// set if bigger
	template< typename T > T& set_if_bigger( T& value, const T& other ) { if ( other > value ) value = other; return value; }

	/// check if an integer value is a power of two
	template< typename T > bool is_power_of_two( T v ) { return v != 0 && !( v & ( v - 1 ) ); }

	/// check if an integer value is odd / even
	template< typename T > bool is_even( T v ) { return ( v & 1 ) == 0; }
	template< typename T > bool is_odd( T v ) { return ( v & 1 ) == 1; }

	/// check if a number is whole (i.e. has no decimals)
	template< typename T > bool is_whole( T v ) { return floor( v ) == v; }

	/// clamp a value so that it is between min and max
	template< typename T > T& clamp( T& v, const T& min, const T& max )
	{ if ( v < min ) v = min; else if ( v > max ) v = max; return v; } // TODO: use efficient instructions

	/// return clamped value that is between min and max
	template< typename T > T clamped( T v, const T& min, const T& max ) { return clamp( v, min, max ); }

	/// limit transform function
	template< typename T > T limit_transfer( T x, T limit ) { return limit - limit * limit / ( x + limit ); }

	/// clamp with smooth boundary transformation
	template< typename T > T soft_clamp( T& v, const T& min, const T& max, const T& boundary ) {
		auto r = boundary * ( max - min );
		if ( v > max - r ) v = max - r + limit_transfer( v - max + r, r );
		else if ( v < min + r )	v = min + r - limit_transfer( min + r - v, r );
		return v;
	}

	template< typename T > T soft_clamped( T v, const T& min, const T& max, const T& boundary )
	{ return soft_clamp( v, min, max, boundary ); }

	/// wrap a value to a range
	template< typename T > T& wrap( T& v, const T& lower, const T& upper )
	{
		if ( ( v - lower ) >= 0 )
			return v = std::fmod( v - lower, upper - lower ) + lower;
		else return v = std::fmod( v - lower, upper - lower ) + upper;
	}

	/// wrap a value to a range
	template< typename T > T wrapped( T v, const T& lower, const T& upper ) { return wrap( v, lower, upper ); }

	/// check a value is within a range
	template< typename T > bool is_between( T v, T min, T max ) { return ( v >= min && v <= max ); }

	/// square wave, period = 2, min = -1, max = 1
	template< typename T > T square_wave( T v ) { return fmod( v, T(2) ) < T(1) ? T(1) : T(-1); }
}
