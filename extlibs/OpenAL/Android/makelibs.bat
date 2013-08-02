@echo off

rem Pfade duerfen KEINE LEERZEICHEN enthalten

set BASHPATH="C:\cygwin\bin\bash"
set PROJECTDIR="/cygdrive/d/dev/workspace-android/OpenAL4Android"
set NDKDIR="/cygdrive/d/dev/SDKs/android-ndk-r5b/ndk-build"

@echo on

rem javah -classpath bin -d jni org.haptimap.offis.accessiblemap.OpenAl

%BASHPATH% --login -c "cd %PROJECTDIR% && %NDKDIR%

pause: