#include "background.h"
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <string>
#include <vector>

static std::string trim(std::string s) {
  while (!s.empty() && std::isspace((unsigned char)s.front())) s.erase(s.begin());
  while (!s.empty() && std::isspace((unsigned char)s.back())) s.pop_back();
  return s;
}

struct BackgroundDef {
  std::string name;
  std::string source; // "PHB", "SCAG", "VRGR", "AL: ...", "Homebrew"

  std::vector<std::string> skills;
  std::vector<std::string> tools;
  std::vector<std::string> langs;

  BackgroundFeature feat;
};

class BackgroundFromData : public Background {
public:
  BackgroundFromData() : def(nullptr) {}
  explicit BackgroundFromData(const BackgroundDef* d) : def(d) {}

  void bind(const BackgroundDef* d) { def = d; }

  std::string name() { return def ? def->name : "Unknown"; }
  std::string source() { return def ? def->source : ""; }

  std::vector<std::string> skillProficiencies() { return def ? def->skills : std::vector<std::string>{}; }
  std::vector<std::string> toolProficiencies() { return def ? def->tools : std::vector<std::string>{}; }
  std::vector<std::string> languages() { return def ? def->langs : std::vector<std::string>{}; }

  BackgroundFeature feature() { return def ? def->feat : BackgroundFeature{"",""}; }

private:
  const BackgroundDef* def;
};

