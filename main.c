#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "colibro.h"
#include "CXml.h"

unsigned long load_file( const char* file, unsigned char** file_contents );

unsigned int timestamp_to_time( time_t time, char** time_str )
{
	struct tm *tmp;
	
	tmp = localtime( &time );
	*time_str = (char*)malloc( 256 );
	
	return strftime( *time_str, 256, "%H:%M:%S", tmp );
}

void parse_ITEM( struct CXml* cxml )
{
	unsigned char *title = NULL;
	unsigned char *begin = NULL;
	unsigned char *end = NULL;
	unsigned char *station = NULL;
	char *time_start = NULL;
	char *time_end = NULL;
	
	while( 
		CXml_next_tag( cxml ) && 
		!( strcmp( (char*)cxml->current_tag->name, "ITEM" ) == 0 && cxml->current_tag->state == CLOSE )
	)
	{
		if ( cxml->current_tag->state == CLOSE )
		{
			continue;
		}
		if ( cxml->current_tag->name != NULL && strcmp( (char*)cxml->current_tag->name, "TITLE" ) == 0 )
		{
			title = CXml_get_text( cxml );
		}
		if ( cxml->current_tag->name != NULL && strcmp( (char*)cxml->current_tag->name, "STATION" ) == 0 )
		{
			station = CXml_get_text( cxml );
		}
		if ( cxml->current_tag->name != NULL && strcmp( (char*)cxml->current_tag->name, "BEGIN" ) == 0 )
		{
			begin = CXml_get_text( cxml );
			timestamp_to_time( atoi( (char*)begin ), &time_start );
		}
		if ( cxml->current_tag->name != NULL && strcmp( (char*)cxml->current_tag->name, "END" ) == 0 )
		{
			end = CXml_get_text( cxml );
			timestamp_to_time( atoi( (char*)end ), &time_end );
		}
	}
	
	printf( "%s (%s)\n%s bis %s\n\n", title, station, time_start, time_end );
	fflush( stdout );
	
	free( title );
	free( station );
	free( begin );
	free( end );
	
	free( time_start );
	free( time_end );
}

void parse_OTR( struct CXml* cxml )
{
	while( CXml_next_tag( cxml ) )
	{
		if ( cxml->current_tag->state == CLOSE )
		{
			continue;
		}
		if ( cxml->current_tag->name != NULL && strcmp( (char*)cxml->current_tag->name, "ITEM" ) == 0 )
		{
			parse_ITEM( cxml );
		}
	}
}

int main( int argc, char **argv )
{
	unsigned char *file_contents;
	int file_size;
	struct CXml* cxml;
	struct HTTP http;
	
	#ifdef XML_LOCAL
		char *xml_file = "input.xml";
		
		file_size = load_file( xml_file, &file_contents );
		if ( file_contents == NULL )
		{
			fprintf( stderr, "No such file '%s'\n", xml_file );
			return -1;
		}
		if ( file_size == 0 )
		{
			fprintf( stderr, "Empty file '%s'\n", xml_file );
			return -1;
		}
	#else
		http_get_page( &http, "http://www.onlinetvrecorder.com/rss/toprecordings_germany.xml", (char**)&file_contents, &file_size );
	#endif
	
	http_init( &http );
	if ( file_contents == NULL )
	{
		fprintf( stderr, "No contents\n" );
		return -1;
	}
	
	cxml = CXml_parse( file_contents, file_size );
	
	// Skip xml-definition
	CXml_next_tag( cxml );
	parse_OTR( cxml );
	CXml_free( cxml );
	
	free( file_contents );
	http_free( &http );
	
	return 0;
}

unsigned long load_file( const char* file, unsigned char** file_contents )
{
	long file_size;
	FILE *fFile;
	
	fFile = fopen( file, "rb" );
	if ( fFile == NULL )
	{
		*file_contents = NULL;
		return 0;
	}
	
	fseek( fFile, 0, SEEK_END );
	file_size = ftell( fFile );
	fseek( fFile, 0, SEEK_SET );
	
	*file_contents = (unsigned char*)malloc( file_size + 1 );
	file_size = fread( *file_contents, 1, file_size, fFile );
	fclose( fFile );
	
	return file_size;
}