// coded by https://github.com/SorcierMaheP

#include <stdio.h>
#include <math.h>

float sigmoid(float net)
{
    return 1 / (1 + exp(-1.0 * net));
}

void print_outputs(int layer, int nodes, float matrix[layer][nodes])
{
    for (int i = 1; i < layer; i++)
    {
        for (int j = 0; j < nodes && i + j < 3; j++)
        {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void print_weights(int layer, int nodes, int prev_nodes, float matrix[layer][nodes][prev_nodes])
{
    for (int i = 1; i < layer; i++)
    {
        for (int j = 0; j < nodes; j++)
        {
            for (int k = 0; k < prev_nodes && i + j < 3; k++)
                printf("%f ", matrix[i][j][k]);
        }
        printf("\n");
    }
    printf("\n");
}

void forward_pass(float weights[3][2][2], float outputs[3][2])
{
    for (int layer = 1; layer < 3; layer++)
    {
        for (int node = 0; node < 2; node++)
        {
            if (outputs[layer][node] == -1)
                continue;

            float sum = 0.0;
            for (int prev_node = 0; prev_node < 2; prev_node++)
            {
                sum += outputs[layer - 1][prev_node] * weights[layer][node][prev_node];
            }
            outputs[layer][node] = sigmoid(sum);
        }
    }
}

void backpropagation(float weights[3][2][2], float outputs[3][2], float error, float lr)
{
    // gradients[layer_num][current_node_num]
    float gradients[3][2] = {
        {},
        {0, 0},
        {0, -1}};

    for (int layer = 2; layer > 0; layer--)
    {
        for (int node = 0; node < 2; node++)
        {
            // Final layer has different formula for gradient
            if (layer == 2 && gradients[layer][node] != -1)
            {
                // grad = output * (1 - output) * (teacher - output)
                gradients[layer][node] = outputs[layer][node] * (1 - outputs[layer][node]) * error;
            }
            else if (layer < 2)
            {
                // grad = output * (1 - output) * summation(next_layer_node_grad * weight)
                for (int next_node = 0; next_node < 2; next_node++)
                {
                    if (gradients[layer + 1][next_node] != -1)
                    {
                        gradients[layer][node] += outputs[layer][node] * (1 - outputs[layer][node]) * gradients[layer + 1][next_node] * weights[layer + 1][next_node][node];
                    }
                }
            }

            // Update weights in reverse direction
            if (gradients[layer][node] != -1)
            {
                for (int prev_node = 0; prev_node < 2; prev_node++)
                {
                    weights[layer][node][prev_node] += lr * gradients[layer][node] * outputs[layer - 1][prev_node];
                }
            }
        }
    }
}

int main()
{
    // weights[layer_num][current_node_num][node_num_in_prev_layer]
    float weights[3][2][2] = {
        {},
        {{0.2, 0.2}, {0.3, 0.3}},
        {{0.3, 0.9}}};

    // outputs[layer_num][current_node_num]
    float outputs[3][2] = {
        {0.35, 0.7},
        {0, 0},
        {0, -1}};

    // Assume desired target output
    float target_output = 0.5;

    // Learning rate for backpropagation
    float lr = 1;

    for (int i = 0;; i++)
    {
        // Perform forward pass
        forward_pass(weights, outputs);

        printf("Output Matrix for Forward Pass %d:\n", i);
        print_outputs(3, 2, outputs);

        // Calculate error and continue with backprop if desired
        float error = target_output - outputs[2][0];

        if (fabs(error) < 0.1)
            break;

        // Perform backpropagation
        backpropagation(weights, outputs, error, lr);

        printf("Weight Matrix for Backward Pass %d:\n", i);
        print_weights(3, 2, 2, weights);
        printf("-------------------------------------------------------------\n");
    }
    return 0;
}