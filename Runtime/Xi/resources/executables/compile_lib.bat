@echo off

call "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Auxiliary\Build\vcvars64.bat"

SET includes= /I"/__NAME__/src" /I"Z:\Dev\Xi\Engine\Core\src"
SET links= /link /LIBPATH:"Z:\Dev\Xi\Build\Engine\" core.lib 
SET defines= /D DEBUG 

SET binaries=/IMPLIB: /Build__NAME__.lib
SET intermediates=/Fo"/Build/" /FdBuild__NAME__.pdb 

echo "Building LIB Project"

cl /EHsc /c %intermediates% %includes% %defines% __NAME__/src/__NAME__.cpp %links% %binaries%
