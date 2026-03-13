// class.cpp (OPTION B: NO const, NO override)
// FULL: main classes + ALL subclasses shown in your screenshots
// Provides: availableMainClasses(), availableSubclasses(main), getClass(main, sub)
// Back-compat: availableClasses(), getClassByName(main)

#include "class.h"
#include <stdexcept>
#include <string>
#include <vector>

static bool isNone(const std::string &s) {
  return s.empty() || s == "None" || s == "none";
}

// ===================== BASE MAIN CLASSES (subclass empty) =====================

class Barbarian_Base : public DndClass {
public:
  std::string mainClass() { return "Barbarian"; }
  std::string subclass() { return ""; }
  int hitDie() { return 12; }

  std::vector<Ability> savingThrowProficiencies() { return {Ability::STR, Ability::CON}; }
  std::vector<ArmorProf> armorProficiencies() { return {ArmorProf::Light, ArmorProf::Medium, ArmorProf::Shields}; }
  std::vector<WeaponProf> weaponProficiencies() { return {WeaponProf::Simple, WeaponProf::Martial}; }

  std::vector<std::string> skillOptions() {
    return {"Animal Handling", "Athletics", "Intimidation", "Nature", "Perception", "Survival"};
  }
  int numberOfSkillChoices() { return 2; }

  std::vector<ClassFeature> level1Features() {
    return {
      {"Rage", "Bonus action to rage; advantage on strength checks and saves; melee attacks using strength gain bonus to damage; resistance to bludgeoning, piercing, and slashing damage."},
      {"Unarmored Defense", "AC = 10 + DEX mod + CON mod when unarmored (PHB)."}
    };
  }
  std::vector<ClassFeature> subclassFeatures() { return {}; }
};

class Bard_Base : public DndClass {
public:
  std::string mainClass() { return "Bard"; }
  std::string subclass() { return ""; }
  int hitDie() { return 8; }

  std::vector<Ability> savingThrowProficiencies() { return {Ability::DEX, Ability::CHA}; }
  std::vector<ArmorProf> armorProficiencies() { return {ArmorProf::Light}; }
  std::vector<WeaponProf> weaponProficiencies() { return {WeaponProf::Simple, WeaponProf::HandCrossbow, WeaponProf::Longsword, WeaponProf::Rapier, WeaponProf::Shortsword}; }

  std::vector<std::string> skillOptions() {
    return {"Acrobatics","Animal Handling","Arcana","Athletics","Deception","History",
            "Insight","Intimidation","Investigation","Medicine","Nature","Perception",
            "Performance","Persuasion","Religion","Sleight of Hand","Stealth","Survival"};
  }
  int numberOfSkillChoices() { return 3; }

  std::vector<ClassFeature> level1Features() {
    return {{"Spellcasting", "Cast bard spells using Charisma."},
            {"Bardic Inspiration", "Bonus action: Creature of choice can roll 1d6 and add it to an ability check, attack roll, or saving throw."}};
  }
  std::vector<ClassFeature> subclassFeatures() { return {}; }
};

class Cleric_Base : public DndClass {
public:
  std::string mainClass() { return "Cleric"; }
  std::string subclass() { return ""; }
  int hitDie() { return 8; }

  std::vector<Ability> savingThrowProficiencies() { return {Ability::WIS, Ability::CHA}; }
  std::vector<ArmorProf> armorProficiencies() { return {ArmorProf::Light, ArmorProf::Medium, ArmorProf::Shields}; }
  std::vector<WeaponProf> weaponProficiencies() { return {WeaponProf::Simple}; }

  std::vector<std::string> skillOptions() { return {"History", "Insight", "Medicine", "Persuasion", "Religion"}; }
  int numberOfSkillChoices() { return 2; }

  std::vector<ClassFeature> level1Features() {
    return {{"Spellcasting", "Cast prepared cleric spells using Wisdom."},
            {"Divine Domain", "Choose a domain; gain features/spells."}};
  }
  std::vector<ClassFeature> subclassFeatures() { return {}; }
};

class Druid_Base : public DndClass {
public:
  std::string mainClass() { return "Druid"; }
  std::string subclass() { return ""; }
  int hitDie() { return 8; }

  std::vector<Ability> savingThrowProficiencies() { return {Ability::INT, Ability::WIS}; }
  std::vector<ArmorProf> armorProficiencies() { return {ArmorProf::Light, ArmorProf::Medium, ArmorProf::Shields}; }
  std::vector<WeaponProf> weaponProficiencies() { return {WeaponProf::Simple}; }

  std::vector<std::string> skillOptions() {
    return {"Arcana","Animal Handling","Insight","Medicine","Nature","Perception","Religion","Survival"};
  }
  int numberOfSkillChoices() { return 2; }

  std::vector<ClassFeature> level1Features() {
    return {{"Druidic", "Secret druid language."},
            {"Spellcasting", "Cast prepared druid spells using Wisdom."}};
  }
  std::vector<ClassFeature> subclassFeatures() { return {}; }
};

class Fighter_Base : public DndClass {
public:
  std::string mainClass() { return "Fighter"; }
  std::string subclass() { return ""; }
  int hitDie() { return 10; }

  std::vector<Ability> savingThrowProficiencies() { return {Ability::STR, Ability::CON}; }
  std::vector<ArmorProf> armorProficiencies() {
    return {ArmorProf::Light, ArmorProf::Medium, ArmorProf::Heavy, ArmorProf::Shields};
  }
  std::vector<WeaponProf> weaponProficiencies() { return {WeaponProf::Simple, WeaponProf::Martial}; }

  std::vector<std::string> skillOptions() {
    return {"Acrobatics","Animal Handling","Athletics","History","Insight","Intimidation","Perception","Survival"};
  }
  int numberOfSkillChoices() { return 2; }

  std::vector<ClassFeature> level1Features() {
    return {{"Fighting Style", "Choose a Fighting Style."},
            {"Second Wind", "Bonus action heal 1d10 + fighter level."}};
  }
  std::vector<ClassFeature> subclassFeatures() { return {}; }
};

class Monk_Base : public DndClass {
public:
  std::string mainClass() { return "Monk"; }
  std::string subclass() { return ""; }
  int hitDie() { return 8; }

  std::vector<Ability> savingThrowProficiencies() { return {Ability::STR, Ability::DEX}; }
  std::vector<ArmorProf> armorProficiencies() { return {}; }
  std::vector<WeaponProf> weaponProficiencies() { return {WeaponProf::Simple, WeaponProf::Shortsword}; }

  std::vector<std::string> skillOptions() { return {"Acrobatics","Athletics","History","Insight","Religion","Stealth"}; }
  int numberOfSkillChoices() { return 2; }

  std::vector<ClassFeature> level1Features() {
    return {{"Unarmored Defense", "AC = 10 + DEX mod + WIS mod (PHB)."},
            {"Martial Arts", "Monk unarmed/weapon benefits (PHB)."}};
  }
  std::vector<ClassFeature> subclassFeatures() { return {}; }
};

class Paladin_Base : public DndClass {
public:
  std::string mainClass() { return "Paladin"; }
  std::string subclass() { return ""; }
  int hitDie() { return 10; }

  std::vector<Ability> savingThrowProficiencies() { return {Ability::WIS, Ability::CHA}; }
  std::vector<ArmorProf> armorProficiencies() {
    return {ArmorProf::Light, ArmorProf::Medium, ArmorProf::Heavy, ArmorProf::Shields};
  }
  std::vector<WeaponProf> weaponProficiencies() { return {WeaponProf::Simple, WeaponProf::Martial}; }

  std::vector<std::string> skillOptions() { return {"Athletics","Insight","Intimidation","Medicine","Persuasion","Religion"}; }
  int numberOfSkillChoices() { return 2; }

  std::vector<ClassFeature> level1Features() {
    return {{"Divine Sense", "Detect celestial, fiend, or undead within 60 feet."},
            {"Lay on Hands", "Healing pool (PHB)."}};
  }
  std::vector<ClassFeature> subclassFeatures() { return {}; }
};

class Ranger_Base : public DndClass {
public:
  std::string mainClass() { return "Ranger"; }
  std::string subclass() { return ""; }
  int hitDie() { return 10; }

  std::vector<Ability> savingThrowProficiencies() { return {Ability::STR, Ability::DEX}; }
  std::vector<ArmorProf> armorProficiencies() { return {ArmorProf::Light, ArmorProf::Medium, ArmorProf::Shields}; }
  std::vector<WeaponProf> weaponProficiencies() { return {WeaponProf::Simple, WeaponProf::Martial}; }

  std::vector<std::string> skillOptions() {
    return {"Animal Handling","Athletics","Insight","Investigation","Nature","Perception","Stealth","Survival"};
  }
  int numberOfSkillChoices() { return 3; }

  std::vector<ClassFeature> level1Features() {
    return {{"Favored Enemy", "Choose favored enemy: aberrations, beasts, celestials, constructs, dragons, elementals, fey, fiends, giants, monstrosities, oozes, plants, undead. Advantage on survival checks to track them and intelligence checks to recall information about them."},
            {"Natural Explorer", "Choose favored terrain: arctic, coast, desert, forest, grassland, mountain, swamp, Underdark."}};
  }
  std::vector<ClassFeature> subclassFeatures() { return {}; }
};

class Rogue_Base : public DndClass {
public:
  std::string mainClass() { return "Rogue"; }
  std::string subclass() { return ""; }
  int hitDie() { return 8; }

  std::vector<Ability> savingThrowProficiencies() { return {Ability::DEX, Ability::INT}; }
  std::vector<ArmorProf> armorProficiencies() { return {ArmorProf::Light}; }
  std::vector<WeaponProf> weaponProficiencies() { return {WeaponProf::Simple, WeaponProf::HandCrossbow, WeaponProf::Longsword, WeaponProf::Rapier, WeaponProf::Shortsword}; }

  std::vector<std::string> skillOptions() {
    return {"Acrobatics","Athletics","Deception","Insight","Intimidation","Investigation",
            "Perception","Performance","Persuasion","Sleight of Hand","Stealth"};
  }
  int numberOfSkillChoices() { return 4; }

  std::vector<ClassFeature> level1Features() {
    return {{"Expertise", "Choose two proficiencies; double proficiency (PHB)."},
            {"Sneak Attack", "Extra damage once/turn under conditions (PHB)."},
            {"Thieves' Cant", "Secret rogue language (PHB)."}};
  }
  std::vector<ClassFeature> subclassFeatures() { return {}; }
};

class Sorcerer_Base : public DndClass {
public:
  std::string mainClass() { return "Sorcerer"; }
  std::string subclass() { return ""; }
  int hitDie() { return 6; }

  std::vector<Ability> savingThrowProficiencies() { return {Ability::CON, Ability::CHA}; }
  std::vector<ArmorProf> armorProficiencies() { return {}; }
  std::vector<WeaponProf> weaponProficiencies() { return {WeaponProf::Simple}; }

  std::vector<std::string> skillOptions() { return {"Arcana","Deception","Insight","Intimidation","Persuasion","Religion"}; }
  int numberOfSkillChoices() { return 2; }

