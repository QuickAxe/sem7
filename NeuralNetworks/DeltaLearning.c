#include <stdio.h>
#include <math.h>

float activation(float n, float lambda)
{
    // using bipolar sigmoid in this case
    return 2 / (1 + exp(-1.0 * lambda * n)) - 1;
}

float activationDerivative(float output)
{
    // the derivative of the bipolar sigmoid function
    return 0.5 * (1 - pow(output, 2));
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
    float alpha = 1;

    // training loop
    for (int i = 0; i < 3; i++)
    {
        float net = 0;
        for (int j = 0; j < 4; j++)
            net += w[j] * x[i][j];

        float activationValue = activation(net, alpha);
        // printf("%f:%f\n", net, activationValue);

        // if the value is the same as the desired value, skip this step
        if (d[i] == activationValue)
        {
            printf("\nActivation value matches output, skipping step\n");
            continue;
        }

        printf("Activation Value: %f\n", activationValue);
        float r = (d[i] - activationValue) * activationDerivative(activationValue);
        printf("r Value: %f\n", r);

        // update weights
        for (int j = 0; j < 4; j++)
        {
            w[j] += (c * r * x[i][j]);
            printf("W%d[%d] = %f\n", i + 1, j, w[j]);
        }
        printf("\n");
    }

    // output final weights:
    printf("Final weights: \n");
    for (int j = 0; j < 4; j++)
        printf("w[%d] = %f\n", j, w[j]);
}