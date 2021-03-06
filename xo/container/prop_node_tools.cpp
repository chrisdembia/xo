#include "prop_node_tools.h"

namespace xo
{
	void log_unaccessed( const prop_node& pn, log::level level, int depth )
	{
		for ( auto& n : pn )
		{
			if ( n.second.count_unaccessed() > 0 )
			{
				string str = string( depth * 2, ' ' ) + n.first;
				if ( !n.second.is_accessed() )
				{
					if ( n.second.has_value() )
						str += " = " + n.second.get_value();
					str += " *";
				}
				log::message( level, str );
			}
			log_unaccessed( n.second, level, depth + 1 );
		}
	}

	std::pair< bool, string > find_query_to_node( const prop_node* from, const prop_node* to, const char delim )
	{
		if ( from == to )
			return { true, "" };

		for ( auto& child : *from )
		{
			auto result = find_query_to_node( &child.second, to, delim );
			if ( result.first )
				return { true, result.second.empty() ? child.first : child.first + delim + result.second };
		}

		return { false, "" };
	}
}
