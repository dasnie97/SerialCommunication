#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    HANDLE hFile;
    BOOL succesfulOperation;
    char ReadBuffer[100];
    DWORD dwBytesToWrite = 0;

    SYSTEMTIME st;
    
    hFile = CreateFileA(
        "C:\\Users\\Damian\\source\\repos\\SerialCommunication\\Driver\\test.txt",
        FILE_APPEND_DATA | FILE_READ_ACCESS,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);

    if (hFile == INVALID_HANDLE_VALUE) 
    { 
        printf("Nie dziala");
        return 0; 
    }

    succesfulOperation = ReadFile(hFile, ReadBuffer, 99, NULL, NULL);

    for (int i=0 ; i<100; i++)
    {
        GetLocalTime(&st);

        char* ptr = (char*)calloc(100, sizeof(char));

        sprintf(ptr, "Application running at %.2d.%.2d.%.4d  %.2d:%.2d:%.2d\n", st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute, st.wSecond);

        dwBytesToWrite = (DWORD)strlen(ptr);

        succesfulOperation = WriteFile(hFile, ptr, dwBytesToWrite, NULL, NULL);

        free(ptr);
    }

    CloseHandle(hFile);

    return 0;
}