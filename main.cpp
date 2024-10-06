#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;

const int GHEIGHT = 10;
const int GWIDTH = 20;
const int FACTOR = 15;
const double SCALE_FACTOR = 0.6;

class Cell {
    private:
    bool cellType;
    vector<Cell*> links;

    public:
    Cell(bool x = false) {
        cellType = x;
    }
    
    char getChar() {
        return cellType ? '#' : '`';
    }

    void linkTo(Cell* link) {
        links.push_back(link);
    }

    bool type() {
        return cellType;
    }

};

class Grid {
    private:
    Cell* arr[GHEIGHT][GWIDTH];
    Cell* root;

    public:

    Grid() {
        for (int i = 0; i < GHEIGHT; i++) { for (int j = 0; j < GWIDTH; j++) {
            arr[i][j] = new Cell(false);
        }}
    }
    
    Cell* parent(int i, int j, int factor) {
        if (factor <= 0 || i < 0 || i >= GHEIGHT || j < 0 || j >= GWIDTH)
            return nullptr;
        arr[i][j] = create(arr[i][j], factor);
        if (!arr[i][j]->type()) return arr[i][j];
        changeNei(i, j, factor*SCALE_FACTOR);
        return arr[i][j];
    }

    void changeNei(int i, int j, int x) {
        if (i > 0) {
            parent(i-1, j, x);
        } if (i < GHEIGHT - 1) {
            parent(i+1, j, x);
        } if (j > 0) {
            parent(i, j-1, x);
        } if (j < GWIDTH) {
            parent(i, j+1, x);
        }
    }

    void rootCell(int i, int j) {
        arr[i][j] = new Cell(true);
        arr[i][j] = parent(i, j, FACTOR);
        root = arr[i][j];
    }

    Cell* create(Cell* cell, int factor) {
        if (cell->type()) return cell;
        if ((rand() % 10) + 1 < factor) {
            delete cell;
            return new Cell(true);
        }
        return cell;
    }

    bool isRoot(Cell* cell) {
        if (root == cell) return 1;
        return 0;
    }

    void print() {
        for (int i = 0; i < GHEIGHT; i++) {
            for (int j = 0; j < GWIDTH; j++) {
                // if (isRoot(arr[i][j])) cout << 'M';
                // else
                cout << arr[i][j]->getChar();
            } cout << endl;
        }
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0)));
    Grid g;

    g.rootCell(5, 9);


    g.print();


    return 0;
}