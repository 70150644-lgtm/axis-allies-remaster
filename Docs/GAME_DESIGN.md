# Axis & Allies Remaster - Game Design Document

## 1. Overview

**Title**: Axis & Allies Remaster  
**Genre**: Turn-Based Strategy / War Game  
**Platform**: Windows, Mac, Linux  
**Engine**: Unreal Engine 5  
**Target Audience**: Strategy game enthusiasts, 18+

## 2. Game Premise

Players assume control of major world powers during WWII. The objective is to achieve military and economic dominance through strategic territory control, unit deployment, and diplomatic negotiations. The game combines resource management, tactical combat, and long-term strategy.

## 3. Core Game Mechanics

### 3.1 Territories & Map
- **7 Continents** with 42+ territories
- Each territory has:
  - Production value (income generator)
  - Defense level (terrain bonus)
  - Resources (optional special resources)
  - Unit capacity

### 3.2 Playable Nations
1. **Germany** - Strong land forces, economic power
2. **Japan** - Naval dominance, aerial superiority
3. **Italy** - Mediterranean control, moderate forces
4. **Soviet Union** - Large standing army, defensive capability
5. **United States** - Industrial power, air/sea dominance
6. **United Kingdom** - Naval superiority, global presence

### 3.3 Unit Types

| Unit | Cost | Attack | Defense | Move | Special |
|------|------|--------|---------|------|----------|
| **Infantry** | 3 IPC | 1 | 2 | 1 | Basic unit |
| **Armor (Tank)** | 5 IPC | 3 | 3 | 2 | Mobile assault |
| **Artillery** | 4 IPC | 2 | 2 | 1 | Support unit |
| **Fighter** | 10 IPC | 3 | 3 | 4 | Air superiority |
| **Bomber** | 12 IPC | 4 | 1 | 5 | Area damage |
| **Transport** | 5 IPC | 0 | 1 | 2 | Unit carrier (1-2 units) |
| **Battleship** | 20 IPC | 4 | 4 | 2 | Naval power |
| **Cruiser** | 12 IPC | 3 | 3 | 2 | Naval support |
| **Submarine** | 6 IPC | 2 | 1 | 2 | Stealth unit |

### 3.4 Turn Structure

**Each Turn Consists of:**

1. **Purchase Phase**
   - Player collects income from controlled territories
   - Income used to build new units (must have factory/shipyard)
   - Units purchased but not deployed yet

2. **Deploy Phase**
   - Place newly purchased units on the board
   - Can only deploy in controlled territories with factories/shipyards
   - Combat units ready for action

3. **Combat Phase**
   - Attacker chooses target territory
   - Determine casualty rolls:
     - Attacker rolls 1d6 per attacking unit (1,2,3 hits on 2+, 3+, or 4+ depending on unit)
     - Defender rolls 1d6 per defending unit
     - Both sides remove casualties
   - Battle continues until attacker retreats or defender eliminated
   - Attacker can occupy won territory

4. **Movement Phase**
   - Move units to adjacent territories
   - Non-combat movement only
   - Subject to enemy interception

5. **End Phase**
   - Check territorial control for next income
   - Resolve special events
   - Pass turn to next player

### 3.5 Combat System

**Attack Resolution:**
```
1. Each attacking/defending unit rolls 1d6
2. Hits based on unit type:
   - Infantry: 1-2 (miss), 3-6 (hit) = 4/6 chance
   - Armor: 1-2 (miss), 3-6 (hit) = 4/6 chance
   - Fighter: 1 (miss), 2-6 (hit) = 5/6 chance
   - Battleship: 1-3 (miss), 4-6 (hit) = 3/6 chance
3. Remove casualties based on total hits
4. Continue until one side eliminated or attacker retreats
```

**Special Rules:**
- Fighters provide air cover (defend at +1)
- Armor deals extra damage (attack at +1)
- Transport units cannot attack
- Submarines ignore surface ships on first round

### 3.6 Territory Control & Income

- **Income**: 1 IPC per controlled territory
- **Factories**: Produce units (cost 15 IPC)
- **Shipyards**: Produce naval units (cost 20 IPC)
- **Neutral Territories**: No income until controlled

## 4. Victory Conditions

