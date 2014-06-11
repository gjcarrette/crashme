@SETLOCAL
@CALL %~dps0SETUP.CMD
@
@SET NSUB_PARAM=05:00:00
@IF NOT "%1" == "" SET NSUB_PARAM=%1
@
@ECHO NSUB_PARAM=%NSUB_PARAM%
@
@SET CRASHLOG=%LOG_PREFIX%CRASHME-TEST5-%NOW_TS%.LOG
@SET CRASHPRNG=MT
@
@ECHO CRASHLOG=%CRASHLOG%
@
@REM A verbose setting of 3 will show individual crashme sub-process
@REM command line parameters allowing a quicker problem reproduction
@REM by identifying the most recent random number seed before
@REM a system crash. There remains variability still in the location
@REM of virtual memory returned by VirtualAlloc
@REM A verbose setting of 5 will show the individual try/catch exceptions
@REM encountered by each subprocess
@
@CRASHME +65536.128 666 100 %NSUB_PARAM% 3
@
@ECHO ENDED %DATE% %TIME% >> %CRASHLOG%
@
@ECHO CRASHLOG=%CRASHLOG%
@
@IF "%NOPAUSE%"=="1" GOTO :EOF
@PAUSE


