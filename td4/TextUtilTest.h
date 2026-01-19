#ifndef TEXT_UTIL_TEST_H
#define TEXT_UTIL_TEST_H

//==============================================================================
  
void TextUtilTest_runNlOnFile_withSkipEmpty_withoutFinalNL (void);
void TextUtilTest_runNlOnFile_withoutSkipEmpty_withFinalNL (void);

//==============================================================================
  
void TextUtilTest_runRevOnFile_withoutFinalNL (void);
void TextUtilTest_runRevOnFile_withFinalNL    (void);

//==============================================================================

void TextUtilTest_runTacOnFile_withoutFinalNL (void);
void TextUtilTest_runTacOnFile_withFinalNL    (void);

//==============================================================================

void TextUtilTest_runFgrepOnFile_withoutFinalNL(void);
void TextUtilTest_runFgrepOnFile_withFinalNL   (void);

//==============================================================================

void TextUtilTest_readOneLinePerFile (void);

void TextUtilTest_printPastedLines_withoutFinalNL (void);
void TextUtilTest_printPastedLines_withFinalNL    (void);

void TextUtilTest_runPasteOnFiles    (void);

//==============================================================================

void TextUtilTest_printCutLine_firstField    (void);
void TextUtilTest_printCutLine_lastField     (void);
void TextUtilTest_printCutLine_middleField   (void);
void TextUtilTest_printCutLine_wholeLineField(void);
void TextUtilTest_printCutLine_missingField  (void);

void TextUtilTest_runCutOnFile (void);

//==============================================================================

void TextUtilTest_runAll (void);

//==============================================================================

#endif
