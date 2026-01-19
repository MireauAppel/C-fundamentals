#include "TextUtilTest.h"
#include "TextUtil.h"

#include <assert.h>
#include <stdbool.h>
#include <string.h>

//==============================================================================
  
void TextUtilTest_runNlOnFile_withSkipEmpty_withoutFinalNL (void) {
  char inputBuffer[]=
    "aaa\n"
    "bb\0cc\n"
    "\n"
    "ddd";
  FILE * inputFile= fmemopen (inputBuffer, sizeof inputBuffer - 1, "r");
  assert (inputFile != NULL);
   
  char * outputBuffer; size_t outputSize;
  FILE * outputFile= open_memstream (& outputBuffer, & outputSize);
  assert (outputFile != NULL);
  
  TextUtil_runNlOnFile (inputFile, 100, 10, true, outputFile);
  fclose (inputFile); fclose (outputFile);

  char expectedBuffer[]=
    "   100\taaa\n"
    "   110\tbb\0cc\n"
    "\n"
    "   120\tddd\n";
  assert (outputSize == sizeof expectedBuffer - 1); 
  assert (memcmp (expectedBuffer, outputBuffer, outputSize) == 0);  
  free (outputBuffer);
}

//------------------------------------------------------------------------------

void TextUtilTest_runNlOnFile_withoutSkipEmpty_withFinalNL (void) {
  char inputBuffer[]=
    "aaa\n"
    "bb\0cc\n"
    "\n"
    "ddd\n";
  FILE * inputFile= fmemopen (inputBuffer, sizeof inputBuffer - 1, "r");
  assert (inputFile != NULL);
   
  char * outputBuffer; size_t outputSize;
  FILE * outputFile= open_memstream (& outputBuffer, & outputSize);
  assert (outputFile != NULL);
  
  TextUtil_runNlOnFile (inputFile, 100, 10, false, outputFile);
  fclose (inputFile); fclose (outputFile);

  char expectedBuffer[]=
    "   100\taaa\n"
    "   110\tbb\0cc\n"
    "   120\t\n"
    "   130\tddd\n";
  assert (outputSize == sizeof expectedBuffer - 1); 
  assert (memcmp (expectedBuffer, outputBuffer, outputSize) == 0);  
  free (outputBuffer);
}

//==============================================================================
  
void TextUtilTest_runRevOnFile_withoutFinalNL (void) {
  char inputBuffer[]=
    "abc\n"
    "de\0fg\n"
    "hij";
  FILE * inputFile= fmemopen (inputBuffer, sizeof inputBuffer - 1, "r");
  assert (inputFile != NULL);
   
  char * outputBuffer; size_t outputSize;
  FILE * outputFile= open_memstream (& outputBuffer, & outputSize);
  assert (outputFile != NULL);
  
  TextUtil_runRevOnFile (inputFile, outputFile);
  fclose (inputFile); fclose (outputFile);

  char expectedBuffer[]=
    "cba\n"
    "gf\0ed\n"
    "jih";
  assert (outputSize == sizeof expectedBuffer - 1); 
  assert (memcmp (expectedBuffer, outputBuffer, outputSize) == 0);  
  free (outputBuffer);
}

//------------------------------------------------------------------------------

void TextUtilTest_runRevOnFile_withFinalNL (void) {
  char inputBuffer[]=
    "abc\n"
    "de\0fg\n"
    "hij\n";
  FILE * inputFile= fmemopen (inputBuffer, sizeof inputBuffer - 1, "r");
  assert (inputFile != NULL);
   
  char * outputBuffer; size_t outputSize;
  FILE * outputFile= open_memstream (& outputBuffer, & outputSize);
  assert (outputFile != NULL);
  
  TextUtil_runRevOnFile (inputFile, outputFile);
  fclose (inputFile); fclose (outputFile);

  char expectedBuffer[]=
    "cba\n"
    "gf\0ed\n"
    "jih\n";
  assert (outputSize == sizeof expectedBuffer - 1); 
  assert (memcmp (expectedBuffer, outputBuffer, outputSize) == 0);  
  free (outputBuffer);
}

