#pragma once

#include <iosfwd>

#include "xo/container/prop_node.h"
#include "prop_node_serializer.h"
#include "xo/utility/factory.h"
#include "char_stream.h"
#include "xo/geometry/angle.h"
#include "xo/utility/pointer_type.h"
#include <string>

namespace xo
{
	XO_API factory< prop_node_serializer >& get_serializer_factory();
	XO_API u_ptr< prop_node_serializer > make_serializer( const std::string& file_type, prop_node& pn, error_code* ec = nullptr, path p = path() );
	XO_API u_ptr< prop_node_serializer > make_serializer( const std::string& file_type, const prop_node& pn, error_code* ec = nullptr, path p = path() );
	template< class S > void register_serializer( const std::string& extension ) { get_serializer_factory().register_class< S >( extension ); }

	XO_API prop_node load_file( const path& filename, error_code* ec = nullptr );
	XO_API prop_node load_file( const path& filename, const std::string& file_type, error_code* ec = nullptr );
	XO_API prop_node load_file_with_include( const path& filename, const std::string& include_directive = "INCLUDE" );

	XO_API void save_file( const prop_node& pn, const path& filename, error_code* ec = nullptr );
	XO_API void save_file( const prop_node& pn, const path& filename, const std::string& file_type, error_code* ec = nullptr );

	/// streaming
	template< angle_unit U, typename T > std::ostream& operator<<( std::ostream& str, const angle_<U, T>& a ) { return ( str << a.value ); }
	template< angle_unit U, typename T > std::istream& operator>>( std::istream& str, angle_<U, T>& a ) { return ( str >> a.value ); }
	template< angle_unit U, typename T > char_stream& operator>>( char_stream& str, angle_<U, T>& a ) { return ( str >> a.value ); }
}
