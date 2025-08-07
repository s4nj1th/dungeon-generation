#pragma once
#include <utility>

using namespace std;

struct Room {
    int x, y, width, height;

    bool intersects(const Room& other) const {
        return (x < other.x + other.width && x + width > other.x &&
                y < other.y + other.height && y + height > other.y);
    }

    pair<int, int> center() const {
        return {x + width / 2, y + height / 2};
    }
};