//==============================================================================

void TextUtilTest_runTacOnFile_withoutFinalNL (void) {
  char inputBuffer[]=
    "abc\n"
    "de\0fg\n"
    "hij";
  FILE * inputFile= fmemopen (inputBuffer, sizeof inputBuffer - 1, "r");
  assert (inputFile != NULL);
   
  char * outputBuffer; size_t outputSize;
  FILE * outputFile= open_memstream (& outputBuffer, & outputSize);
  assert (outputFile != NULL);
  
  TextUtil_runTacOnFile (inputFile, outputFile);
  fclose (inputFile); fclose (outputFile);

  char expectedBuffer[]=
    "hij\n"
    "de\0fg\n"
    "abc\n";
  assert (outputSize == sizeof expectedBuffer - 1); 
  assert (memcmp (expectedBuffer, outputBuffer, outputSize) == 0);  
  free (outputBuffer);
}

//------------------------------------------------------------------------------

void TextUtilTest_runTacOnFile_withFinalNL (void) {
  char inputBuffer[]=
    "abc\n"
    "de\0fg\n"
    "hij\n";
  FILE * inputFile= fmemopen (inputBuffer, sizeof inputBuffer - 1, "r");
  assert (inputFile != NULL);
   
  char * outputBuffer; size_t outputSize;
  FILE * outputFile= open_memstream (& outputBuffer, & outputSize);
  assert (outputFile != NULL);
  
  TextUtil_runTacOnFile (inputFile, outputFile);
  fclose (inputFile); fclose (outputFile);

  char expectedBuffer[]=
    "hij\n"
    "de\0fg\n"
    "abc\n";
  assert (outputSize == sizeof expectedBuffer - 1); 
  assert (memcmp (expectedBuffer, outputBuffer, outputSize) == 0);  
  free (outputBuffer);
}

//==============================================================================

void TextUtilTest_runFgrepOnFile_withFinalNL (void) {
 char inputBuffer[]=
   "xxx\n"
   "xxxaaayyy\n"
   "www\0xxxaaayyy\0zzz\n"
   "xxx\0yyy\0zzz\n"
   "xxxaaayyyaaazzzaaa\n";
  FILE * inputFile= fmemopen (inputBuffer, sizeof inputBuffer - 1, "r");
  assert (inputFile != NULL);
   
  char * outputBuffer; size_t outputSize;
  FILE * outputFile= open_memstream (& outputBuffer, & outputSize);
  assert (outputFile != NULL);
  
  TextUtil_runFgrepOnFile (inputFile, "aaa", "<", ">", outputFile);
  fclose (inputFile); fclose (outputFile);

  char expectedBuffer[]=
    "xxx<aaa>yyy\n"
    "www\0xxx<aaa>yyy\0zzz\n"
    "xxx<aaa>yyyaaazzzaaa\n";
  assert (outputSize == sizeof expectedBuffer - 1); 
  assert (memcmp (expectedBuffer, outputBuffer, outputSize) == 0);  
  free (outputBuffer);
}

//------------------------------------------------------------------------------

void TextUtilTest_runFgrepOnFile_withoutFinalNL (void) {
 char inputBuffer[]=
   "xxx\n"
   "xxxaaayyy\n"
   "www\0xxxaaayyy\0zzz\n"
   "xxx\0yyy\0zzz\n"
   "xxxaaayyyaaazzzaaa";
  FILE * inputFile= fmemopen (inputBuffer, sizeof inputBuffer - 1, "r");
  assert (inputFile != NULL);
   
  char * outputBuffer; size_t outputSize;
  FILE * outputFile= open_memstream (& outputBuffer, & outputSize);
  assert (outputFile != NULL);
  
  TextUtil_runFgrepOnFile (inputFile, "aaa", "[", "]", outputFile);
  fclose (inputFile); fclose (outputFile);

  char expectedBuffer[]=
    "xxx[aaa]yyy\n"
    "www\0xxx[aaa]yyy\0zzz\n"
    "xxx[aaa]yyyaaazzzaaa\n";
  assert (outputSize == sizeof expectedBuffer - 1); 
  assert (memcmp (expectedBuffer, outputBuffer, outputSize) == 0);  
  free (outputBuffer);
}

