if not exist "./Debug" mkdir "./Debug"
copy "..\Assimp\lib\assimp-vc140-mt.dll" ".\Debug"

if not exist "./project" mkdir "./project"
cd project
cmake ../