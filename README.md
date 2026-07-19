# Axis & Allies Remaster - 3D Strategy Game

A complete 3D remake of the classic board game **Axis & Allies by TimeGate**, featuring single-player AI opponents, full multiplayer support, and authentic turn-based strategy gameplay.

## 📋 Game Overview

**Axis & Allies Remaster** is a turn-based strategy game where players control major world powers during WWII. Build armies, manage resources, and conquer territories in a fully immersive 3D environment.

### Core Features

- **3D World Map** - Full globe with all territories and regions
- **Unit System** - Infantry, Armor, Artillery, Fighters, Bombers, Transports, Battleships
- **Turn-Based Gameplay** - Purchase → Deploy → Attack → Move phases
- **Combat System** - Realistic dice-roll based battle resolution
- **Economy Management** - Production, income, resource allocation
- **AI Opponents** - Advanced strategic decision-making
- **Single-Player & Multiplayer** - Campaign and skirmish modes
- **Save/Load System** - Persistent game states
- **Dynamic Weather & Lighting** - Day/night cycles, terrain variety

## 🛠 Tech Stack

- **Engine**: Unreal Engine 5 (C++)
- **Graphics**: Nanite virtualized geometry, Lumen global illumination
- **Backend**: C++ with modular game systems
- **Networking**: Unreal's Replication Graph for multiplayer
- **Database**: SQLite for game saves
- **Version Control**: Git/GitHub

## 📁 Project Structure

```
axis-allies-remaster/
├── Source/
│   ├── AxisAllies/
│   │   ├── Core/              # Core game systems
│   │   ├── Game/              # Game mode & rules
│   │   ├── Units/             # Unit system
│   │   ├── Combat/            # Combat resolution
│   │   ├── UI/                # User interface
│   │   ├── AI/                # AI system
│   │   ├── Map/               # World map system
│   │   └── Network/           # Multiplayer
│   └── ThirdParty/
├── Content/
│   ├── Maps/                  # Game levels/maps
│   ├── Characters/            # Unit models
│   ├── Materials/             # Shaders & materials
│   ├── Animations/            # Unit animations
│   └── UI/                    # UI assets
├── Binaries/
├── Intermediate/
├── Docs/
│   ├── GAME_DESIGN.md         # Game design document
│   ├── ARCHITECTURE.md        # Technical architecture
│   └── RULES.md               # Game rules
└── .gitignore
```

## 🎮 Game Phases

1. **Purchase Phase** - Spend income to build units
2. **Deploy Phase** - Place new units on the board
3. **Attack Phase** - Engage enemy territories
4. **Move Phase** - Reposition units
5. **End Phase** - Collect income, resolve effects

## 🤖 AI System

- Strategic territory control
- Resource optimization
- Threat assessment
- Unit composition planning
- Diplomatic decisions (alliances)

## 🚀 Getting Started

### Prerequisites
- Unreal Engine 5.3+
- Visual Studio 2022 (Windows) or Xcode (Mac)
- 50GB+ disk space
- Modern GPU (RTX 3070 equivalent recommended)

### Installation

1. Clone the repository:
```bash
git clone https://github.com/70150644-lgtm/axis-allies-remaster.git
cd axis-allies-remaster
```

2. Generate Visual Studio project files:
```bash
./GenerateProjectFiles.sh  # Mac/Linux
GenerateProjectFiles.bat   # Windows
```

3. Open `AxisAllies.sln` in Visual Studio

4. Build the project:
```bash
Build Solution (Ctrl+Shift+B)
```

5. Launch in Unreal Editor:
```bash
./Binaries/Win64/UE4Editor-Cmd.exe AxisAllies.uproject
```

## 📖 Documentation

- [Game Design Document](Docs/GAME_DESIGN.md) - Complete game rules & mechanics
- [Architecture Guide](Docs/ARCHITECTURE.md) - Technical design & systems
- [Rules Reference](Docs/RULES.md) - Official game rules

## 🤝 Contributing

Contributions welcome! See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

## 📜 License

This project is a fan-made remaster of the original Axis & Allies game. Please respect intellectual property rights.

## 🎯 Development Status

- [x] Project setup & structure
- [ ] Core game systems
- [ ] 3D map & board
- [ ] Unit system
- [ ] Combat mechanics
- [ ] AI system
- [ ] UI/UX
- [ ] Multiplayer
- [ ] Polish & optimization

## 👨‍💻 Development Team

**Lead Developer**: 70150644-lgtm

## 📞 Contact & Support

For issues, feature requests, or questions, please open a GitHub issue.

---

**Last Updated**: July 2026
**Engine Version**: Unreal Engine 5.3+
**Status**: Early Development