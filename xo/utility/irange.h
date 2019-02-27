#pragma once

#ifdef XO_COMP_MSVC
#   include <xutility>
#endif
#include "sfinae.h"

namespace xo
{
	template< typename T >
	struct irange
	{
		using value_type = T;
		irange() : begin_( T( 0 ) ), end_( T( 0 ) ) {}
		irange( T b, T e ) : begin_( b ), end_( e ) {}

		struct iterator : public std::iterator< std::forward_iterator_tag, T, T >
		{
			using value_type = T;
			iterator( T v ) : value_( v ) { xo_assert_msg( is_whole( v ), "irange requires whole numbers" ); }
			T value_;
			T operator++() { return ++value_; }
			T operator++( int ) { return value_++; }
			iterator operator+( const T& offset ) { return iterator( value_ + offset ); }

			bool operator==( const iterator& other ) { return other.value_ == value_; }
			bool operator!=( const iterator& other ) { return other.value_ != value_; }
			T operator-( const iterator& other ) { return value_ - other.value_; }
			T operator*() { return value_; }
		};

		iterator begin() const { return iterator( begin_ ); }
		iterator end() const { return iterator( end_ ); }

		T begin_, end_;
	};

	template< typename T >
	struct irange_step
	{
		using value_type = T;
		irange_step( T b, T e, T s = T( 1 ) ) : begin_( b ), end_( e ), step_( s ) {}
		irange_step( const irange< T >& r, T s = T( 1 ) ) : begin_( r.begin_ ), end_( r.end_ ), step_( s ) {}

		struct iterator : public std::iterator< std::forward_iterator_tag, T, T >
		{
			using value_type = T;
			iterator( T v, T s ) : value_( v ), step_( s ) { xo_assert_msg( is_whole( v ) && is_whole( s ), "irange requires whole numbers" ); }
			T value_, step_;
			T operator-( const iterator& other ) { return ( value_ - other.value_ ) / step_; }
			T operator++() { return value_ += step_; }
			T operator++( int ) { value_ += step_; return value_ - step_; }
			bool operator==( const iterator& other ) { return other.value_ == value_; }
			bool operator!=( const iterator& other ) { return other.value_ != value_; }
			T operator*() { return value_; }
		};

		iterator begin() const { return iterator( begin_, step_ ); }
		iterator end() const { return iterator( end_, step_ ); }

		T begin_, end_, step_;
	};

	template< typename T, XO_ENABLE_IF_INTEGRAL > irange< T > make_irange( T b, T e ) { return irange< T >( b, e ); }
	template< typename T, XO_ENABLE_IF_INTEGRAL > irange< T > make_irange( T e ) { return irange< T >( T( 0 ), e ); }
	template< typename T, XO_ENABLE_IF_INTEGRAL > irange_step< T > make_irange( T b, T e, T s ) { return irange_step< T >( b, e, s ); }
	template< typename T, XO_ENABLE_IF_INTEGRAL > irange_step< T > make_irange( const irange< T >& r, T s ) { return irange_step< T >( r, s ); }

	/// make integer range from containter
	template< typename C > auto make_range( const C& cont ) { return irange< size_t >( 0, size( cont ) ); }
	template< typename C > auto make_range( const C& cont, size_t step ) { return irange_step< size_t >( 0, size( cont ), step ); }
}