  std::vector<ClassFeature> level1Features() {
    return {{"Spellcasting", "Cast sorcerer spells using Charisma."},
            {"Sorcerous Origin", "Choose an origin; it grants features."}};
  }
  std::vector<ClassFeature> subclassFeatures() { return {}; }
};

class Warlock_Base : public DndClass {
public:
  std::string mainClass() { return "Warlock"; }
  std::string subclass() { return ""; }
  int hitDie() { return 8; }

  std::vector<Ability> savingThrowProficiencies() { return {Ability::WIS, Ability::CHA}; }
  std::vector<ArmorProf> armorProficiencies() { return {ArmorProf::Light}; }
  std::vector<WeaponProf> weaponProficiencies() { return {WeaponProf::Simple}; }

  std::vector<std::string> skillOptions() {
    return {"Arcana","Deception","History","Intimidation","Investigation","Nature","Religion"};
  }
  int numberOfSkillChoices() { return 2; }

  std::vector<ClassFeature> level1Features() {
    return {{"Otherworldly Patron", "Choose a patron; it grants features."},
            {"Pact Magic", "Cast warlock spells using Charisma (special rules)."}};
  }
  std::vector<ClassFeature> subclassFeatures() { return {}; }
};

class Wizard_Base : public DndClass {
public:
  std::string mainClass() { return "Wizard"; }
  std::string subclass() { return ""; }
  int hitDie() { return 6; }

  std::vector<Ability> savingThrowProficiencies() { return {Ability::INT, Ability::WIS}; }
  std::vector<ArmorProf> armorProficiencies() { return {}; }
  std::vector<WeaponProf> weaponProficiencies() { return {WeaponProf::Simple}; }

  std::vector<std::string> skillOptions() { return {"Arcana","History","Insight","Investigation","Medicine","Religion"}; }
  int numberOfSkillChoices() { return 2; }

  std::vector<ClassFeature> level1Features() {
    return {{"Spellcasting", "Cast prepared wizard spells using Intelligence."},
            {"Arcane Recovery", "Recover spell slots after a short rest (PHB)."}};
  }
  std::vector<ClassFeature> subclassFeatures() { return {}; }
};

class Artificer_Base : public DndClass {
public:
  std::string mainClass() { return "Artificer"; }
  std::string subclass() { return ""; }
  int hitDie() { return 8; }

  std::vector<Ability> savingThrowProficiencies() { return {Ability::CON, Ability::INT}; }
  std::vector<ArmorProf> armorProficiencies() { return {ArmorProf::Light, ArmorProf::Medium, ArmorProf::Shields}; }
  std::vector<WeaponProf> weaponProficiencies() { return {WeaponProf::Simple}; }

  std::vector<std::string> skillOptions() { return {"Arcana","History","Investigation","Medicine","Nature","Perception","Sleight of Hand"}; }
  int numberOfSkillChoices() { return 2; }

  std::vector<ClassFeature> level1Features() {
    return {{"Magical Tinkering", "Minor magical effects (Artificer)."},
            {"Spellcasting", "Cast artificer spells using Intelligence."}};
  }
  std::vector<ClassFeature> subclassFeatures() { return {}; }
};

// ===================== SUBCLASS GENERATORS =====================

#define MAKE_SUBCLASS_EX(DerivedName, BaseName, SubName, StartLevel, ...) \
class DerivedName : public BaseName { \
public: \
  std::string subclass(){ return SubName; } \
  int subclassStartLevel(){ return StartLevel; } \
  std::vector<ClassFeature> subclassFeatures(){ return { __VA_ARGS__ }; } \
};

// Convenience wrappers: most subclasses start at 3 in 2014 5e
#define MAKE_SUBCLASS1(DerivedName, BaseName, SubName, ...) \
  MAKE_SUBCLASS_EX(DerivedName, BaseName, SubName, 1, __VA_ARGS__)

#define MAKE_SUBCLASS2(DerivedName, BaseName, SubName, ...) \
  MAKE_SUBCLASS_EX(DerivedName, BaseName, SubName, 2, __VA_ARGS__)

#define MAKE_SUBCLASS3(DerivedName, BaseName, SubName, ...) \
  MAKE_SUBCLASS_EX(DerivedName, BaseName, SubName, 3, __VA_ARGS__)

MAKE_SUBCLASS2(Druid_Land, Druid_Base, "Circle of the Land",
  ClassFeature{"Bonus Cantrip", "Gain an extra druid cantrip."},
  ClassFeature{"Natural Recovery", "Recover spell slots on short rest (spell slots can have a combined level equal to or less than half the druid's level). Can't be used again until long rest."}
)

MAKE_SUBCLASS2(Druid_Moon, Druid_Base, "Circle of the Moon",
  ClassFeature{"Combat Wild Shape", "Wild Shape as bonus action; heal 1d8 hp per level of spell slot while shifted."},
  ClassFeature{"Circle Forms", "Access stronger beast forms earlier."}
)

// Outside PHB circles (still start at 2)
MAKE_SUBCLASS2(Druid_Dreams, Druid_Base, "Circle of Dreams",
  ClassFeature{"Balm of the Summer Court", "Healing pool with bonus temp HP (number of d6s equal to your druid level)/mobility vibe. And a reaction to heal an ally within 120 ft with it. Recovery on a long rest."},
)

MAKE_SUBCLASS2(Druid_Shepherd, Druid_Base, "Circle of the Shepherd",
  ClassFeature{"Speech of the Woods", "Learn Sylvan. Communicate with beasts."},
  ClassFeature{"Spirit Totem", "Bonus action to summon a spirit totem within 60 ft of you with an aura in a 30 ft radius that grants benefits (bear/eagle/wolf options). Spirit remains for 1 minute or until you dismiss it as a bonus action. Once you use this feature, you can't use it again until you finish a short or long rest. Effect of spirit depends on the chosen option."}
)

MAKE_SUBCLASS2(Druid_Spores, Druid_Base, "Circle of Spores",
  ClassFeature{"Halo of Spores", "When a creature you can see moves into a 10 ft radius around you or starts its turn there, you can use your reaction to deal necrotic damage (1d4 + Int mod, scaling with level) unless it succeeds on a Constitution save."},
  ClassFeature{"Symbiotic Entity", "Expend a use of Wild Shape to gain 4 temp hp per druid level. While active, when you deal Halo of Spores damage, roll damage die a second time and add it to the total and melee attacks deal extra 1d6 necrotic damage."}
)

MAKE_SUBCLASS2(Druid_Stars, Druid_Base, "Circle of Stars",
  ClassFeature{"Star Map", "While holding a Star Map (spellcasting focus), you know Guidance cantirp, Guiding Bolt prepared, can cast Guiding Bolt without expending spell slot (number of times equal to proficiency bonus and all uses regained on long rest)."},
  ClassFeature{"Starry Form", "As bonus action, expend a use of Wild Shape to take on a starry form for 10 minutes. Benefits depend on form choice: Archer, Chalice, or Dragon."}
)

MAKE_SUBCLASS2(Druid_Wildfire, Druid_Base, "Circle of Wildfire",
  ClassFeature{"Summon Wildfire Spirit", "Summon spirit companion. Any creature within 10 ft of the spirit when it appears must succeed on a Dexterity save or take 2d6 fire damage."}
)

MAKE_SUBCLASS1(Cleric_Knowledge, Cleric_Base, "Knowledge Domain",
  ClassFeature{"Blessings of Knowledge", "Gain languages and knowledge-skill expertise-style boost."}
)

MAKE_SUBCLASS1(Cleric_Life, Cleric_Base, "Life Domain",
  ClassFeature{"Bonus Proficiency", "Heavy armor training."},
  ClassFeature{"Disciple of Life", "Healing spells restore extra HP."}
)

MAKE_SUBCLASS1(Cleric_Light, Cleric_Base, "Light Domain",
  ClassFeature{"Bonus Cantrip", "Gain a light-themed cantrip."},
  ClassFeature{"Warding Flare", "Reaction: impose disadvantage on a visible attacker."}
)

MAKE_SUBCLASS1(Cleric_Nature, Cleric_Base, "Nature Domain",
  ClassFeature{"Acolyte of Nature", "Gain a druid cantrip and a nature-flavored skill."},
  ClassFeature{"Bonus Proficiency", "Heavy armor training."}
)

MAKE_SUBCLASS1(Cleric_Tempest, Cleric_Base, "Tempest Domain",
  ClassFeature{"Bonus Proficiencies", "Martial weapons and heavy armor training."},
  ClassFeature{"Wrath of the Storm", "Reaction: punish a creature that hits you with lightning/thunder."}
)

MAKE_SUBCLASS1(Cleric_Trickery, Cleric_Base, "Trickery Domain",
  ClassFeature{"Blessing of the Trickster", "Give an ally a stealth advantage buff."}
)

MAKE_SUBCLASS1(Cleric_War, Cleric_Base, "War Domain",
  ClassFeature{"Bonus Proficiencies", "Martial weapons and heavy armor training."},
  ClassFeature{"War Priest", "Limited bonus-action weapon attacks."}
)

// Outside PHB domains (still start at 1)
MAKE_SUBCLASS1(Cleric_Arcana, Cleric_Base, "Arcana Domain",
  ClassFeature{"Arcane Initiate", "Gain wizard cantrips and arcane-themed benefits."}
)

MAKE_SUBCLASS1(Cleric_Death, Cleric_Base, "Death Domain",
  ClassFeature{"Bonus Proficiency", "Martial weapons training."},
  ClassFeature{"Reaper", "Upgrade necromancy cantrip usage against multiple targets."}
)

MAKE_SUBCLASS1(Cleric_Forge, Cleric_Base, "Forge Domain",
  ClassFeature{"Bonus Proficiencies", "Heavy armor and smith’s tools training."},
  ClassFeature{"Blessing of the Forge", "Imbue a weapon/armor with a temporary bonus."}
)

MAKE_SUBCLASS1(Cleric_Grave, Cleric_Base, "Grave Domain",
  ClassFeature{"Circle of Mortality", "Improve healing on downed allies; stabilize at range."},
  ClassFeature{"Eyes of the Grave", "Sense undead presence nearby."}
)

MAKE_SUBCLASS1(Cleric_Order, Cleric_Base, "Order Domain",
  ClassFeature{"Bonus Proficiencies", "Social/command-focused proficiency package."},
  ClassFeature{"Voice of Authority", "Buffing an ally can enable an extra attack reaction."}
)

MAKE_SUBCLASS1(Cleric_Peace, Cleric_Base, "Peace Domain",
  ClassFeature{"Implement of Peace", "Gain a skill/tool proficiency for peacemaking."},
  ClassFeature{"Emboldening Bond", "Link allies for bonus/defense-style benefits."}
)

MAKE_SUBCLASS1(Cleric_Twilight, Cleric_Base, "Twilight Domain",
  ClassFeature{"Bonus Proficiencies", "Martial weapons and heavy armor training."},
  ClassFeature{"Eyes of Night", "Share enhanced darkvision; twilight-themed support."},
  ClassFeature{"Vigilant Blessing", "Give an initiative advantage-style buff."}
)

