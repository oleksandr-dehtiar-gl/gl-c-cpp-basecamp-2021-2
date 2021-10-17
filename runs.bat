@echo off

rem ======================= SERVER =====================
echo -- Start server 
REM ==> compiling whith minGW
start cmd /k "build\transferBigData\server\server.exe"
REM ==> compiling whith MSVC
REM start cmd /k "..\build\transferBigData\server\Debug\server.exe"

