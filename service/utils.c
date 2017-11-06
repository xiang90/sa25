#include <string.h>
#include "utils.h"

char *chop( char *s )
{
    int l = strlen(s);
    if( l >= 1 ){
        s[l-1]=0;
    }
    return s;
}

void easyGetTokenFromString(char *src, int count, char *output, int len)
{
  int i;
  int counter = 0;

  if(len <= 0)
    return;

#define ISSPACETAB(c) ((c) == ' ' || (c) == '\t')

  for(i = 0; ; i++){
    if(src[i] == '\0'){
      output[0] = '\0';
      return;
    }
    
    if(i > 0 && !ISSPACETAB(src[i-1]) &&
       !ISSPACETAB(src[i])){
      continue;
    }

    if(!ISSPACETAB(src[i])){
      counter++;
      if(counter == count){
	int j;
	for(j = 0; j < len - 1; j++){
	  if(src[i + j] == '\0' ||
	     ISSPACETAB(src[i + j])){
	    break;
	  }
	  output[j] = src[i + j];
	}
	output[j] = '\0';
	return;
      }
    }
  }
}

/*
void easyGetTokenFromString_semicolon(char *src, int count, char *output, int len)
{
  int i;
  int counter = 0;

  if(len <= 0)
    return;

#define ISSEMICOLON(c) ((c) == ';')

  for(i = 0; ; i++){
    if(src[i] == '\0'){
      output[0] = '\0';
      return;
    }
    
    if(i > 0 && !ISSEMICOLON(src[i-1]) &&
       !ISSEMICOLON(src[i])){
      continue;
    }

    if(!ISSEMICOLON(src[i])){
      counter++;
      if(counter == count){
	int j;
	for(j = 0; j < len - 1; j++){
	  if(src[i + j] == '\0' ||
	     ISSEMICOLON(src[i + j])){
	    break;
	  }
	  output[j] = src[i + j];
	}
	output[j] = '\0';
	return;
      }
    }
  }
}
*/
