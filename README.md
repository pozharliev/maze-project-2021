![Vavylon Logo](public/VAVYLON_LOGO_BIG_NOBG.png)

<h1 align="center"><strong> Team VAVYLØN</strong></h1>

***badges***
___

<br>

<p align="center">
   <strong> Game about the Babylon tower, powered by olcPixelGameEngine.</strong> 
</p>
<br>

___

# 💻 About

<p align="center"><strong>Our project is a highly engaging, story-based, rogue-like, skill-based, speedrun-optimized, randomized  game, related to the Babylon tower. It consists of a main menu, lobby and 2 random generated mazes for each floor. Each floor has 2 mazes in it and every maze can have up to 3 types of scrolls in it.</strong></p>

# Storyline

**You are a lost adventurer. It's dark, and you can't see anything. While wondering around, trying to find a way to escape the darkness, you come around the entrance of the famous Babylon tower. Because the tower is famous for ligthing the way, you go in. But before you can find your way, you need to go through series of mazes. But fear not, there are all types of scrolls left from previous adventurers to help you. Solve the mazes, find all the runes and light your way!**

# Gameplay
## 1. Scrolls
| Scroll | Description                                     |
|--------|-------------------------------------------------|
| Dash   | Dash 2 tiles ahead.                             |
| Speed  | Get 25% faster for the rest of the run.         |
| Path   | Shows the shortest path to the end of the maze. |

## 2. Structures

| Structure | Description                               |
|-----------|-------------------------------------------|
| Maze      | Two mazes per floor.                      |
| Lobby     | One lobby for every two mazes(one floor). |
| Floor     | Currenty three per game.                  |

## 3. Rules
### 1. Going outside any path in the maze results in **losing**.
### 2. Picking up the two runes from the 2 mazes will result in going one floor up.
### 3. Have fun!

# Screenshots

# Setup
## Dependancies

- [g++](https://gcc.gnu.org/) 10.3.0 or higher;
- make 4.3 or higher;
  - You can install it by using [chocolatey](https://chocolatey.org/).

## Usage
Start the ***powershell*** script by doing *(powershell only)*:
```powershell
> ./start.ps1
```

![Script Example](public/POWERSHELL_SCRIPT_EXAMPLE.png)
![Script Developers Example](public/POWERSHELL_SCRIPT_DEVELOPERS.png)

## Using the binary from release

Some link

# Building

## **If you want to build it manually, you can do it by following these steps:**
- **1st option in the powershell script**

### 1. Prepare the build directory:

```bash
> mkdir build
> cd build
```

### 2. After this, compile:

```bash
> make
```

### 3. Then, just run the exe:
#### **On powershell or bash:**

```bash
> ./main
```

#### **On cmd(windows):**
```bash
> main.exe
```

## Generating the documentation:
### Make sure you have [doxygen](https://www.doxygen.nl/index.html) installed:

```bash
> doxygen
```
### Then, open the index.html file in the docs/doxygen/html folder.
- **5th option in the powershell script**

# Reviews
If you're not sold on this game yet, just listen to what our very satisfied customers have to say about it!

![Picture](public/Jeff.png) "This game is pretty cool" - Lost Adventurer
    (picture of Lost Adventurer)

![Picture](public/Jeff.png) "Really fun to play with friends and family haha" - Also Lost Adventurer
    (another picture of Lost Adventurer)