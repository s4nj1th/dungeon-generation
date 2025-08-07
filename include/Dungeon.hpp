#pragma once
#include <vector>
#include <string>
#include "Tile.hpp"
#include "Room.hpp"

using namespace std;

class Dungeon {
public:
    Dungeon(int w, int h, int minRoom, int maxRoom, int maxRooms);
    void generate();
    void print() const;
    const vector<vector<Tile>>& getGrid() const;
    static string renderTile(Tile t);
    static char rawTileChar(Tile t);

private:
    int width, height;
    int roomMinSize, roomMaxSize, maxRooms;
    vector<vector<Tile>> grid;
    vector<Room> rooms;
    bool inBounds(int y, int x);
    void drawRoom(const Room& room);
    void drawCorridor(int x1, int y1, int x2, int y2);
    void placeCorridorTile(int x, int y);
};
