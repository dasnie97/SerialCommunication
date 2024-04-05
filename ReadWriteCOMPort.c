#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

HANDLE OpenCOMPortForAppendingAndReading(char* fileName)
{
    HANDLE hFile = CreateFileA(
        fileName,
        GENERIC_READ | GENERIC_WRITE,
        NULL,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (hFile == INVALID_HANDLE_VALUE) 
    { 
        printf("\nFatal Error 0x%x: Unable to open\n", GetLastError());
        return 0;
    }
    else
    {
        printf("\nCOM is now open\n");
        return hFile;
    }
}    

//Purge any outstanding requests on the serial port (initialize)
void purgePort(HANDLE hCom) 
{
    PurgeComm(hCom, PURGE_RXABORT | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_TXCLEAR);
}

static int SetComParms(HANDLE hCom, int nComRate, int nComBits, COMMTIMEOUTS timeout) {
	DCB dcb;										// Windows device control block
	// Clear DCB to start out clean, then get current settings
	memset(&dcb, 0, sizeof(dcb));
	dcb.DCBlength = sizeof(dcb);
	if (!GetCommState(hCom, &dcb))
		return(0);

	// Set our own parameters from Globals
	dcb.BaudRate = nComRate;						// Baud (bit) rate
	dcb.ByteSize = (BYTE)nComBits;					// Number of bits(8)
	dcb.Parity = 0;									// No parity	
	dcb.StopBits = ONESTOPBIT;						// One stop bit
	if (!SetCommState(hCom, &dcb))
		return(0);

	// Set communication timeouts (SEE COMMTIMEOUTS structure in MSDN) - want a fairly long timeout
	memset((void *)&timeout, 0, sizeof(timeout));
	timeout.ReadIntervalTimeout = 500;				// Maximum time allowed to elapse before arival of next byte in milliseconds. If the interval between the arrival of any two bytes exceeds this amount, the ReadFile operation is completed and buffered data is returned
	timeout.ReadTotalTimeoutMultiplier = 1;			// The multiplier used to calculate the total time-out period for read operations in milliseconds. For each read operation this value is multiplied by the requested number of bytes to be read
	timeout.ReadTotalTimeoutConstant = 5000;		// A constant added to the calculation of the total time-out period. This constant is added to the resulting product of the ReadTotalTimeoutMultiplier and the number of bytes (above).
	SetCommTimeouts(hCom, &timeout);
	return(1);
}

char* BuildStringToWrite()
{
    SYSTEMTIME st;

    GetLocalTime(&st);
    char* ptr = (char*)calloc(100, sizeof(char));
    sprintf(ptr, "Application running at %.2d.%.2d.%.4d  %.2d:%.2d:%.2d\n", st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute, st.wSecond);

    return ptr;
}

int main()
{
    BOOL succesfulOperation;
    char ReadBuffer[100];
    DWORD dwBytesToWrite = 0;
    COMMTIMEOUTS timeout;

    HANDLE hFile = OpenCOMPortForAppendingAndReading("COM3");
    purgePort(hFile);
    SetComParms(hFile, 9600, 8, timeout);
    purgePort(hFile);

    for (int i=0 ; i<100; i++)
    {
        char* ptr = BuildStringToWrite();
        dwBytesToWrite = (DWORD)strlen(ptr);
        succesfulOperation = WriteFile(hFile, ptr, dwBytesToWrite, NULL, NULL);
        succesfulOperation = ReadFile(hFile, ReadBuffer, dwBytesToWrite, NULL, NULL);
        free(ptr);
    }

    CloseHandle(hFile);
    return 0;
}