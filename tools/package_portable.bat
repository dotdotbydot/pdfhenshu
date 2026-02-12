@echo off
setlocal

if "%~1"=="" (
  echo Usage: package_portable.bat ^<BUILD_DIR^>
  exit /b 1
)

set BUILD_DIR=%~1
set OUT_DIR=%BUILD_DIR%\portable

if exist "%OUT_DIR%" rmdir /s /q "%OUT_DIR%"
mkdir "%OUT_DIR%\runtime\bin"
mkdir "%OUT_DIR%\runtime\dll"

copy "%BUILD_DIR%\pdfhenshu.exe" "%OUT_DIR%\" >nul
copy "runtime\pdfhenshu.ini" "%OUT_DIR%\runtime\" >nul

echo Copy qpdf.exe / mutool.exe and required DLLs into:
echo   %OUT_DIR%\runtime\bin
echo   %OUT_DIR%\runtime\dll

exit /b 0