MAKE_SUBCLASS1(Warlock_Archfey, Warlock_Base, "Archfey",
  ClassFeature{"Fey Presence", "Charm/frighten creatures in a short-range burst."}
)

MAKE_SUBCLASS1(Warlock_Fiend, Warlock_Base, "Fiend",
  ClassFeature{"Dark One’s Blessing", "Gain temporary HP when you drop a foe to 0 HP."}
)

MAKE_SUBCLASS1(Warlock_GreatOldOne, Warlock_Base, "Great Old One",
  ClassFeature{"Awakened Mind", "Telepathy with a creature you can see within range."}
)

// Outside PHB patrons (start at 1)
MAKE_SUBCLASS1(Warlock_Celestial, Warlock_Base, "Celestial",
  ClassFeature{"Bonus Cantrips", "Gain cleric-style light/healing cantrips."},
  ClassFeature{"Healing Light", "Pool of healing dice to restore HP at range."}
)

MAKE_SUBCLASS1(Warlock_Hexblade, Warlock_Base, "Hexblade",
  ClassFeature{"Hexblade’s Curse", "Curse a target for damage/crit/HP benefits."},
  ClassFeature{"Hex Warrior", "Weapon/armor benefits; charisma-weapon style option."}
)

MAKE_SUBCLASS1(Warlock_Genie, Warlock_Base, "The Genie",
  ClassFeature{"Genie’s Vessel", "Magical vessel; resting/storage/utility hook."},
  ClassFeature{"Genie’s Wrath", "Extra damage once per turn tied to patron element."}
)

MAKE_SUBCLASS1(Warlock_Fathomless, Warlock_Base, "Fathomless",
  ClassFeature{"Tentacle of the Deeps", "Summon a spectral tentacle for control/damage."}
)

MAKE_SUBCLASS1(Warlock_Undead, Warlock_Base, "Undead",
  ClassFeature{"Form of Dread", "Transform for fear/temporary HP style benefits."}
)

MAKE_SUBCLASS1(Warlock_Undying, Warlock_Base, "Undying",
  ClassFeature{"Among the Dead", "Undead-themed resistance/turning interactions."}
)
MAKE_SUBCLASS1(Sorc_DraconicBloodline, Sorcerer_Base, "Draconic Bloodline",
  ClassFeature{"Dragon Ancestor", "Choose draconic lineage; affects later features."},
  ClassFeature{"Draconic Resilience", "Extra durability and natural-armor-style defense."}
)

MAKE_SUBCLASS1(Sorc_WildMagic, Sorcerer_Base, "Wild Magic",
  ClassFeature{"Wild Magic Surge", "Random surge can trigger after casting."},
  ClassFeature{"Tides of Chaos", "Gain advantage; recharges via surge trigger."}
)

// Outside PHB origins (start at 1)
MAKE_SUBCLASS1(Sorc_DivineSoul, Sorcerer_Base, "Divine Soul",
  ClassFeature{"Divine Magic", "Access a divine-flavored spell option package."},
  ClassFeature{"Favored by the Gods", "Boost a failed save/attack with a bonus roll."}
)

MAKE_SUBCLASS1(Sorc_ShadowMagic, Sorcerer_Base, "Shadow Magic",
  ClassFeature{"Eyes of the Dark", "Improved darkvision; darkness interaction."},
  ClassFeature{"Strength of the Grave", "Chance to avoid dropping to 0 HP."}
)

MAKE_SUBCLASS1(Sorc_StormSorcery, Sorcerer_Base, "Storm Sorcery",
  ClassFeature{"Wind Speaker", "Primordial language."},
  ClassFeature{"Tempestuous Magic", "Free movement after casting (storm mobility)."}
)

MAKE_SUBCLASS1(Sorc_AberrantMind, Sorcerer_Base, "Aberrant Mind",
  ClassFeature{"Telepathic Speech", "Limited-duration telepathy with allies."}
)

MAKE_SUBCLASS1(Sorc_ClockworkSoul, Sorcerer_Base, "Clockwork Soul",
  ClassFeature{"Clockwork Magic", "Expanded spell package theme."},
  ClassFeature{"Restore Balance", "Cancel advantage/disadvantage as a reaction-style effect."}
)

MAKE_SUBCLASS1(Sorc_LunarSorcery, Sorcerer_Base, "Lunar Sorcery",
  ClassFeature{"Lunar Embodiment", "Phase-based spell package/theme benefits."}
)
// Wizard traditions start at 2
MAKE_SUBCLASS2(Wiz_Abjuration, Wizard_Base, "School of Abjuration",
  ClassFeature{"Abjuration Savant", "Cheaper/faster copying abjuration spells."},
  ClassFeature{"Arcane Ward", "Protective ward that absorbs damage."}
)

MAKE_SUBCLASS2(Wiz_Conjuration, Wizard_Base, "School of Conjuration",
  ClassFeature{"Conjuration Savant", "Cheaper copying conjuration spells."},
  ClassFeature{"Minor Conjuration", "Create a small temporary object."}
)

MAKE_SUBCLASS2(Wiz_Divination, Wizard_Base, "School of Divination",
  ClassFeature{"Divination Savant", "Cheaper copying divination spells."},
  ClassFeature{"Portent", "Replace rolls using pre-rolled d20s."}
)

MAKE_SUBCLASS2(Wiz_Enchantment, Wizard_Base, "School of Enchantment",
  ClassFeature{"Enchantment Savant", "Cheaper copying enchantment spells."},
  ClassFeature{"Hypnotic Gaze", "Charm/disable a creature briefly with a stare."}
)

MAKE_SUBCLASS2(Wiz_Evocation, Wizard_Base, "School of Evocation",
  ClassFeature{"Evocation Savant", "Cheaper copying evocation spells."},
  ClassFeature{"Sculpt Spells", "Protect allies from your area spells."}
)

MAKE_SUBCLASS2(Wiz_Illusion, Wizard_Base, "School of Illusion",
  ClassFeature{"Illusion Savant", "Cheaper copying illusion spells."},
  ClassFeature{"Improved Minor Illusion", "Boost the minor illusion cantrip."}
)

MAKE_SUBCLASS2(Wiz_Necromancy, Wizard_Base, "School of Necromancy",
  ClassFeature{"Necromancy Savant", "Cheaper copying necromancy spells."},
  ClassFeature{"Grim Harvest", "Heal when you kill with a spell (limited)."}
)

MAKE_SUBCLASS2(Wiz_Transmutation, Wizard_Base, "School of Transmutation",
  ClassFeature{"Transmutation Savant", "Cheaper copying transmutation spells."},
  ClassFeature{"Minor Alchemy", "Temporarily transform materials."}
)

// Outside PHB wizard options (still start at 2)
MAKE_SUBCLASS2(Wiz_Bladesinging, Wizard_Base, "School of Bladesinging",
  ClassFeature{"Training in War and Song", "Light armor + weapon training package."},
  ClassFeature{"Bladesong", "Combat mode: defense/speed/concentration boost."}
)

MAKE_SUBCLASS2(Wiz_WarMagic, Wizard_Base, "School of War Magic",
  ClassFeature{"Arcane Deflection", "Reaction boost to AC/saves after being attacked."},
  ClassFeature{"Tactical Wit", "Initiative bonus."}
)

MAKE_SUBCLASS2(Wiz_Scribes, Wizard_Base, "Order of Scribes",
  ClassFeature{"Wizardly Quill", "Fast spell copying + magical quill."},
  ClassFeature{"Awakened Spellbook", "Spellbook gains flexible damage-type features."}
)

MAKE_SUBCLASS2(Wiz_Chronurgy, Wizard_Base, "School of Chronurgy",
  ClassFeature{"Chronal Shift", "Force a reroll in a short window."},
  ClassFeature{"Temporal Awareness", "Initiative bonus."}
)

MAKE_SUBCLASS2(Wiz_Graviturgy, Wizard_Base, "School of Graviturgy",
  ClassFeature{"Adjust Density", "Buff/debuff weight for movement/utility."}
)

// ===================== LEVEL 3 START SUBCLASSES (2014) =====================

// ---------------- Barbarian (Primal Path) ----------------
MAKE_SUBCLASS3(Barbarian_AncestralGuardian, Barbarian_Base, "Path of the Ancestral Guardian",
  ClassFeature{"Ancestral Protectors", "First hit while raging hinders the target and protects allies."}
)

MAKE_SUBCLASS3(Barbarian_Battlerager, Barbarian_Base, "Path of the Battlerager",
  ClassFeature{"Battlerager Armor", "Spiked-armor style combat bonuses and mobility while raging."}
)

MAKE_SUBCLASS3(Barbarian_Beast, Barbarian_Base, "Path of the Beast",
  ClassFeature{"Form of the Beast", "While raging, manifest natural weapons with different options."}
)

MAKE_SUBCLASS3(Barbarian_Berserker, Barbarian_Base, "Path of the Berserker",
  ClassFeature{"Frenzy", "Rage option that boosts offense with a drawback after it ends."}
)

MAKE_SUBCLASS3(Barbarian_Giant, Barbarian_Base, "Path of the Giant",
  ClassFeature{"Giant's Power", "Grow/empower your rage with giant-themed strength and throws."}
)

MAKE_SUBCLASS3(Barbarian_StormHerald, Barbarian_Base, "Path of the Storm Herald",
  ClassFeature{"Storm Aura", "Choose an environment aura that triggers effects while raging."}
)

MAKE_SUBCLASS3(Barbarian_Totem, Barbarian_Base, "Path of the Totem Warrior",
  ClassFeature{"Spirit Seeker", "Ritual utility spells tied to nature spirits."},
  ClassFeature{"Totem Spirit", "Choose a spirit (bear/eagle/wolf etc.) to shape your rage benefits."}
)

MAKE_SUBCLASS3(Barbarian_WildMagic, Barbarian_Base, "Path of Wild Magic",
  ClassFeature{"Magic Awareness", "Sense magic around you for a short time."},
  ClassFeature{"Wild Surge", "While raging, a random magical effect can occur."}
)

MAKE_SUBCLASS3(Barbarian_Zealot, Barbarian_Base, "Path of the Zealot",
  ClassFeature{"Divine Fury", "Extra radiant/necrotic damage on the first hit each turn while raging."},
  ClassFeature{"Warrior of the Gods", "Easier revival-style interaction when brought back to life."}
)

// ---------------- Bard (Bard College) ----------------
MAKE_SUBCLASS3(Bard_Creation, Bard_Base, "College of Creation",
  ClassFeature{"Mote of Potential", "Bardic Inspiration gains an extra effect depending on use."},
  ClassFeature{"Performance of Creation", "Create a nonmagical item for a time."}
)

MAKE_SUBCLASS3(Bard_Eloquence, Bard_Base, "College of Eloquence",
  ClassFeature{"Silver Tongue", "More reliable Persuasion/Deception-style outcomes."},
  ClassFeature{"Unsettling Words", "Spend Inspiration to weaken a creature’s next save."}
)

