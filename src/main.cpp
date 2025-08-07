#include "../include/Constants.hpp"
#include "../include/Dungeon.hpp"
#include "../include/Exporter.hpp"
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

void printHelp() {
  cout << "Usage: dun-gen [options]\n"
       << "Options:\n"
       << "  -w <width>      Set canvas width\n"
       << "  -h <height>     Set canvas height\n"
       << "  -min <size>     Minimum room size\n"
       << "  -max <size>     Maximum room size\n"
       << "  -r <count>      Maximum number of rooms\n"
       << "  --help          Show this help message\n";
}

int main(int argc, char *argv[]) {
  int width = DEFAULT_WIDTH;
  int height = DEFAULT_HEIGHT;
  int minRoom = DEFAULT_ROOM_MIN_SIZE;
  int maxRoom = DEFAULT_ROOM_MAX_SIZE;
  int maxRooms = DEFAULT_MAX_ROOMS;

  unordered_map<string, string> args;

  for (int i = 1; i < argc; ++i) {
    string key = argv[i];

    if (key == "--help") {
      printHelp();
      return 0;
    }

    if (!key.empty() && key[0] == '-') {
      if (i + 1 < argc) {
        string val = argv[i + 1];
        if (val.empty() || val[0] == '-') {
          cerr << "Missing value for " << key << "\n";
          return 1;
        }
        args[key] = val;
        ++i;
      } else {
        cerr << "Missing value for " << key << "\n";
        return 1;
      }
    }
  }

  if (args.count("-w"))
    width = stoi(args["-w"]);
  if (args.count("-h"))
    height = stoi(args["-h"]);
  if (args.count("-min"))
    minRoom = stoi(args["-min"]);
  if (args.count("-max"))
    maxRoom = stoi(args["-max"]);
  if (args.count("-r"))
    maxRooms = stoi(args["-r"]);

  Dungeon dungeon(width, height, minRoom, maxRoom, maxRooms);
  dungeon.generate();
  dungeon.print();
  exportToFile(dungeon);

  return 0;
}