//==============================================================================

void TextUtilTest_readOneLinePerFile (void) {
  char inputBuffer0[]= "xxx\n";
  char inputBuffer1[]= "";
  char inputBuffer2[]= "yyy\0zzz";
  char inputBuffer3[]= "(should not be read, eof was already reached)";
  
  FILE * inputFile0= fmemopen (inputBuffer0, sizeof inputBuffer0 - 1, "r");
  FILE * inputFile1= fmemopen (inputBuffer1, sizeof inputBuffer1 - 1, "r");
  FILE * inputFile2= fmemopen (inputBuffer2, sizeof inputBuffer2 - 1, "r");
  FILE * inputFile3= fmemopen (inputBuffer3, sizeof inputBuffer3 - 1, "r");
  assert (inputFile0 != NULL);
  assert (inputFile1 != NULL);
  assert (inputFile2 != NULL);
  assert (inputFile3 != NULL);

  FILE * inputFiles[4]= { inputFile0, inputFile1, inputFile2, inputFile3 };
  bool         eofs[4]= { false     , false     , false      , true  };
  Line        lines[4];
  
  int readCount= TextUtil_readOneLinePerFile (lines, inputFiles, eofs, 4);
  fclose (inputFile0);
  fclose (inputFile1);
  fclose (inputFile2);
  fclose (inputFile3);
  
  assert (readCount == 2);
  
  assert ( ! eofs[0]); // unchanged
  assert (   eofs[1]); // set to true as eof is reached
  assert ( ! eofs[2]); // unchanged
  assert (   eofs[3]); // unchanged
  
  assert (lines[0].length == 4);
  assert (lines[1].length == 0);
  assert (lines[2].length == 7);
  assert (lines[3].length == 0); // not read, eof was already reached

  assert (memcmp (lines[0].chars, "xxx\n", 4+1) == 0);
  assert (memcmp (lines[1].chars, "", 0+1) == 0);
  assert (memcmp (lines[2].chars, "yyy\0zzz", 7+1) == 0);
  assert (memcmp (lines[3].chars, "", 0+1) == 0);

  Line_clean (lines[0]);
  Line_clean (lines[1]);
  Line_clean (lines[2]);
  Line_clean (lines[3]); 
}

//------------------------------------------------------------------------------

void TextUtilTest_printPastedLines_withoutFinalNL (void) {
  Line line0= (Line) { .length= 8 , .chars= "aaa\0bbb\n" };
  Line line1= (Line) { .length= 4 , .chars= "ccc\n" };
  Line line2= (Line) { .length= 7 , .chars= "ddd\0eee" };
  Line lines[3]= { line0, line1, line2 };

  char * outputBuffer; size_t outputSize;
  FILE * outputFile= open_memstream (& outputBuffer, & outputSize);
  assert (outputFile != NULL);
  
  TextUtil_printPastedLines (lines, 3, "<*>", outputFile);
  fclose (outputFile);

  char expectedBuffer[]= "aaa\0bbb<*>ccc<*>ddd\0eee\n";
  assert (outputSize == sizeof expectedBuffer - 1);
  assert (memcmp (expectedBuffer, outputBuffer, outputSize) == 0);
  free (outputBuffer);
}

//------------------------------------------------------------------------------

void TextUtilTest_printPastedLines_withFinalNL (void) {
  Line line0= (Line) { .length= 8 , .chars= "aaa\0bbb\n" };
  Line line1= (Line) { .length= 4 , .chars= "ccc\n" };
  Line line2= (Line) { .length= 8 , .chars= "ddd\0eee\n" };
  Line lines[3]= { line0, line1, line2 };

  char * outputBuffer; size_t outputSize;
  FILE * outputFile= open_memstream (& outputBuffer, & outputSize);
  assert (outputFile != NULL);
  
  TextUtil_printPastedLines (lines, 3, "<*>", outputFile);
  fclose (outputFile);

  char expectedBuffer[]= "aaa\0bbb<*>ccc<*>ddd\0eee\n";
  assert (outputSize == sizeof expectedBuffer - 1);
  assert (memcmp (expectedBuffer, outputBuffer, outputSize) == 0);
  free (outputBuffer);
}

