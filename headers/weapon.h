#ifndef WEAPON_H_INCLUDED
#define WEAPON_H_INCLUDED

// CLASSE REPRESENTANT UNE ARME (epee et armure)


class weapon
{
    public:
        virtual ~weapon()=default;
        virtual void use()=0;
        int getSolidity() const;
    private:
        int d_solidity;

};

#endif