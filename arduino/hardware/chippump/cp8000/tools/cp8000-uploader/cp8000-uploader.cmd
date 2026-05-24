@echo off
set DIR=%~dp0
set PYTHONPATH=%DIR%;%PYTHONPATH%
if not "%PYTHON%"=="" (
  "%PYTHON%" -m cp8000_uploader %*
  exit /b %errorlevel%
)
where py >nul 2>nul
if not errorlevel 1 (
  py -3 -m cp8000_uploader %*
  exit /b %errorlevel%
)
where python3 >nul 2>nul
if not errorlevel 1 (
  python3 -m cp8000_uploader %*
  exit /b %errorlevel%
)
where python >nul 2>nul
if not errorlevel 1 (
  python -m cp8000_uploader %*
  exit /b %errorlevel%
)
echo cp8000-uploader: Python 3.9 or newer was not found. 1>&2
echo cp8000-uploader: Install Python 3 for Windows, or set PYTHON to the full python.exe path. 1>&2
exit /b 1
