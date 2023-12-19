#ifndef WEAPON_H_INCLUDED
#define WEAPON_H_INCLUDED

// CLASSE REPRESENTANT UNE ARME (epee et armure)


class weapon
{
    public:
        virtual ~weapon()=default;
        weapon(double solidite);
        double getSolidity() const;
        void setSolidity(double nouvforce);
    private:
        double d_solidity;

};

#endif