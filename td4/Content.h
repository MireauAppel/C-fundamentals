
#ifndef CONTENT_H
#define CONTENT_H

//==============================================================================

#include "Line.h"

//==============================================================================

typedef struct Content {
  Line * lines;
  size_t lineCount;
} Content;

//==============================================================================

void    Content_clean (Content content);
Content Content_read (FILE * file, size_t initialCapacity);

//==============================================================================

#endif
