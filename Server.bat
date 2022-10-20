@echo off
set map=%1
set sessionName=%*
set launchDir="%cd%\SessionTestServer.exe"
echo %launchDir% %map% -log %sessionName%

start "ServerFile" %launchDir% %map% -log -sessionName=sessionName