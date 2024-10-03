#include <stdio.h>

int activation(int n)
{
    return (n >= 0) ? 1 : -1;
}

int main()
{
    // "dataset"
    float x[3][4];
    float x[0] = {1, -2, 0, -1};
    float x[1] = {0, 1.5, -0.5, -1};
    float x[2] = {-1, 1, 0.5, -1};

    float w[4][4];
    float w[0] = {1, -1, 0, 0.5};

    float d[] = {-1, -1, 3};

    float c = 0.1;

    // training loop

    for (int i = 0; i < 3; i++)
    {
        int net = 0;
        for (int j = 0; j < 4; j++)
            net += w[i][j] * x[i][j];

        int activationValue = activation(net);

        // // if the value is the same as the desired value, skip this step
        // if(d[i] == activationValue)
        //     continue;

        int r = d[i] * activationValue;
        



    }
}