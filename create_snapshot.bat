:: This command will create a local pre release version for local testing
@ECHO OFF

REM Check if a release version argument is provided
if "%~1"=="" (
    echo Error: Please provide a release version as an argument.
    exit /b 1
)

REM Set the RELEASE_VERSION variable to the user input
set "RELEASE_VERSION=%~1"

REM Create the directory structure
mkdir "Community_A-4E-C_%RELEASE_VERSION%\Mods\aircraft"

REM Run the Python script to get binaries
python get_binaries.py

REM Copy files
xcopy /s /i A-4E-C "Community_A-4E-C_%RELEASE_VERSION%\Mods\aircraft\A-4E-C"
copy README.md "Community_A-4E-C_%RELEASE_VERSION%\README.md"
copy CHANGELOG.md "Community_A-4E-C_%RELEASE_VERSION%\CHANGELOG %RELEASE_VERSION%.md"

REM Change directory
cd "Community_A-4E-C_%RELEASE_VERSION%"

REM End of the script
exit /b 0