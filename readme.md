Readme

# Stronghold Kingdoms – OOP Final Project

A console-based C++ strategy simulation game inspired by medieval kingdom management. This game allows users to control their own kingdom, manage resources, train armies, form alliances, engage in wars, and interact with AI players — all in a structured turn-based system using Object-Oriented Programming principles.

---

Technologies Used

- **Language:** C++
- **IDE:** Visual Studio / Code::Blocks / Dev C++
- **Concepts:**  
  - Object-Oriented Programming (Inheritance, Polymorphism, Encapsulation)
  - Smart Pointers (`shared_ptr`)
  - File Handling
  - Exception Handling
  - Game Simulation Logic

---

## 📁 Project Structure and Code Breakdown

Kingdom Systems (Game Mechanics)
- **Population.cpp:** Simulates population growth, revolts, and integrates with resource usage.
- **Army.cpp:** Manages soldier recruitment, morale, feeding, and salaries.
- **Economy.cpp:** Handles taxes, inflation, and financial summaries.
- **Bank.cpp:** Allows kingdoms to take or repay loans.
- **Leadership.cpp:** Manages the leader’s popularity, elections, and leadership changes.
- **Resource.cpp:** Manages food, wood, stone, and iron gathering and usage.
- **Event.cpp:** Introduces random disasters/events that impact game variables.

Core Game Engine
- **main.cpp:** Entry point of the game. Contains the turn-based game loop, user interface, and integration of all modules.
- **save_load.cpp:** Implements save/load functionality for persisting game state.

Multiplayer Interaction
- **Player.cpp:** Base class representing each kingdom/player.
- **AIPlayer (in stronghold.cpp):** Derived from Player, automates AI decisions for non-human players.

World Interaction
- **Map.cpp:** Manages a 4x4 grid showing player positions and movement.
- **Conflict.cpp:** Contains the logic for declaring and handling wars.
- **Alliance.cpp:** Implements alliance formation, betrayal checks, and management.
- **Trade.cpp:** Manages resource trades between players, including smuggling and validation.
- **Society.cpp:** Simulates social class behavior and its effect on kingdom structure.

---

## 👥 Team Members & Contributions

### 👨‍💻 Muhammad Saim Naveed
**Files:**
- `trade.cpp`
- `society.cpp`
- `player.cpp`
- `map.cpp`
- `conflict.cpp`
- `alliance.cpp`
- `stronghold.cpp`
- `AIplayer.cpp`

**Responsibilities:**
- Designed core systems for player interactions, diplomacy (alliances), warfare, and map movement.
- Developed AI player logic and class inheritance via `AIPlayer`.
- Implemented the core structure of the game in `stronghold.cpp`.

---

### 👨‍💻 Anas Saqib
**Files:**
- `Army.cpp`
- `Bank.cpp`
- `Economy.cpp`
- `Event.cpp`
- `Leadership.cpp`
- `Population.cpp`
- `save_load.cpp`
- `Resource.cpp`
- `main.cpp`

**Responsibilities:**
- Created kingdom subsystems: leadership, economy, population, army, and banking.
- Wrote the main game loop, user interface, and menu control.
- Developed save/load feature and disaster/random event system.

---

Key Features
- ✅ Human and AI players in a turn-based kingdom simulation.
- ✅ Map-based movement and visual representation (4x4 grid).
- ✅ Diplomacy system (alliances & betrayal logic).
- ✅ War declaration and military strength comparison.
- ✅ Dynamic leadership with popularity-based elections.
- ✅ Smart resource and economy management.
- ✅ Persistent save/load functionality for game continuity.

---

 How to Run the Project

1. Open the project in your preferred C++ IDE.
2. Ensure all `.cpp` and `.h` files are added to the build.
3. Compile and run `main.cpp`.
4. Follow on-screen instructions to simulate each player’s turn.

---


 Note
- The game is a console-based simulation project for academic purposes.
- Designed with modularity and scalability in mind for future enhancements.

