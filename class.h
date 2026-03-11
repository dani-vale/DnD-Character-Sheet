#pragma once
#include "ability.h"
#include <string>
#include <vector>

enum class ArmorProf { Light, Medium, Heavy, Shields };
enum class WeaponProf { Simple, Martial };

inline std::string armorProfToString(ArmorProf a) {
  switch (a) {
    case ArmorProf::Light: return "Light Armor";
    case ArmorProf::Medium: return "Medium Armor";
    case ArmorProf::Heavy: return "Heavy Armor";
    case ArmorProf::Shields: return "Shields";
    default: return "???";
  }
}

inline std::string weaponProfToString(WeaponProf w) {
  switch (w) {
    case WeaponProf::Simple: return "Simple Weapons";
    case WeaponProf::Martial: return "Martial Weapons";
    default: return "???";
  }
}

struct ClassFeature {
  std::string name;
  std::string description;
};

class DndClass {
public:
  virtual ~DndClass() = default;

  virtual std::string mainClass() = 0;
  virtual std::string subclass() = 0;

  // Convenience: "Fighter (Champion)" or "Fighter" if subclass empty
  virtual std::string displayName() {
    if (subclass().empty()) return mainClass();
    return mainClass() + " (" + subclass() + ")";
  }

  // Back-compat: if old code prints name()
  virtual std::string name() { return displayName(); }

  virtual int hitDie() = 0;

  virtual std::vector<Ability> savingThrowProficiencies() = 0;
  virtual std::vector<ArmorProf> armorProficiencies() = 0;
  virtual std::vector<WeaponProf> weaponProficiencies() = 0;

  virtual std::vector<std::string> skillOptions() = 0;
  virtual int numberOfSkillChoices() = 0;

  virtual std::vector<ClassFeature> level1Features() = 0;
  virtual std::vector<ClassFeature> subclassFeatures() = 0;
  virtual int subclassStartLevel() { return 3; }


  // Show subclass features only if the character is high enough level.
  virtual std::vector<ClassFeature> subclassFeaturesAtLevel(int level) {
    if (subclass().empty()) return {};
    if (level < subclassStartLevel()) return {};
    return subclassFeatures();
}
};

// Menus
std::vector<std::string> availableMainClasses();
std::vector<std::string> availableSubclasses(const std::string& mainClass);

// Factory
DndClass& getClass(const std::string& mainClass, const std::string& subclass);

// Optional back-compat (main class only)
std::vector<std::string> availableClasses();
DndClass& getClassByName(const std::string& className);