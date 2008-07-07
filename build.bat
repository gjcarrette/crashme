@SETLOCAL
@SET WIXBIN=%PROGRAMFILES%\Windows Installer XML\bin
@SET NETBIN=%WINDIR%\Microsoft.NET\Framework\v3.5
@SET VS9BIN=%PROGRAMFILES%\Microsoft Visual Studio 9.0\Common7\IDE
@PATH %PATH%;%WIXBIN%;%NETBIN%;%VS8BIN%
@SET T=Release
@MSBUILD CRASHME.SLN /Target:Build /p:Configuration=Release
@
@IF EXIST CRASHME.WIXOBJ DEL CRASHME.WIXOBJ
@CANDLE CRASHME.WXS -nologo
@ECHO Linking CRASHME installer.
@IF EXIST CRASHME.MSI DEL CRASHME.MSI
@REM Note: WixUI_en-us.wxl might be in your wix-2.0.4820.0-binaries
@REM       and not in the %WIXBIN% as installed.
@LIGHT CRASHME.WIXOBJ -nologo "%WIXBIN%\WixUI.wixlib" -loc "%WIXBIN%\WixUI_en-us.wxl" -out CRASHME.MSI
@Echo Build Done







