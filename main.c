#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CXml.h"

unsigned long load_file( const char* file, unsigned char** file_contents );

void parse_ITEM( struct CXml* cxml )
{
	unsigned char *title;
	unsigned char *begin;
	unsigned char *end;
	
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
		if ( cxml->current_tag->name != NULL && strcmp( (char*)cxml->current_tag->name, "NICEBEGIN" ) == 0 )
		{
			begin = CXml_get_text( cxml );
		}
		if ( cxml->current_tag->name != NULL && strcmp( (char*)cxml->current_tag->name, "NICEEND" ) == 0 )
		{
			end = CXml_get_text( cxml );
		}
	}
	
	printf( "%s\n%s bis %s\n\n", title, begin, end );
	fflush( stdout );
	free( title );
	free( begin );
	free( end );
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
	char *xml_file = "input.xml";
	unsigned char *file_contents;
	unsigned long file_size;
	struct CXml* cxml;
	
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
	cxml = CXml_parse( file_contents, file_size );
	
	// Skip xml-definition
	CXml_next_tag( cxml );
	parse_OTR( cxml );
	CXml_free( cxml );
	
	free( file_contents );
	
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