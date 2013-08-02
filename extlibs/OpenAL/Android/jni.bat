@echo off

rem Pfade duerfen KEINE LEERZEICHEN enthalten

@echo on

javah -classpath bin/classes -d jni org.pielot.openal.OpenAlBridge

pause: