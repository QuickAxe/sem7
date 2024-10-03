#include <stdio.h>

float activation(int n)
{
    return (n >= 0) ? 1.0 : -1.0;
}

int main()
{
    // "dataset"
    float x[3][4] = {{1, -2, 0, -1},
                     {0, 1.5, -0.5, -1},
                     {-1, 1, 0.5, -1}};

    float w[] = {1, -1, 0, 0.5};

    float d[] = {-1, -1, 1};

    float c = 0.1;

    // training loop

    for (int i = 0; i < 3; i++)
    {
        float net = 0;
        for (int j = 0; j < 4; j++)
            net += w[j] * x[i][j];

        float activationValue = activation(net);

        // // if the value is the same as the desired value, skip this step
        // if(d[i] == activationValue)
        //     continue;

        int r = d[i] - activationValue;

        // update weights
        for (int j = 0; j < 4; j++)
            w[j] += (c * r * x[i][j]);
    }

    // output final weights:
    for (int j = 0; j < 4; j++)
        printf("\nw[%d] = %f\n", j, w[j]);
}