MAKE_SUBCLASS3(Bard_Glamour, Bard_Base, "College of Glamour",
  ClassFeature{"Mantle of Inspiration", "Spend Inspiration to grant temp HP + movement to allies."},
  ClassFeature{"Enthralling Performance", "Perform to charm a small group afterward."}
)

MAKE_SUBCLASS3(Bard_Lore, Bard_Base, "College of Lore",
  ClassFeature{"Bonus Proficiencies", "Gain additional skill proficiencies."},
  ClassFeature{"Cutting Words", "Use Inspiration to reduce an enemy’s roll as a reaction."}
)

MAKE_SUBCLASS3(Bard_Spirits, Bard_Base, "College of Spirits",
  ClassFeature{"Guiding Whispers", "Learn a spirit-flavored guidance/communication spell."},
  ClassFeature{"Tales from Beyond", "Use your focus to tell magical tales with random effects."}
)

MAKE_SUBCLASS3(Bard_Swords, Bard_Base, "College of Swords",
  ClassFeature{"Bonus Proficiencies", "Gain armor/weapon-style proficiencies for blade work."},
  ClassFeature{"Fighting Style", "Choose a combat style option."},
  ClassFeature{"Blade Flourish", "Use Bardic Inspiration to add special effects to weapon attacks."}
)

MAKE_SUBCLASS3(Bard_Valor, Bard_Base, "College of Valor",
  ClassFeature{"Bonus Proficiencies", "Gain armor/weapon proficiencies for battle support."},
  ClassFeature{"Combat Inspiration", "Bardic Inspiration can boost damage or defense."}
)

MAKE_SUBCLASS3(Bard_Whispers, Bard_Base, "College of Whispers",
  ClassFeature{"Psychic Blades", "Spend Inspiration to deal extra psychic damage on a hit."},
  ClassFeature{"Words of Terror", "Talk to frighten a creature after a conversation."}
)

// ---------------- Fighter (Martial Archetype) ----------------
MAKE_SUBCLASS3(Fighter_ArcaneArcher, Fighter_Base, "Arcane Archer",
  ClassFeature{"Arcane Archer Lore", "Gain arcane/skill knowledge tied to the archetype."},
  ClassFeature{"Arcane Shot", "Special shots with limited uses that add effects to attacks."}
)

MAKE_SUBCLASS3(Fighter_Banneret, Fighter_Base, "Banneret",
  ClassFeature{"Rallying Cry", "Second Wind also helps nearby allies recover a bit."},
  ClassFeature{"Royal Envoy", "Social skill boost (proficiency/expertise-style) and language."}
)

MAKE_SUBCLASS3(Fighter_BattleMaster, Fighter_Base, "Battle Master",
  ClassFeature{"Combat Superiority", "Maneuvers powered by superiority dice."},
  ClassFeature{"Student of War", "Gain a tool proficiency for battlefield know-how."}
)

MAKE_SUBCLASS3(Fighter_Cavalier, Fighter_Base, "Cavalier",
  ClassFeature{"Bonus Proficiency", "Gain an extra skill (often animal/ride themed)."},
  ClassFeature{"Born to the Saddle", "Mounted benefits and improved staying-in-the-saddle."},
  ClassFeature{"Unwavering Mark", "Mark a foe you hit and punish them for ignoring you."}
)

MAKE_SUBCLASS3(Fighter_Champion, Fighter_Base, "Champion",
  ClassFeature{"Improved Critical", "Your weapon attacks crit on a wider range."}
)

MAKE_SUBCLASS3(Fighter_EchoKnight, Fighter_Base, "Echo Knight",
  ClassFeature{"Manifest Echo", "Create an echo you can swap with and attack from."},
  ClassFeature{"Unleash Incarnation", "Extra attack bursts through the echo a limited number of times."}
)

MAKE_SUBCLASS3(Fighter_EldritchKnight, Fighter_Base, "Eldritch Knight",
  ClassFeature{"Spellcasting", "Gain wizard-style spellcasting progression (limited schools)."},
  ClassFeature{"Weapon Bond", "Bond weapons to summon/prevent disarm interactions."}
)

MAKE_SUBCLASS3(Fighter_PsiWarrior, Fighter_Base, "Psi Warrior",
  ClassFeature{"Psionic Power", "Psionic dice fuel defensive/offensive techniques."},
  ClassFeature{"Telekinetic Adept", "Minor telekinesis-style utility option."}
)

MAKE_SUBCLASS3(Fighter_RuneKnight, Fighter_Base, "Rune Knight",
  ClassFeature{"Bonus Proficiencies", "Gain tool proficiencies tied to runes/giants."},
  ClassFeature{"Rune Carver", "Inscribe runes that grant passive/activated effects."},
  ClassFeature{"Giant’s Might", "Grow and gain combat buffs a limited number of times."}
)

MAKE_SUBCLASS3(Fighter_Samurai, Fighter_Base, "Samurai",
  ClassFeature{"Bonus Proficiency", "Gain an extra skill proficiency."},
  ClassFeature{"Fighting Spirit", "Burst of temp HP + advantage-style offense a limited number of times."}
)

// ---------------- Monk (Monastic Tradition) ----------------
MAKE_SUBCLASS3(Monk_Mercy, Monk_Base, "Way of Mercy",
  ClassFeature{"Implements of Mercy", "Proficiency options for medicine/poisoner style tools."},
  ClassFeature{"Hand of Healing", "Spend ki to heal with a touch."},
  ClassFeature{"Hand of Harm", "Spend ki to add necrotic harm to a strike."}
)

MAKE_SUBCLASS3(Monk_AscendantDragon, Monk_Base, "Way of the Ascendant Dragon",
  ClassFeature{"Draconic Disciple", "Draconic language + elemental flavor to unarmed strikes."},
  ClassFeature{"Breath of the Dragon", "Replace attacks with a breath weapon using ki."}
)

MAKE_SUBCLASS3(Monk_AstralSelf, Monk_Base, "Way of the Astral Self",
  ClassFeature{"Arms of the Astral Self", "Summon spectral arms for reach and altered damage/utility."}
)

MAKE_SUBCLASS3(Monk_DrunkenMaster, Monk_Base, "Way of the Drunken Master",
  ClassFeature{"Bonus Proficiencies", "Gain performance/brewer’s supplies style proficiencies."},
  ClassFeature{"Drunken Technique", "After Flurry of Blows, gain mobility and disengage-style benefit."}
)

MAKE_SUBCLASS3(Monk_FourElements, Monk_Base, "Way of the Four Elements",
  ClassFeature{"Disciple of the Elements", "Spend ki to cast elemental disciplines (spell-like effects)."}
)

MAKE_SUBCLASS3(Monk_Kensei, Monk_Base, "Way of the Kensei",
  ClassFeature{"Kensei Weapons", "Choose special weapons as monk weapons."},
  ClassFeature{"Agile Parry", "Defensive benefit when fighting a certain way."},
  ClassFeature{"Kensei’s Shot", "Ranged bonus option for kensei weapons."},
  ClassFeature{"Way of the Brush", "Calligrapher/painter utility flavor feature."}
)

MAKE_SUBCLASS3(Monk_LongDeath, Monk_Base, "Way of the Long Death",
  ClassFeature{"Touch of Death", "Gain temp HP when you drop a creature to 0 HP nearby."}
)

MAKE_SUBCLASS3(Monk_OpenHand, Monk_Base, "Way of the Open Hand",
  ClassFeature{"Open Hand Technique", "Flurry of Blows can impose control effects (push/knock prone/disable reactions)."}
)

MAKE_SUBCLASS3(Monk_Shadow, Monk_Base, "Way of Shadow",
  ClassFeature{"Shadow Arts", "Spend ki to cast stealthy shadow spells and gain minor utility."}
)

MAKE_SUBCLASS3(Monk_SunSoul, Monk_Base, "Way of the Sun Soul",
  ClassFeature{"Radiant Sun Bolt", "Ranged radiant attacks using martial arts scaling."}
)

// ---------------- Paladin (Sacred Oath) ----------------
MAKE_SUBCLASS3(Paladin_Ancients, Paladin_Base, "Oath of the Ancients",
  ClassFeature{"Sacred Oath", "You swear an oath and gain oath spells and Channel Divinity."},
  ClassFeature{"Channel Divinity: Nature’s Wrath", "Restraining vines-style control option."},
  ClassFeature{"Channel Divinity: Turn the Faithless", "Turn fey/fiends in an area."}
)

MAKE_SUBCLASS3(Paladin_Conquest, Paladin_Base, "Oath of Conquest",
  ClassFeature{"Sacred Oath", "You swear an oath and gain oath spells and Channel Divinity."},
  ClassFeature{"Channel Divinity: Conquering Presence", "Frighten creatures in an area."},
  ClassFeature{"Channel Divinity: Guided Strike", "Add a big bonus to an attack roll."}
)

MAKE_SUBCLASS3(Paladin_Crown, Paladin_Base, "Oath of the Crown",
  ClassFeature{"Sacred Oath", "You swear an oath and gain oath spells and Channel Divinity."},
  ClassFeature{"Channel Divinity: Champion Challenge", "Force nearby foes to stay close (limited movement away)."},
  ClassFeature{"Channel Divinity: Turn the Tide", "Small group heal burst for allies."}
)

MAKE_SUBCLASS3(Paladin_Devotion, Paladin_Base, "Oath of Devotion",
  ClassFeature{"Sacred Oath", "You swear an oath and gain oath spells and Channel Divinity."},
  ClassFeature{"Channel Divinity: Sacred Weapon", "Imbue your weapon for accuracy/shine."},
  ClassFeature{"Channel Divinity: Turn the Unholy", "Turn fiends and undead."}
)

MAKE_SUBCLASS3(Paladin_Glory, Paladin_Base, "Oath of Glory",
  ClassFeature{"Sacred Oath", "You swear an oath and gain oath spells and Channel Divinity."},
  ClassFeature{"Channel Divinity: Peerless Athlete", "Boost athletic movement/jumps/strength feats briefly."},
  ClassFeature{"Channel Divinity: Inspiring Smite", "After smiting, grant temp HP to allies nearby."}
)

MAKE_SUBCLASS3(Paladin_Redemption, Paladin_Base, "Oath of Redemption",
  ClassFeature{"Sacred Oath", "You swear an oath and gain oath spells and Channel Divinity."},
  ClassFeature{"Channel Divinity: Emissary of Peace", "Large persuasion/social boost briefly."},
  ClassFeature{"Channel Divinity: Rebuke the Violent", "Reaction punish a creature for harming another."}
)

MAKE_SUBCLASS3(Paladin_Vengeance, Paladin_Base, "Oath of Vengeance",
  ClassFeature{"Sacred Oath", "You swear an oath and gain oath spells and Channel Divinity."},
  ClassFeature{"Channel Divinity: Abjure Enemy", "Frighten/lock down a chosen foe."},
  ClassFeature{"Channel Divinity: Vow of Enmity", "Gain strong advantage-style focus vs one creature."}
)

