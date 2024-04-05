#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

char* SayHello()
{
    char* string = "Hello World!";
    return string;
}

int main()
{
    char* value = SayHello();
    printf(value);

    return 0;
}