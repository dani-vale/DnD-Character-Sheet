#include "race.h"
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <string>
#include <vector>

static bool isNone(const std::string& s) {
  return s.empty() || s == "None" || s == "none";
}

static std::string trim(std::string s) {
  while (!s.empty() && std::isspace((unsigned char)s.front())) s.erase(s.begin());
  while (!s.empty() && std::isspace((unsigned char)s.back())) s.pop_back();
  return s;
}

// ---------------- Flexible ASI helpers (exported) ----------------

static void applyAsiChoice(AbilityScores& s, Ability a, int amount) {
  s[idx(a)] += amount;
}

void applyFlexibleAsi_2_1(AbilityScores& s, Ability plus2, Ability plus1) {
  applyAsiChoice(s, plus2, 2);
  applyAsiChoice(s, plus1, 1);
}

void applyFlexibleAsi_1_1_1(AbilityScores& s, Ability a, Ability b, Ability c) {
  applyAsiChoice(s, a, 1);
  applyAsiChoice(s, b, 1);
  applyAsiChoice(s, c, 1);
}

// ---------------- Data model ----------------

struct RaceDef {
  std::string main;
  std::string sub; // "" if none
  int baseSpeed = 30;

  bool needsFlexibleAsi = false;

  // Fixed ASI can be applied here; if flexible, leave empty.
  void (*applyAsi)(AbilityScores&) = nullptr;

  std::vector<Trait> traitList;
};

static void fixedAsi(int str, int dex, int con, int intel, int wis, int cha, AbilityScores& s) {
  s[idx(Ability::STR)] += str;
  s[idx(Ability::DEX)] += dex;
  s[idx(Ability::CON)] += con;
  s[idx(Ability::INT)] += intel;
  s[idx(Ability::WIS)] += wis;
  s[idx(Ability::CHA)] += cha;
}

// One Race wrapper for each RaceDef
class RaceFromData : public Race {
public:
  RaceFromData() : def(nullptr) {}
  explicit RaceFromData(const RaceDef* d) : def(d) {}

  std::string mainRace() { return def ? def->main : "Unknown"; }
  std::string subrace() { return def ? def->sub : ""; }

  void applyAbilityScoreIncreases(AbilityScores& scores) {
    if (def && def->applyAsi) def->applyAsi(scores);
  }

  int speed() { return def ? def->baseSpeed : 30; }
  std::vector<Trait> traits() { return def ? def->traitList : std::vector<Trait>{}; }

  void bind(const RaceDef* d) { def = d; }

private:
  const RaceDef* def;
};

static std::string displayOf(const RaceDef& d) {
  return d.sub.empty() ? d.main : d.main + " (" + d.sub + ")";
}

// ---------------- Registry ----------------

