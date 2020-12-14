@echo off
pushd ..\
call vendor\premake\bin\premake5.exe vs2019
popd
PAUSE