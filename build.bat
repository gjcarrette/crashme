@SETLOCAL
@REM This was tested using the following development environment:
@REM VS Express 2013 for Desktop
@REM WiX Toolset v3.8
@REM
@SET WIXBIN=c:\Program Files (x86)\WiX Toolset v3.8\bin
@SET NETBIN=c:\Program Files (x86)\MSBuild\12.0\Bin
@PATH %PATH%;%WIXBIN%;%NETBIN%
@
@MSBUILD CRASHME.SLN /Target:Build /p:Configuration=Release /p:Platform=x64
@
@ECHO Compiling CRASHME installer
@
@IF EXIST CRASHME.WIXOBJ DEL CRASHME.WIXOBJ
@CANDLE CRASHME.WXS -nologo
@
@ECHO Linking CRASHME installer.
@
@IF EXIST CRASHME.MSI DEL CRASHME.MSI
@LIGHT CRASHME.WIXOBJ  -ext WixUIExtension -nologo -out CRASHME-2-8-4.MSI
@
@Echo Build Done
