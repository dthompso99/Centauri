SET FREETYPE_DIR="D:\dev\magnum-centauri\output\"
rd /s /q cmake_build_win\CENTAURI
mkdir cmake_build_win
cd cmake_build_win
cmake .. -DCMAKE_GENERATOR="Visual Studio 14 2015 Win64" -DCMAKE_BUILD_TYPE=Debug -DHUNTER_CONFIGURATION_TYPES=Debug
cmake --build . --target custom-install --config Debug
cd ..
output\Debug\bin\Centauri.exe