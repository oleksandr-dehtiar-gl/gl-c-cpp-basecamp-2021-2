cd run

@echo off

echo -- Delete file copy
del copy.mp4

timeout /t 2
echo -- Start server 
start cmd /k "..\build\transferBigData\server\server.exe"

timeout /t 1
echo -- Start client
start cmd /k "..\build\transferBigData\client\client.exe"

cd ..
