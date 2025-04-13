# Euchre (C++)

A fully functional C++ implementation of the classic card game **Euchre**, designed for four players in two teams. The program handles all core mechanics including shuffling, dealing, trump selection, trick resolution, and scoring.

## 🎯 Objective

The goal is for a team to be the first to score 10 points by winning tricks in each round. Standard Euchre rules are followed throughout the game.

## 👥 Players

- 4 players total
- 2 teams of 2
- Players can be human or computer-controlled (based on implementation)

## 🛠 Features

- Euchre deck logic (24-card deck: 9 to Ace)
- Shuffling and dealing
- Trump selection and order-up logic
- Trick-taking mechanics with correct suit-following
- Scoring and win detection
- Command-line interface for interaction

## 🧱 Technologies Used

- **C++**
- Standard Template Library (STL)
- Object-Oriented Programming (OOP)
- Terminal I/O

## ▶️ How to Compile & Run

1. **Clone the repo:**

```bash
git clone https://github.com/yourusername/euchre-game-cpp.git
cd euchre-game-cpp
Complile:
g++ -std=c++17 -o euchre main.cpp Deck.cpp Player.cpp Game.cpp
Run:
./euchre

euchre-game-cpp/
├── main.cpp           # Game entry point
├── Game.cpp/.h        # Handles game logic and flow
├── Player.cpp/.h      # Player behavior and decision making
├── Deck.cpp/.h        # Card and deck operations
├── Utils.cpp/.h       # Helper functions (if used)
└── README.md

