#pragma once
#include "ability.h"
#include <string>
#include <vector>

struct Trait {
  std::string name;
  std::string description;
};

class Race {
public:
  virtual ~Race() = default;

  // Option B: NOT abstract. Defaults return "unknown".
  virtual std::string mainRace() { return "Unknown"; }
  virtual std::string subrace() { return ""; }

  virtual void applyAbilityScoreIncreases(AbilityScores &) {}
  virtual int speed() { return 30; }
  virtual std::vector<Trait> traits() { return {}; }
};

// Menus
std::vector<std::string> availableMainRaces();
std::vector<std::string> availableSubraces(const std::string& mainRace);

// Factory
Race& getRace(const std::string& mainRace, const std::string& subrace);

// Optional back-compat
std::vector<std::string> availableRaceDisplayNames();
Race& getRaceByDisplayName(const std::string& displayName);

// Flexible ASI support
bool raceNeedsFlexibleAsi(const std::string& mainRace, const std::string& subrace);
void applyFlexibleAsi_2_1(AbilityScores& s, Ability plus2, Ability plus1);
void applyFlexibleAsi_1_1_1(AbilityScores& s, Ability a, Ability b, Ability c);