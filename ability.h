#pragma once
#include <array>
#include <string>

enum class Ability { STR = 0, DEX, CON, INT, WIS, CHA, COUNT };

inline std::string abilityToString(Ability a) {
  switch (a) {
    case Ability::STR: return "STR";
    case Ability::DEX: return "DEX";
    case Ability::CON: return "CON";
    case Ability::INT: return "INT";
    case Ability::WIS: return "WIS";
    case Ability::CHA: return "CHA";
    default: return "???";
  }
}

using AbilityScores = std::array<int, static_cast<size_t>(Ability::COUNT)>;

inline size_t idx(Ability a) { return static_cast<size_t>(a); }