echo off

REM batch file for distribution of CHIRRUP
REM $Header: /comm/chirrup/dist.bat 1     09/05/14 3:50 tsupo $

chmod -R +w dist

rm -Rf dist\src

mkdir dist\src
mkdir dist\src\chirrup
mkdir dist\src\chirrup\res
mkdir dist\src\chirrup\png2bmp
mkdir dist\src\include
mkdir dist\src\lib

copy *.c dist\src\chirrup
copy *.h dist\src\chirrup
copy *.cpp dist\src\chirrup
copy png2bmp\*.c dist\src\chirrup\png2bmp
copy png2bmp\*.h dist\src\chirrup\png2bmp
copy chirrup.rc dist\src\chirrup
copy res\*.ico dist\src\chirrup\res
copy res\*.rc2 dist\src\chirrup\res
copy res\*.bmp dist\src\chirrup\res
copy res\*.cur dist\src\chirrup\res
copy readme.txt           dist
copy chirrup.exe.manifest dist
copy Release\chirrup.exe  dist
copy Release\xmlRPC.dll   dist

copy ..\xmlRPC\encryptRSA.h    dist\src\include
copy ..\xmlRPC\multipart.h     dist\src\include
copy ..\xmlRPC\sha1.h          dist\src\include
copy ..\xmlRPC\xmlRPC.h        dist\src\include
copy ..\xmlRPC\misc\strncmpi.c dist\src\chirrup
copy ..\bookey\timelocal.c     dist\src\chirrup

copy ..\xmlRPC\Release\xmlRPC.lib dist\src\lib
