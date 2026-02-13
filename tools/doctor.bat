@echo off
setlocal

echo [pdfhenshu doctor] Checking folder layout...

if not exist "CMakeLists.txt" (
  echo ERROR: CMakeLists.txt not found in current directory.
  echo Open the repository root folder and run this again.
  exit /b 1
)

if not exist "src\main.c" (
  echo ERROR: src\main.c missing.
  exit /b 1
)

if not exist "src\config.c" (
  echo ERROR: src\config.c missing.
  exit /b 1
)

if not exist "include\config.h" (
  echo ERROR: include\config.h missing.
  exit /b 1
)

echo OK: required files exist.

echo [pdfhenshu doctor] Checking toolchain commands...
where cmake >nul 2>nul
if errorlevel 1 (
  echo ERROR: cmake not found in PATH.
  exit /b 1
)

echo OK: cmake found.

echo Hint: run
 echo   cmake --preset default
 echo   cmake --build --preset default

exit /b 0