static std::vector<RaceDef>& defs() {
  static std::vector<RaceDef> v;
  if (!v.empty()) return v;

  auto add = [&](RaceDef d) { v.push_back(std::move(d)); };

// ===================== PHB 2014 RACES (data-driven) =====================

// Human
add({"Human","",30,false,
     [](AbilityScores& s){ for (auto& score : s) score += 1; },
     {{"Extra Language","One extra language of your choice."}}});

// Dwarf (Hill / Mountain)
add({"Dwarf","Hill",25,false,
     [](AbilityScores& s){ fixedAsi(0,0,+2,0,+1,0,s); },
     {{"Darkvision","60 ft."},
      {"Dwarven Resilience","Poison save advantage + poison resistance."},
      {"Dwarven Combat Training","Battleaxe/handaxe/light hammer/warhammer proficiency."},
      {"Tool Proficiency","Choose one: smith’s tools, brewer’s supplies, or mason’s tools."},
      {"Stonecunning","History related to stonework bonus."},
      {"Dwarven Toughness","+1 HP per level."}}});

add({"Dwarf","Mountain",25,false,
     [](AbilityScores& s){ fixedAsi(+2,0,+2,0,0,0,s); },
     {{"Darkvision","60 ft."},
      {"Dwarven Resilience","Poison save advantage + poison resistance."},
      {"Dwarven Combat Training","Battleaxe/handaxe/light hammer/warhammer proficiency."},
      {"Tool Proficiency","Choose one: smith’s tools, brewer’s supplies, or mason’s tools."},
      {"Stonecunning","History related to stonework bonus."},
      {"Dwarven Armor Training","Light and medium armor proficiency."}}});

// Elf (High / Wood / Drow)
add({"Elf","High",30,false,
     [](AbilityScores& s){ fixedAsi(0,+2,0,+1,0,0,s); },
     {{"Darkvision","60 ft."},
      {"Keen Senses","Perception proficiency."},
      {"Fey Ancestry","Charm save advantage; immune to magic sleep."},
      {"Trance","4-hour meditation."},
      {"Elf Weapon Training","Longsword/shortsword/shortbow/longbow proficiency."},
      {"Cantrip","One wizard cantrip of your choice."},
      {"Extra Language","One extra language of your choice."}}});

add({"Elf","Wood",35,false,
     [](AbilityScores& s){ fixedAsi(0,+2,0,0,+1,0,s); },
     {{"Darkvision","60 ft."},
      {"Keen Senses","Perception proficiency."},
      {"Fey Ancestry","Charm save advantage; immune to magic sleep."},
      {"Trance","4-hour meditation."},
      {"Elf Weapon Training","Longsword/shortsword/shortbow/longbow proficiency."},
      {"Fleet of Foot","Base walking speed is 35 ft."},
      {"Mask of the Wild","Hide when lightly obscured by nature."}}});

add({"Elf","Drow",30,false,
     [](AbilityScores& s){ fixedAsi(0,+2,0,0,0,+1,s); },
     {{"Superior Darkvision","120 ft."},
      {"Sunlight Sensitivity","Sunlight penalties (PHB drow)."},
      {"Keen Senses","Perception proficiency."},
      {"Fey Ancestry","Charm save advantage; immune to magic sleep."},
      {"Trance","4-hour meditation."},
      {"Drow Magic","Innate magic as you level."},
      {"Drow Weapon Training","Rapier/shortsword/hand crossbow proficiency."}}});

// Halfling (Lightfoot / Stout)
add({"Halfling","Lightfoot",25,false,
     [](AbilityScores& s){ fixedAsi(0,+2,0,0,0,+1,s); },
     {{"Lucky","Reroll 1s on d20 for attack/check/save."},
      {"Brave","Advantage vs frightened."},
      {"Halfling Nimbleness","Move through space of creatures larger than you."},
      {"Naturally Stealthy","Hide when obscured by a creature larger than you."}}});

add({"Halfling","Stout",25,false,
     [](AbilityScores& s){ fixedAsi(0,+2,+1,0,0,0,s); },
     {{"Lucky","Reroll 1s on d20 for attack/check/save."},
      {"Brave","Advantage vs frightened."},
      {"Halfling Nimbleness","Move through space of creatures larger than you."},
      {"Stout Resilience","Poison save advantage + poison resistance."}}});

// Gnome (Forest / Rock)
add({"Gnome","Forest",25,false,
     [](AbilityScores& s){ fixedAsi(0,+1,0,+2,0,0,s); },
     {{"Darkvision","60 ft."},
      {"Gnome Cunning","Advantage on INT/WIS/CHA saves vs magic."},
      {"Natural Illusionist","Know minor illusion cantrip."},
      {"Speak with Small Beasts","Communicate simple ideas with Small or smaller beasts."}}});

add({"Gnome","Rock",25,false,
     [](AbilityScores& s){ fixedAsi(0,0,+1,+2,0,0,s); },
     {{"Darkvision","60 ft."},
      {"Gnome Cunning","Advantage on INT/WIS/CHA saves vs magic."},
      {"Artificer’s Lore","History bonus on magic items/alchemy/tech."},
      {"Tinker","Build tiny clockwork devices (PHB rules)."}}});

// Half-Elf (PHB has choices; we apply fixed +2 CHA and note choices)
add({"Half-Elf","",30,false,
     [](AbilityScores& s){ fixedAsi(0,0,0,0,0,+2,s); },
     {{"Darkvision","60 ft."},
      {"Fey Ancestry","Charm save advantage; immune to magic sleep."},
      {"Skill Versatility","Gain proficiency in two skills of your choice."},
      {"Extra Language","One extra language of your choice."},
      {"ASI Choice Note","PHB: +1 to two other abilities of your choice (implement as UI pick)."}}});

// Half-Orc
add({"Half-Orc","",30,false,
     [](AbilityScores& s){ fixedAsi(+2,0,+1,0,0,0,s); },
     {{"Darkvision","60 ft."},
      {"Menacing","Intimidation proficiency."},
      {"Relentless Endurance","Drop to 1 HP instead of 0 (1/long rest)."},
      {"Savage Attacks","On melee crit, roll one extra weapon damage die."}}});

// Dragonborn
add({"Dragonborn","",30,false,
     [](AbilityScores& s){ fixedAsi(+2,0,0,0,0,+1,s); },
     {{"Draconic Ancestry","Choose ancestry; affects breath/resistance."},
      {"Breath Weapon","Use action to exhale energy (ancestry-based)."},
      {"Damage Resistance","Resistance matching ancestry."}}});

// Tiefling (PHB)
add({"Tiefling","",30,false,
     [](AbilityScores& s){ fixedAsi(0,0,0,+1,0,+2,s); },
     {{"Darkvision","60 ft."},
      {"Hellish Resistance","Resistance to fire damage."},
      {"Infernal Legacy","Innate magic as you level."}}});

// ===================== BIG OFFICIAL NON-PHB RACE PACK (Flexible ASI) =====================
// Paste these inside defs() in race.cpp, after your PHB adds.

auto flexNote = Trait{"Flexible ASI", "Choose +2/+1 or +1/+1/+1 to abilities."};

// ---------- Aarakocra (EEPC) ----------
add({"Aarakocra","",25,true,nullptr,
     {flexNote,
      {"Flight","You have a flying speed (see table rules/restrictions)."},
      {"Talons","Natural weapon option."}}});

// ---------- Aasimar (Volo/MToF legacy; subraces) ----------
add({"Aasimar","Protector",30,true,nullptr,
     {flexNote,
      {"Darkvision","60 ft."},
      {"Celestial Resistance","Radiant + necrotic resistance."},
      {"Healing Hands","Touch heal (limited)."},
      {"Light Bearer","Know light cantrip."},
      {"Radiant Soul","Transformation feature (later)."}}});

add({"Aasimar","Scourge",30,true,nullptr,
     {flexNote,
      {"Darkvision","60 ft."},
      {"Celestial Resistance","Radiant + necrotic resistance."},
      {"Healing Hands","Touch heal (limited)."},
      {"Light Bearer","Know light cantrip."},
      {"Radiant Consumption","Transformation aura feature (later)."}}});

add({"Aasimar","Fallen",30,true,nullptr,
     {flexNote,
      {"Darkvision","60 ft."},
      {"Celestial Resistance","Radiant + necrotic resistance."},
      {"Healing Hands","Touch heal (limited)."},
      {"Light Bearer","Know light cantrip."},
      {"Necrotic Shroud","Frighten/necrotic transformation (later)."}}});

// ---------- Astral Elf (Spelljammer) ----------
add({"Astral Elf","",30,true,nullptr,
     {flexNote,
      {"Astral Trance","Elf trance with extra astral flavor (version-dependent)."},
      {"Starlight Step","Teleport-style movement feature."}}});

// ---------- Autognome (Spelljammer) ----------
add({"Autognome","",30,true,nullptr,
     {flexNote,
      {"Construct Nature","Construct-like resilience (version-dependent)."},
      {"Built-in Tool","Integrated tool/utility feature."}}});

// ---------- Bugbear (Volo/MPMM) ----------
add({"Bugbear","",30,true,nullptr,
     {flexNote,
      {"Long-Limbed","Extra reach on your turn."},
      {"Surprise Attack","Extra damage when you catch foes off guard."},
      {"Powerful Build","Count as larger for carrying/push/pull."}}});

// ---------- Centaur (Ravnica/MPMM) ----------
add({"Centaur","",40,true,nullptr,
     {flexNote,
      {"Charge","After moving, bonus attack option."},
      {"Hooves","Natural weapon."},
      {"Equine Build","Body-shape limitations + carrying advantages."}}});

// ---------- Changeling (Eberron) ----------
add({"Changeling","",30,true,nullptr,
     {flexNote,
      {"Shapechanger","Change appearance/voice."}}});

// ---------- Dhampir (Van Richten lineage) ----------
add({"Dhampir","",35,true,nullptr,
     {flexNote,
      {"Vampiric Bite","Natural bite with special effects."},
      {"Spider Climb","Wall/ceiling movement (version-dependent)."}}});

// ---------- Duergar (as Dwarf subrace; SCAG/MToF/MPMM legacy) ----------
add({"Dwarf","Duergar",25,true,nullptr,
     {flexNote,
      {"Superior Darkvision","120 ft."},
      {"Duergar Resilience","Mental/illusion resilience (version-dependent)."},
      {"Duergar Magic","Innate duergar-themed magic (later)."},
      {"Sunlight Sensitivity","Legacy versions: sunlight penalties."}}});

// ---------- Eladrin / Sea Elf / Shadar-kai (Elf variants) ----------
add({"Elf","Eladrin",30,true,nullptr,
     {flexNote,
      {"Darkvision","60 ft."},
      {"Fey Ancestry","Charm save advantage; immune to magic sleep."},
      {"Trance","4-hour meditation."},
      {"Fey Step","Teleport with seasonal rider (version-dependent)."}}});

add({"Elf","Sea",30,true,nullptr,
     {flexNote,
      {"Darkvision","60 ft."},
      {"Swim","Swim speed."},
      {"Friend of the Sea","Communicate simple ideas with sea creatures (typical)."},
      {"Fey Ancestry","Charm save advantage; immune to magic sleep."},
      {"Trance","4-hour meditation."}}});

add({"Elf","Shadar-kai",30,true,nullptr,
     {flexNote,
      {"Darkvision","60–120 ft (version-dependent)."},
      {"Fey Ancestry","Charm save advantage; immune to magic sleep."},
      {"Trance","4-hour meditation."},
      {"Blessing of the Raven Queen","Teleport + defensive rider (version-dependent)."}}});

// ---------- Fairy (WBtW/MPMM) ----------
add({"Fairy","",30,true,nullptr,
     {flexNote,
      {"Flight","You have a flying speed (see table rules/restrictions)."},
      {"Fey Magic","Innate fey-themed spells/utility."}}});

// ---------- Firbolg (Volo/MPMM) ----------
add({"Firbolg","",30,true,nullptr,
     {flexNote,
      {"Firbolg Magic","Innate magic/utility."},
      {"Hidden Step","Brief invisibility (limited)."},
      {"Powerful Build","Count as larger for carrying."},
      {"Speech of Beast and Leaf","Communicate simple ideas to beasts/plants."}}});

// ---------- Genasi (Air/Earth/Fire/Water) ----------
add({"Genasi","Air",30,true,nullptr,
     {flexNote,
      {"Unending Breath","Breath-holding benefits."},
      {"Air Magic","Air-themed spells/utility (version-dependent)."}}});

add({"Genasi","Earth",30,true,nullptr,
     {flexNote,
      {"Earth Walk","Ignore difficult terrain made of earth/stone."},
      {"Earth Magic","Earth-themed spells/utility (version-dependent)."}}});

add({"Genasi","Fire",30,true,nullptr,
     {flexNote,
      {"Darkvision","60 ft (often)."},
      {"Fire Resistance","Resistance to fire damage."},
      {"Fire Magic","Fire-themed spells/utility (version-dependent)."}}});

add({"Genasi","Water",30,true,nullptr,
     {flexNote,
      {"Amphibious","Breathe air and water."},
      {"Swim","Swim speed."},
      {"Water Magic","Water-themed spells/utility (version-dependent)."}}});

// ---------- Giff / Hadozee / Plasmoid / Thri-kreen (Spelljammer) ----------
add({"Giff","",30,true,nullptr,
     {flexNote,
      {"Astral Spark","Giff battle confidence-style feature (version-dependent)."},
      {"Firearms Familiarity","Table-dependent firearms proficiency/affinity."}}});

add({"Hadozee","",30,true,nullptr,
     {flexNote,
      {"Glide","Glide using membranes."},
      {"Dexterous Feet","Extra manipulation utility."}}});

add({"Plasmoid","",30,true,nullptr,
     {flexNote,
      {"Amorphous","Squeeze through narrow spaces."},
      {"Shape Self","Basic shapeshift/utility."},
      {"Hold Breath","Long breath-holding."}}});

add({"Thri-kreen","",30,true,nullptr,
     {flexNote,
      {"Secondary Arms","Extra arms for item manipulation."},
      {"Chameleon Carapace","Defensive/stealthy carapace feature."},
      {"Telepathy","Limited telepathy."}}});

// ---------- Gith (MToF/MPMM) ----------
add({"Gith","Githyanki",30,true,nullptr,
     {flexNote,
      {"Psionics","Innate psionic spells/utility."},
      {"Astral Knowledge","Temporary skill/tool proficiency (version-dependent)."}}});

add({"Gith","Githzerai",30,true,nullptr,
     {flexNote,
      {"Psionics","Innate psionic spells/utility."},
      {"Mental Discipline","Resilience vs mental effects (version-dependent)."}}});

// ---------- Goblinoids (Goblin/Hobgoblin/Bugbear already above) ----------
add({"Goblin","",30,true,nullptr,
     {flexNote,
      {"Nimble Escape","Bonus action Hide/Disengage."},
      {"Small Fury","Extra damage/boost vs larger foes (version-dependent)."}}});

add({"Hobgoblin","",30,true,nullptr,
     {flexNote,
      {"Saving Face","Add a bonus to a failed roll (limited)."},
      {"Martial Training","Weapon/armor training (version-dependent)."}}});

// ---------- Goliath (EEPC/MPMM) ----------
add({"Goliath","",30,true,nullptr,
     {flexNote,
      {"Natural Athlete","Athletics proficiency (common)."},
      {"Stone’s Endurance","Reaction reduce damage (limited)."},
      {"Powerful Build","Count as larger for carrying/push/pull."}}});

// ---------- Grung (One Grung Above) ----------
add({"Grung","",25,true,nullptr,
     {flexNote,
      {"Poisonous Skin","Poison interaction on contact (table-dependent)."},
      {"Standing Leap","Powerful jumps."},
      {"Water Dependency","Needs water regularly (table-dependent)."}}});

// ---------- Harengon (WBtW/MPMM) ----------
add({"Harengon","",30,true,nullptr,
     {flexNote,
      {"Hare-Trigger","Initiative bonus."},
      {"Rabbit Hop","Bonus-action hop (limited)."},
      {"Leporine Senses","Perception bonus/proficiency (version-dependent)."}}});

// ---------- Hexblood (Van Richten lineage) ----------
add({"Hexblood","",30,true,nullptr,
     {flexNote,
      {"Hex Magic","Innate hex-themed spells/utility."},
      {"Eerie Token","Token-based scry/communication style feature (version-dependent)."}}});

// ---------- Kalashtar (Eberron) ----------
add({"Kalashtar","",30,true,nullptr,
     {flexNote,
      {"Mind Link","Telepathic communication."},
      {"Mental Discipline","Psychic resistance and mental resilience (version-dependent)."}}});

// ---------- Kenku (Volo/MPMM) ----------
add({"Kenku","",30,true,nullptr,
     {flexNote,
      {"Mimicry","Imitate sounds/voices."},
      {"Kenku Recall","Skill memory/advantage-style feature (version-dependent)."}}});

// ---------- Kobold (Volo/MPMM) ----------
add({"Kobold","",30,true,nullptr,
     {flexNote,
      {"Draconic Cry / Pack Tactics","Teamwork combat feature (varies by printing)."},
      {"Darkvision","60 ft."},
      {"Sunlight Sensitivity","Legacy versions: sunlight penalties."}}});

// ---------- Leonin (Theros) ----------
add({"Leonin","",35,true,nullptr,
     {flexNote,
      {"Daunting Roar","Frighten nearby creatures (limited)."},
      {"Claws","Natural weapon option."}}});

// ---------- Lizardfolk (Volo/MPMM) ----------
add({"Lizardfolk","",30,true,nullptr,
     {flexNote,
      {"Natural Armor","Higher base AC without armor."},
      {"Hungry Jaws","Bonus-action bite + temp HP (limited)."},
      {"Hold Breath","Hold breath for a long time."}}});

// ---------- Locathah (Locathah Rising) ----------
add({"Locathah","",30,true,nullptr,
     {flexNote,
      {"Swim","Swim speed."},
      {"Natural Armor","Tough scales base AC option."},
      {"Leviathan Will","Mental resilience feature (version-dependent)."},
      {"Water Dependency","Needs water regularly (table-dependent)."}}});

// ---------- Loxodon (Ravnica) ----------
add({"Loxodon","",30,true,nullptr,
     {flexNote,
      {"Natural Armor","Tough hide AC option."},
      {"Trunk","Use trunk for simple tasks."},
      {"Powerful Build","Carrying boost."},
      {"Keen Smell","Smell-related benefit (typical)."}}});

// ---------- Minotaur (Ravnica/Theros variants) ----------
add({"Minotaur","",30,true,nullptr,
     {flexNote,
      {"Horns","Natural weapon."},
      {"Goring Rush","Charge-style bonus attack option."},
      {"Hammering Horns","Push a creature after hitting (typical)."}}});

// ---------- Orc (Volo/MPMM) ----------
add({"Orc","",30,true,nullptr,
     {flexNote,
      {"Darkvision","60 ft."},
      {"Aggressive","Bonus action move toward an enemy."},
      {"Powerful Build","Count as larger for carrying/push/pull."}}});

// ---------- Owlin (Strixhaven) ----------
add({"Owlin","",30,true,nullptr,
     {flexNote,
      {"Flight","Flying speed."},
      {"Darkvision","Darkvision."},
      {"Silent Feathers","Stealth/proficiency-style benefit (version-dependent)."}}});

// ---------- Reborn (Van Richten lineage) ----------
add({"Reborn","",30,true,nullptr,
     {flexNote,
      {"Deathless Nature","Reduced needs; resilience (version-dependent)."},
      {"Knowledge from a Past Life","Add a d6 to some checks (limited)."}}});

// ---------- Satyr (Theros) ----------
add({"Satyr","",35,true,nullptr,
     {flexNote,
      {"Ram","Natural weapon."},
      {"Mirthful Leaps","Jump/mobility benefit (typical)."},
      {"Magic Resistance","Resilience vs spells (version-dependent)."}}});

// ---------- Simic Hybrid (Ravnica) ----------
add({"Simic Hybrid","",30,true,nullptr,
     {flexNote,
      {"Animal Enhancements","Choose mutation options as you level."},
      {"Adaptation","Swim/climb/glide-style options (version-dependent)."}}});

// ---------- Shifter (Eberron) subraces ----------
add({"Shifter","Beasthide",30,true,nullptr,
     {flexNote,
      {"Shifting","Bonus action shift for temporary benefits."},
      {"Beasthide Shift","Toughness/defense shift rider."}}});

add({"Shifter","Longtooth",30,true,nullptr,
     {flexNote,
      {"Shifting","Bonus action shift for temporary benefits."},
      {"Longtooth Shift","Offense/bite-style shift rider."}}});

add({"Shifter","Swiftstride",30,true,nullptr,
     {flexNote,
      {"Shifting","Bonus action shift for temporary benefits."},
      {"Swiftstride Shift","Speed/evasion shift rider."}}});

add({"Shifter","Wildhunt",30,true,nullptr,
     {flexNote,
      {"Shifting","Bonus action shift for temporary benefits."},
      {"Wildhunt Shift","Tracking/awareness shift rider."}}});

// ---------- Tabaxi (Volo/MPMM) ----------
add({"Tabaxi","",30,true,nullptr,
     {flexNote,
      {"Cat’s Claws","Climb speed + natural weapon."},
      {"Feline Agility","Burst of speed (recharge by standing still)."}}});

// ---------- Tortle (Tortle Package/MPMM) ----------
add({"Tortle","",30,true,nullptr,
     {flexNote,
      {"Natural Armor","High base AC without armor."},
      {"Shell Defense","Withdraw into shell for defense (trade-offs)."}}});

// ---------- Triton (Volo/MPMM) ----------
add({"Triton","",30,true,nullptr,
     {flexNote,
      {"Amphibious","Breathe air and water."},
      {"Swim","Swim speed."},
      {"Guardians of the Depths","Cold resistance/deep adaptation (version-dependent)."},
      {"Innate Magic","Sea-themed spells/utility (version-dependent)."}}});

// ---------- Vedalken (Ravnica) ----------
add({"Vedalken","",30,true,nullptr,
     {flexNote,
      {"Vedalken Dispassion","Advantage vs certain mental saves."},
      {"Tireless Precision","Add d4 to chosen skill/tool checks (limited)."}}});

// ---------- Verdan (Acq Inc) ----------
add({"Verdan","",30,true,nullptr,
     {flexNote,
      {"Telepathic Insight","Limited telepathy."},
      {"Black Blood Healing","Resilience/healing interaction (version-dependent)."},
      {"Limited Mutation","Size/trait changes over levels (version-dependent)."}}});

// ---------- Warforged (Eberron) ----------
add({"Warforged","",30,true,nullptr,
     {flexNote,
      {"Constructed Resilience","Construct-like resilience (version-dependent)."},
      {"Integrated Protection","Built-in defensive trait (version-dependent)."},
      {"Specialized Design","Skill/tool proficiency bonus (version-dependent)."}}});

// ---------- Yuan-ti (Volo/MPMM) ----------
add({"Yuan-ti","",30,true,nullptr,
     {flexNote,
      {"Darkvision","60 ft (typical)."},
      {"Poison Resilience","Poison resilience (version-dependent)."},
      {"Innate Magic","Snake-themed spells/utility."}}});

// ---------- Tiefling bloodlines (SCAG/MToF style, modeled as Tiefling subraces) ----------
add({"Tiefling","Asmodeus",30,true,nullptr,
     {flexNote, {"Hellish Resistance","Fire resistance."}, {"Infernal Legacy","Asmodeus spell package (later)."}, {"Darkvision","60 ft."}}});

add({"Tiefling","Baalzebul",30,true,nullptr,
     {flexNote, {"Hellish Resistance","Fire resistance."}, {"Legacy of Maladomini","Baalzebul spell package (later)."}, {"Darkvision","60 ft."}}});

add({"Tiefling","Dispater",30,true,nullptr,
     {flexNote, {"Hellish Resistance","Fire resistance."}, {"Legacy of Dis","Dispater spell package (later)."}, {"Darkvision","60 ft."}}});

add({"Tiefling","Fierna",30,true,nullptr,
     {flexNote, {"Hellish Resistance","Fire resistance."}, {"Legacy of Phlegethos","Fierna spell package (later)."}, {"Darkvision","60 ft."}}});

add({"Tiefling","Glasya",30,true,nullptr,
     {flexNote, {"Hellish Resistance","Fire resistance."}, {"Legacy of Malbolge","Glasya spell package (later)."}, {"Darkvision","60 ft."}}});

add({"Tiefling","Levistus",30,true,nullptr,
     {flexNote, {"Hellish Resistance","Fire resistance."}, {"Legacy of Stygia","Levistus spell package (later)."}, {"Darkvision","60 ft."}}});

add({"Tiefling","Mammon",30,true,nullptr,
     {flexNote, {"Hellish Resistance","Fire resistance."}, {"Legacy of Minauros","Mammon spell package (later)."}, {"Darkvision","60 ft."}}});

add({"Tiefling","Mephistopheles",30,true,nullptr,
     {flexNote, {"Hellish Resistance","Fire resistance."}, {"Legacy of Cania","Mephistopheles spell package (later)."}, {"Darkvision","60 ft."}}});

add({"Tiefling","Zariel",30,true,nullptr,
     {flexNote, {"Hellish Resistance","Fire resistance."}, {"Legacy of Avernus","Zariel spell package (later)."}, {"Darkvision","60 ft."}}});
  return v;
}

