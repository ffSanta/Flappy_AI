# Flappy Bird AI (C++)

An AI-controlled Flappy Bird simulation developed in C++ using SFML.
The project demonstrates a custom implementation of a Neural Network
trained through a Genetic Algorithm to autonomously play the game.

This project is intended for learning, experimentation, and evaluation purposes.

---

## Features
- AI-controlled gameplay using a **custom Neural Network implementation**
- **Genetic Algorithm–based training**, evolving neural network parameters
  by mutating weights from top-performing agents
- Adjustable simulation speed for faster or slower training
- Manual agent termination to reset evolution cycles and accelerate learning
- Real-time visualization of AI behavior during training

---

## Controls
- **W** : Increase simulation speed  
- **S** : Decrease simulation speed  
- **D** : Force terminate the current agent and restart evolution

---

## Technical Overview
- Neural Network is implemented from scratch without external ML libraries
- Genetic Algorithm workflow:
  - Evaluate agent performance based on survival time
  - Select top-performing agents
  - Generate a new population through mutation
(Two parameters are inherited from the top three performing agents, and one parameter is randomly generated)
- Designed to allow rapid experimentation by adjusting simulation speed

---

## Technologies Used
- **Language**: C++
- **Graphics Library**: SFML
- **Concepts**:
  - Neural Networks
  - Genetic Algorithms
  - Simulation-based training
  - Real-time visualization

---

## Project Status
This project was developed during Year 2 (2024) as a learning-focused AI simulation.
It is considered complete but may be extended with additional optimization or features.

---
## Note
This README was generated with AI assistance and reviewed by the author.

## License
All rights reserved.

This source code is provided for viewing and evaluation purposes only.
Copying, modifying, or distributing this code without explicit permission
from the author is prohibited.
