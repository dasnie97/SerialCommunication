#include <windows.h>
#include <stdio.h>
#include <tchar.h>

int main()
{
    HANDLE hFile;
    BOOL succesfulOperation;
    char ReadBuffer[100];
    char WriteBuffer[] = "\nCoś tam działa :)\n";
    DWORD dwBytesToWrite = (DWORD)strlen(WriteBuffer);
    OVERLAPPED ol = {0};

    hFile = CreateFileA(
        "C:\\Users\\Damian\\source\\repos\\SerialCommunication\\Driver\\test.txt",
        GENERIC_ALL,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);

    if (hFile == INVALID_HANDLE_VALUE) 
    { 
        printf(_T("Nie dziala"));
        return 0; 
    }

    succesfulOperation = ReadFile(hFile, ReadBuffer, 99, NULL, NULL);

    succesfulOperation = WriteFile(hFile, WriteBuffer, dwBytesToWrite, NULL, NULL);

    CloseHandle(hFile);

    return 0;
}