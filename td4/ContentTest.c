
#include "ContentTest.h"
#include "Content.h"
#include <assert.h>
#include <string.h>

//------------------------------------------------------------------------------

void
ContentTest_read (void) {
  char buffer[]=
    "aaa\n"
    "bb\0cc\n"
    "ddd";
  FILE * file= fmemopen (buffer, sizeof buffer - 1, "r");
  assert (file != NULL);
  Content content= Content_read (file, 2);
  fclose (file);
  
  assert (content.lineCount == 3);
  assert (content.lines[0].length == 4);
  assert (content.lines[1].length == 6);
  assert (content.lines[2].length == 3);
  assert (content.lines[3].length == 0);
  assert (memcmp (content.lines[0].chars, "aaa\n", 4+1) == 0);
  assert (memcmp (content.lines[1].chars, "bb\0cc\n", 6+1) == 0);
  assert (memcmp (content.lines[2].chars, "ddd", 3+1) == 0);
  assert (memcmp (content.lines[3].chars, "", 0+1) == 0);
  Content_clean (content);
}

//------------------------------------------------------------------------------

void
ContentTest_runAll (void) {
  ContentTest_read();
}
