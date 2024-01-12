#include <iostream>
#include <bitset>
using namespace std;
typedef unsigned long long ll;
class Bitboards{
    private:
        ll pawnMovement;
        ll knightMovement;
        ll bishopMovement;
        ll rookMovement;
        ll queenMovement;
        ll kingMovement;

        const int center;
        bool bitmapNM[64] ={0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , //Centered at 34th bit
                            0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
                            0 ,0 ,1 ,0 ,1 ,0 ,0 ,0 ,
                            0 ,1 ,0 ,0 ,0 ,1 ,0 ,0 ,
                            0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
                            0 ,1 ,0 ,0 ,0 ,1 ,0 ,0 ,
                            0 ,0 ,1 ,0 ,1 ,0 ,0 ,0 ,
                            0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,};


        bool bitmapPM[64] ={0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , //Cented at 34th
                            0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
                            0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,
                            0 ,0 ,1 ,1 ,1 ,0 ,0 ,0 ,
                            0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
                            0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
                            0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
                            0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,};


        bool bitmapKM[64] ={0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , //Cented at 34th
                            0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
                            0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
                            0 ,0 ,1 ,1 ,1 ,0 ,0 ,0 ,
                            0 ,0 ,1 ,0 ,1 ,0 ,0 ,0 ,
                            0 ,0 ,1 ,1 ,1 ,0 ,0 ,0 ,
                            0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
                            0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,};
        
    public:
        ll getKnightMoves(int centerBit){
            if (centerBit > center){
                return knightMovement >> (centerBit - center);
            }
            else if (centerBit < center){
                return knightMovement << (center - centerBit);
            }
        }
};

