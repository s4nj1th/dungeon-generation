#include "../include/Exporter.hpp"
#include "../include/Renderer.hpp"
#include <filesystem>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

void exportToFile(const Dungeon& dungeon) {
    filesystem::create_directory("outputs");
    auto now = chrono::system_clock::now();
    time_t t = chrono::system_clock::to_time_t(now);
    stringstream ss;
    ss << "outputs/" << put_time(localtime(&t), "%Y-%m-%d_%H-%M-%S") << ".txt";
    ofstream out(ss.str());

    const auto& grid = dungeon.getGrid();
    for (const auto& row : grid) {
        for (Tile t : row) {
            out << Renderer::rawTileChar(t);
        }
        out << '\n';
    }

    cout << "Exported to: " << ss.str() << endl;
}
