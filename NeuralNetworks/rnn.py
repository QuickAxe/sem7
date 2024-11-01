import torch
import torch.nn as nn
import torch.optim as optim
import torch.nn.functional as F
from torch.utils.data import DataLoader
from torchvision import datasets
from torchvision import transforms

# create RNN


class RNN(nn.Module):

    def __init__(self, input_size, hidden_size, num_layer, num_classes=10):
        super(RNN, self).__init__()
        self.hidden_size = hidden_size
        self.num_layer = num_layer
        self.rnn = nn.RNN(input_size, hidden_size, num_layer, batch_first=True)
        self.fc = nn.Linear(hidden_size*seq_len, num_classes)

    def forward(self, x):
        h0 = torch.zeros(self.num_layer, x.size(0),
                         self.hidden_size).to(device)
        out, _ = self.rnn(x, h0)
        out = out.reshape(out.shape[0], -1)
        out = self.fc(out)
        return out


# Set device
device = 'cuda' if torch.cuda.is_available() else 'cpu'

# Hyperparameters
input_size = 28
seq_len = 28
num_layer = 2
hidden_size = 256
num_classes = 10
learning_rate = 0.001
batch_size = 64
num_epochs = 2

# Load the dataset
train_dataset = datasets.MNIST(
    root='Dataset/', train=True, transform=transforms.ToTensor(), download=True)
train_loader = DataLoader(dataset=train_dataset,
                          batch_size=batch_size, shuffle=True)

test_dataset = datasets.MNIST(
    root='Dataset/', train=False, transform=transforms.ToTensor(), download=True)
test_loader = DataLoader(dataset=test_dataset,
                         batch_size=batch_size, shuffle=True)

# Initialize the network
model = RNN(input_size=input_size, num_layer=num_layer,
            hidden_size=hidden_size).to(device)
# Loss function and optimizer
loss_fn = nn.CrossEntropyLoss()
optimizer = optim.Adam(model.parameters(), lr=learning_rate)

# Train the network
for epoch in range(num_epochs):
    print(f"Epoch: {epoch}")
    for batch_idx, (data, targets) in enumerate(train_loader):
        data = data.squeeze(1).to(device)
        targets = targets.to(device)

        # Forward pass
        scores = model(data)
        loss = loss_fn(scores, targets)

        # Backward pass and optimization
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

# Check accuracy on both train and test sets


def check_accuracy(loader, model):
    if loader.dataset.train:
        print("Checking accuracy on train dataset")
    else:
        print("Checking accuracy on test dataset")

    num_correct = 0
    num_samples = 0
    model.eval()

    with torch.no_grad():
        for x, y in loader:
            x = x.to(device).squeeze(1)
            y = y.to(device)

            scores = model(x)
            _, pred = scores.max(1)
            num_correct += (pred == y).sum().item()
            num_samples += pred.size(0)

        accuracy = 100.0 * num_correct / num_samples
        print(f"Accuracy: {accuracy:.2f}%")

    model.train()


check_accuracy(train_loader, model)
check_accuracy(test_loader, model)
