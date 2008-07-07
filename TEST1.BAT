@SETLOCAL
@SET SELF=%~dp0
@PATH %SELF%output\Release\pddet;%SELF%output\Release\crashme;%SELF%;%PATH%
@
@PDDET -examine 16
@
@SET CRASHLOG=CRASHME.LOG
@CRASHME 8192 666 100 00:00:30 3