MAKE_SUBCLASS3(Paladin_Watchers, Paladin_Base, "Oath of the Watchers",
  ClassFeature{"Sacred Oath", "You swear an oath and gain oath spells and Channel Divinity."},
  ClassFeature{"Channel Divinity: Watcher’s Will", "Protect allies from mental control effects briefly."},
  ClassFeature{"Channel Divinity: Abjure the Extraplanar", "Turn/contain extraplanar creatures."}
)

MAKE_SUBCLASS3(Paladin_Oathbreaker, Paladin_Base, "Oathbreaker",
  ClassFeature{"Dark Oath", "You take the Oathbreaker path and gain Channel Divinity options."},
  ClassFeature{"Channel Divinity: Control Undead", "Seize control of an undead creature."},
  ClassFeature{"Channel Divinity: Dreadful Aspect", "Frighten creatures around you."}
)

// ---------------- Ranger (Archetype/Conclave) ----------------
MAKE_SUBCLASS3(Ranger_BeastMasterConclave, Ranger_Base, "Beast Master Conclave",
  ClassFeature{"Ranger’s Companion", "Gain an animal companion that fights alongside you."}
)

MAKE_SUBCLASS3(Ranger_Drakewarden, Ranger_Base, "Drakewarden",
  ClassFeature{"Draconic Gift", "Drake-themed minor benefits and language."},
  ClassFeature{"Drake Companion", "Summon/bond a drake ally to fight with you."}
)

MAKE_SUBCLASS3(Ranger_FeyWanderer, Ranger_Base, "Fey Wanderer",
  ClassFeature{"Dreadful Strikes", "Add extra psychic-style damage once per turn."},
  ClassFeature{"Fey Wanderer Magic", "Expanded spell options tied to the subclass."},
  ClassFeature{"Otherworldly Glamour", "Social boost using Wisdom/Charisma-style bend."}
)

MAKE_SUBCLASS3(Ranger_GloomStalker, Ranger_Base, "Gloom Stalker Conclave",
  ClassFeature{"Gloom Stalker Magic", "Expanded spell options tied to the subclass."},
  ClassFeature{"Dread Ambusher", "Initiative boost + first-turn burst package."},
  ClassFeature{"Umbral Sight", "Enhanced darkvision and stealth in darkness."}
)

MAKE_SUBCLASS3(Ranger_HorizonWalker, Ranger_Base, "Horizon Walker Conclave",
  ClassFeature{"Horizon Walker Magic", "Expanded spell options tied to the subclass."},
  ClassFeature{"Detect Portal", "Sense planar portals nearby."},
  ClassFeature{"Planar Warrior", "Convert extra damage to force and mark targets with planar energy."}
)

MAKE_SUBCLASS3(Ranger_HunterConclave, Ranger_Base, "Hunter Conclave",
  ClassFeature{"Hunter’s Prey", "Choose a combat style option like Colossus Slayer/Giant Killer/Horde Breaker."}
)

MAKE_SUBCLASS3(Ranger_MonsterSlayer, Ranger_Base, "Monster Slayer Conclave",
  ClassFeature{"Monster Slayer Magic", "Expanded spell options tied to the subclass."},
  ClassFeature{"Hunter’s Sense", "Learn a target’s defenses/traits briefly."},
  ClassFeature{"Slayer’s Prey", "Mark a creature to deal extra damage once per turn."}
)

MAKE_SUBCLASS3(Ranger_Swarmkeeper, Ranger_Base, "Swarmkeeper",
  ClassFeature{"Swarmkeeper Magic", "Expanded spell options tied to the subclass."},
  ClassFeature{"Gathered Swarm", "Your swarm can deal damage, move you, or move a target (choice each turn)."}
)

// ---------------- Rogue (Roguish Archetype) ----------------
MAKE_SUBCLASS3(Rogue_ArcaneTrickster, Rogue_Base, "Arcane Trickster",
  ClassFeature{"Spellcasting", "Gain limited wizard-style spellcasting (illusion/enchantment focus)."},
  ClassFeature{"Mage Hand Legerdemain", "Upgrade Mage Hand for stealthy thievery tricks."}
)

MAKE_SUBCLASS3(Rogue_Assassin, Rogue_Base, "Assassin",
  ClassFeature{"Bonus Proficiencies", "Disguise/poison toolkit style training."},
  ClassFeature{"Assassinate", "Strong opening-round advantage and crit potential on surprised foes."}
)

MAKE_SUBCLASS3(Rogue_Inquisitive, Rogue_Base, "Inquisitive",
  ClassFeature{"Ear for Deceit", "More reliable insight vs lies."},
  ClassFeature{"Eye for Detail", "Bonus-action search/spot hidden details."},
  ClassFeature{"Insightful Fighting", "Read a foe to enable sneak attack without advantage in some cases."}
)

MAKE_SUBCLASS3(Rogue_Mastermind, Rogue_Base, "Mastermind",
  ClassFeature{"Master of Intrigue", "Disguise/forgery/language-style expertise package."},
  ClassFeature{"Master of Tactics", "Help as a bonus action at range."}
)

MAKE_SUBCLASS3(Rogue_Phantom, Rogue_Base, "Phantom",
  ClassFeature{"Whispers of the Dead", "Gain a rotating proficiency from spirits."},
  ClassFeature{"Wails from the Grave", "Splash extra necrotic damage to a second target (limited)."}
)

MAKE_SUBCLASS3(Rogue_Scout, Rogue_Base, "Scout",
  ClassFeature{"Skirmisher", "Reaction movement when an enemy closes in."},
  ClassFeature{"Survivalist", "Strong nature/survival skill proficiency boost."}
)

MAKE_SUBCLASS3(Rogue_Soulknife, Rogue_Base, "Soulknife",
  ClassFeature{"Psionic Power", "Psionic dice resource for checks/utility."},
  ClassFeature{"Psychic Blades", "Create psychic blades to attack with."}
)

MAKE_SUBCLASS3(Rogue_Swashbuckler, Rogue_Base, "Swashbuckler",
  ClassFeature{"Fancy Footwork", "Hit-and-run: avoid opportunity attacks from a target you attacked."},
  ClassFeature{"Rakish Audacity", "Initiative bonus and easier sneak attack in duels."}
)

MAKE_SUBCLASS3(Rogue_Thief, Rogue_Base, "Thief",
  ClassFeature{"Fast Hands", "Use objects/thieves’ tools style actions as a bonus action."},
  ClassFeature{"Second-Story Work", "Better climbing and jumping mobility."}
)

// ---------------- Artificer (Specialist) ----------------
MAKE_SUBCLASS3(Art_Alchemist, Artificer_Base, "Alchemist",
  ClassFeature{"Tool Proficiency", "Gain alchemist’s supplies proficiency."},
  ClassFeature{"Experimental Elixir", "Create random/selected elixirs with helpful effects."}
)

MAKE_SUBCLASS3(Art_Armorer, Artificer_Base, "Armorer",
  ClassFeature{"Tool Proficiency", "Gain heavy armor / smithing-style tool focus (specialist)."},
  ClassFeature{"Arcane Armor", "Turn armor into a special suit with built-in modes and functions."}
)

MAKE_SUBCLASS3(Art_Artillerist, Artificer_Base, "Artillerist",
  ClassFeature{"Tool Proficiency", "Gain woodcarver’s tools proficiency (typical specialist tool)."},
  ClassFeature{"Eldritch Cannon", "Create a magical cannon companion with different firing modes."}
)

MAKE_SUBCLASS3(Art_BattleSmith, Artificer_Base, "Battle Smith",
  ClassFeature{"Tool Proficiency", "Gain smith’s tools proficiency."},
  ClassFeature{"Battle Ready", "Weapon proficiency/attack-style improvements for combat readiness."},
  ClassFeature{"Steel Defender", "Gain a construct companion that can fight and protect allies."}
)
// ===================== REGISTRY (NON-CONST) =====================

// Bases
static Barbarian_Base BARBARIAN;
static Bard_Base BARD;
static Cleric_Base CLERIC;
static Druid_Base DRUID;
static Fighter_Base FIGHTER;
static Monk_Base MONK;
static Paladin_Base PALADIN;
static Ranger_Base RANGER;
static Rogue_Base ROGUE;
static Sorcerer_Base SORCERER;
static Warlock_Base WARLOCK;
static Wizard_Base WIZARD;
static Artificer_Base ARTIFICER;

// Subclasses (instances)
static Barbarian_AncestralGuardian BARB_ANCESTRAL;
static Barbarian_Battlerager BARB_BATTLERAGER;
static Barbarian_Beast BARB_BEAST;
static Barbarian_Berserker BARB_BERSERKER;
static Barbarian_Giant BARB_GIANT;
static Barbarian_StormHerald BARB_STORM;
static Barbarian_Totem BARB_TOTEM;
static Barbarian_WildMagic BARB_WILD;
static Barbarian_Zealot BARB_ZEALOT;

static Bard_Creation BARD_CREATION;
static Bard_Eloquence BARD_ELOQUENCE;
static Bard_Glamour BARD_GLAMOUR;
static Bard_Lore BARD_LORE;
static Bard_Spirits BARD_SPIRITS;
static Bard_Swords BARD_SWORDS;
static Bard_Valor BARD_VALOR;
static Bard_Whispers BARD_WHISPERS;

static Cleric_Arcana CLERIC_ARCANA;
static Cleric_Death CLERIC_DEATH;
static Cleric_Forge CLERIC_FORGE;
static Cleric_Grave CLERIC_GRAVE;
static Cleric_Knowledge CLERIC_KNOWLEDGE;
static Cleric_Life CLERIC_LIFE;
static Cleric_Light CLERIC_LIGHT;
static Cleric_Nature CLERIC_NATURE;
static Cleric_Order CLERIC_ORDER;
static Cleric_Peace CLERIC_PEACE;
static Cleric_Tempest CLERIC_TEMPEST;
static Cleric_Trickery CLERIC_TRICKERY;
static Cleric_Twilight CLERIC_TWILIGHT;
static Cleric_War CLERIC_WAR;

static Druid_Dreams DRUID_DREAMS;
static Druid_Land DRUID_LAND;
static Druid_Moon DRUID_MOON;
static Druid_Shepherd DRUID_SHEPHERD;
static Druid_Spores DRUID_SPORES;
static Druid_Stars DRUID_STARS;
static Druid_Wildfire DRUID_WILDFIRE;

static Fighter_ArcaneArcher FIGHTER_ARCANE_ARCHER;
static Fighter_Banneret FIGHTER_BANNERET;
static Fighter_BattleMaster FIGHTER_BATTLEMASTER;
static Fighter_Cavalier FIGHTER_CAVALIER;
static Fighter_Champion FIGHTER_CHAMPION;
static Fighter_EchoKnight FIGHTER_ECHO;
static Fighter_EldritchKnight FIGHTER_ELDRITCH;
static Fighter_PsiWarrior FIGHTER_PSI;
static Fighter_RuneKnight FIGHTER_RUNE;
static Fighter_Samurai FIGHTER_SAMURAI;

