@echo off

call "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Auxiliary\Build\vcvars64.bat"

SET SOURCE_FILE=__NAME__/src/main.cpp
SET OUTPUT_FILE=Build/__NAME__.exe

cl /EHsc %SOURCE_FILE% /Fe%OUTPUT_FILE% /FoBuild/


