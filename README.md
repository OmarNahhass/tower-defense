# Tower Defense

A 2D tower defense game built in C++ with [SFML](https://www.sfml-dev.org/), developed as a team project for a software design course. The codebase is built around classic OOP design patterns (Factory, Strategy, Decorator, Observer) to keep towers, critters, and game systems extensible.

Team Code Name: **JOB**
Team Members:
- Brandon Nguyen
- Omar Nahhas
- Jean Naima

## Gameplay

Place towers along a critter path, upgrade them with earned gold, and survive successive waves of enemies before they reach the exit.

**Towers**
- Direct Damage Tower
- Slowing Tower
- Sniper Tower
- AoE Tower

Towers can be upgraded (increased power, range, or rate of fire) or sold back for a partial refund.

**Critters**
- Basic Critter
- Fast Critter
- Strong Critter
- Boss Critter

Each wave scales critter count and difficulty, generated via a critter group generator.

## Architecture

- **Factory** (`CritterFactory`, `CritterFactoryManager`) — spawns critter types per wave.
- **Strategy** (`Strategies`) — encapsulates tower targeting/attack behavior.
- **Decorator** (`TowerDecorator`, `PowerDecorator`, `RangeDecorator`, `AtkSpeekDecorator`) — applies tower upgrades without modifying the base tower classes.
- **Observer** (`CritterObserver`, `MapObserver`) — keeps views (`CritterView`, `MapView`) in sync with game state.
- **Map** (`Map`, `NextWave`) — handles the grid, path validation, and wave progression.
- **UI** (`Menu`, `UpgradeButton`) — main menu and in-game tower upgrade controls.

Game events (waves, upgrades, map validation) are written to `game_log.txt` via `LogFile`.

## Requirements

- Windows
- Visual Studio 2022
- SFML (bundled under `Tower Defense/External/SFML`)

## Building & Running

1. Open `Tower Defense/Tower Defense.sln` in Visual Studio 2022.
2. Set the build **Configuration/Platform to x86**.
3. Build and run (`F5`).

The required SFML DLLs are already included alongside the executable's output directory.

## Project Structure

```
Tower Defense/
├── Tower Defense.sln
├── External/SFML/          # Bundled SFML headers and libraries
└── Tower Defense/           # Game source code, assets, and project files
```
