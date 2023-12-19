#ifndef POSITION_H_INCLUDED
#define POSITION_H_INCLUDED

class position
{
    public:
        position();
        position(int l,int c);
        position& operator=(const position& pos);
        bool operator==(const position& pos) const;
        int getLine() const;
        int getColumn() const;
        void setPosition(int line,int col);
    public:
        int d_line,d_column;
};


#endif