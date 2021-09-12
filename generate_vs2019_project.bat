@echo off
where /q conan
IF ERRORLEVEL 1 (
    echo Conan package manager is not installed. The installation instructions are located on the official website: https://conan.io/.
    pause
    exit /b
)

conan install .

echo.
echo Packages were downloaded. Generating project files with premake.
echo.

where /q premake5
IF ERRORLEVEL 1 (
    echo Project would be generated with premake5, but it was not found. You can download it from its repository: https://premake.github.io/.
    pause
    exit /b
)
premake5 vs2019

echo.
echo Visual Studio project successfully generated!
echo.
pause
