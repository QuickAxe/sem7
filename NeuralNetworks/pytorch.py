import torch
import torch.nn as nn
import torch.optim as optim

# Create a simple toy dataset
# Features: (x1, x2), Labels: (0 or 1)
X = torch.tensor([[0.0, 0.0],
                  [0.0, 1.0],
                  [1.0, 0.0],
                  [1.0, 1.0]], dtype=torch.float32)

y = torch.tensor([0, 0, 0, 1], dtype=torch.long)  # AND operation

# Define the neural network
class SimpleNN(nn.Module):
    def __init__(self):
        super(SimpleNN, self).__init__()
        self.fc1 = nn.Linear(2, 2)  # Input layer to hidden layer
        self.fc2 = nn.Linear(2, 2)  # Hidden layer to output layer

    def forward(self, x):
        x = torch.relu(self.fc1(x))  # Activation function
        x = self.fc2(x)               # Output layer
        return x

# Initialize the model, loss function, and optimizer
model = SimpleNN()
criterion = nn.CrossEntropyLoss()
optimizer = optim.SGD(model.parameters(), lr=0.1)

# Training loop
num_epochs = 100
for epoch in range(num_epochs):
    model.train()
    
    optimizer.zero_grad()  # Zero the gradients
    outputs = model(X)     # Forward pass
    loss = criterion(outputs, y)  # Compute loss
    loss.backward()        # Backward pass
    optimizer.step()       # Update weights

    if (epoch + 1) % 10 == 0:
        print(f'Epoch [{epoch + 1}/{num_epochs}], Loss: {loss.item():.4f}')

# Testing the model
model.eval()
with torch.no_grad():
    outputs = model(X)
    _, predicted = torch.max(outputs.data, 1)
    print(f'Predictions: {predicted.numpy()}, Actual: {y.numpy()}')

