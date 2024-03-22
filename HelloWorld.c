#include <stdio.h>

int main()
{
    char array_of_chars[] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!', '\0'};
    int array_of_addresses[13];

    int i=0;
    while(array_of_chars[i])
    {
        array_of_addresses[i] = &array_of_chars[i];
        printf("%c", array_of_chars[i++]);
    }

    i = 0;
    while(array_of_addresses[i])
    {
        printf("\n");
        printf("%c", *(char*)array_of_addresses[i++]);
    }

    return 0;
}