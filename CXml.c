#include "CXml.h"

struct CXml* CXml_parse( unsigned char* file_contents, unsigned long file_size )
{
	struct CXml* cxml;
	cxml = (struct CXml*)malloc( sizeof( struct CXml ) );
	memset( cxml, 0, sizeof( struct CXml ) );
	
	cxml->file_contents = file_contents;
	cxml->file_size = file_size;
	
	CXml_next_tag( cxml );
	CXml_next_tag( cxml );
	
	return cxml;
}

unsigned char CXml_next_tag( struct CXml* cxml )
{
	unsigned char hasNext = 0;
	
	__CXml_tag_free( cxml->current_tag );
	free( cxml->current_tag );
	
	cxml->current_tag = cxml->next_tag;
	cxml->next_tag = (struct CXml_Tag*)malloc( sizeof( struct CXml_Tag ) );
	memset( cxml->next_tag, 0, sizeof( struct CXml_Tag ) );
	
	while( cxml->position < cxml->file_size )
	{
		if ( *( cxml->file_contents + cxml->position ) == '<' )
		{
			// New start tag
			hasNext = 1;
			
			cxml->next_tag = __CXml_get_tag( cxml->file_contents + cxml->position );
			
			cxml->next_tag->start = cxml->position;
			cxml->position += cxml->next_tag->length;
			break;
		}
		else
		{
			cxml->position++;
		}
	}
	return hasNext;
}

unsigned char* CXml_get_text( struct CXml* cxml )
{
	unsigned char* text;
	unsigned long text_length;
	
	text_length = cxml->next_tag->start - cxml->current_tag->start - cxml->current_tag->length;
	
	if ( cxml->position == cxml->file_size )
	{
		text = (unsigned char*)malloc( 1 );
		*text = '\0';
		return text;
	}
	text = (unsigned char*)malloc( text_length + 1 );
	memcpy( text, cxml->file_contents + cxml->current_tag->start + cxml->current_tag->length, text_length );
	memset( text + text_length, 0, 1 );
	
	return text;
}

void CXml_free( struct CXml* cxml )
{
	__CXml_tag_free( cxml->current_tag );
	__CXml_tag_free( cxml->next_tag );
	memset( cxml, 0, sizeof( struct CXml ) );
}

struct CXml_Tag* __CXml_get_tag( unsigned char* element )
{
	struct CXml_Tag* tag;
	unsigned long start;
	
	unsigned long name_end;
	unsigned long name_length;
	
	unsigned long attr_start;
	unsigned long attr_end;
	unsigned long attr_length;
	
	if ( *element != '<' )
	{
		// Not a valid tag start
		return NULL;
	}
	tag = (struct CXml_Tag*)malloc( sizeof( struct CXml_Tag ) );
	memset( tag, 0, sizeof( struct CXml_Tag ) );
	
	start = 1;
	tag->state = OPEN;
	if ( *( element + start ) == '/' )
	{
		tag->state = CLOSE;
		start++;
	}
	
	// Search name end
	for ( name_end = start ; 
		*( element + name_end ) != ' ' && 
		*( element + name_end ) != '>' && 
		*( element + name_end ) != '\0' ; 
	name_end++ );
	name_length = name_end - start;
	
	tag->name = (unsigned char*)malloc( name_length + 1 );
	memcpy( tag->name, element+start, name_length );
	memset( tag->name + name_length, 0, 1 );
	
	if ( *( element + name_end ) != '>' )
	{
		// Tag has attributes
		// Search attribute end
		for ( attr_start = name_end + 1, attr_end = attr_start ; 
			*( element + attr_end ) != '>' && 
			*( element + attr_end ) != '\0' ; 
			attr_end++ );
		attr_length = attr_end - attr_start;
		
		tag->attributes = (unsigned char*)malloc( attr_length + 1 );
		memcpy( tag->attributes, element+attr_start, attr_length );
		memset( tag->attributes + attr_length, 0, 1 );
		
		tag->length = attr_end - start + 2;
	} 
	else 
	{
		tag->length = name_end - start + 2;
	}
	return tag;
}

void __CXml_tag_free( struct CXml_Tag *tag )
{
	if ( tag == NULL )
	{
		return;
	}
	free( tag->name );
	free( tag->attributes );
	
	memset( tag, 0, sizeof( struct CXml_Tag ) );
} 