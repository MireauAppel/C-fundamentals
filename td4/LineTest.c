
#include "LineTest.h"
#include "Line.h"
#include <assert.h>
#include <string.h>

void
LineTest_read (void) {
  char buffer[]=
    "aaa\n"
    "bb\0cc\n"
    "ddd";
  FILE * file= fmemopen (buffer, sizeof buffer - 1, "r");
  assert (file != NULL);

  Line line1= Line_read (file, 2);
  assert (line1.length == 4 && memcmp (line1.chars, "aaa\n", 4+1) == 0);
  Line_clean (line1);
  
  Line line2= Line_read (file, 2);
  assert (line2.length == 6 && memcmp (line2.chars, "bb\0cc\n", 6+1) == 0);
  Line_clean (line2);

  Line line3= Line_read (file, 2);
  assert (line3.length == 3 && memcmp (line3.chars, "ddd", 3+1) == 0);
  Line_clean (line3);

  Line line4= Line_read (file, 2);
  assert (line4.length == 0 && memcmp (line4.chars, "", 0+1) == 0);
  Line_clean (line4);
 
  fclose (file);  
}

//------------------------------------------------------------------------------

void
LineTest_isEnd (void) {
  assert (   Line_isEnd ((Line) { .length= 0, .chars= "" }));
  assert ( ! Line_isEnd ((Line) { .length= 6, .chars= "\0aa\0bb" }));
}

//------------------------------------------------------------------------------

void
LineTest_endsWithNL (void) {
  assert ( ! Line_endsWithNL ((Line) { .length= 0, .chars= "" }));
  assert ( ! Line_endsWithNL ((Line) { .length= 3, .chars= "aaa" }));
  assert (Line_endsWithNL ((Line) { .length= 1, .chars= "\n" }));
  assert (Line_endsWithNL ((Line) { .length= 4, .chars= "aaa\n" }));
  assert (Line_endsWithNL ((Line) { .length= 6, .chars= "aa\0bb\n" }));
}
  
//------------------------------------------------------------------------------

void
LineTest_startsWithNL (void) {
  assert ( ! Line_startsWithNL ((Line) { .length= 0, .chars= "" }));
  assert ( ! Line_startsWithNL ((Line) { .length= 3, .chars= "aaa" }));
  assert (Line_startsWithNL ((Line) { .length= 1, .chars= "\n" }));
  assert ( ! Line_startsWithNL ((Line) { .length= 4, .chars= "aaa\n" }));
  assert ( ! Line_startsWithNL ((Line) { .length= 6, .chars= "aa\0bb\n" }));
}
 
//------------------------------------------------------------------------------
 
void
LineTest_findString (void) {
  char chars[]= "aabbcc\0ddeeff\0gghhii\n";
  Line line= (Line) { .length= 21, .chars= chars };
  assert (Line_findString (line, "bb") == chars + 2);
  assert (Line_findString (line, "ee") == chars + 9);
  assert (Line_findString (line, "hh") == chars + 16);
  assert (Line_findString (line, "xx") == NULL);
}

//------------------------------------------------------------------------------

void
LineTest_findNthString (void) {
  char chars[]= "aabbxxcc\0ddxxee\0ffxxggxxhh\0iijj\0xx\n";
  Line line= (Line) { .length= 35, .chars= chars };
  assert (Line_findNthString (line, "xx", 1) == chars + 4);
  assert (Line_findNthString (line, "xx", 2) == chars + 11);
  assert (Line_findNthString (line, "xx", 3) == chars + 18);
  assert (Line_findNthString (line, "xx", 4) == chars + 22);
  assert (Line_findNthString (line, "xx", 5) == chars + 32);
  assert (Line_findNthString (line, "xx", 6) == NULL);  
  assert (Line_findNthString (line, "xx", 0) == NULL);
  assert (Line_findNthString (line, "xx",-1) == NULL);
}

//------------------------------------------------------------------------------

void
LineTest_printFromTo(void) {
  {
    char * printed; size_t size;
    FILE * file= open_memstream (& printed, & size);
    Line_printFromTo ((Line){ .length= 8, .chars= "aa\0bb\0cc"}, 0, 4, file);
    fclose (file);
    assert (size == 4 && memcmp (printed, "aa\0b", size) == 0);
    free (printed);
  } {
    char * printed; size_t size;
    FILE * file= open_memstream (& printed, & size);
    Line_printFromTo ((Line){ .length= 9, .chars= "aa\0bb\0cc\n"}, 3, 9, file);
    fclose (file);
    assert (size == 6 && memcmp (printed, "bb\0cc\n", size) == 0);
    free (printed);
  }
}


//------------------------------------------------------------------------------

void
LineTest_print(void) {
  {
    char * printed; size_t size;
    FILE * file= open_memstream (& printed, & size);
    Line_print ((Line) { .length= 8, .chars= "aa\0bb\0cc"}, file);
    fclose (file);
    assert (size == 8 && memcmp (printed, "aa\0bb\0cc", size) == 0);
    free (printed);
  } {
    char * printed; size_t size;
    FILE * file= open_memstream (& printed, & size);
    Line_print ((Line) { .length= 9, .chars= "aa\0bb\0cc\n"}, file);
    fclose (file);
    assert (size == 9 && memcmp (printed, "aa\0bb\0cc\n", size) == 0);
    free (printed);
  }
}

//------------------------------------------------------------------------------

void
LineTest_printBackward(void) {
  {
    char * printed; size_t size;
    FILE * file= open_memstream (& printed, & size);
    Line_printBackward ((Line) { .length= 8, .chars= "aa\0bb\0cc"}, file);
    fclose (file);
    assert (size == 8 && memcmp (printed, "cc\0bb\0aa", size) == 0);
    free (printed);
  } {
    char * printed; size_t size;
    FILE * file= open_memstream (& printed, & size);
    Line_printBackward ((Line) { .length= 9, .chars= "aa\0bb\0cc\n"}, file);
    fclose (file);
    assert (size == 9 && memcmp (printed, "cc\0bb\0aa\n", size) == 0);
    free (printed);
  }
}

//------------------------------------------------------------------------------

void LineTest_runAll (void) {
  LineTest_read();
  LineTest_isEnd();
  LineTest_startsWithNL();
  LineTest_endsWithNL();
  LineTest_findString();
  LineTest_findNthString();
  LineTest_printFromTo();
  LineTest_print();
  LineTest_printBackward();
}
