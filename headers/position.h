#ifndef POSITION_H_INCLUDED
#define POSITION_H_INCLUDED

class position
{
    public:
        position();
        position(int l,int c);
        int getLine() const;
        int getColumn() const;
    private:
        int d_line,d_column;
};


#endif