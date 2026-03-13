# CPTR142: D&D Character Sheet Generator

Creating a clean Dungeons and Dragons (5e) character sheet can be both a daunting and tedious process, especially for new players, due to the complexity of manual calculations and the volume of rulebook cross-referencing required. Manual sheets are often prone to mathematical errors in derived statistics, such as Armor Class (AC) and Skill Modifiers, which can disrupt gameplay.

## Overview

**D&D Character Sheet Generator** is a terminal-based C++ application that automates the entire character creation workflow for Dungeons & Dragons 5e. The program guides users through a structured selection process—choosing Race, Class, and Background—and automatically calculates all derived statistics. The result is a fully validated, battle-ready character sheet saved to a text file.

## Features

- **Flexible Character Creation**
  - Multiple races with subrace support and racial ability score increases
  - Diverse class selection with subclass specializations (e.g., Champion Fighter, Path of the Berserker Barbarian)
  - Rich background options with unique features and proficiencies
  
- **Multiple Ability Score Entry Methods**
  - Manual entry (3-20 per ability)
  - Standard Array assignment (15, 14, 13, 12, 10, 8)
  - Support for Flexible Ability Score Increases (ASI) for revised ruleset
  
- **Automatic D&D 5e Calculations**
  - Ability modifiers based on scores
  - Proficiency bonuses (scales with character level)
  - Armor Class (AC) calculation
  - Initiative modifier
  - Hit Points (HP) and Hit Dice calculation
  - Skill proficiencies with corresponding ability modifiers
  - Saving throw proficiencies
  - Weapon and armor proficiencies
  
- **Combat-Ready Output**
  - Attack rolls with ability modifiers
  - Weapon damage calculations
  - Equipment inventory tracking
  - Class features summary

- **Formatted Character Sheet Export**
  - Saves to `.txt` file with character name as filename
  - Clean, readable summary format
  - Ready for immediate tabletop use

## Getting Started

### Running

The program will launch an interactive menu where you:
1. Enter your character's name
2. Choose your Race (and subrace if applicable)
3. Select your Class (and subclass specialization)
4. Pick your Background
5. Select your ability score generation method
6. Choose skill proficiencies for your class
7. Review and confirm your character

Your completed character sheet will be saved as `{character_name}.txt` in the current directory.

## Example Output

See `ded_sheet.txt` for a sample Level 1 character with full combat statistics, equipment, and attack information.

Sample output includes:
- Character summary (Name, Level, Proficiency Bonus, Race, Class)
- Ability scores with modifiers
- Combat stats (AC, Initiative, Speed, HP)
- Attack options with damage calculations
- Equipment and inventory
