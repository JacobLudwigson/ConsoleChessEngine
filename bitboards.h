#include <iostream>

using namespace std;
typedef unsigned long long ll;
class Bitboards{
    private:
        ll pawnMovement;
        ll knightMovement;
        ll kingMovement;
        ll bishopMovement;
        ll rookMovement;
        ll queenMovement;
        ll kingMovement;
        bool bitmapPM[64] ={0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , //Cented at
                            0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
                            0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
                            0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
                            0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
                            1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
                            1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
                            1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,};
        bool bitmapKM[64] ={0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , //Centered at 34th bit
                            0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
                            0 ,0 ,1 ,0 ,1 ,0 ,0 ,0 ,
                            0 ,1 ,0 ,0 ,0 ,1 ,0 ,0 ,
                            0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
                            0 ,1 ,0 ,0 ,0 ,1 ,0 ,0 ,
                            0 ,0 ,1 ,0 ,1 ,0 ,0 ,0 ,
                            0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,};

    public:

};