static Monk_Mercy MONK_MERCY;
static Monk_AscendantDragon MONK_DRAGON;
static Monk_AstralSelf MONK_ASTRAL;
static Monk_DrunkenMaster MONK_DRUNKEN;
static Monk_FourElements MONK_ELEMENTS;
static Monk_Kensei MONK_KENSEI;
static Monk_LongDeath MONK_LONG_DEATH;
static Monk_OpenHand MONK_OPEN_HAND;
static Monk_Shadow MONK_SHADOW;
static Monk_SunSoul MONK_SUN_SOUL;

static Paladin_Ancients PAL_ANCESTS;
static Paladin_Conquest PAL_CONQUEST;
static Paladin_Crown PAL_CROWN;
static Paladin_Devotion PAL_DEVOTION;
static Paladin_Glory PAL_GLORY;
static Paladin_Redemption PAL_REDEMPTION;
static Paladin_Vengeance PAL_VENGEANCE;
static Paladin_Watchers PAL_WATCHERS;
static Paladin_Oathbreaker PAL_OATHBREAKER;

static Ranger_BeastMasterConclave RNG_BEAST_CONCLAVE;
static Ranger_Drakewarden RNG_DRAKEWARDEN;
static Ranger_FeyWanderer RNG_FEY_WANDERER;
static Ranger_GloomStalker RNG_GLOOM;
static Ranger_HorizonWalker RNG_HORIZON;
static Ranger_HunterConclave RNG_HUNTER_CONCLAVE;
static Ranger_MonsterSlayer RNG_MONSTER;
static Ranger_Swarmkeeper RNG_SWARM;

static Rogue_ArcaneTrickster ROGUE_ARCANE;
static Rogue_Assassin ROGUE_ASSASSIN;
static Rogue_Inquisitive ROGUE_INQUISITIVE;
static Rogue_Mastermind ROGUE_MASTERMIND;
static Rogue_Phantom ROGUE_PHANTOM;
static Rogue_Scout ROGUE_SCOUT;
static Rogue_Soulknife ROGUE_SOULKNIFE;
static Rogue_Swashbuckler ROGUE_SWASH;
static Rogue_Thief ROGUE_THIEF;

static Sorc_AberrantMind SORC_ABERRANT;
static Sorc_ClockworkSoul SORC_CLOCKWORK;
static Sorc_DraconicBloodline SORC_DRACONIC;
static Sorc_DivineSoul SORC_DIVINE;
static Sorc_LunarSorcery SORC_LUNAR;
static Sorc_ShadowMagic SORC_SHADOW;
static Sorc_StormSorcery SORC_STORM;
static Sorc_WildMagic SORC_WILD;

static Warlock_Archfey WL_ARCHFEY;
static Warlock_Celestial WL_CELESTIAL;
static Warlock_Fathomless WL_FATHOMLESS;
static Warlock_Fiend WL_FIEND;
static Warlock_Genie WL_GENIE;
static Warlock_GreatOldOne WL_GOO;
static Warlock_Hexblade WL_HEXBLADE;
static Warlock_Undead WL_UNDEAD;
static Warlock_Undying WL_UNDYING;

static Wiz_Abjuration WIZ_ABJ;
static Wiz_Bladesinging WIZ_BLADE;
static Wiz_Chronurgy WIZ_CHRON;
static Wiz_Conjuration WIZ_CONJ;
static Wiz_Divination WIZ_DIV;
static Wiz_Enchantment WIZ_ENCH;
static Wiz_Evocation WIZ_EVO;
static Wiz_Graviturgy WIZ_GRAV;
static Wiz_Illusion WIZ_ILL;
static Wiz_Necromancy WIZ_NEC;
static Wiz_Scribes WIZ_SCRIBES;
static Wiz_Transmutation WIZ_TRANS;
static Wiz_WarMagic WIZ_WAR;

static Art_Alchemist ART_ALCH;
static Art_Armorer ART_ARMOR;
static Art_Artillerist ART_ARTIL;
static Art_BattleSmith ART_BSMITH;

// ===================== ENUMS + SWITCH FACTORY =====================

enum class MainClassId {
  Barbarian, Bard, Cleric, Druid, Fighter, Monk, Paladin, Ranger, Rogue,
  Sorcerer, Warlock, Wizard, Artificer, Unknown
};

static MainClassId toMainClassId(const std::string& s) {
  if (s == "Barbarian") return MainClassId::Barbarian;
  if (s == "Bard") return MainClassId::Bard;
  if (s == "Cleric") return MainClassId::Cleric;
  if (s == "Druid") return MainClassId::Druid;
  if (s == "Fighter") return MainClassId::Fighter;
  if (s == "Monk") return MainClassId::Monk;
  if (s == "Paladin") return MainClassId::Paladin;
  if (s == "Ranger") return MainClassId::Ranger;
  if (s == "Rogue") return MainClassId::Rogue;
  if (s == "Sorcerer") return MainClassId::Sorcerer;
  if (s == "Warlock") return MainClassId::Warlock;
  if (s == "Wizard") return MainClassId::Wizard;
  if (s == "Artificer") return MainClassId::Artificer;
  return MainClassId::Unknown;
}

enum class SubclassId {
  None, Unknown,

  Barb_Ancestral, Barb_Battlerager, Barb_Beast, Barb_Berserker, Barb_Giant, Barb_Storm, Barb_Totem, Barb_Wild, Barb_Zealot,
  Bard_Creation, Bard_Eloquence, Bard_Glamour, Bard_Lore, Bard_Spirits, Bard_Swords, Bard_Valor, Bard_Whispers,
  Cl_Arcana, Cl_Death, Cl_Forge, Cl_Grave, Cl_Knowledge, Cl_Life, Cl_Light, Cl_Nature, Cl_Order, Cl_Peace, Cl_Tempest, Cl_Trickery, Cl_Twilight, Cl_War,
  Dr_Dreams, Dr_Land, Dr_Moon, Dr_Shepherd, Dr_Spores, Dr_Stars, Dr_Wildfire,
  Fi_ArcaneArcher, Fi_Banneret, Fi_BattleMaster, Fi_Cavalier, Fi_Champion, Fi_Echo, Fi_Eldritch, Fi_Psi, Fi_Rune, Fi_Samurai,
  Mo_Mercy, Mo_Dragon, Mo_Astral, Mo_Drunken, Mo_Elements, Mo_Kensei, Mo_LongDeath, Mo_OpenHand, Mo_Shadow, Mo_SunSoul,
  Pa_Ancients, Pa_Conquest, Pa_Crown, Pa_Devotion, Pa_Glory, Pa_Redemption, Pa_Vengeance, Pa_Watchers, Pa_Oathbreaker,
  Ra_BeastConclave, Ra_Drakewarden, Ra_FeyWanderer, Ra_Gloom, Ra_Horizon, Ra_HunterConclave, Ra_Monster, Ra_Swarm,
  Ro_Arcane, Ro_Assassin, Ro_Inquisitive, Ro_Mastermind, Ro_Phantom, Ro_Scout, Ro_Soulknife, Ro_Swash, Ro_Thief,
  So_Aberrant, So_Clockwork, So_Draconic, So_Divine, So_Lunar, So_Shadow, So_Storm, So_Wild,
  Wa_Archfey, Wa_Celestial, Wa_Fathomless, Wa_Fiend, Wa_Genie, Wa_GOO, Wa_Hexblade, Wa_Undead, Wa_Undying,
  Wi_Abj, Wi_Bladesinging, Wi_Chronurgy, Wi_Conj, Wi_Div, Wi_Ench, Wi_Evo, Wi_Grav, Wi_Ill, Wi_Nec, Wi_Scribes, Wi_Trans, Wi_War,
  Ar_Alch, Ar_Armor, Ar_Artil, Ar_BSmith
};

