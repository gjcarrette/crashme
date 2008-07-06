@SETLOCAL
@SET SELF=%~dp0
@ECHO %SELF%
@PATH %SELF%output\Release\pddet;%SELF%output\Release\crashme;%PATH%
@PATH
@pddet -examine 16
@SET CRASHLOG=CRASHME.LOG
@CRASHME 8192 666 0 -3






