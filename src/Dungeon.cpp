#include "../include/Dungeon.hpp"
#include "../include/Renderer.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

Dungeon::Dungeon(int w, int h, int minRoom, int maxRoom, int maxR)
    : width(w), height(h),
      roomMinSize(minRoom), roomMaxSize(maxRoom), maxRooms(maxR),
      grid(h, vector<Tile>(w, EMPTY)) {}


bool Dungeon::inBounds(int y, int x) {
    return x >= 0 && x < width && y >= 0 && y < height;
}

void Dungeon::drawRoom(const Room& room) {
    for (int y = room.y; y < room.y + room.height; ++y) {
        for (int x = room.x; x < room.x + room.width; ++x) {
            if (y == room.y || y == room.y + room.height - 1 ||
                x == room.x || x == room.x + room.width - 1) {
                grid[y][x] = WALL;
            } else {
                grid[y][x] = ROOM;
            }
        }
    }
}

void Dungeon::placeCorridorTile(int x, int y) {
    if (!inBounds(y, x)) return;
    grid[y][x] = CORRIDOR;
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            int nx = x + dx;
            int ny = y + dy;
            if (!inBounds(ny, nx)) continue;
            if (grid[ny][nx] == EMPTY) {
                grid[ny][nx] = WALL;
            }
        }
    }
}

void Dungeon::drawCorridor(int x1, int y1, int x2, int y2) {
    for (int x = min(x1, x2); x <= max(x1, x2); ++x)
        placeCorridorTile(x, y1);
    for (int y = min(y1, y2); y <= max(y1, y2); ++y)
        placeCorridorTile(x2, y);
}

void Dungeon::generate() {
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < maxRooms; ++i) {
        int w = roomMinSize + rand() % (roomMaxSize - roomMinSize + 1);
        int h = roomMinSize + rand() % (roomMaxSize - roomMinSize + 1);
        int x = rand() % (width - w - 1);
        int y = rand() % (height - h - 1);

        Room newRoom{x, y, w, h};
        bool failed = false;

        for (const auto& room : rooms) {
            if (newRoom.intersects(room)) {
                failed = true;
                break;
            }
        }

        if (!failed) {
            drawRoom(newRoom);

            int area = w * h;
            int numEnemies = max(1, area / 20);
            int numChests  = max(1, area / 30);

            for (int e = 0; e < numEnemies; ++e) {
                int ex = x + 1 + rand() % (w - 2);
                int ey = y + 1 + rand() % (h - 2);
                if (grid[ey][ex] == ROOM) grid[ey][ex] = ENEMY;
            }

            for (int c = 0; c < numChests; ++c) {
                int cx = x + 1 + rand() % (w - 2);
                int cy = y + 1 + rand() % (h - 2);
                if (grid[cy][cx] == ROOM) grid[cy][cx] = CHEST;
            }

            if (!rooms.empty()) {
                auto [px, py] = rooms.back().center();
                auto [nx, ny] = newRoom.center();
                drawCorridor(px, py, nx, ny);
            }

            rooms.push_back(newRoom);
        }
    }
}

void Dungeon::print() const {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            cout << Renderer::renderTile(grid[y][x]);
        }
        cout << '\n';
    }
}

const vector<vector<Tile>>& Dungeon::getGrid() const {
    return grid;
}
