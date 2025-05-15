Readme
# Stronghold Kingdoms – Module Contribution by Muhammad Saim Naveed

This document outlines the specific contributions made by **Muhammad Saim Naveed** to the *Stronghold Kingdoms* C++ strategy simulation game. His role focused on key gameplay systems such as diplomacy, conflict handling, map movement, and AI player logic.

---

Technologies Used

- **Language:** C++
- **Concepts:**  
  - Inheritance and Polymorphism  
  - Smart Pointers (`shared_ptr`)  
  - Encapsulation  
  - Game Event Handling  
  - AI Decision Making  
  - Map & Grid Logic  
  - Exception Handling

---

Contributed Files & Responsibilities

### 1. **`trade.cpp`**
- Developed the trading system between players.
- Enabled sending offers and requests, validating trade logic.
- Implemented smuggling mechanics with consequences.

### 2. **`society.cpp`**
- Simulated social class dynamics (nobles, peasants, etc.).
- Added growth and decline simulations affecting population behavior.

### 3. **`player.cpp`**
- Defined the base `Player` class structure.
- Added message system for inter-player communication.
- Managed player-specific data like kingdom ID and name.

### 4. **`map.cpp`**
- Created a 4x4 visual grid-based map.
- Managed player movement and position validation.
- Implemented `is_occupied()` check to prevent overlapping moves.
- Used exception handling to manage invalid moves and map errors.

### 5. **`conflict.cpp`**
- Handled the declaration of war between kingdoms.
- Compared army strength and decided battle outcomes.
- Applied damage logic and handled post-war updates.

### 6. **`alliance.cpp`**
- Enabled alliance formation and breaking.
- Included betrayal detection (e.g., attacking a former ally).
- Managed alliance state and involved player IDs.

### 7. **`stronghold.cpp`**
- Implemented the `AIPlayer` class derived from `Player`.
- Designed AI decision-making for gathering, recruiting, war, and events.
- Integrated AI behavior into the game loop with strategic logic.

---

Key Concepts Demonstrated

- Effective use of **inheritance** (e.g., `AIPlayer` : `Player`).
- Game interaction systems: **trade, conflict, alliance**.
- Real-time **map-based movement** with occupancy validation.
- Robust **AI logic** for automated kingdom decisions.
- Clean use of **exception handling** to prevent runtime errors.

---

Summary

Muhammad Saim Naveed’s modules were critical in creating:
- An intelligent and dynamic AI opponent.
- A robust diplomacy system through alliances and betrayals.
- Realistic and fair map-based player movement.
- Interactive trade and war mechanics.

These features together formed the **strategic backbone** of the game and made each turn rich in decisions and consequences.

