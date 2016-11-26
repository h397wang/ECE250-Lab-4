@echo off
setlocal
path C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\;C:\Program Files (x86)\Dev-Cpp\MinGW64\libexec\gcc\x86_64-w64-mingw32\4.8.1\;%path%
g++ %1.cpp -o %1.exe
endlocal
echo on