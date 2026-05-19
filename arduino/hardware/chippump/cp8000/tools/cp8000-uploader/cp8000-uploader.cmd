@echo off
set DIR=%~dp0
if "%PYTHON%"=="" set PYTHON=python
set PYTHONPATH=%DIR%;%PYTHONPATH%
"%PYTHON%" -m cp8000_uploader %*
