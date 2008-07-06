@SETLOCAL
@SET WIXBIN=%PROGRAMFILES%\Windows Installer XML\bin
@SET NETBIN=%WINDIR%\Microsoft.NET\Framework\v3.5
@SET VS9BIN=%PROGRAMFILES%\Microsoft Visual Studio 9.0\Common7\IDE
@PATH %PATH%;%WIXBIN%;%NETBIN%;%VS8BIN%
@SET T=Release
@MSBUILD CRASHME.SLN /Target:Build /p:Configuration=Release