static SubclassId toSubclassId(MainClassId main, const std::string& sub) {
  if (isNone(sub)) return SubclassId::None;

  switch (main) {
    case MainClassId::Barbarian:
      if (sub == "Path of the Ancestral Guardian") return SubclassId::Barb_Ancestral;
      if (sub == "Path of the Battlerager") return SubclassId::Barb_Battlerager;
      if (sub == "Path of the Beast") return SubclassId::Barb_Beast;
      if (sub == "Path of the Berserker") return SubclassId::Barb_Berserker;
      if (sub == "Path of the Giant") return SubclassId::Barb_Giant;
      if (sub == "Path of the Storm Herald") return SubclassId::Barb_Storm;
      if (sub == "Path of the Totem Warrior") return SubclassId::Barb_Totem;
      if (sub == "Path of Wild Magic") return SubclassId::Barb_Wild;
      if (sub == "Path of the Zealot") return SubclassId::Barb_Zealot;
      return SubclassId::Unknown;

    case MainClassId::Bard:
      if (sub == "College of Creation") return SubclassId::Bard_Creation;
      if (sub == "College of Eloquence") return SubclassId::Bard_Eloquence;
      if (sub == "College of Glamour") return SubclassId::Bard_Glamour;
      if (sub == "College of Lore") return SubclassId::Bard_Lore;
      if (sub == "College of Spirits") return SubclassId::Bard_Spirits;
      if (sub == "College of Swords") return SubclassId::Bard_Swords;
      if (sub == "College of Valor") return SubclassId::Bard_Valor;
      if (sub == "College of Whispers") return SubclassId::Bard_Whispers;
      return SubclassId::Unknown;

    case MainClassId::Cleric:
      if (sub == "Arcana Domain") return SubclassId::Cl_Arcana;
      if (sub == "Death Domain") return SubclassId::Cl_Death;
      if (sub == "Forge Domain") return SubclassId::Cl_Forge;
      if (sub == "Grave Domain") return SubclassId::Cl_Grave;
      if (sub == "Knowledge Domain") return SubclassId::Cl_Knowledge;
      if (sub == "Life Domain") return SubclassId::Cl_Life;
      if (sub == "Light Domain") return SubclassId::Cl_Light;
      if (sub == "Nature Domain") return SubclassId::Cl_Nature;
      if (sub == "Order Domain") return SubclassId::Cl_Order;
      if (sub == "Peace Domain") return SubclassId::Cl_Peace;
      if (sub == "Tempest Domain") return SubclassId::Cl_Tempest;
      if (sub == "Trickery Domain") return SubclassId::Cl_Trickery;
      if (sub == "Twilight Domain") return SubclassId::Cl_Twilight;
      if (sub == "War Domain") return SubclassId::Cl_War;
      return SubclassId::Unknown;

    case MainClassId::Druid:
      if (sub == "Circle of Dreams") return SubclassId::Dr_Dreams;
      if (sub == "Circle of the Land") return SubclassId::Dr_Land;
      if (sub == "Circle of the Moon") return SubclassId::Dr_Moon;
      if (sub == "Circle of the Shepherd") return SubclassId::Dr_Shepherd;
      if (sub == "Circle of Spores") return SubclassId::Dr_Spores;
      if (sub == "Circle of Stars") return SubclassId::Dr_Stars;
      if (sub == "Circle of Wildfire") return SubclassId::Dr_Wildfire;
      return SubclassId::Unknown;

    case MainClassId::Fighter:
      if (sub == "Arcane Archer") return SubclassId::Fi_ArcaneArcher;
      if (sub == "Banneret") return SubclassId::Fi_Banneret;
      if (sub == "Battle Master") return SubclassId::Fi_BattleMaster;
      if (sub == "Cavalier") return SubclassId::Fi_Cavalier;
      if (sub == "Champion") return SubclassId::Fi_Champion;
      if (sub == "Echo Knight") return SubclassId::Fi_Echo;
      if (sub == "Eldritch Knight") return SubclassId::Fi_Eldritch;
      if (sub == "Psi Warrior") return SubclassId::Fi_Psi;
      if (sub == "Rune Knight") return SubclassId::Fi_Rune;
      if (sub == "Samurai") return SubclassId::Fi_Samurai;
      return SubclassId::Unknown;

    case MainClassId::Monk:
      if (sub == "Way of Mercy") return SubclassId::Mo_Mercy;
      if (sub == "Way of the Ascendant Dragon") return SubclassId::Mo_Dragon;
      if (sub == "Way of the Astral Self") return SubclassId::Mo_Astral;
      if (sub == "Way of the Drunken Master") return SubclassId::Mo_Drunken;
      if (sub == "Way of the Four Elements") return SubclassId::Mo_Elements;
      if (sub == "Way of the Kensei") return SubclassId::Mo_Kensei;
      if (sub == "Way of the Long Death") return SubclassId::Mo_LongDeath;
      if (sub == "Way of the Open Hand") return SubclassId::Mo_OpenHand;
      if (sub == "Way of Shadow") return SubclassId::Mo_Shadow;
      if (sub == "Way of the Sun Soul") return SubclassId::Mo_SunSoul;
      return SubclassId::Unknown;

    case MainClassId::Paladin:
      if (sub == "Oath of the Ancients") return SubclassId::Pa_Ancients;
      if (sub == "Oath of Conquest") return SubclassId::Pa_Conquest;
      if (sub == "Oath of the Crown") return SubclassId::Pa_Crown;
      if (sub == "Oath of Devotion") return SubclassId::Pa_Devotion;
      if (sub == "Oath of Glory") return SubclassId::Pa_Glory;
      if (sub == "Oath of Redemption") return SubclassId::Pa_Redemption;
      if (sub == "Oath of Vengeance") return SubclassId::Pa_Vengeance;
      if (sub == "Oath of the Watchers") return SubclassId::Pa_Watchers;
      if (sub == "Oathbreaker") return SubclassId::Pa_Oathbreaker;
      return SubclassId::Unknown;

    case MainClassId::Ranger:
      if (sub == "Beast Master Conclave") return SubclassId::Ra_BeastConclave;
      if (sub == "Drakewarden") return SubclassId::Ra_Drakewarden;
      if (sub == "Fey Wanderer") return SubclassId::Ra_FeyWanderer;
      if (sub == "Gloom Stalker Conclave") return SubclassId::Ra_Gloom;
      if (sub == "Horizon Walker Conclave") return SubclassId::Ra_Horizon;
      if (sub == "Hunter Conclave") return SubclassId::Ra_HunterConclave;
      if (sub == "Monster Slayer Conclave") return SubclassId::Ra_Monster;
      if (sub == "Swarmkeeper") return SubclassId::Ra_Swarm;
      return SubclassId::Unknown;

    case MainClassId::Rogue:
      if (sub == "Arcane Trickster") return SubclassId::Ro_Arcane;
      if (sub == "Assassin") return SubclassId::Ro_Assassin;
      if (sub == "Inquisitive") return SubclassId::Ro_Inquisitive;
      if (sub == "Mastermind") return SubclassId::Ro_Mastermind;
      if (sub == "Phantom") return SubclassId::Ro_Phantom;
      if (sub == "Scout") return SubclassId::Ro_Scout;
      if (sub == "Soulknife") return SubclassId::Ro_Soulknife;
      if (sub == "Swashbuckler") return SubclassId::Ro_Swash;
      if (sub == "Thief") return SubclassId::Ro_Thief;
      return SubclassId::Unknown;

    case MainClassId::Sorcerer:
      if (sub == "Aberrant Mind") return SubclassId::So_Aberrant;
      if (sub == "Clockwork Soul") return SubclassId::So_Clockwork;
      if (sub == "Draconic Bloodline") return SubclassId::So_Draconic;
      if (sub == "Divine Soul") return SubclassId::So_Divine;
      if (sub == "Lunar Sorcery") return SubclassId::So_Lunar;
      if (sub == "Shadow Magic") return SubclassId::So_Shadow;
      if (sub == "Storm Sorcery") return SubclassId::So_Storm;
      if (sub == "Wild Magic") return SubclassId::So_Wild;
      return SubclassId::Unknown;

    case MainClassId::Warlock:
      if (sub == "Archfey") return SubclassId::Wa_Archfey;
      if (sub == "Celestial") return SubclassId::Wa_Celestial;
      if (sub == "Fathomless") return SubclassId::Wa_Fathomless;
      if (sub == "Fiend") return SubclassId::Wa_Fiend;
      if (sub == "The Genie") return SubclassId::Wa_Genie;
      if (sub == "Great Old One") return SubclassId::Wa_GOO;
      if (sub == "Hexblade") return SubclassId::Wa_Hexblade;
      if (sub == "Undead") return SubclassId::Wa_Undead;
      if (sub == "Undying") return SubclassId::Wa_Undying;
      return SubclassId::Unknown;

    case MainClassId::Wizard:
      if (sub == "School of Abjuration") return SubclassId::Wi_Abj;
      if (sub == "School of Bladesinging") return SubclassId::Wi_Bladesinging;
      if (sub == "School of Chronurgy") return SubclassId::Wi_Chronurgy;
      if (sub == "School of Conjuration") return SubclassId::Wi_Conj;
      if (sub == "School of Divination") return SubclassId::Wi_Div;
      if (sub == "School of Enchantment") return SubclassId::Wi_Ench;
      if (sub == "School of Evocation") return SubclassId::Wi_Evo;
      if (sub == "School of Graviturgy") return SubclassId::Wi_Grav;
      if (sub == "School of Illusion") return SubclassId::Wi_Ill;
      if (sub == "School of Necromancy") return SubclassId::Wi_Nec;
      if (sub == "Order of Scribes") return SubclassId::Wi_Scribes;
      if (sub == "School of Transmutation") return SubclassId::Wi_Trans;
      if (sub == "School of War Magic") return SubclassId::Wi_War;
      return SubclassId::Unknown;

    case MainClassId::Artificer:
      if (sub == "Alchemist") return SubclassId::Ar_Alch;
      if (sub == "Armorer") return SubclassId::Ar_Armor;
      if (sub == "Artillerist") return SubclassId::Ar_Artil;
      if (sub == "Battle Smith") return SubclassId::Ar_BSmith;
      return SubclassId::Unknown;

    default:
      return SubclassId::Unknown;
  }
}

// ===================== PUBLIC API =====================

std::vector<std::string> availableMainClasses() {
  return {"Artificer","Barbarian","Bard","Cleric","Druid","Fighter","Monk","Paladin",
          "Ranger","Rogue","Sorcerer","Warlock","Wizard"};
}

std::vector<std::string> availableSubclasses(const std::string& mainClass) {
  switch (toMainClassId(mainClass)) {
    case MainClassId::Artificer:
      return {"Alchemist","Armorer","Artillerist","Battle Smith"};

    case MainClassId::Barbarian:
      return {"Path of the Ancestral Guardian","Path of the Battlerager","Path of the Beast",
              "Path of the Berserker","Path of the Giant","Path of the Storm Herald",
              "Path of the Totem Warrior","Path of Wild Magic","Path of the Zealot"};

    case MainClassId::Bard:
      return {"College of Creation","College of Eloquence","College of Glamour","College of Lore",
              "College of Spirits","College of Swords","College of Valor","College of Whispers"};

    case MainClassId::Cleric:
      return {"Arcana Domain","Death Domain","Forge Domain","Grave Domain","Knowledge Domain",
              "Life Domain","Light Domain","Nature Domain","Order Domain","Peace Domain",
              "Tempest Domain","Trickery Domain","Twilight Domain","War Domain"};

    case MainClassId::Druid:
      return {"Circle of Dreams","Circle of the Land","Circle of the Moon","Circle of the Shepherd",
              "Circle of Spores","Circle of Stars","Circle of Wildfire"};

    case MainClassId::Fighter:
      return {"Arcane Archer","Banneret","Battle Master","Cavalier","Champion",
              "Echo Knight","Eldritch Knight","Psi Warrior","Rune Knight","Samurai"};

    case MainClassId::Monk:
      return {"Way of Mercy","Way of the Ascendant Dragon","Way of the Astral Self","Way of the Drunken Master",
              "Way of the Four Elements","Way of the Kensei","Way of the Long Death","Way of the Open Hand",
              "Way of Shadow","Way of the Sun Soul"};

    case MainClassId::Paladin:
      return {"Oath of the Ancients","Oath of Conquest","Oath of the Crown","Oath of Devotion",
              "Oath of Glory","Oath of Redemption","Oath of Vengeance","Oath of the Watchers","Oathbreaker"};

    case MainClassId::Ranger:
      return {"Beast Master Conclave","Drakewarden","Fey Wanderer","Gloom Stalker Conclave",
              "Horizon Walker Conclave","Hunter Conclave","Monster Slayer Conclave","Swarmkeeper"};

    case MainClassId::Rogue:
      return {"Arcane Trickster","Assassin","Inquisitive","Mastermind","Phantom","Scout",
              "Soulknife","Swashbuckler","Thief"};

    case MainClassId::Sorcerer:
      return {"Aberrant Mind","Clockwork Soul","Draconic Bloodline","Divine Soul",
              "Lunar Sorcery","Shadow Magic","Storm Sorcery","Wild Magic"};

    case MainClassId::Warlock:
      return {"Archfey","Celestial","Fathomless","Fiend","The Genie","Great Old One",
              "Hexblade","Undead","Undying"};

    case MainClassId::Wizard:
      return {"School of Abjuration","School of Bladesinging","School of Chronurgy","School of Conjuration",
              "School of Divination","School of Enchantment","School of Evocation","School of Graviturgy",
              "School of Illusion","School of Necromancy","Order of Scribes","School of Transmutation","School of War Magic"};

    default:
      return {};
  }
}

