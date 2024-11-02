#! deprecated code, it has its own repo now, at:
#! https://github.com/QuickAxe/Ga-Gpu
import random


class GPU:
    def __init__(self, name, performance, cost, vram):
        self.name = name
        self.performance = performance
        self.cost = cost
        self.vram = vram


# Sample GPU options with performance, cost, and VRAM
# performance in terms of FP16 TFLOPS, cost in usd, vram in GB
# values may or may not be correct
gpus = [
    GPU("NVIDIA A100", 312, 12000, 40),
    GPU("NVIDIA V100", 125, 10000, 32),
    GPU("NVIDIA H100", 500, 35000, 80),
    GPU("AMD MI200 (MI250X)", 218, 8000, 64),
    GPU("NVIDIA RTX 6000", 130, 5000, 24),
    GPU("NVIDIA A40", 156, 6000, 48),
    GPU("AMD MI210", 138, 4000, 32),
    GPU("NVIDIA Quadro RTX 8000", 130, 12000, 48),
]

# Parameters for the GA
POPULATION_SIZE = 10
GENERATIONS = 20
MUTATION_RATE = 0.1
CROSSOVER_RATE = 0.7
NUM_GPUS = 3
BUDGET = 50000
MIN_VRAM = 40


# Initialize a population with ramdom combinations of gpus
def initPopulation():
    return [random.sample(gpus, NUM_GPUS) for _ in range(POPULATION_SIZE)]


# fitness function
def fitness(individual):
    total_performance = sum(gpu.performance for gpu in individual)
    total_cost = sum(gpu.cost for gpu in individual)
    total_vram = sum(gpu.vram for gpu in individual)

    # if constraints not met, return negative fitness
    if total_cost > BUDGET or total_vram < MIN_VRAM:
        return -1

    return total_performance / total_cost


# select the best chromosomes from the current population
def select(population):
    sorted_population = sorted(population, key=fitness, reverse=True)
    # return only the top 50%
    return sorted_population[:POPULATION_SIZE // 2]


def crossover(parent1, parent2):
    if random.random() < CROSSOVER_RATE:
        crossover_point = random.randint(1, NUM_GPUS - 1)
        return parent1[:crossover_point] + parent2[crossover_point:]
    return parent1


def mutate(individual):
    if random.random() < MUTATION_RATE:
        mutated_gpu = random.choice(gpus)
        individual[random.randint(0, NUM_GPUS - 1)] = mutated_gpu
    return individual


# main GA function
def geneticAlgo():
    population = initPopulation()

    for generation in range(GENERATIONS):
        # Evaluate fitness and select parents
        parents = select(population)

        # Generate new population
        next_generation = []
        while len(next_generation) < POPULATION_SIZE:
            parent1, parent2 = random.sample(parents, 2)
            child = crossover(parent1, parent2)
            child = mutate(child)
            next_generation.append(child)

        population = next_generation

    # Find the best chromosome in the final population
    best_solution = max(population, key=fitness)
    return best_solution


if __name__ == "__main__":
    best_gpus = geneticAlgo()
    print("Best GPU combination:")
    for gpu in best_gpus:
        print(
            f"{gpu.name} with performance {gpu.performance}, cost {gpu.cost}, and VRAM {gpu.vram} GB")
