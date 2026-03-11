#pragma once
#include <string>
#include <vector>

struct BackgroundFeature {
  std::string name;
  std::string description;
};

class Background {
public:
  virtual ~Background() = default;

  virtual std::string name() { return "Unknown"; }
  virtual std::string source() { return ""; } // "PHB", "SCAG", "VRGR", "AL: Mulmaster", etc.

  // Typical background outputs (keep simple; you can expand later)
  virtual std::vector<std::string> skillProficiencies() { return {}; }
  virtual std::vector<std::string> toolProficiencies() { return {}; }
  virtual std::vector<std::string> languages() { return {}; }

  virtual BackgroundFeature feature() { return {"", ""}; }
};

// Menus
std::vector<std::string> availableBackgroundNames();

// Factory
Background& getBackgroundByName(const std::string& name);