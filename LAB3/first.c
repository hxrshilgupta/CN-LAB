#include <stdio.h>

int isLittleEndian()
{
    int num = 1;
    return (*(char *)&num == 1);
}

unsigned int swapEndianness(unsigned int num)
{
    return ((num >> 24) & 0xFF) | ((num >> 8) & 0xFF00) | ((num << 8) & 0xFF0000) | ((num << 24) & 0xFF000000);
}

int main()
{
    // Determine the endianness of the host machine.
    int isLittleEndian = isLittleEndian();

    // Enter a number.
    unsigned int num;
    printf("Enter a number: ");
    scanf("%u", &num);

    // Print the content of each byte location of the number.
    unsigned char *ptr = (unsigned char *)&num;
    printf("Content of each byte location:\n");
    for (int i = 0; i < sizeof(num); i++)
    {
        printf("Byte %d: %02X\n", i + 1, ptr[i]);
    }

    // Swap the endianness of the number.
    unsigned int swappedNum = swapEndianness(num);

    // Print the number after endianness conversion.
    printf("Number after endianness conversion: %u\n", swappedNum);

    return 0;
}
