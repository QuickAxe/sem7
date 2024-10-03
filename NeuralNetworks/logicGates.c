#include <stdio.h>

int w1, w2, x1, x2, y;

void AND()
{
    w1 = 1;
    w2 = 1;

    printf("Enter two values fro AND gate: ");
    scanf("%d %d", &x1, &x2);

    int value = (x1 * w1) + (x2 * w2);

    // threshold
    if (value >= 2)
        y = 1;
    else
        y = 0;

    printf("\n Y value: %d\n", y);
}

void OR()
{
    w1 = 1;
    w2 = 1;

    printf("Enter two values for OR gate: ");
    scanf("%d %d", &x1, &x2);

    int value = (x1 * w1) + (x2 * w2);

    // threshold
    if (value >= 1)
        y = 1;
    else
        y = 0;

    printf("\n Y value: %d\n", y);
}

void NOT()
{
    w1 = -1;

    printf("Enter value for NOT gate: ");
    scanf("%d", &x1);

    int value = (x1 * w1);

    // threshold
    if (value >= 0)
        y = 1;
    else
        y = 0;

    printf("\n Y value: %d\n", y);
}



int main()
{
    AND();
    NOT();
    OR();
}