### 4.1 Military Victory
- Control 18+ territories
- Eliminate all enemy capitals
- Hold for 3+ consecutive turns

### 4.2 Economic Victory
- Accumulate 200+ IPC
- Maintain superiority for 5+ turns

### 4.3 Diplomatic Victory
- Form alliance with 2+ AI players
- All align against remaining opponent
- Maintain for 3+ turns

## 5. Game Phases & Duration

- **Early Game (Turns 1-5)**: Build armies, claim territories
- **Mid Game (Turns 6-15)**: Major conflicts, shifting alliances
- **Late Game (Turns 16+)**: Endgame, victory pursuit
- **Average Game Length**: 45-120 minutes

## 6. AI System

### 6.1 AI Difficulty Levels

**Easy**
- Random unit selection
- Basic territory control
- Limited planning

**Medium**
- Strategic territory priority
- Balanced offense/defense
- Resource optimization

**Hard**
- Advanced tactics
- Multi-turn planning
- Dynamic alliance formation
- Threat assessment

**Expert**
- Perfect information analysis
- Optimal resource allocation
- Coordinated multi-front operations
- Predictive positioning

### 6.2 AI Decision Tree

1. **Evaluate Board State**
   - Territory count vs opponents
   - Military strength comparison
   - Economic advantage

2. **Threat Assessment**
   - Identify vulnerable territories
   - Predict enemy moves
   - Calculate defense needs

3. **Strategy Selection**
   - Aggressive expansion
   - Defensive consolidation
   - Economic buildup
   - Diplomatic alliances

4. **Unit Production**
   - Allocate production based on strategy
   - Prioritize unit types
   - Build factories/shipyards

5. **Movement Execution**
   - Optimize unit positioning
   - Execute coordinated attacks
   - Defend key territories

## 7. User Interface

### 7.1 Main Views

- **3D Board View** - Interactive world map with zoom/pan/rotate
- **Unit Management** - Purchase, deploy, upgrade units
- **Territory Info** - Stats, garrison, income
- **Combat Log** - Battle history and results
- **Stats Dashboard** - Income, strength, progress

### 7.2 HUD Elements

- Player status (IPC, territories, units)
- Turn indicator
- Current phase display
- Unit selection & info
- Attack/Move options

## 8. Game Settings

- **Game Speed**: Slow, Normal, Fast
- **Unit Movement**: Instant, Animated
- **Combat Resolution**: Auto-resolve or manual
- **Difficulty**: Easy, Medium, Hard, Expert
- **Game Length**: Short (30 min), Medium (60 min), Long (120+ min)

## 9. Save/Load System

- **Auto-save**: Every turn
- **Manual save**: Unlimited slots
- **Save includes**:
  - Territory ownership
  - Unit positions & count
  - Player resources (IPC)
  - Turn history
  - Game settings

## 10. Progression & Achievements

### 10.1 Unlockables
- New nations (with different units/abilities)
- Historical campaigns
- Custom map editor
- AI personality profiles

### 10.2 Achievements
- "Blitzkrieg" - Win in 10 turns
- "Fortress Europe" - Hold 15+ European territories
- "Naval Supremacy" - Win with 50+ naval units
- "Economic Master" - Accumulate 500 IPC in one game
- "Diplomatic Genius" - Win by alliance

## 11. Special Rules (Optional)

- **Alliances**: Players can form temporary pacts
- **Technology**: Research upgrades (improved weapons, defense)
- **Events**: Random historical events affecting gameplay
- **Superpowers**: Special abilities unique to each nation

## 12. Multiplayer Features (Future)

- **Online Multiplayer**: 2-6 players
- **Turn Timer**: Enforced time limits per turn
- **Chat & Emotes**: Player communication
- **Leaderboards**: Ranked matchmaking
- **Tournaments**: Seasonal competitions

## 13. Accessibility

- High contrast mode
- Text-to-speech for rules
- Customizable font sizes
- Colorblind-friendly UI
- Controller & keyboard support

## 14. Performance Targets

- **Frame Rate**: 60 FPS at 1440p (recommended specs)
- **Load Time**: <30 seconds for maps
- **AI Turn Time**: <10 seconds per turn
- **Memory Usage**: <8GB RAM typical usage

---

**Document Version**: 1.0  
**Last Updated**: July 2026  
**Status**: Approved for Development