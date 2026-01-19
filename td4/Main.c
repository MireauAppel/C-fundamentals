
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "TextUtil.h"
#include "Line.h"
#include "LineTest.h"
#include "ContentTest.h"
#include "TextUtilTest.h"
#include <unistd.h>

void
Main_printUsage (char const commandName[], FILE * file) {
  fprintf (file, "Usage:\n");
  fprintf (file, "%s -h|-help\n", commandName);
  fprintf (file, "%s -nl start step skip [FILE...]\n", commandName);
  fprintf (file, "%s -rev [FILE...]\n", commandName);
  fprintf (file, "%s -tac [FILE...]\n", commandName);
  fprintf (file, "%s -fgrep word [FILE...]\n", commandName);
  fprintf (file, "%s -paste sep [FILE...]\n", commandName);
  fprintf (file, "%s -cut sep num [FILE...]\n", commandName);
  
}

int main (int argc, char * argv[]) {
  LineTest_runAll();
  ContentTest_runAll();
  TextUtilTest_runAll();

  bool isShortHelp= (argc == 1+1 && strcmp (argv[1], "-h"   ) == 0);
  bool isLongHelp = (argc == 1+1 && strcmp (argv[1], "-help") == 0);
  bool isHelp= isShortHelp || isLongHelp;
  
  if (isHelp ) { Main_printUsage (argv[0], stdout); exit (0); }
  
  bool isNl =   (argc >= 1+4 && strcmp (argv[1], "-nl"   ) == 0);
  bool isTac=   (argc >= 1+1 && strcmp (argv[1], "-tac"  ) == 0);
  bool isRev=   (argc >= 1+1 && strcmp (argv[1], "-rev"  ) == 0);
  bool isFgrep= (argc >= 1+2 && strcmp (argv[1], "-fgrep") == 0);
  bool isPaste= (argc >= 1+3 && strcmp (argv[1], "-paste") == 0);
  bool isCut=   (argc >= 1+3 && strcmp (argv[1], "-cut"  ) == 0);
  
  if (isNl   ) return TextUtil_runNl    (argc, argv, stdout);
  if (isTac  ) return TextUtil_runTac   (argc, argv, stdout);
  if (isRev  ) return TextUtil_runRev   (argc, argv, stdout);
  if (isFgrep) return TextUtil_runFgrep (argc, argv, stdout);
  if (isPaste) return TextUtil_runPaste (argc, argv, stdout);
  if (isCut  ) return TextUtil_runCut   (argc, argv, stdout);

  Main_printUsage (argv[0], stderr);
  return 1;
}
