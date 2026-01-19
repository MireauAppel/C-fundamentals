
#ifndef LINE_H
#define LINE_H

//==============================================================================

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//==============================================================================

typedef struct Line {
  char * chars;  // malloc'ed, can have '\0' in middle of string
  size_t length; // includes all '\0' except the last one.
} Line;

//==============================================================================

void Line_clean (Line line) ;
Line Line_read  (FILE * file, size_t initialCapacity);
bool Line_isEnd        (Line line);
bool Line_endsWithNL   (Line line);
bool Line_startsWithNL (Line line);

char * Line_findString    (Line line, char const string[]);
char * Line_findNthString (Line line, char const string[], int nth);

void Line_printFromTo   (Line line, size_t start, size_t end, FILE * file); 
void Line_print         (Line line, FILE * file);
void Line_printBackward (Line line, FILE * file);

//==============================================================================

#endif
