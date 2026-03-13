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

  add({"Anthropologist","Common"
      {"Insight", "Religion"}, {}, {"Two languages"},
      {"Adept language","You can learn/speak languages you don't know."}});
  
  add({"Archaeologist","Common"
    {"History", "Survival"}, {"Cartographer's tools", "Navagator's tools"}, {"One language"},
    {"Historical Knowledge", "You know the purpose/builders of dungeons/ruins and the value of old art."}});
    
  add({"Athlete","Common"
    {"Acrobatics", "Athletics"}, {"Vehicles (land)"}, {"One language"},
    {"Echos of Victory", "Chance of finding a fan who will give information or shelter when near home town."}});
  
  add({"City Watch","Common"
    {"Athletics", "Insight"}, {}, {"Two languages"},
    {"Watcher's Eye", "You con find local outposts of the watch and criminal dens."}} );
  
  add({"Clan Crafter","Common"
    {"History", "Insight"}, {"One artisan's tools"}, {"One language"},
    {"Respect of the Stout Folk", "Sheild and gold dwarves give you free room and board."}});
  
  add({"Cloistered Scholar","Common"
    {"History", "Arcana"}, {}, {"Two languages"},
    {"Library Access", "You have access to the majority of the library and you have connections to your cloister."}});
  
  add({"Courtier","Common"
    {"Insight", "Persuasion"}, {}, {"Two languages"},
    {"Court Functionary", "You have access to the records and inner workings of any government."}});
  
  add({"Faceless","Common"
    {"Deception", "Intimidation"}, {"Disguise kit"}, {"One language"},
    {"Dual Personalities", "You can freely switch between your persona and your true self."}});
  
  addSimple({"Faction Agent","Common"
    {"Insight", ""}, {}, {"Two languages"},
    {"Safe Haven", "You know opratives who will give information, a safe house, or free room and board."}});
  
  add({"Far Traveler","Common"
    {"Insight", "Persuasion"}, {"One musical instrument"}, {"One language"},
    {"All Eyes on You", "Others notice you are foreign."}});
  
  add({"Feylost","Common"
    {"Deception", "Survival"}, {"One musical instrument"}, {"One language"},
    {"Feywild Connection", "Friendly Fey creatures are inclined to help you."}});
  
  add({"Fisher","Common"
    {"History", "Survival"}, {}, {"One laguage"},
    {"Harvest the Water", "You have advantage on fishing tackle and you can catch enough food for 11 people each day."}});
  
  add({"Giant Foundling","Common"
    {"Intimidation", "Survival"}, {}, {"Two languages"},
    {"Strike of the Giants", "You gain the Strike of the Giants feat."}});
  
  add({"Gladiator","Common"
    {"Acrobatics", "Performance"}, {"One gaming set"}, {},
    {"By popular Demand", "You can perform in combat for free lodging."}});
  
  add({"Guild Merchant","Common"
    {"Insight", "Persuasion"}, {"One artisan's tools"}, {"One language"},
    {"Guiild Membership", "You gain all the benefets of being a guild member, you must pay 5gp per month to the guild."}});
  
  add({"Haunted One","Common"
    {"Arcana", "Investigation"}, {"Monster hunter's pack"}, {"Two languages"},
    {"Heart of Darkness", "Commoners will help you to the utmost."}});
  
  add({"House Agent","Common"
    {"Investigation", "Persuasion"}, {"One artisan's tools"}, {},
    {"House Connection", "You can get provisions for yourself/others at house enclaves."}});
  
  add({"Inheritor","Common"
    {"Survival", "History"}, {"Your Inheritance"}, {"One language"},
    {"Inheritance", "Choose what your inheritance is (work with DM) you may keep it a secret."}});
  
  add({"Investigator (SCAG)","SCAG"
    {"Insight", "Investigation"}, {}, {"Two languages"},
    {"Watcher's Eye", "You know how to find local, legal, or criminal info, and can easily locate a city watch outpost."}});
    
  add({"Investigator (VRGR)","VRGR"
    {"Insight", "Investigation"}, {"Magnifying glass"}, {},
    {"Official Inquiry", "You can easily gain access to a place or person."}});
    
  add({"Knight","Common"
    {"History", "Persuasion"}, {}, {"One language"},
    {"Retainers", "You have the service of three retainers loyal to your family. They can leave."}});
  
  add({"Knight of the Order","Common"
    {"Persuasion", "Religion"}, {}, {"One language"},
    {"Knightly Regard", "You receive help from your order."}});
  
  add({"Marine","Common"
    {"Athletics", "Survival"}, {"Dagger"}, {},
    {"Steady", "You can move 16 hours each day without forced march. You can find a safe route for a boat to land on shore."}});
  
  add({"Mercenary Veteran","Common"
    {"Athletics", "Persuasion"}, {"One gaming set"}, {},
    {"Mercenary Life", "You can identify other mercenary companies and you can find mercenary work."}});
  
  add({"Pirate","Common"
    {"Athletics", "Perception"}, {"Belaying pin", "50 ft rope"}, {},
    {"Bad Reputation", "You can get away with minor crime."}});
  
  add({"Rewarded","Common"
    {"Insight", "Persuasion"}, {"One gaming set"}, {"One language"},
    {"Fourtune's Favor", "You gain the Lucky, Magic Initiate, or Skilled feat."}});
  
  add({"Ruined","Common"
    {"Stealth", "Survival"}, {"One gaming set"}, {"One language"},
    {"Still Standing", "You gain the Alert, Skilled, or Tough feat."}});
  
  add({"Rune Carver","Common"
    {"History", "Perception"}, {"One artisan's tools"}, {"Giant"},
    {"Rune Shaper", "You gain the Rune Shaper feat."}}); // incredibly inventive name
  
  add({"Shipwright","Common"
    {"History", "Perception"}, {"Carpenter's tools"}, {},
    {"I'll Patch It!", "You can repair water vehicles with carpenter's tools."}});

  add({"Smuggler","Common"
    {"Athletics", "Deception"}, {}, {},
    {"Down Low", "You are connected with smugglers and you can stay in a safe house for free."}});
  
  add({"Spy","Common"
    {"Dception", "Stealth"}, {"Crowbar"}, {},
    {"Criminal Contact", "You have a connection to a network of other criminals."}});

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
