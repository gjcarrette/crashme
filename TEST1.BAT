@SETLOCAL
@SET SELF=%~dps0
@PATH %SELF%output\Release\pddet;%SELF%output\Release\crashme;%PATH%
@PATH
@%SELF%OUTPUT\RELEASE\PDDET\PDDET.EXE -examine 16
@REM NOTE: For CRASHME to work properly in subprocess-creation mode
@REM       it must be invoked with a pathname which is fully qualified
@REM       and without spaces.
@SET CRASHLOG=CRASHME.LOG
@%SELF%OUTPUT\RELEASE\CRASHME\CRASHME.EXE 8192 666 100 00:00:30 3


