Readme
Stronghold Kingdoms – Module Contribution by Anas Saqib

This document outlines the core components developed by **Anas Saqib** in the *Stronghold Kingdoms* C++ strategy simulation project. His work focused on the internal systems that govern kingdom management, economic flow, leadership, disasters, and the overall game loop.

---

Technologies Used

- **Language:** C++
- **Concepts:**  
  - Object-Oriented Programming (OOP)  
  - Smart Pointers (`shared_ptr`)  
  - File Handling (Save/Load)  
  - Exception Handling  
  - Game Loop Design  
  - User Interface (Console Menus)

---

 Contributed Files & Responsibilities

### 1. **`Army.cpp`**
- Managed army recruitment, morale tracking, feeding, and salary payouts.
- Integrated army logic with population and economy systems.

### 2. **`Bank.cpp`**
- Enabled banking actions like loans and repayments.
- Connected financial mechanics to the economy class.

### 3. **`Economy.cpp`**
- Managed treasury, tax collection, and inflation.
- Updated treasury values based on leadership popularity and population.

### 4. **`Event.cpp`**
- Implemented a random disaster system (e.g., plagues, droughts).
- Affected multiple systems (population, army, economy, resources).

### 5. **`Leadership.cpp`**
- Created the leadership system with popularity metrics.
- Added leader change logic and election triggers (scheduled or forced).

### 6. **`Population.cpp`**
- Simulated population growth and revolts.
- Interacted with leadership, economy, and resources.

### 7. **`Resource.cpp`**
- Handled resource gathering and consumption (food, wood, stone, iron).
- Integrated with population and army systems for usage tracking.

### 8. **`save_load.cpp`**
- Provided full save/load functionality to persist game state.
- Supported serialization of key systems to resume progress.

### 9. **`main.cpp`**
- Wrote the main game loop with all menus and user interaction.
- Integrated every subsystem and ensured smooth turn-based transitions.
- Managed player actions, error handling, AI turns, and logging.
- Controlled scoring, elections, and system status reporting.

---

Key Concepts Demonstrated

- Strong command of **game system integration** (economy ↔ army ↔ leadership).
- Implemented **smart pointer architecture** for memory safety.
- Designed a clean and responsive **turn-based menu system**.
- Applied **exception handling** to prevent invalid user input and crashes.
- Developed reusable logging tools for tracking population, treasury, and army metrics.

---

Summary

Anas Saqib’s contributions formed the **core engine of the game**, powering everything from population growth to leadership elections. His work allowed players to:

- Recruit and maintain an army.
- Collect and spend resources wisely.
- Handle natural disasters and leadership crises.
- Interact with the full game world in a seamless console interface.

Without this solid foundation, the simulation and decision-making systems would not function — making these modules essential to the entire game.

