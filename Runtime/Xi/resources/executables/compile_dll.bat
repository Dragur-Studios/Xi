@echo off

call "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Auxiliary\Build\vcvars64.bat"

SET includes= /I"__NAME__/src" /I"Z:\Dev\Xi\Engine\Core\src"
SET links= /link /LIBPATH:"Z:\Dev\Xi\Build\Engine\" core.lib 
SET defines= /D DEBUG 

SET binaries=/OUT:Build/__NAME__.dll /IMPLIB:Build/__NAME__.lib
SET intermediates=/Fo"Build/" /FdBuild/__NAME__.pdb 

echo "Building DLL Project"


cl /EHsc /LD %intermediates% %includes% %defines% __NAME__/src/__NAME__.cpp %links% %binaries%