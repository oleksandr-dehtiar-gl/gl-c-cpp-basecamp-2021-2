@echo off

rem ======================= CLIENT =====================
echo -- Start client
REM timeout /t 1
REM ==> compiling whith minGW
start cmd /k "build\transferBigData\client\client.exe"
REM ==> compiling whith MSVC
REM start cmd /k "build\transferBigData\client\Debug\client.exe"