//------------------------------------------------------------------------------

void TextUtilTest_runPasteOnFiles  (void) {
 char inputBuffer0[]=
   "xxx\n"
   "yyy\n"
   "zzz\n";
 char inputBuffer1[]=
   "aaa\n"
   "bbb\0ccc\n";
 char inputBuffer2[]=
   "rrr\0sss\n"
   "ttt\n"
   "uuu\0vvv\n"
   "www";

  FILE * inputFile0= fmemopen (inputBuffer0, sizeof inputBuffer0 - 1, "r");
  FILE * inputFile1= fmemopen (inputBuffer1, sizeof inputBuffer1 - 1, "r");
  FILE * inputFile2= fmemopen (inputBuffer2, sizeof inputBuffer2 - 1, "r");
  assert (inputFile0 != NULL);
  assert (inputFile1 != NULL);
  assert (inputFile2 != NULL);
   
  char * outputBuffer; size_t outputSize;
  FILE * outputFile= open_memstream (& outputBuffer, & outputSize);
  assert (outputFile != NULL);

  FILE * inputFiles[3]= { inputFile0, inputFile1, inputFile2 };
  TextUtil_runPasteOnFiles (inputFiles, 3, "<*>", outputFile);
  fclose (inputFile0); fclose (inputFile1); fclose (inputFile2);
  fclose (outputFile);

  char expectedBuffer[]=
    "xxx<*>aaa<*>rrr\0sss\n"
    "yyy<*>bbb\0ccc<*>ttt\n"
    "zzz<*><*>uuu\0vvv\n"
    "<*><*>www\n"; 
  assert (outputSize == sizeof expectedBuffer - 1); 
  assert (memcmp (expectedBuffer, outputBuffer, outputSize) == 0);  
  free (outputBuffer);
}

//==============================================================================

void TextUtilTest_printCutLine_firstField (void)
{
  Line line= (Line) { .length= 16, .chars= "a\0a<*>b\0b<*>c\0c\n" };

  char * outputBuffer; size_t outputSize;
  FILE * outputFile= open_memstream (& outputBuffer, & outputSize);
  assert (outputFile != NULL);
  TextUtil_printCutLine (line, "<*>", 1, outputFile); 
  fclose (outputFile);

  char expectedBuffer[]= "a\0a\n";
  assert (outputSize == sizeof expectedBuffer - 1); 
  assert (memcmp (expectedBuffer, outputBuffer, outputSize) == 0);  
  free (outputBuffer);
}

//------------------------------------------------------------------------------

void TextUtilTest_printCutLine_lastField (void)
{
  Line line= (Line) { .length= 16, .chars= "a\0a<*>b\0b<*>c\0c\n" };

  char * outputBuffer; size_t outputSize;
  FILE * outputFile= open_memstream (& outputBuffer, & outputSize);
  assert (outputFile != NULL);
  TextUtil_printCutLine (line, "<*>", 3, outputFile); 
  fclose (outputFile);

  char expectedBuffer[]= "c\0c\n";
  assert (outputSize == sizeof expectedBuffer - 1); 
  assert (memcmp (expectedBuffer, outputBuffer, outputSize) == 0);  
  free (outputBuffer);
}

//------------------------------------------------------------------------------

void TextUtilTest_printCutLine_middleField (void)
{
  Line line= (Line) { .length= 16, .chars= "a\0a<*>b\0b<*>c\0c\n" };

  char * outputBuffer; size_t outputSize;
  FILE * outputFile= open_memstream (& outputBuffer, & outputSize);
  assert (outputFile != NULL);
  TextUtil_printCutLine (line, "<*>", 2, outputFile); 
  fclose (outputFile);

  char expectedBuffer[]= "b\0b\n";
  assert (outputSize == sizeof expectedBuffer - 1); 
  assert (memcmp (expectedBuffer, outputBuffer, outputSize) == 0);  
  free (outputBuffer);
}

