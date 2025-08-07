#include "../include/Renderer.hpp"
#include "../include/Constants.hpp"

using namespace std;

string Renderer::renderTile(Tile t) {
    switch (t) {
        case WALL:     return string(GRAY)   + '#' + RESET;
        case ROOM:
        case CORRIDOR:
        case EMPTY:    return " ";
        case ENEMY:    return string(RED)    + 'X' + RESET;
        case CHEST:    return string(YELLOW) + '$' + RESET;
        default:       return " ";
    }
}

char Renderer::rawTileChar(Tile t) {
    switch (t) {
        case WALL:     return '#';
        case ENEMY:    return 'E';
        case CHEST:    return 'C';
        default:       return ' ';
    }
}
