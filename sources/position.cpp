#include "position.h"

position::position(int l,int c):d_line{l},d_column{c}{}

position::position():d_line{0},d_column{0}{}

int position::getColumn() const
{
    return d_column;
}
int position::getLine() const
{
    return d_line;
}

void position::setPosition(int line,int col)
{
    d_line = line;
    d_column = col;
}

position& position::operator=(const position& pos)
{
    if (this != &pos)
    {
        d_line = pos.d_line;
        d_column = pos.d_column;
    }
    return *this;
}

bool position::operator==(const position& pos) const
{
    return (d_line == pos.d_line) && (d_column == pos.d_column);
}