if not exist "./Debug" mkdir "./Debug"
copy "..\Assimp\lib\assimp-vc140-mt.dll" ".\Debug"
cmake .
start Application.sln