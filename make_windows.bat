REM call "C:\Program Files\Microsoft Visual Studio 9.0\VC\vcvarsall.bat"

cd WindowsAudioInputDevice
echo making WindowsAudioInputDevice...
nmake /NOLOGO /f WindowsAudioInputDevice.mak

cd ../liveMedia
echo making liveMedia...
nmake /NOLOGO /f liveMedia.mak

cd ../groupsock
echo making groupsock...
nmake /NOLOGO /f groupsock.mak

cd ../UsageEnvironment
echo making UsageEnvironment...
nmake /NOLOGO /f UsageEnvironment.mak

cd ../BasicUsageEnvironment
echo making BasicUsageEnvironment...
nmake /NOLOGO /f BasicUsageEnvironment.mak

cd ../testProgs
echo making testProgs...
nmake /NOLOGO /f testProgs.mak

cd ../mediaServer
echo making mediaServer...
nmake /NOLOGO /f mediaServer.mak

cd ..