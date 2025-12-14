#include <iostream>

struct Cell
{
    Cell* pointer_to_last;
    int value;

    Cell(int value, Cell *pointer) : value(value), pointer_to_last(pointer) {

        };
};

struct LinkedTree
{
    Cell* ptr = nullptr;
    int size;

    void push(int value)
    {
        Cell cell = new Cell(value, ptr);
        size++;
        ptr = *cell;
    }
}

