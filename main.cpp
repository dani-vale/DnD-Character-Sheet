#include "ability.h"
#include "background.h"
#include "class.h"
#include "race.h"

#include <algorithm>
#include <array>
#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::vector;

// ---------- Ability helpers ----------
static const std::array<Ability, 6> kAbilities = {
    Ability::STR, Ability::DEX, Ability::CON, Ability::INT, Ability::WIS, Ability::CHA};

static string abilityName(Ability a) {
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

static int modifierFromScore(int score) {
  return static_cast<int>(std::floor((score - 10) / 2.0));
}

static string modString(int mod) {
  return (mod >= 0 ? "+" : "") + std::to_string(mod);
}

static int proficiencyBonus(int level) {
  return 2 + (level - 1) / 4;
}

// ---------- Input helpers ----------
static void clearBadInput() {
  cin.clear();
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static int readIntInRange(const string& prompt, int lo, int hi) {
  while (true) {
    cout << prompt;
    int x;
    if (cin >> x) {
      clearBadInput();
      if (x >= lo && x <= hi) return x;
    } else {
      clearBadInput();
    }
    cout << "Please enter a number from " << lo << " to " << hi << ".\n";
  }
}

static string readLineTrim(const string& prompt) {
  cout << prompt;
  string s;
  std::getline(cin, s);
  while (!s.empty() && std::isspace((unsigned char)s.front())) s.erase(s.begin());
  while (!s.empty() && std::isspace((unsigned char)s.back())) s.pop_back();
  return s;
}

static string readLineNonEmpty(const string& prompt) {
  while (true) {
    string s = readLineTrim(prompt);
    if (!s.empty()) return s;
    cout << "Please enter a non-empty value.\n";
  }
}

static string sanitizeFilename(string s) {
  for (char& c : s) {
    if (c == '<' || c == '>' || c == ':' || c == '"' || c == '/' || c == '\\' ||
        c == '|' || c == '?' || c == '*')
      c = '_';
  }
  while (!s.empty() && std::isspace((unsigned char)s.front())) s.erase(s.begin());
  while (!s.empty() && std::isspace((unsigned char)s.back())) s.pop_back();
  if (s.empty()) s = "character";
  return s;
}

static int pickIndexMenu(const string& title, const vector<string>& options) {
  cout << "\n=== " << title << " ===\n";
  for (size_t i = 0; i < options.size(); ++i) {
    cout << " " << (i + 1) << ") " << options[i] << "\n";
  }
  return readIntInRange("Choose: ", 1, (int)options.size()) - 1;
}

static Ability pickAbility(const string& title, const vector<Ability>& forbidden = {}) {
  while (true) {
    cout << "\n" << title << "\n";
    for (int i = 0; i < 6; ++i) cout << " " << (i + 1) << ") " << abilityName(kAbilities[i]) << "\n";
    int idxPick = readIntInRange("Choose ability: ", 1, 6) - 1;
    Ability a = kAbilities[idxPick];

    for (auto f : forbidden) {
      if (f == a) { cout << "Already chosen.\n"; goto again; }
    }
    return a;
  again:
    continue;
  }
}

// ---------- Ability scores ----------
static AbilityScores enterScoresManual() {
  AbilityScores s{};
  for (Ability a : kAbilities) {
    int val = readIntInRange("Enter " + abilityName(a) + " (3-20): ", 3, 20);
    s[idx(a)] = val;
  }
  return s;
}

static AbilityScores standardArrayAssign() {
  vector<int> pool = {15, 14, 13, 12, 10, 8};
  AbilityScores s{};
  cout << "\nStandard Array: 15,14,13,12,10,8\n";
  for (Ability a : kAbilities) {
    cout << "\nAssign for " << abilityName(a) << ":\n";
    for (size_t i = 0; i < pool.size(); ++i) cout << " " << (i + 1) << ") " << pool[i] << "\n";
    int pick = readIntInRange("Choose: ", 1, (int)pool.size()) - 1;
    s[idx(a)] = pool[pick];
    pool.erase(pool.begin() + pick);
  }
  return s;
}

static void printScores(std::ostream& out, const AbilityScores& scores) {
  out << "Ability Scores:\n";
  for (Ability a : kAbilities) {
    int sc = scores[idx(a)];
    int md = modifierFromScore(sc);
    out << "  " << abilityName(a) << ": " << sc << " (" << modString(md) << ")\n";
  }
}

// ---------- Flexible ASI UI ----------
static void applyFlexibleAsiUI(AbilityScores& scores) {
  cout << "\nThis race uses Flexible ASI.\n";
  cout << " 1) +2 to one ability and +1 to a different ability\n";
  cout << " 2) +1 to three different abilities\n";
  int mode = readIntInRange("Choose: ", 1, 2);

  if (mode == 1) {
    Ability plus2 = pickAbility("Pick ability for +2:");
    Ability plus1 = pickAbility("Pick ability for +1:", {plus2});
    applyFlexibleAsi_2_1(scores, plus2, plus1);
  } else {
    Ability a = pickAbility("Pick first +1 ability:");
    Ability b = pickAbility("Pick second +1 ability:", {a});
    Ability c = pickAbility("Pick third +1 ability:", {a, b});
    applyFlexibleAsi_1_1_1(scores, a, b, c);
  }
}

// ---------- Skills mapping ----------
static std::map<string, Ability> skillAbilityMap() {
  return {
    {"Acrobatics", Ability::DEX}, {"Animal Handling", Ability::WIS}, {"Arcana", Ability::INT},
    {"Athletics", Ability::STR}, {"Deception", Ability::CHA}, {"History", Ability::INT},
    {"Insight", Ability::WIS}, {"Intimidation", Ability::CHA}, {"Investigation", Ability::INT},
    {"Medicine", Ability::WIS}, {"Nature", Ability::INT}, {"Perception", Ability::WIS},
    {"Performance", Ability::CHA}, {"Persuasion", Ability::CHA}, {"Religion", Ability::INT},
    {"Sleight of Hand", Ability::DEX}, {"Stealth", Ability::DEX}, {"Survival", Ability::WIS}
  };
}

static vector<string> allSkills() {
  auto m = skillAbilityMap();
  vector<string> s;
  for (auto& kv : m) s.push_back(kv.first);
  std::sort(s.begin(), s.end());
  return s;
}

static vector<string> chooseNFromList(const string& title, const vector<string>& options, int n) {
  std::set<int> chosen;
  vector<string> result;
  result.reserve(n);

  while ((int)result.size() < n) {
    cout << "\n=== " << title << " (" << result.size() << "/" << n << ") ===\n";
    for (size_t i = 0; i < options.size(); ++i) {
      bool picked = chosen.count((int)i) > 0;
      cout << " " << (i + 1) << ") " << options[i] << (picked ? "  [chosen]" : "") << "\n";
    }
    int pick = readIntInRange("Choose: ", 1, (int)options.size()) - 1;
    if (chosen.count(pick)) { cout << "Already chosen.\n"; continue; }
    chosen.insert(pick);
    result.push_back(options[pick]);
  }
  return result;
}

// ---------- Weapons ----------
struct WeaponDef {
  string name;
  int dieCount;
  int damageDie;
  bool finesse;
  bool martial;

  bool light;
  bool heavy;
  bool twoHanded;
  bool versatile;
  int versatileDie;
  bool reach;
  bool thrown;
  int normalRange;
  int longRange;
  bool loading;
  bool ammunition;
  bool special;
};

static std::map<string, WeaponDef> weaponDB() {
  auto W = [](string n, int dc, int dd,
              bool fin, bool mar,
              bool light, bool heavy, bool twoH, bool vers, int versDie,
              bool reach, bool thr, int r1, int r2,
              bool load, bool ammo, bool special) {
    return WeaponDef{n, dc, dd, fin, mar, light, heavy, twoH, vers, versDie, reach, thr, r1, r2, load, ammo, special};
  };

  return {
    {"Club",          W("Club",1,4,false,false, true,false,false,true, 8,false,false,0,0,false,false,false)},
    {"Dagger",        W("Dagger",1,4,true ,false, true,false,false,false,0,false,true,20,60,false,false,false)},
    {"Greatclub",     W("Greatclub",1,8,false,false,false,true,true,false,0,false,false,0,0,false,false,false)},
    {"Handaxe",       W("Handaxe",1,6,false,false, true,false,false,false,0,false,true,20,60,false,false,false)},
    {"Javelin",       W("Javelin",1,6,false,false, false,false,false,false,0,false,true,30,120,false,false,false)},
    {"Light Hammer",  W("Light Hammer",1,4,false,false, true,false,false,false,0,false,true,20,60,false,false,false)},
    {"Mace",          W("Mace",1,6,false,false, false,false,false,false,0,false,false,0,0,false,false,false)},
    {"Quarterstaff",  W("Quarterstaff",1,6,false,false, false,false,false,true,8,false,false,0,0,false,false,false)},
    {"Sickle",        W("Sickle",1,4,false,false, true,false,false,false,0,false,false,0,0,false,false,false)},
    {"Spear",         W("Spear",1,6,false,false, false,false,false,true,8,false,true,20,60,false,false,false)},

    {"Light Crossbow",W("Light Crossbow",1,8,false,false,false,false,true,false,0,false,false,80,320,true,true,false)},
    {"Dart",          W("Dart",1,4,false,false, false,false,false,false,0,false,true,20,60,false,false,false)},
    {"Shortbow",      W("Shortbow",1,6,false,false,false,false,true,false,0,false,false,80,320,false,true,false)},
    {"Sling",         W("Sling",1,4,false,false,false,false,false,false,0,false,false,30,120,false,true,false)},

    {"Battleaxe",     W("Battleaxe",1,8,false,true, false,false,false,true,10,false,false,0,0,false,false,false)},
    {"Flail",         W("Flail",1,8,false,true, false,false,false,false,0,false,false,0,0,false,false,false)},
    {"Glaive",        W("Glaive",1,10,false,true,false,true,true,false,0,true,false,0,0,false,false,false)},
    {"Greataxe",      W("Greataxe",1,12,false,true,false,true,true,false,0,false,false,0,0,false,false,false)},
    {"Greatsword",    W("Greatsword",2,6,false,true,false,true,true,false,0,false,false,0,0,false,false,false)},
    {"Halberd",       W("Halberd",1,10,false,true,false,true,true,false,0,true,false,0,0,false,false,false)},
    {"Lance",         W("Lance",1,12,false,true,false,false,false,false,0,true,false,0,0,false,false,true)},
    {"Longsword",     W("Longsword",1,8,false,true, false,false,false,true,10,false,false,0,0,false,false,false)},
    {"Maul",          W("Maul",2,6,false,true,false,true,true,false,0,false,false,0,0,false,false,false)},
    {"Morningstar",   W("Morningstar",1,8,false,true,false,false,false,false,0,false,false,0,0,false,false,false)},
    {"Pike",          W("Pike",1,10,false,true,false,true,true,false,0,true,false,0,0,false,false,false)},
    {"Rapier",        W("Rapier",1,8,true ,true, false,false,false,false,0,false,false,0,0,false,false,false)},
    {"Scimitar",      W("Scimitar",1,6,true ,true, true,false,false,false,0,false,false,0,0,false,false,false)},
    {"Shortsword",    W("Shortsword",1,6,true ,true, true,false,false,false,0,false,false,0,0,false,false,false)},
    {"Trident",       W("Trident",1,6,false,true, false,false,false,true,8,false,true,20,60,false,false,false)},
    {"War Pick",      W("War Pick",1,8,false,true,false,false,false,false,0,false,false,0,0,false,false,false)},
    {"Warhammer",     W("Warhammer",1,8,false,true,false,false,false,true,10,false,false,0,0,false,false,false)},
    {"Whip",          W("Whip",1,4,true ,true, false,false,false,false,0,true,false,0,0,false,false,false)},

    {"Blowgun",       W("Blowgun",1,1,false,true,false,false,true,false,0,false,false,25,100,true,true,false)},
    {"Hand Crossbow", W("Hand Crossbow",1,6,false,true,true,false,false,false,0,false,false,30,120,true,true,false)},
    {"Heavy Crossbow",W("Heavy Crossbow",1,10,false,true,false,true,true,false,0,false,false,100,400,true,true,false)},
    {"Longbow",       W("Longbow",1,8,false,true,false,true,true,false,0,false,false,150,600,false,true,false)},
    {"Net",           W("Net",0,0,false,true,false,false,false,false,0,false,true,5,15,false,false,true)}
  };
}

static bool hasWeaponProficiency(DndClass& cls, const WeaponDef& w) {
  bool hasSimple = false, hasMartial = false;
  for (auto p : cls.weaponProficiencies()) {
    if (p == WeaponProf::Simple) hasSimple = true;
    if (p == WeaponProf::Martial) hasMartial = true;
  }
  return w.martial ? hasMartial : hasSimple;
}

static Ability weaponAbilityUsed(const AbilityScores& scores, const WeaponDef& w) {
  int strMod = modifierFromScore(scores[idx(Ability::STR)]);
  int dexMod = modifierFromScore(scores[idx(Ability::DEX)]);
  if (w.thrown) {
    if (w.finesse) return (dexMod > strMod ? Ability::DEX : Ability::STR);
    return Ability::STR;
  }
  if (w.ammunition) return Ability::DEX;
  if (w.finesse) return (dexMod > strMod ? Ability::DEX : Ability::STR);
  return Ability::STR;
}

static string weaponPropertiesString(const WeaponDef& w) {
  vector<string> props;
  props.push_back(w.martial ? "martial" : "simple");
  if (w.light) props.push_back("light");
  if (w.heavy) props.push_back("heavy");
  if (w.twoHanded) props.push_back("two-handed");
  if (w.reach) props.push_back("reach");
  if (w.finesse) props.push_back("finesse");
  if (w.loading) props.push_back("loading");
  if (w.ammunition) props.push_back("ammunition");
  if (w.thrown) props.push_back("thrown");
  if (w.versatile) props.push_back("versatile 1d" + std::to_string(w.versatileDie));
  if (w.special) props.push_back("special");
  if (w.normalRange > 0) props.push_back("range " + std::to_string(w.normalRange) + "/" + std::to_string(w.longRange));

  string out;
  for (size_t i = 0; i < props.size(); ++i) {
    out += props[i];
    if (i + 1 < props.size()) out += ", ";
  }
  return out;
}

// ---------- Armor/AC ----------
struct ArmorChoice {
  string name;
  int baseAC;
  bool addDex;
  bool mediumDexCap;
};

static int calcArmorAC(const AbilityScores& scores, const ArmorChoice& armor, bool shield, int miscBonus) {
  int dexMod = modifierFromScore(scores[idx(Ability::DEX)]);
  int ac = 10;
  if (armor.name == "None") ac = 10 + dexMod;
  else if (armor.addDex) ac = armor.baseAC + dexMod;
  else if (armor.mediumDexCap) ac = armor.baseAC + std::min(dexMod, 2);
  else ac = armor.baseAC;
  if (shield) ac += 2;
  return ac + miscBonus;
}

static int raceNaturalACOption(Race& race, const AbilityScores& scores) {
  int dexMod = modifierFromScore(scores[idx(Ability::DEX)]);
  if (race.mainRace() == "Tortle") return 17;
  if (race.mainRace() == "Lizardfolk") return 13 + dexMod;
  return -1;
}

// ---------- Equipment packs (simple) ----------
static vector<vector<string>> classEquipmentPacks(const string& mainClass) {
  if (mainClass == "Sorcerer") return {{"Light Crossbow","20 bolts","Component pouch","Dagger x2"},
                                      {"Arcane focus","Dagger x2"}};
  if (mainClass == "Wizard")   return {{"Quarterstaff","Spellbook","Component pouch"},
                                      {"Dagger","Spellbook","Arcane focus"}};
  if (mainClass == "Warlock")  return {{"Light Crossbow","20 bolts","Component pouch","Dagger x2"},
                                      {"Simple weapon (choose later)","Arcane focus","Leather armor","Dagger x2"}};
  if (mainClass == "Rogue")    return {{"Rapier","Shortbow","20 arrows","Leather armor","Dagger x2","Thieves' tools"},
                                      {"Shortsword","Shortbow","20 arrows","Leather armor","Dagger x2","Thieves' tools"}};
  if (mainClass == "Fighter")  return {{"Chain Mail","Martial weapon (choose later)","Shield"},
                                      {"Leather armor","Longbow","20 arrows","Martial weapon (choose later)"}};
  if (mainClass == "Barbarian")return {{"Greataxe","Handaxe x2"},
                                      {"Martial weapon (choose later)","Handaxe x2"}};
  if (mainClass == "Cleric")   return {{"Chain Mail","Shield","Mace","Holy symbol"},
                                      {"Leather armor","Shield","Mace","Holy symbol"}};
  if (mainClass == "Bard")     return {{"Rapier","Leather armor","Dagger","Musical instrument (choose later)"},
                                      {"Longsword","Leather armor","Dagger","Musical instrument (choose later)"}};
  if (mainClass == "Druid")    return {{"Wooden shield","Scimitar","Druidic focus"},
                                      {"Wooden shield","Quarterstaff","Druidic focus"}};
  if (mainClass == "Monk")     return {{"Shortsword","Dart x10"},
                                      {"Simple weapon (choose later)","Dart x10"}};
  if (mainClass == "Paladin")  return {{"Chain Mail","Shield","Martial weapon (choose later)","Holy symbol"},
                                      {"Chain Mail","Martial weapon (choose later)","Javelin x5","Holy symbol"}};
  if (mainClass == "Ranger")   return {{"Scale Mail","Shortsword x2","Longbow","20 arrows"},
                                      {"Leather armor","Shortsword x2","Longbow","20 arrows"}};
  if (mainClass == "Artificer")return {{"Leather armor","Light Crossbow","20 bolts","Tinker tools (not tracked)"},
                                      {"Scale Mail","Simple weapon (choose later)","Tinker tools (not tracked)"}};
  return {{"(No pack configured for this class yet)"}};
}

static vector<string> backgroundEquipment(Background& bg) {
  string n = bg.name();
  if (n == "Outlander") return {"Staff","Hunting trap","Trophy","Traveler's clothes","Belt pouch","10 gp"};
  if (n == "Soldier") return {"Insignia of rank","Trophy","Gaming set","Common clothes","Belt pouch","10 gp"};
  if (n == "Acolyte") return {"Holy symbol","Prayer book","Incense x5","Vestments","Common clothes","Belt pouch","15 gp"};
  if (n == "Criminal") return {"Crowbar","Dark common clothes (hood)","Belt pouch","15 gp"};
  if (n == "Sage") return {"Ink","Quill","Small knife","Letter","Common clothes","Belt pouch","10 gp"};
  if (n == "Noble") return {"Fine clothes","Signet ring","Scroll pedigree","Belt pouch","25 gp"};
  return {"(Background equipment not filled for this background yet)"};
}

static void maybeAddWeaponFromItem(vector<string>& weapons, const string& itemRaw) {
  string item = itemRaw;
  auto pos = item.find(" x");
  if (pos != string::npos) item = item.substr(0, pos);
  auto db = weaponDB();
  if (db.count(item)) weapons.push_back(item);
}

// ---------- main ----------
int main() {
  cout << "=== Automatic DnD Sheet (Terminal) ===\n";
  string characterName = readLineNonEmpty("Character name: ");
  int level = readIntInRange("Character level (1-20): ", 1, 20);
  int prof = proficiencyBonus(level);

  cout << "\nChoose ability score method:\n 1) Standard Array (15,14,13,12,10,8)\n 2) Manual entry\n";
  int scoreMode = readIntInRange("Choose: ", 1, 2);

  AbilityScores scores{};
  if (scoreMode == 1) scores = standardArrayAssign();
  else scores = enterScoresManual();

  // ---- Race ----
  vector<string> mains = availableMainRaces();
  string mainRace = mains[pickIndexMenu("Choose Main Race", mains)];

  vector<string> subs = availableSubraces(mainRace);
  string subrace = "";
  if (!subs.empty()) {
    vector<string> subMenu = subs;
    subMenu.insert(subMenu.begin(), "None");
    int sIdx = pickIndexMenu("Choose Subrace for " + mainRace, subMenu);
    subrace = (sIdx == 0 ? "" : subMenu[sIdx]);
  }

  Race& race = getRace(mainRace, subrace);
  race.applyAbilityScoreIncreases(scores);
  if (raceNeedsFlexibleAsi(mainRace, subrace)) applyFlexibleAsiUI(scores);

  // ---- Class ----
  vector<string> classMains = availableMainClasses();
  string mainClass = classMains[pickIndexMenu("Choose Main Class", classMains)];

  vector<string> classSubs = availableSubclasses(mainClass);
  string subclass = "";
  if (!classSubs.empty()) {
    vector<string> subMenu = classSubs;
    subMenu.insert(subMenu.begin(), "None");
    int scIdx = pickIndexMenu("Choose Subclass for " + mainClass, subMenu);
    subclass = (scIdx == 0 ? "" : subMenu[scIdx]);
  }

  DndClass& cls = getClass(mainClass, subclass);

  // ---- Background ----
  vector<string> bgs = availableBackgroundNames();
  string bgName = bgs[pickIndexMenu("Choose Background", bgs)];
  Background& bg = getBackgroundByName(bgName);

  // ---- Skills ----
  vector<string> chosenClassSkills = chooseNFromList("Choose Class Skill Proficiencies",
                                                     cls.skillOptions(), cls.numberOfSkillChoices());
  std::set<string> proficientSkills;
  for (const auto& s : bg.skillProficiencies()) proficientSkills.insert(s);
  for (const auto& s : chosenClassSkills) proficientSkills.insert(s);

  // ---- HP ----
  int conMod = modifierFromScore(scores[idx(Ability::CON)]);
  int maxHP = std::max(1, cls.hitDie() + conMod);
  int currentHP = maxHP;
  int tempHP = 0;

  // ---- Equipment ----
  auto packs = classEquipmentPacks(mainClass);
  vector<string> packNames;
  for (size_t i = 0; i < packs.size(); ++i) packNames.push_back("Pack " + std::string(1, char('A' + (int)i)));
  vector<string> equipment = packs[pickIndexMenu("Choose Starting Equipment Pack", packNames)];

  auto bgEquip = backgroundEquipment(bg);
  equipment.insert(equipment.end(), bgEquip.begin(), bgEquip.end());

  // weapon extraction
  vector<string> weaponNames;
  for (auto& it : equipment) maybeAddWeaponFromItem(weaponNames, it);

  // choose later weapons
  auto askPickWeapon = [&](bool martial) {
    auto db = weaponDB();
    vector<string> opts;
    for (auto& kv : db) {
      if (martial && kv.second.martial) opts.push_back(kv.first);
      if (!martial && !kv.second.martial) opts.push_back(kv.first);
    }
    std::sort(opts.begin(), opts.end());
    string picked = opts[pickIndexMenu(martial ? "Pick a martial weapon" : "Pick a simple weapon", opts)];
    weaponNames.push_back(picked);
    equipment.push_back(picked);
  };
  for (auto& it : equipment) {
    if (it == "Martial weapon (choose later)") askPickWeapon(true);
    if (it == "Simple weapon (choose later)") askPickWeapon(false);
  }

  // Shield
  bool hasShield = false;
  for (auto& it : equipment) if (it == "Shield" || it == "Wooden shield") hasShield = true;
  if (!hasShield) {
    hasShield = (readIntInRange("Using a shield? (1=yes, 2=no): ", 1, 2) == 1);
    if (hasShield) equipment.push_back("Shield");
  }

  // Armor pick (simple)
  vector<ArmorChoice> armors = {
    {"None", 10, false, false},
    {"Leather", 11, true, false},
    {"Studded Leather", 12, true, false},
    {"Hide", 12, false, true},
    {"Chain Shirt", 13, false, true},
    {"Scale Mail", 14, false, true},
    {"Breastplate", 14, false, true},
    {"Half Plate", 15, false, true},
    {"Ring Mail", 14, false, false},
    {"Chain Mail", 16, false, false},
    {"Splint", 17, false, false},
    {"Plate", 18, false, false},
  };
  ArmorChoice worn = armors[pickIndexMenu("Choose Armor to wear (for AC)", [&]{
    vector<string> names; for (auto& a: armors) names.push_back(a.name); return names;
  }())];

  // Natural armor option
  int naturalAC = raceNaturalACOption(race, scores);
  bool useNatural = false;
  if (naturalAC != -1) useNatural = (readIntInRange("Use racial Natural Armor for AC? (1=yes, 2=no): ", 1, 2) == 1);

  int miscACBonus = 0;
  if (race.mainRace() == "Warforged") {
    if (readIntInRange("Warforged AC bonus? (1=legacy +1 AC, 2=none/modern): ", 1, 2) == 1) miscACBonus += 1;
  }

  int AC = useNatural ? (naturalAC + (hasShield ? 2 : 0) + miscACBonus)
                      : calcArmorAC(scores, worn, hasShield, miscACBonus);

  int initiative = modifierFromScore(scores[idx(Ability::DEX)]);

  // Attacks
  auto db = weaponDB();
  struct AttackLine { string name; string toHit; string detail; };
  vector<AttackLine> attacks;

  int lightMeleeCount = 0;

  for (auto& wn : weaponNames) {
    if (!db.count(wn)) continue;
    WeaponDef w = db[wn];

    Ability used = weaponAbilityUsed(scores, w);
    int abilMod = modifierFromScore(scores[idx(used)]);
    bool proficient = hasWeaponProficiency(cls, w);
    int toHit = abilMod + (proficient ? prof : 0);

    string dmg;
    if (wn == "Net" || w.damageDie == 0) {
      dmg = "Special (no damage)";
    } else {
      string dice = (w.dieCount == 2 ? "2d" : "1d") + std::to_string(w.damageDie);
      if (w.versatile) {
        int vh = readIntInRange(("Use " + wn + " two-handed for versatile damage? (1=yes, 2=no): "), 1, 2);
        if (vh == 1) dice = "1d" + std::to_string(w.versatileDie);
      }
      dmg = dice + modString(abilMod);
    }

    if (w.light && !w.ammunition && !w.special) lightMeleeCount++;

    attacks.push_back({wn, modString(toHit), "Damage: " + dmg + "  [" + weaponPropertiesString(w) + "]"});
  }

  bool hasTwoWeaponFightingCandidate = (lightMeleeCount >= 2);

  // Skills totals
  auto skillMap = skillAbilityMap();
  auto skills = allSkills();

  int passivePerception = 10 + modifierFromScore(scores[idx(Ability::WIS)]) + (proficientSkills.count("Perception") ? prof : 0);
  int passiveInsight = 10 + modifierFromScore(scores[idx(Ability::WIS)]) + (proficientSkills.count("Insight") ? prof : 0);
  int passiveInvestigation = 10 + modifierFromScore(scores[idx(Ability::INT)]) + (proficientSkills.count("Investigation") ? prof : 0);

  std::set<Ability> saveProfs;
  for (auto a : cls.savingThrowProficiencies()) saveProfs.insert(a);

  // Output
  std::ostringstream out;
  out << "==================== CHARACTER SUMMARY ====================\n";
  out << "Name: " << characterName << "\n";
  out << "Level: " << level << "   Proficiency Bonus: " << modString(prof) << "\n\n";

  out << "Race: " << race.mainRace();
  if (!race.subrace().empty()) out << " (" << race.subrace() << ")";
  out << "\nSpeed: " << race.speed() << "\n\n";

  out << "Class: " << cls.mainClass();
  if (!cls.subclass().empty()) out << " (" << cls.subclass() << ")";
  out << "\nHit Die: d" << cls.hitDie() << "\n\n";

  out << "Background: " << bg.name();
  if (!bg.source().empty()) out << " [" << bg.source() << "]";
  out << "\n\n";

  printScores(out, scores);

  out << "\nCOMBAT\n";
  out << "AC: " << AC << "   Initiative: " << modString(initiative) << "   Speed: " << race.speed() << "\n";
  out << "HP: " << currentHP << "/" << maxHP << "   Temp HP: " << tempHP << "   Hit Dice: " << level << "d" << cls.hitDie() << "\n";

  out << "\nATTACKS\n";
  if (attacks.empty()) out << " (no attacks recorded)\n";
  for (auto& a : attacks) out << " - " << a.name << " | To Hit: " << a.toHit << " | " << a.detail << "\n";
  if (hasTwoWeaponFightingCandidate) out << "Note: Two-Weapon Fighting available (bonus action off-hand attack) if both are light.\n";

  out << "\nEQUIPMENT\n";
  for (auto& it : equipment) out << " - " << it << "\n";

  out << "\nSAVING THROWS\n";
  for (Ability a : kAbilities) {
    int base = modifierFromScore(scores[idx(a)]);
    int total = base + (saveProfs.count(a) ? prof : 0);
    out << " " << abilityName(a) << ": " << modString(total) << (saveProfs.count(a) ? " (prof)" : "") << "\n";
  }

  out << "\nSKILLS\n";
  for (const auto& sk : skills) {
    Ability a = skillMap[sk];
    int base = modifierFromScore(scores[idx(a)]);
    int total = base + (proficientSkills.count(sk) ? prof : 0);
    out << " " << sk << " (" << abilityName(a) << "): " << modString(total)
        << (proficientSkills.count(sk) ? " (prof)" : "") << "\n";
  }
  out << "\nPassive Perception: " << passivePerception
      << "   Passive Insight: " << passiveInsight
      << "   Passive Investigation: " << passiveInvestigation << "\n";

  auto rTraits = race.traits();
  if (!rTraits.empty()) {
    out << "\nRACE TRAITS\n";
    for (const auto& tr : rTraits) out << " - " << tr.name << ": " << tr.description << "\n";
  }

  auto l1 = cls.level1Features();
  if (!l1.empty()) {
    out << "\nCLASS FEATURES (Level 1)\n";
    for (const auto& f : l1) out << " - " << f.name << ": " << f.description << "\n";
  }

  auto subFeats = cls.subclassFeaturesAtLevel(level);
  if (!subFeats.empty()) {
    out << "\nSUBCLASS FEATURES\n";
    for (const auto& f : subFeats) out << " - " << f.name << ": " << f.description << "\n";
  }

  auto bgFeat = bg.feature();
  if (!bgFeat.name.empty()) {
    out << "\nBACKGROUND FEATURE\n";
    out << " - " << bgFeat.name << ": " << bgFeat.description << "\n";
  }

  out << "===========================================================\n";

  cout << "\n\n" << out.str() << "\n";

  string filename = sanitizeFilename(characterName) + "_sheet.txt";
  std::ofstream fout(filename);
  if (!fout) {
    cout << "ERROR: Could not write file: " << filename << "\n";
  } else {
    fout << out.str();
    fout.close();
    cout << "Saved character sheet to: " << filename << "\n";
  }

  return 0;
}