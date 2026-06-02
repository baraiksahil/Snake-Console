# 🐍 C++ Console Snake Game

A simple **console-based Snake game built using C++**.  
This project demonstrates core game development concepts like movement, collision detection, food spawning, score tracking, and dynamic difficulty.

---

## 🎮 Features

- **Snake movement** in 4 directions (WASD controls)
- **Random food spawning** (ensured to never spawn inside the snake's body)
- **Snake growth** dynamically after eating food
- **Score tracking** system
- **Dynamic difficulty** (speed increases over time as you eat)
- **Wall collision** detection
- **Self-collision** detection
- **Console-based rendering** using pure ASCII characters

---

## 🧠 Concepts Used

- **2D Grid-based Game Design**: Handling coordinates in a grid matrix.
- **Vectors**: Using `std::vector` to store the dynamic coordinates of the snake body segments.
- **Standard Game Loop**: Cycle of `draw()` → `input()` → `logic()`.
- **Collision Systems**: Aabb-like boundary checks and element checking for food and self.
- **POSIX Terminal IO**: Modifying terminal flags (`termios`) for cross-platform, non-blocking real-time keyboard inputs.

---

## 🎮 Controls

| Key | Action |
| :---: | :--- |
| **W** | Move Up |
| **A** | Move Left |
| **S** | Move Down |
| **D** | Move Right |

---

## 🧱 Game Rules

1. Eat food (`O`) to grow and increase your score.
2. Avoid hitting the boundaries/walls (`#`).
3. Avoid hitting your own body.
4. Each piece of food consumed increases your score by **10 points** and increases your speed.

---

## ⚙️ How to Run

### 🖥️ Linux / macOS
```bash
g++ main.cpp -o snake
./snake
```

### 🪟 Windows (MinGW)
```bash
g++ main.cpp -o snake.exe
snake.exe
```

---

## 📸 Preview

```text
############################################################
#                                                          #
#                                                          #
#                    O                                     #
#                                                          #
#              XXXXX                                       #
#                                                          #
############################################################
```

---

## 🚀 Future Improvements

- [ ] Add pause/resume system
- [ ] Add high score saving
- [ ] Add levels / obstacles
- [ ] Add sound effects
- [ ] Convert into SFML graphical version

---

## 📚 What I Learned

This project helped strengthen:
- **Problem solving**: Translating coordinates into rendering blocks.
- **Game loop design**: Understanding how frames update dynamically.
- **Real-time input handling**: Working with POSIX terminal settings to read raw characters.
- **Data structure usage**: Effectively managing vectors to insert/delete segments dynamically.
- **Collision systems**: Implementing math boundary checks and self-overlapping checks.

---

## 🧑💻 Author

Made while learning C++ game development fundamentals.

### ⭐ If you like this project
Give it a ⭐ and try improving it with:
- Better UI
- Smoother movement
- Multiplayer snake