DndClass& getClass(const std::string& mainClass, const std::string& sub) {
  MainClassId m = toMainClassId(mainClass);
  SubclassId s = toSubclassId(m, sub);

  switch (m) {
    case MainClassId::Artificer:
      switch (s) {
        case SubclassId::None: return ARTIFICER;
        case SubclassId::Ar_Alch: return ART_ALCH;
        case SubclassId::Ar_Armor: return ART_ARMOR;
        case SubclassId::Ar_Artil: return ART_ARTIL;
        case SubclassId::Ar_BSmith: return ART_BSMITH;
        default: throw std::runtime_error("Unknown Artificer subclass: " + sub);
      }

    case MainClassId::Barbarian:
      switch (s) {
        case SubclassId::None: return BARBARIAN;
        case SubclassId::Barb_Ancestral: return BARB_ANCESTRAL;
        case SubclassId::Barb_Battlerager: return BARB_BATTLERAGER;
        case SubclassId::Barb_Beast: return BARB_BEAST;
        case SubclassId::Barb_Berserker: return BARB_BERSERKER;
        case SubclassId::Barb_Giant: return BARB_GIANT;
        case SubclassId::Barb_Storm: return BARB_STORM;
        case SubclassId::Barb_Totem: return BARB_TOTEM;
        case SubclassId::Barb_Wild: return BARB_WILD;
        case SubclassId::Barb_Zealot: return BARB_ZEALOT;
        default: throw std::runtime_error("Unknown Barbarian subclass: " + sub);
      }

    case MainClassId::Bard:
      switch (s) {
        case SubclassId::None: return BARD;
        case SubclassId::Bard_Creation: return BARD_CREATION;
        case SubclassId::Bard_Eloquence: return BARD_ELOQUENCE;
        case SubclassId::Bard_Glamour: return BARD_GLAMOUR;
        case SubclassId::Bard_Lore: return BARD_LORE;
        case SubclassId::Bard_Spirits: return BARD_SPIRITS;
        case SubclassId::Bard_Swords: return BARD_SWORDS;
        case SubclassId::Bard_Valor: return BARD_VALOR;
        case SubclassId::Bard_Whispers: return BARD_WHISPERS;
        default: throw std::runtime_error("Unknown Bard subclass: " + sub);
      }

    case MainClassId::Cleric:
      switch (s) {
        case SubclassId::None: return CLERIC;
        case SubclassId::Cl_Arcana: return CLERIC_ARCANA;
        case SubclassId::Cl_Death: return CLERIC_DEATH;
        case SubclassId::Cl_Forge: return CLERIC_FORGE;
        case SubclassId::Cl_Grave: return CLERIC_GRAVE;
        case SubclassId::Cl_Knowledge: return CLERIC_KNOWLEDGE;
        case SubclassId::Cl_Life: return CLERIC_LIFE;
        case SubclassId::Cl_Light: return CLERIC_LIGHT;
        case SubclassId::Cl_Nature: return CLERIC_NATURE;
        case SubclassId::Cl_Order: return CLERIC_ORDER;
        case SubclassId::Cl_Peace: return CLERIC_PEACE;
        case SubclassId::Cl_Tempest: return CLERIC_TEMPEST;
        case SubclassId::Cl_Trickery: return CLERIC_TRICKERY;
        case SubclassId::Cl_Twilight: return CLERIC_TWILIGHT;
        case SubclassId::Cl_War: return CLERIC_WAR;
        default: throw std::runtime_error("Unknown Cleric domain: " + sub);
      }

    case MainClassId::Druid:
      switch (s) {
        case SubclassId::None: return DRUID;
        case SubclassId::Dr_Dreams: return DRUID_DREAMS;
        case SubclassId::Dr_Land: return DRUID_LAND;
        case SubclassId::Dr_Moon: return DRUID_MOON;
        case SubclassId::Dr_Shepherd: return DRUID_SHEPHERD;
        case SubclassId::Dr_Spores: return DRUID_SPORES;
        case SubclassId::Dr_Stars: return DRUID_STARS;
        case SubclassId::Dr_Wildfire: return DRUID_WILDFIRE;
        default: throw std::runtime_error("Unknown Druid circle: " + sub);
      }

    case MainClassId::Fighter:
      switch (s) {
        case SubclassId::None: return FIGHTER;
        case SubclassId::Fi_ArcaneArcher: return FIGHTER_ARCANE_ARCHER;
        case SubclassId::Fi_Banneret: return FIGHTER_BANNERET;
        case SubclassId::Fi_BattleMaster: return FIGHTER_BATTLEMASTER;
        case SubclassId::Fi_Cavalier: return FIGHTER_CAVALIER;
        case SubclassId::Fi_Champion: return FIGHTER_CHAMPION;
        case SubclassId::Fi_Echo: return FIGHTER_ECHO;
        case SubclassId::Fi_Eldritch: return FIGHTER_ELDRITCH;
        case SubclassId::Fi_Psi: return FIGHTER_PSI;
        case SubclassId::Fi_Rune: return FIGHTER_RUNE;
        case SubclassId::Fi_Samurai: return FIGHTER_SAMURAI;
        default: throw std::runtime_error("Unknown Fighter archetype: " + sub);
      }

    case MainClassId::Monk:
      switch (s) {
        case SubclassId::None: return MONK;
        case SubclassId::Mo_Mercy: return MONK_MERCY;
        case SubclassId::Mo_Dragon: return MONK_DRAGON;
        case SubclassId::Mo_Astral: return MONK_ASTRAL;
        case SubclassId::Mo_Drunken: return MONK_DRUNKEN;
        case SubclassId::Mo_Elements: return MONK_ELEMENTS;
        case SubclassId::Mo_Kensei: return MONK_KENSEI;
        case SubclassId::Mo_LongDeath: return MONK_LONG_DEATH;
        case SubclassId::Mo_OpenHand: return MONK_OPEN_HAND;
        case SubclassId::Mo_Shadow: return MONK_SHADOW;
        case SubclassId::Mo_SunSoul: return MONK_SUN_SOUL;
        default: throw std::runtime_error("Unknown Monk tradition: " + sub);
      }

    case MainClassId::Paladin:
      switch (s) {
        case SubclassId::None: return PALADIN;
        case SubclassId::Pa_Ancients: return PAL_ANCESTS;
        case SubclassId::Pa_Conquest: return PAL_CONQUEST;
        case SubclassId::Pa_Crown: return PAL_CROWN;
        case SubclassId::Pa_Devotion: return PAL_DEVOTION;
        case SubclassId::Pa_Glory: return PAL_GLORY;
        case SubclassId::Pa_Redemption: return PAL_REDEMPTION;
        case SubclassId::Pa_Vengeance: return PAL_VENGEANCE;
        case SubclassId::Pa_Watchers: return PAL_WATCHERS;
        case SubclassId::Pa_Oathbreaker: return PAL_OATHBREAKER;
        default: throw std::runtime_error("Unknown Paladin oath: " + sub);
      }

    case MainClassId::Ranger:
      switch (s) {
        case SubclassId::None: return RANGER;
        case SubclassId::Ra_BeastConclave: return RNG_BEAST_CONCLAVE;
        case SubclassId::Ra_Drakewarden: return RNG_DRAKEWARDEN;
        case SubclassId::Ra_FeyWanderer: return RNG_FEY_WANDERER;
        case SubclassId::Ra_Gloom: return RNG_GLOOM;
        case SubclassId::Ra_Horizon: return RNG_HORIZON;
        case SubclassId::Ra_HunterConclave: return RNG_HUNTER_CONCLAVE;
        case SubclassId::Ra_Monster: return RNG_MONSTER;
        case SubclassId::Ra_Swarm: return RNG_SWARM;
        default: throw std::runtime_error("Unknown Ranger conclave: " + sub);
      }

    case MainClassId::Rogue:
      switch (s) {
        case SubclassId::None: return ROGUE;
        case SubclassId::Ro_Arcane: return ROGUE_ARCANE;
        case SubclassId::Ro_Assassin: return ROGUE_ASSASSIN;
        case SubclassId::Ro_Inquisitive: return ROGUE_INQUISITIVE;
        case SubclassId::Ro_Mastermind: return ROGUE_MASTERMIND;
        case SubclassId::Ro_Phantom: return ROGUE_PHANTOM;
        case SubclassId::Ro_Scout: return ROGUE_SCOUT;
        case SubclassId::Ro_Soulknife: return ROGUE_SOULKNIFE;
        case SubclassId::Ro_Swash: return ROGUE_SWASH;
        case SubclassId::Ro_Thief: return ROGUE_THIEF;
        default: throw std::runtime_error("Unknown Rogue archetype: " + sub);
      }

    case MainClassId::Sorcerer:
      switch (s) {
        case SubclassId::None: return SORCERER;
        case SubclassId::So_Aberrant: return SORC_ABERRANT;
        case SubclassId::So_Clockwork: return SORC_CLOCKWORK;
        case SubclassId::So_Draconic: return SORC_DRACONIC;
        case SubclassId::So_Divine: return SORC_DIVINE;
        case SubclassId::So_Lunar: return SORC_LUNAR;
        case SubclassId::So_Shadow: return SORC_SHADOW;
        case SubclassId::So_Storm: return SORC_STORM;
        case SubclassId::So_Wild: return SORC_WILD;
        default: throw std::runtime_error("Unknown Sorcerer origin: " + sub);
      }

    case MainClassId::Warlock:
      switch (s) {
        case SubclassId::None: return WARLOCK;
        case SubclassId::Wa_Archfey: return WL_ARCHFEY;
        case SubclassId::Wa_Celestial: return WL_CELESTIAL;
        case SubclassId::Wa_Fathomless: return WL_FATHOMLESS;
        case SubclassId::Wa_Fiend: return WL_FIEND;
        case SubclassId::Wa_Genie: return WL_GENIE;
        case SubclassId::Wa_GOO: return WL_GOO;
        case SubclassId::Wa_Hexblade: return WL_HEXBLADE;
        case SubclassId::Wa_Undead: return WL_UNDEAD;
        case SubclassId::Wa_Undying: return WL_UNDYING;
        default: throw std::runtime_error("Unknown Warlock patron: " + sub);
      }

    case MainClassId::Wizard:
      switch (s) {
        case SubclassId::None: return WIZARD;
        case SubclassId::Wi_Abj: return WIZ_ABJ;
        case SubclassId::Wi_Bladesinging: return WIZ_BLADE;
        case SubclassId::Wi_Chronurgy: return WIZ_CHRON;
        case SubclassId::Wi_Conj: return WIZ_CONJ;
        case SubclassId::Wi_Div: return WIZ_DIV;
        case SubclassId::Wi_Ench: return WIZ_ENCH;
        case SubclassId::Wi_Evo: return WIZ_EVO;
        case SubclassId::Wi_Grav: return WIZ_GRAV;
        case SubclassId::Wi_Ill: return WIZ_ILL;
        case SubclassId::Wi_Nec: return WIZ_NEC;
        case SubclassId::Wi_Scribes: return WIZ_SCRIBES;
        case SubclassId::Wi_Trans: return WIZ_TRANS;
        case SubclassId::Wi_War: return WIZ_WAR;
        default: throw std::runtime_error("Unknown Wizard school: " + sub);
      }

    default:
      throw std::runtime_error("Unknown class: " + mainClass);
  }
}

// Back-compat (main class only)
std::vector<std::string> availableClasses() { return availableMainClasses(); }
DndClass& getClassByName(const std::string& className) { return getClass(className, ""); }