static std::vector<BackgroundDef>& defs() {
  static std::vector<BackgroundDef> v;
  if (!v.empty()) return v;

  auto add = [&](BackgroundDef d){ v.push_back(std::move(d)); };

  // ===================== PHB CORE BACKGROUNDS =====================
  // Note: short paraphrases; you can refine later.

  add({"Acolyte","PHB",
       {"Insight","Religion"}, {}, {"Two languages"},
       {"Shelter of the Faithful","Get help from temples and religious communities."}});

  add({"Charlatan","PHB",
       {"Deception","Sleight of Hand"}, {"Disguise kit","Forgery kit"}, {},
       {"False Identity","Maintain a second identity with documents and contacts."}});

  add({"Criminal","PHB",
       {"Deception","Stealth"}, {"One gaming set","Thieves' tools"}, {},
       {"Criminal Contact","You have a reliable contact in the criminal world."}});

  add({"Entertainer","PHB",
       {"Acrobatics","Performance"}, {"Disguise kit","One musical instrument"}, {},
       {"By Popular Demand","You can find food/lodging by performing."}});

  add({"Folk Hero","PHB",
       {"Animal Handling","Survival"}, {"One artisan's tools","Vehicles (land)"}, {},
       {"Rustic Hospitality","Common folk will shelter and help you."}});

  add({"Guild Artisan","PHB",
       {"Insight","Persuasion"}, {"One artisan's tools"}, {"One language"},
       {"Guild Membership","Support from your guild and access to contacts."}});

  add({"Hermit","PHB",
       {"Medicine","Religion"}, {"Herbalism kit"}, {"One language"},
       {"Discovery","You uncovered a major secret (work with DM)."}});

  add({"Noble","PHB",
       {"History","Persuasion"}, {"One gaming set"}, {"One language"},
       {"Position of Privilege","People assume you have authority/wealth."}});

  add({"Outlander","PHB",
       {"Athletics","Survival"}, {"One musical instrument"}, {"One language"},
       {"Wanderer","Excellent memory for maps/terrain; find food/water."}});

  add({"Sage","PHB",
       {"Arcana","History"}, {}, {"Two languages"},
       {"Researcher","You know where to find information (or who does)."}});

  add({"Sailor","PHB",
       {"Athletics","Perception"}, {"Navigator's tools","Vehicles (water)"}, {},
       {"Ship's Passage","You can secure passage on a ship for you/companions."}});

  add({"Soldier","PHB",
       {"Athletics","Intimidation"}, {"One gaming set","Vehicles (land)"}, {},
       {"Military Rank","Soldiers recognize your rank and may help."}});

  add({"Urchin","PHB",
       {"Sleight of Hand","Stealth"}, {"Disguise kit","Thieves' tools"}, {},
       {"City Secrets","You know city routes and hidden passages."}});

  // ===================== COMMON (NON-PHB) FROM YOUR LIST =====================
  // These are placeholders so your menu has them; you can later fill exact profs.
  auto addSimple = [&](const std::string& n, const std::string& src){
    add({n, src, {}, {}, {}, {"", ""}});
  };

  addSimple("Anthropologist","Common");
  addSimple("Archaeologist","Common");
  addSimple("Athlete","Common");
  addSimple("City Watch","Common");
  addSimple("Clan Crafter","Common");
  addSimple("Cloistered Scholar","Common");
  addSimple("Courtier","Common");
  addSimple("Faceless","Common");
  addSimple("Faction Agent","Common");
  addSimple("Far Traveler","Common");
  addSimple("Feylost","Common");
  addSimple("Fisher","Common");
  addSimple("Giant Foundling","Common");
  addSimple("Gladiator","Common");
  addSimple("Guild Merchant","Common");
  addSimple("Haunted One","Common");
  addSimple("House Agent","Common");
  addSimple("Inheritor","Common");
  addSimple("Investigator (SCAG)","SCAG");
  addSimple("Investigator (VRGR)","VRGR");
  addSimple("Knight","Common");
  addSimple("Knight of the Order","Common");
  addSimple("Marine","Common");
  addSimple("Mercenary Veteran","Common");
  addSimple("Pirate","Common");
  addSimple("Rewarded","Common");
  addSimple("Ruined","Common");
  addSimple("Rune Carver","Common");
  addSimple("Shipwright","Common");
  addSimple("Smuggler","Common");
  addSimple("Spy","Common");

  // ===================== AL: CURSE OF STRAHD =====================
  addSimple("Black Fist Double Agent","AL: Curse of Strahd");
  addSimple("Dragon Casualty","AL: Curse of Strahd");
  addSimple("Iron Route Bandit","AL: Curse of Strahd");
  addSimple("Phlan Insurgent","AL: Curse of Strahd");
  addSimple("Stojanow Prisoner","AL: Curse of Strahd");
  addSimple("Ticklebelly Nomad","AL: Curse of Strahd");

  // ===================== AL: MULMASTER =====================
  addSimple("Caravan Specialist","AL: Mulmaster");
  addSimple("Earthspur Miner","AL: Mulmaster");
  addSimple("Harborfolk","AL: Mulmaster");
  addSimple("Mulmaster Aristocrat","AL: Mulmaster");
  addSimple("Phlan Refugee","AL: Mulmaster");

  // ===================== AL: HILLSFAR =====================
  addSimple("Cormanthor Refugee","AL: Hillsfar");
  addSimple("Gate Urchin","AL: Hillsfar");
  addSimple("Hillsfar Merchant","AL: Hillsfar");
  addSimple("Hillsfar Smuggler","AL: Hillsfar");
  addSimple("Secret Identity","AL: Hillsfar");
  addSimple("Shade Fanatic","AL: Hillsfar");
  addSimple("Trade Sheriff","AL: Hillsfar");

  // ===================== HOMEBREW =====================
  addSimple("Ashari","Homebrew");

  return v;
}

static std::vector<BackgroundFromData>& objs() {
  static std::vector<BackgroundFromData> o;
  if (!o.empty()) return o;

  auto& d = defs();
  o.resize(d.size());
  for (size_t i = 0; i < d.size(); ++i) o[i].bind(&d[i]);
  return o;
}

// ---------------- Public API ----------------

std::vector<std::string> availableBackgroundNames() {
  auto& d = defs();
  std::vector<std::string> out;
  out.reserve(d.size());
  for (auto& b : d) out.push_back(b.name);
  std::sort(out.begin(), out.end());
  return out;
}

Background& getBackgroundByName(const std::string& name) {
  auto& d = defs();
  auto& o = objs();
  std::string n = trim(name);

  for (size_t i = 0; i < d.size(); ++i) {
    if (d[i].name == n) return o[i];
  }
  throw std::runtime_error("Unknown background: " + name);
}