#include <stdio.h>

int w1, w2, w3, x1, x2, x3, y;

// AND gate function
void AND()
{
    w1 = 1;
    w2 = 1;
    w3 = 1;

    printf("AND Gate Outputs:\n");
    for (x1 = 0; x1 <= 1; x1++)
    {
        for (x2 = 0; x2 <= 1; x2++)
        {
            for (x3 = 0; x3 <= 1; x3++)
            {
                int value = (x1 * w1) + (x2 * w2) + (x3 * w3);

                // threshold
                y = (value >= 3) ? 1 : 0;

                printf("%d AND %d AND %d = %d\n", x1, x2, x3, y);
            }
        }
    }
}

// OR gate function
void OR()
{
    w1 = 1;
    w2 = 1;
    w3 = 1;

    printf("\nOR Gate Outputs:\n");
    for (x1 = 0; x1 <= 1; x1++)
    {
        for (x2 = 0; x2 <= 1; x2++)
        {
            for (x3 = 0; x3 <= 1; x3++)
            {
                int value = (x1 * w1) + (x2 * w2) + (x3 * w3);

                // threshold
                y = (value >= 1) ? 1 : 0;

                printf("%d OR %d OR %d = %d\n", x1, x2, x3, y);
            }
        }
    }
}

// NOT gate function
void NOT()
{
    w1 = -1;

    printf("\nNOT Gate Outputs:\n");
    for (x1 = 0; x1 <= 1; x1++)
    {
        int value = (x1 * w1);

        // threshold
        y = (value >= 0) ? 1 : 0;

        printf("NOT %d = %d\n", x1, y);
    }
}

// XOR gate function
void XOR()
{
    printf("\nXOR Gate Outputs:\n");
    for (x1 = 0; x1 <= 1; x1++)
    {
        for (x2 = 0; x2 <= 1; x2++)
        {
            // XOR is true if inputs are different
            y = (x1 ^ x2); // Using bitwise XOR operator
            printf("%d XOR %d = %d\n", x1, x2, y);
        }
    }
}

// NAND gate function
void NAND()
{
    w1 = 1;
    w2 = 1;
    w3 = 1;

    printf("\nNAND Gate Outputs:\n");
    for (x1 = 0; x1 <= 1; x1++)
    {
        for (x2 = 0; x2 <= 1; x2++)
        {
            for (x3 = 0; x3 <= 1; x3++)
            {
                int value = (x1 * w1) + (x2 * w2) + (x3 * w3);

                // threshold for NAND
                y = (value < 3) ? 1 : 0; // Inverse of AND gate output
                printf("%d NAND %d NAND %d = %d\n", x1, x2, x3, y);
            }
        }
    }
}

// NOR gate function
void NOR()
{
    w1 = 1;
    w2 = 1;
    w3 = 1;

    printf("\nNOR Gate Outputs:\n");
    for (x1 = 0; x1 <= 1; x1++)
    {
        for (x2 = 0; x2 <= 1; x2++)
        {
            for (x3 = 0; x3 <= 1; x3++)
            {
                int value = (x1 * w1) + (x2 * w2) + (x3 * w3);

                // threshold for NOR
                y = (value == 0) ? 1 : 0; // Inverse of OR gate output
                printf("%d NOR %d NOR %d = %d\n", x1, x2, x3, y);
            }
        }
    }
}

int main()
{
    AND();
    NOT();
    OR();
    XOR();
    NAND();
    NOR();

    return 0;
}
