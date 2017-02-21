#include <stdio.h>
#include <Windows.h>
#include <winioctl.h>

int main(int argc, char *argv[])
{
    char driveLetter = 'd';
    char filePath[10];
    
    sprintf(filePath, "\\\\.\\%c:", driveLetter);
    
    printf("Drive: %s\r\n", filePath);
    
    // like the open() syscal on linux    
    HANDLE drive = CreateFile(filePath,GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, \
                              0,  OPEN_EXISTING, 0, 0);
    
    if (drive == INVALID_HANDLE_VALUE)
    {
        int error = GetLastError();
        printf("fail: %i\r\n", error);
        ExitProcess(-1);
    }
    
    DWORD bytes = 0;
    
    DeviceIoControl(drive, FSCTL_LOCK_VOLUME, 0,0,0,0,&bytes,0);
    //DeviceIoControl(drive, FSCTL_DISMOUNT_VOLUME, 0,0,0,0,0&bytes,0);
    DeviceIoControl(drive, IOCTL_STORAGE_MEDIA_REMOVAL, 0,0,0,0,&bytes,0);
    DeviceIoControl(drive, IOCTL_STORAGE_EJECT_MEDIA, 0,0,0,0,&bytes,0);
    DeviceIoControl(drive, FSCTL_UNLOCK_VOLUME, 0,0,0,0,&bytes,0);     
    
    CloseHandle(drive);
    
    
    //mciSendStringA("set cdaudio door open",0,0,0);
    return 0;
}
