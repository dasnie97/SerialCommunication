#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main()
{
    char* mystring = "Hello World!";
    printf(mystring);

    for(int i=0;i<strlen(mystring);i++)
    {
        printf("\n");
        printf("%c", mystring[i]);
    }

    return 0;
}