static std::vector<RaceFromData>& objs() {
  static std::vector<RaceFromData> o;
  if (!o.empty()) return o;

  auto& d = defs();
  o.resize(d.size());
  for (size_t i = 0; i < d.size(); ++i) o[i].bind(&d[i]);
  return o;
}

// ---------------- Public API ----------------

std::vector<std::string> availableMainRaces() {
  auto& d = defs();
  std::vector<std::string> mains;
  for (auto& r : d) mains.push_back(r.main);
  std::sort(mains.begin(), mains.end());
  mains.erase(std::unique(mains.begin(), mains.end()), mains.end());
  return mains;
}

std::vector<std::string> availableSubraces(const std::string& mainRace) {
  auto& d = defs();
  std::vector<std::string> subs;
  for (auto& r : d) if (r.main == mainRace && !r.sub.empty()) subs.push_back(r.sub);
  std::sort(subs.begin(), subs.end());
  subs.erase(std::unique(subs.begin(), subs.end()), subs.end());
  return subs;
}

Race& getRace(const std::string& mainRace, const std::string& subrace) {
  auto& d = defs();
  auto& o = objs();

  std::string sub = isNone(subrace) ? "" : subrace;

  for (size_t i = 0; i < d.size(); ++i) {
    if (d[i].main == mainRace && d[i].sub == sub) return o[i];
  }

  auto subs = availableSubraces(mainRace);
  if (!subs.empty() && sub.empty()) throw std::runtime_error(mainRace + " requires a subrace.");
  throw std::runtime_error("Unknown race: " + mainRace + (sub.empty() ? "" : (" (" + sub + ")")));
}

std::vector<std::string> availableRaceDisplayNames() {
  auto& d = defs();
  std::vector<std::string> out;
  for (auto& r : d) out.push_back(displayOf(r));
  std::sort(out.begin(), out.end());
  return out;
}

Race& getRaceByDisplayName(const std::string& displayName) {
  auto& d = defs();
  auto& o = objs();
  std::string disp = trim(displayName);

  for (size_t i = 0; i < d.size(); ++i) {
    if (displayOf(d[i]) == disp) return o[i];
  }
  throw std::runtime_error("Unknown race display name: " + disp);
}

bool raceNeedsFlexibleAsi(const std::string& mainRace, const std::string& subrace) {
  auto& d = defs();
  std::string sub = isNone(subrace) ? "" : subrace;

  for (auto& r : d) {
    if (r.main == mainRace && r.sub == sub) return r.needsFlexibleAsi;
  }
  throw std::runtime_error("Unknown race: " + mainRace);
}