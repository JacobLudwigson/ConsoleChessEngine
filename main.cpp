#include <iostream>
#include <vector>

using namespace std;
struct ChessPiece {
    short id;
    pair <short,short> position;
    char chessPiece;
    char color;
};
typedef long long ll;
const int BOARDAREA = 64;
const int BOARDHEIGHT = 8;
const int BOARDWIDTH = 8;
ChessPiece* game[BOARDHEIGHT][BOARDWIDTH];



void printBoard(){
    for (int i = 0; i < BOARDHEIGHT; i++){
        cout << "-------------------------------------------------\n";
        for (int j = 0; j < BOARDWIDTH; j++){
            if (j == 0) {cout << "|";}
            cout << "  " << game[i][j]->chessPiece<<"  |";
        }
        cout << "\n";
        if(i == 7) {cout << "-------------------------------------------------\n";}
    }
}
void initBoard(){
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < BOARDWIDTH; j++){
            game[i][j] = new ChessPiece;
            game[i][j]->id = 0;
            game[i][j]->position = make_pair(i,j);        
            game[i][j]->chessPiece = ' ';
            game[i][j]->color = 'N';
        } 
    } 
    char color = 'W',piece;
    int j = 1, k;


    for(int i = 0; i < 16; i++){
        if (i == 8) {
            color = 'B';
            j = 6;
        }
        k = (i % 8); 
        game[j][k]->id = i;
        game[j][k]->position = make_pair(j,k);        
        game[j][k]->chessPiece = 'P';
        game[j][k]->color = color;
    }
    color = 'W';
    j = 0;
    for(int i = 16; i < 32; i++){
        if (i == 24) {
            color = 'B';
            j = 7;
        }
        k = (i % 8);
        if (k == 0 || k == 7) piece = 'R';
        if (k == 1 || k == 6) piece = 'N';
        if (k == 2 || k == 5) piece = 'B';
        if (k == 3) piece = 'Q';
        if (k == 4) piece = 'K';        
        game[j][k]->id = i;
        game[j][k]->position = make_pair(j,k);        
        game[j][k]->chessPiece = piece;
        game[j][k]->color = color;
    }
}

int main(){
    initBoard();
    printBoard();
}