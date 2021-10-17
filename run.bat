cd run

@echo off

echo -- Delete file copy
del copy.mp4

rem ======================= SERVER =====================
echo -- Start server 
timeout /t 1
REM ==> compiling whith minGW
start cmd /k "..\build\transferBigData\server\server.exe"
REM ==> compiling whith MSVC
REM start cmd /k "..\build\transferBigData\server\Debug\server.exe"

rem ======================= CLIENT =====================
echo -- Start client
timeout /t 1
REM ==> compiling whith minGW
start cmd /k "..\build\transferBigData\client\client.exe"
REM ==> compiling whith MSVC
REM start cmd /k "..\build\transferBigData\client\Debug\client.exe"

cd ..
