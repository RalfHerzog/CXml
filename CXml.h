#ifndef __CXML__
#define __CXML__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum CXml_state
{
	OPEN,
	CLOSE,
	OPEN_CLOSE
};

struct CXml
{
	unsigned char* file_contents;
	unsigned long file_size;
	
	unsigned long position;
	
	struct CXml_Tag* current_tag;
	struct CXml_Tag* next_tag;
};

struct CXml_Tag
{
	unsigned char* name;
	unsigned char* attributes;
	
	unsigned long start;
	unsigned long length;
	
	enum CXml_state state;
};

struct CXml* CXml_parse( unsigned char*, unsigned long );
unsigned char CXml_next_tag( struct CXml* );
unsigned char* CXml_get_text( struct CXml* );
void CXml_free( struct CXml* );

struct CXml_Tag* __CXml_get_tag( unsigned char* );
void __CXml_tag_free( struct CXml_Tag *tag );

#endif