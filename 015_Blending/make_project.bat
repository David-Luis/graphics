@echo off
if not exist "./project" mkdir "./project"
cd project

if not exist "./Debug" mkdir "./Debug"
copy "..\..\Assimp\lib\assimp-vc140-mt.dll" ".\Debug"

cmake ../

cd ..