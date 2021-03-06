#include "debug_storage.h"
#include "xo/container/storage.h"
#include "xo/numerical/constants.h"
#include <fstream>

namespace xo
{
	template< typename T, typename L >
	struct auto_storage_writer
	{
		auto_storage_writer( const path& filename ) : filename_( filename ) {}
		~auto_storage_writer() {
			if ( !storage_.empty() )
				std::ofstream( filename_.str() ) << storage_;
		}

		void write( const L& label, T value ) {
			auto idx = storage_.find_or_add_channel( label, const_sentinel<T>() );
			if ( storage_.empty() || storage_.back()[ idx ] != const_sentinel<T>() )
				storage_.add_frame( const_sentinel<T>() );
			storage_.back()[ idx ] = value;
		}
		path filename_;
		storage< T, L > storage_;
	};

	auto_storage_writer< float, string > g_debug_storage_writer( "debug.txt" );

	void set_debug_output( const path& filename )
	{
		g_debug_storage_writer.filename_ = filename;
	}

	void write_debug( const string& label, float data )
	{
		g_debug_storage_writer.write( label, data );
	}
}