//------------------------------------------------------------------------------

void TextUtilTest_printCutLine_wholeLineField (void)
{
  Line line= (Line) { .length= 4, .chars= "x\0x\n" };

  char * outputBuffer; size_t outputSize;
  FILE * outputFile= open_memstream (& outputBuffer, & outputSize);
  assert (outputFile != NULL);
  TextUtil_printCutLine (line, "<*>", 1, outputFile); 
  fclose (outputFile);

  char expectedBuffer[]= "x\0x\n";
  
  assert (outputSize == sizeof expectedBuffer - 1); 
  assert (memcmp (expectedBuffer, outputBuffer, outputSize) == 0);  
  free (outputBuffer);
}

//------------------------------------------------------------------------------

void TextUtilTest_printCutLine_missingField (void)
{
  Line line= (Line) { .length= 16, .chars= "a\0a<*>b\0b<*>c\0c\n" };

  char * outputBuffer; size_t outputSize;
  FILE * outputFile= open_memstream (& outputBuffer, & outputSize);
  assert (outputFile != NULL);
  TextUtil_printCutLine (line, "<*>", 4, outputFile); 
  fclose (outputFile);

  char expectedBuffer[]= "\n";
  assert (outputSize == sizeof expectedBuffer - 1); 
  assert (memcmp (expectedBuffer, outputBuffer, outputSize) == 0);  
  free (outputBuffer);
}

//------------------------------------------------------------------------------

void TextUtilTest_runCutOnFile (void) {
 char inputBuffer[]=
   "xxx<*>yyy<*>zzz\n"
   "aaa<*>b\0b\n"
   "zzz\n"
   "r\0r<*>sss<*>ttt\n";
 
  FILE * inputFile= fmemopen (inputBuffer, sizeof inputBuffer - 1, "r");
  assert (inputFile != NULL);
   
  char * outputBuffer; size_t outputSize;
  FILE * outputFile= open_memstream (& outputBuffer, & outputSize);
  assert (outputFile != NULL);
  
  TextUtil_runCutOnFile (inputFile, "<*>", 2, outputFile);
  fclose (inputFile); fclose (outputFile);

  char expectedBuffer[]=
    "yyy\n"
    "b\0b\n"
    "\n"
    "sss\n";
  assert (outputSize == sizeof expectedBuffer - 1); 
  assert (memcmp (expectedBuffer, outputBuffer, outputSize) == 0);  
  free (outputBuffer);
}

//==============================================================================

void TextUtilTest_runAll (void) {

 TextUtilTest_runNlOnFile_withSkipEmpty_withoutFinalNL ();
 TextUtilTest_runNlOnFile_withoutSkipEmpty_withFinalNL ();

 TextUtilTest_runRevOnFile_withoutFinalNL ();
 TextUtilTest_runRevOnFile_withFinalNL ();

 TextUtilTest_runTacOnFile_withoutFinalNL ();
 TextUtilTest_runTacOnFile_withFinalNL ();
 
 TextUtilTest_runFgrepOnFile_withoutFinalNL ();
 TextUtilTest_runFgrepOnFile_withFinalNL ();
 
 TextUtilTest_readOneLinePerFile ();
 TextUtilTest_printPastedLines_withoutFinalNL ();
 TextUtilTest_printPastedLines_withFinalNL ();
 TextUtilTest_runPasteOnFiles ();

 TextUtilTest_printCutLine_firstField ();
 TextUtilTest_printCutLine_lastField ();
 TextUtilTest_printCutLine_middleField ();
 TextUtilTest_printCutLine_wholeLineField ();
 TextUtilTest_printCutLine_missingField ();
 TextUtilTest_runCutOnFile ();
}

//==============================================================================
