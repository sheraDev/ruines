#ifndef WEAPON_H_INCLUDED
#define WEAPON_H_INCLUDED



class weapon
{
    public:
        virtual ~weapon()=default;
        weapon(double solidite);
        double getSolidity() const;
        void setSolidity(double nouvforce);
        void addToSolidity(double f);
    private:
        double d_solidity;

};

#endif