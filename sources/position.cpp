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