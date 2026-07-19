# Axis & Allies Remaster - Technical Architecture

## 1. High-Level Architecture

```
┌─────────────────────────────────────────────────────────────────┐
│                     Unreal Engine 5 Runtime                      │
├─────────────────────────────────────────────────────────────────┤
│                                                                   │
│  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐            │
│  │   Game Mode  │  │  Pawn/Player │  │   HUD/UI     │            │
│  │   Logic      │  │   Controller  │  │   System     │            │
│  └──────────────┘  └──────────────┘  └──────────────┘            │
│         │                  │                  │                   │
│  ┌──────────────────────────────────────────────────────────┐    │
│  │              Game Systems (Core)                          │    │
│  ├──────────────────────────────────────────────────────────┤    │
│  │  ┌────────────┐ ┌────────────┐ ┌────────────┐            │    │
│  │  │   Board    │ │   Unit     │ │   Combat   │            │    │
│  │  │  System    │ │   System   │ │   System   │            │    │
│  │  └────────────┘ └────────────┘ └────────────┘            │    │
│  │  ┌────────────┐ ┌────────────┐ ┌────────────┐            │    │
│  │  │  AI        │ │   Economy  │ │   Turn     │            │    │
│  │  │  System    │ │   System   │ │   Manager  │            │    │
│  │  └────────────┘ └────────────┘ └────────────┘            │    │
│  └──────────────────────────────────────────────────────────┘    │
│         │                  │                  │                   │
│  ┌──────────────────────────────────────────────────────────┐    │
│  │         Utility & Data Management                         │    │
│  ├──────────────────────────────────────────────────────────┤    │
│  │  ┌────────────┐ ┌────────────┐ ┌────────────┐            │    │
│  │  │  Save/Load │ │   Config   │ │   Events   │            │    │
│  │  │  System    │ │   Manager  │ │   Bus      │            │    │
│  │  └────────────┘ └────────────┘ └────────────┘            │    │
│  └──────────────────────────────────────────────────────────┘    │
│                                                                   │
└───────────────────���─────────────────────────────────────────────┘
```

## 2. Core Systems

### 2.1 Board System
- Territory management
- Map visualization
- Territory connections
- Owner tracking

### 2.2 Unit System
- Unit types (9 different types)
- Unit pooling & recycling
- Movement & positioning
- Unit state management

### 2.3 Combat System
- Attack resolution
- Dice rolling mechanics
- Casualty calculation
- Combat logging

### 2.4 AI System
- Strategy selection
- Board analysis
- Threat assessment
- Decision making

### 2.5 Economy System
- Income calculation
- Unit production
- Factory/Shipyard management
- Resource tracking

### 2.6 Turn Manager
- Phase progression
- Turn order
- Validation
- State transitions

---

**Document Version**: 1.0  
**Last Updated**: July 2026  
**Engine**: Unreal Engine 5.3+