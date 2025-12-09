<<<<<<< HEAD
# 🍝 Philosophers

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Concurrency](https://img.shields.io/badge/Concurrency-Threads%20%26%20Processes-orange?style=for-the-badge)

<img src="simulation_output.png" alt="Philosophers Simulation Output" width="200">

A classic concurrency problem dealing with synchronization, mutexes, and semaphores. The goal is to manage a group of philosophers who alternate between eating, thinking, and sleeping without starving.

## 🧠 The Problem

One or more philosophers sit at a round table.
*   The philosophers alternatively **eat**, **think**, or **sleep**.
*   There are as many forks as there are philosophers.
*   To eat, a philosopher needs **two forks** (left and right).
*   Simulation stops if a philosopher dies of starvation or if all philosophers have eaten the specified number of times (if argument is provided).

## 🛠️ Implementation

### Mandatory (`philo`)
*   **Threads** & **Mutexes**: Each philosopher is a thread. Forks are protected by mutexes to prevent data races.
*   **One process**: Everything runs in a single process.

### Bonus (`philo_bonus`)
*   **Processes** & **Semaphores**: Each philosopher is a separate process. Forks are represented by a centralized semaphore.
*   **Parent/Child**: Synchronization is handled via semaphores across processes.

## 🚀 Usage

### Compilation
Navigate to the respective directory and compile:

```bash
# Mandatory
cd philo
make

# Bonus
cd philo_bonus
make
```

### Execution
The program takes the following arguments:
`./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat (optional)]`

**Examples:**

```bash
# 5 Philosophers, 800ms to die, 200ms to eat, 200ms to sleep
./philo 5 800 200 200

# Simulation should stop (philosopher dies)
./philo 4 310 200 100

# 5 Philosophers, run 7 times each (simulation stops successfully)
./philo 5 800 200 200 7
```
=======

# **philo**

## **Project overview**
The **philo** project is an essential part of the **42 curriculum**.
It tasks students with creating a simulation of the dining philosophers problem using threads and mutexes.
This project aims to improve understanding of concurrency, synchronization, and efficient coding practices in C.

#### **Objective**
- **Simulate Philosophers' Dining**: Implement a simulation where philosophers alternately eat, think, and sleep, using shared resources (forks).
- **Thread Management**: Create threads for each philosopher and ensure proper synchronization to avoid race conditions.
- **Mutex Usage**: Use mutexes to manage access to shared resources (forks) and prevent data races.
- **Monitor Philosopher State**: Use an external thread to monitor the state of philosophers and ensure they don't starve.
- **Error Handling**: Ensure thorough error handling to prevent unexpected crashes (segmentation faults, bus errors, etc.).
- **Memory Management**: Properly manage dynamic memory allocation to avoid memory leaks.

#### **Key features**
- **Philosopher Threads**: Each philosopher is represented by a separate thread.
- **Fork Management**: Use mutexes to manage access to forks and ensure proper synchronization.
- **State Monitoring**: An external thread monitors the state of each philosopher to ensure they do not starve.
- **Logging State Changes**: Log state changes (eating, thinking, sleeping) with timestamps to track the behavior of philosophers.

#### **Compiling the Project**
The **philo** project includes a Makefile for easy compilation. Simply run:
xxx
make
xxx
This will generate the `philo` executable.

#### **Running the Project**
To start the simulation, run:
```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
Example:
```
./philo 4 800 200 200
```
>>>>>>> cbaf2d2fa8661965687378273229b9b700d04610
