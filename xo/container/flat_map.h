#pragma once

#include <algorithm>
#include <vector>
#include "xo/system/assert.h"

namespace xo
{
	template< typename K, typename V >
	class flat_map
	{
	public:
		using value_type = typename std::pair< K, V >;
		using container_t = typename std::vector< value_type >;
		using iterator = typename container_t::iterator;
		using reverse_iterator = typename container_t::reverse_iterator;
		using const_iterator = typename container_t::const_iterator;
		using const_reverse_iterator = typename container_t::const_reverse_iterator;

		flat_map() : data_() {};
		flat_map( const flat_map& other ) : data_( other.data_ ) {};
		flat_map( flat_map&& other ) : data_( std::move( other.data_ ) ) {};
		flat_map( std::initializer_list< value_type > l ) : data_( l ) {};
		flat_map& operator=( const flat_map& other ) { data_ = other.data_; return *this; };
		flat_map& operator=( flat_map&& other ) { data_ = std::move( other.data_ ); return *this; };

		bool empty() const { return data_.empty(); }
		void clear() { data_.clear(); }
		size_t size() const { return data_.size(); }

		iterator begin() { return data_.begin(); }
		const_iterator begin() const { return data_.begin(); }
		const_iterator cbegin() const { return data_.cbegin(); }
		reverse_iterator rbegin() { return data_.rbegin(); }
		const_reverse_iterator crbegin() const { return data_.crbegin(); }

		iterator end() { return data_.end(); }
		const_iterator end() const { return data_.end(); }
		const_iterator cend() const { return data_.cend(); }
		reverse_iterator rend() { return data_.rend(); }
		const_reverse_iterator crend() const { return data_.crend(); }

		const value_type& front() const { return data_.front(); }
		value_type& front() { return data_.front(); }

		const value_type& back() const { return data_.back(); }
		value_type& back() { return data_.back(); }

		iterator erase( iterator it ) { return data_.erase( it ); }

		iterator lower_bound( const K& key ) { return std::lower_bound( begin(), end(), key, [&]( const value_type& kvp, const K& key ) { return kvp.first < key; } ); }
		const_iterator lower_bound( const K& key ) const { return std::lower_bound( begin(), end(), key, [&]( const value_type& kvp, const K& key ) { return kvp.first < key; } ); }

		iterator upper_bound( const K& key ) { return std::upper_bound( begin(), end(), key, [&]( const K& key, const value_type& kvp ) { return key < kvp.first; } ); }
		const_iterator upper_bound( const K& key ) const { return std::upper_bound( begin(), end(), key, [&]( const K& key, const value_type& kvp ) { return key < kvp.first; } ); }

		iterator find( const K& key ) {
			auto it = lower_bound( key );
			return ( it != end() && it->first == key ) ? it : end();
		}
		const_iterator find( const K& key ) const {
			auto it = lower_bound( key );
			return ( it != end() && it->first == key ) ? it : end();
		}

		size_t count( const K& key ) const { return std::count_if( cbegin(), cend(), [&]( const value_type& kvp ) { return kvp.first == key; } ); }
		bool has_key( const K& key ) const { return find( key ) != end(); }

		std::pair< iterator, bool > insert( const value_type& value ) {
			auto it = lower_bound( value.first );
			if ( it != end() && it->first == value.first ) {
				it->second = value.second; // replace existing item
				return make_pair( it, false );
			}
			else return make_pair( data_.insert( it, value ), true );
		}

		std::pair< iterator, bool > insert( value_type&& value ) {
			auto it = lower_bound( value.first );
			if ( it != end() && it->first == value.first ) {
				it->second = std::move( value.second ); // replace existing item
				return make_pair( it, false );
			}
			else return make_pair( data_.insert( it, std::move( value ) ), true );
		}

		V& operator[]( const K& key ) {
			auto it = lower_bound( key );
			if ( it != end() && it->first == key )
				return it->second;
			return data_.insert( it, std::make_pair( key, V() ) )->second;
		}

		const V& operator[]( const K& key ) const { return at( key ); }

		V& at( const K& key ) {
			auto it = find( key );
			xo_error_if( it == end(), "Could not find key: " + to_str( key ) );
			return it->second;
		}

		const V& at( const K& key ) const {
			auto it = find( key );
			xo_error_if( it == end(), "Could not find key: " + to_str( key ) );
			return it->second;
		}

	private:
		container_t data_;
	};
}
