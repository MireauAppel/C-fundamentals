#ifndef TEXT_UTIL_H
#define TEXT_UTIL_H

//==============================================================================
  
#include "Line.h"

//==============================================================================
  
size_t TextUtil_runNlOnFile (FILE * file,
                             size_t numStart, size_t numStep, bool skipEmpty,
                             FILE * output);

int TextUtil_runNl (int argc, char * argv[],
                    FILE * output);

//==============================================================================
  
void TextUtil_runRevOnFile (FILE * file,
                            FILE * output);

int  TextUtil_runRev (int argc, char * argv[],
                      FILE * output);

//==============================================================================

void TextUtil_runTacOnFile (FILE * file,
                            FILE * output);

int TextUtil_runTac (int argc, char * argv[],
                     FILE * output);
  
//==============================================================================

void TextUtil_runFgrepOnFile (FILE * file,
                              char const word[],
                              char const markupStart[],
                              char const markupEnd[],
                              FILE * output); 
 
int TextUtil_runFgrepWithMarkup (int argc, char * argv[],
                                 char const markupStart[],
                                 char const markupEnd[],
                                 FILE * output); 
 
int TextUtil_runFgrep (int argc, char * argv[],
                       FILE * output);

//==============================================================================

int TextUtil_openFiles (FILE * files[], int fileCount,
                        char * const filenames[], char const mode[]);

void TextUtil_closeFiles (FILE * files[], int fileCount);

int TextUtil_readOneLinePerFile (Line lines[],
                                 FILE * files[], bool eofs[], int fileCount);

void TextUtil_cleanLines (Line lines[], int lineCount);

//-----------------------------------------------------------------------------

void TextUtil_printPastedLines (Line lines[], int lineCount,
                                char const separator[],
                                FILE * output); 

//-----------------------------------------------------------------------------

void TextUtil_runPasteOnFiles (FILE * files[], int fileCount,
                               char const separator[],
                               FILE * output);

int TextUtil_runPaste (int argc, char * argv[],
                       FILE * output);

//==============================================================================

void TextUtil_printCutLine (Line line, 
                            char const separator[], int num,
                            FILE * output);

//-----------------------------------------------------------------------------

void TextUtil_runCutOnFile (FILE * file,
                            char const separator[], int num,
                            FILE * output);

int TextUtil_runCut (int argc, char * argv[],
                     FILE * output);

//==============================================================================

#endif

