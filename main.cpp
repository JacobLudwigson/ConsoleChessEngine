#include <iostream>
#include <windows.h>
#include <vector>

using namespace std;
int pawn = 1, knight = 2, bishop = 3, rook = 4, queen = 5, king = 6, none = 0;
char pieces[7] = {' ','P', 'N', 'B', 'R', 'Q', 'K'};
bool white = 0, black = 1;
struct pos{
    unsigned int x : 3;
    unsigned int y : 3;
};
struct ChessPiece{
    unsigned int pieceType : 3;
    unsigned int x : 3;
    unsigned int y : 3;
    bool color;
    bool castlingRightsFlag = TRUE;
    bool hasMovedFlag = FALSE;
    bool free;
};

struct moves {
    unsigned int x : 3;
    unsigned int y : 3;
    bool attack;
};
typedef long long ll;
const short int BOARDAREA = 64;
const short int BOARDHEIGHT = 8;
const short int BOARDWIDTH = 8;
ChessPiece* game[BOARDHEIGHT][BOARDWIDTH];

void printBoard(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < BOARDHEIGHT; i++){
        cout << "-------------------------------------------------\n";
        for (int j = 0; j < BOARDWIDTH; j++){
            if (j == 0) {cout << "|";}
            if ((j+i) % 2 == 0){SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_INTENSITY);}
            else {SetConsoleTextAttribute(hConsole, 0x8080 | FOREGROUND_INTENSITY);}
            cout << "  ";
            if (game[i][j]->color == 'B'){
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            }
            else if (game[i][j]->color == 'W') {
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            }
            cout << pieces[game[i][j]->pieceType];
            if ((j+i) % 2 == 0){SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_INTENSITY);}
            else {SetConsoleTextAttribute(hConsole, 0x8080 | FOREGROUND_INTENSITY);}
            cout <<"  ";
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
            cout << "|";
        }
        cout << "\n";
        if(i == 7) {cout << "-------------------------------------------------\n";}
    }
}
void initBoard(){
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            game[i][j] = new ChessPiece;
            game[i][j]->x = i;
            game[i][j]->y = j;      
            game[i][j]->pieceType = none;
            game[i][j]->color = white;
        } 
    } 
    char color = white,piece;
    int j = 1, k;


    for(int i = 0; i < 16; i++){
        if (i == 8) {
            color = black;
            j = 6;
        }
        k = (i % 8); 
        game[j][k]->x = j;
        game[j][k]->y = k;     
        game[j][k]->pieceType = pawn;
        game[j][k]->color = color;
    }
    color = white;
    j = 0;
    for(int i = 16; i < 32; i++){
        if (i == 24) {
            color = black;
            j = 7;
        }
        k = (i % 8);
        if (k == 0 || k == 7) piece = rook;
        if (k == 1 || k == 6) piece = knight;
        if (k == 2 || k == 5) piece = bishop;
        if (k == 3) piece = queen;
        if (k == 4) piece = king;        
        game[j][k]->x = j;
        game[j][k]->y = k;      
        game[j][k]->pieceType = piece;
        game[j][k]->color = color;
    }
}

pos chessNotCordsConvert(string chessMove){
    pos temp;
    temp.x = chessMove[1];
    temp.y = (chessMove[0]-96);
    return temp;
}
bool isValidMove(ChessPiece piece, moves move){

}
vector<moves> genMoves(ChessPiece piece){
    vector<moves> moveArr;
    moves move;
    int srcx = piece.x;
    int srcy = piece.y;
    short mov = piece.color == white ? 1 : -1;
    bool oneSrcYp = (srcy + 1 <= 7);
    bool oneSrcym = (srcy - 1 >= 0);
    bool oneSrcXp = (srcx + 1 <= 7);
    bool oneSrcXm = (srcx - 1 >= 0);
    switch(piece.pieceType){
        
        case 0: //nothing
            return {};
            break;
        case 1: //pawn
            if(piece.hasMovedFlag){ //pawn has moved
                //Check if the pawn can move forward one rank
                move.x = srcx + mov;
                move.y = srcy;
                if (game[move.x][move.y]->pieceType == 0)moveArr.push_back(move);
                //Check if pawn can capture left or right
                if (game[srcx+mov][srcy+mov]->pieceType != 0 && game[srcx+mov][srcy+mov]->color != piece.color)moveArr.push_back(move);
                if (game[srcx+mov][srcy-mov]->pieceType != 0 && game[srcx+mov][srcy-mov]->color != piece.color)moveArr.push_back(move);
            }
            else {
                move.x = srcx + mov;
                move.y = srcy;
                if (game[move.x][move.y]->pieceType == 0){
                    moveArr.push_back(move);
                    move.x += mov;
                    if (game[move.x][move.y]->pieceType == 0) moveArr.push_back(move);
                }
                if (game[srcx+mov][srcy+mov]->pieceType != 0 && game[srcx+mov][srcy+mov]->color != piece.color)moveArr.push_back(move);
                if (game[srcx+mov][srcy-mov]->pieceType != 0 && game[srcx+mov][srcy-mov]->color != piece.color)moveArr.push_back(move);
            }
            break;
        case 2: //knight
            if(srcx+2 <= 7){
                move.attack = 0;
                if (oneSrcym){
                    move.x = srcx + 2;
                    move.y = srcy + 1;
                    if (game[srcx+2][srcy+1]->pieceType != 0 && game[srcx+2][srcy+1]->color != piece.color){
                        move.attack = 1;
                        moveArr.push_back(move);                        
                    }
                    if (game[srcx+2][srcy+1]->pieceType == 0)moveArr.push_back(move);
                }
                move.attack = 0;
                if (oneSrcYp){
                    move.x = srcx + 2;
                    move.y = srcy - 1;
                    if (game[srcx+2][srcy-1]->pieceType != 0 && game[srcx+2][srcy-1]->color != piece.color){
                        move.attack = 1;
                        moveArr.push_back(move);                        
                    }
                    if (game[srcx+2][srcy-1]->pieceType == 0)moveArr.push_back(move);
                }
            }
            if(srcx-2 >= 0 ){
                move.attack = 0;
                if (oneSrcym){
                    move.x = srcx - 2;
                    move.y = srcy + 1;
                    if (game[srcx-2][srcy+1]->pieceType != 0 && game[srcx-2][srcy+1]->color != piece.color){
                        move.attack = 1;
                        moveArr.push_back(move);                        
                    }
                    if (game[srcx-2][srcy+1]->pieceType == 0)moveArr.push_back(move);
                }
                move.attack = 0;
                if (oneSrcYp){
                    move.x = srcx - 2;
                    move.y = srcy - 1;
                    if (game[srcx-2][srcy-1]->pieceType != 0 && game[srcx-2][srcy-1]->color != piece.color){
                        move.attack = 1;
                        moveArr.push_back(move);                         
                    }
                    if (game[srcx-2][srcy-1]->pieceType == 0)moveArr.push_back(move);
                }
            }
            if(srcy+2 >= 0 ){
                move.attack = 0;
                if (oneSrcXm){
                    move.x = srcx - 1;
                    move.y = srcy + 2;
                    if (game[srcx-1][srcy+2]->pieceType != 0 && game[srcx-1][srcy+2]->color != piece.color){
                        move.attack = 1;
                        moveArr.push_back(move);                        
                    }
                    if (game[srcx-1][srcy+2]->pieceType == 0)moveArr.push_back(move);
                }
                move.attack = 0;
                if (oneSrcXp){
                    move.x = srcx + 1;
                    move.y = srcy + 2;
                    if (game[srcx+1][srcy+2]->pieceType != 0 && game[srcx+1][srcy+2]->color != piece.color){
                        move.attack = 1;
                        moveArr.push_back(move);                        
                    }
                    if (game[srcx+1][srcy+2]->pieceType == 0)moveArr.push_back(move);
                }
            }
            
            if(srcy-2 >= 0 ){
                move.attack = 0;
                if (oneSrcXm){
                    move.x = srcx - 2;
                    move.y = srcy - 1;
                    if (game[srcx-1][srcy-2]->pieceType != 0 && game[srcx-1][srcy-2]->color != piece.color){
                        move.attack = 1;
                        moveArr.push_back(move);
                    }
                    if (game[srcx-1][srcy-2]->pieceType == 0)moveArr.push_back(move);
                }
                move.attack = 0;
                if (oneSrcXp){
                    move.x = srcx - 2;
                    move.y = srcy + 1;
                    if (game[srcx+1][srcy-2]->pieceType != 0 && game[srcx+1][srcy-2]->color != piece.color){
                        move.attack = 1;
                        moveArr.push_back(move);
                    }
                    if (game[srcx+1][srcy-2]->pieceType == 0)moveArr.push_back(move);
                }
            }
            break;
        case 3: //bishop
            move.attack = 0;
            for (int i = 0; i < 8; i++){
                move.x = srcx+i;
                move.y = srcy+i;
                if (srcx + i> 7 || srcy + i > 7)break;
                if (game[srcx+i][srcy+i]->pieceType != 0 && game[srcx+i][srcy+i]->color != piece.color){
                    move.attack = 1;
                    moveArr.push_back(move);
                    break;
                }
                if (game[srcx+i][srcy+i]->pieceType == 0)moveArr.push_back(move);
            }
            move.attack = 0;
            for (int i = 0; i < 8; i++){
                move.x = srcx+i;
                move.y = srcy-i;
                if (srcx + i > 7 || srcy - i < 0)break;
                if (game[srcx+i][srcy-i]->pieceType != 0 && game[srcx+i][srcy-i]->color != piece.color){
                    move.attack = 1;
                    moveArr.push_back(move);
                    break;
                }
                if (game[srcx+i][srcy-i]->pieceType == 0)moveArr.push_back(move);
                
            }
            move.attack = 0;
            for (int i = 0; i < 8; i++){
                move.x = srcx-i;
                move.y = srcy-i;
                if (srcx - i < 0 || srcy - i < 0)break;
                if (game[srcx-i][srcy-i]->pieceType != 0 && game[srcx-i][srcy-i]->color != piece.color){
                    move.attack = 1;
                    moveArr.push_back(move);
                    break;
                }
                if (game[srcx-i][srcy-i]->pieceType == 0)moveArr.push_back(move);
                
            }
            move.attack = 0;
            for (int i = 0; i < 8; i++){
                move.x = srcx-i;
                move.y = srcy+i;
                if (srcx - i < 0 || srcy + i > 7)break;
                if (game[srcx-i][srcy+i]->pieceType != 0 && game[srcx-i][srcy+i]->color != piece.color){
                    move.attack = 1;
                    moveArr.push_back(move);
                    break;
                }
                if (game[srcx-i][srcy+i]->pieceType == 0)moveArr.push_back(move);
            }
            break;
        case 4: //rook
            if(!piece.hasMovedFlag){ //rook has not moved
                //castle
            }
            move.attack = 0;
            for (int i = 0; i < 8; i++){
                move.x = srcx;
                move.y = srcy + i;
                if (srcy + i > 7)break;
                if (game[srcx][srcy+i]->pieceType != 0 && game[srcx][srcy+i]->color != piece.color){
                    move.attack = 1;
                    moveArr.push_back(move);
                    break;
                }
                if (game[srcx][srcy+i]->pieceType == 0)moveArr.push_back(move);
            }
            move.attack = 0;
            for (int i = 0; i < 8; i++){
                move.x = srcx;
                move.y = srcy - i;
                if (srcy - i < 0)break;
                if (game[srcx][srcy-i]->pieceType != 0 && game[srcx][srcy-i]->color != piece.color){
                    move.attack = 1;
                    moveArr.push_back(move);
                    break;
                }
                if (game[srcx][srcy-i]->pieceType == 0)moveArr.push_back(move);
            }
            move.attack = 0;
            for (int i = 0; i < 8; i++){
                move.x = srcx + i;
                move.y = srcy;
                if (srcx + i > 7)break;
                if (game[srcx+i][srcy]->pieceType != 0 && game[srcx+i][srcy]->color != piece.color){
                    move.attack = 1;
                    moveArr.push_back(move);
                    break;
                }
                if (game[srcx+i][srcy]->pieceType == 0)moveArr.push_back(move);
            }
            move.attack = 0;
            for (int i = 0; i < 8; i++){
                move.x = srcx - i;
                move.y = srcy;
                if (srcx - i < 0)break;
                if (game[srcx-i][srcy]->pieceType != 0 && game[srcx-i][srcy]->color != piece.color){
                    move.attack = 1;
                    moveArr.push_back(move);
                    break;
                }
                if (game[srcx-i][srcy]->pieceType == 0)moveArr.push_back(move);
            }
            break;
        case 5: //queen
            move.attack = 0;
            for (int i = 0; i < 8; i++){
                move.x = srcx;
                move.y = srcy + i;
                if (srcy + i > 7)break;
                if (game[srcx][srcy+i]->pieceType != 0 && game[srcx][srcy+i]->color != piece.color){
                    move.attack = 1;
                    moveArr.push_back(move);
                    break;
                }
                if (game[srcx][srcy+i]->pieceType != 0 && game[srcx][srcy+i]->color == piece.color){
                    break;
                }
                if (game[srcx][srcy+i]->pieceType == 0)moveArr.push_back(move);
            }
            move.attack = 0;
            for (int i = 0; i < 8; i++){
                move.x = srcx;
                move.y = srcy - i;
                if (srcy - i < 0)break;
                if (game[srcx][srcy-i]->pieceType != 0 && game[srcx][srcy-i]->color != piece.color){
                    move.attack = 1;
                    moveArr.push_back(move);
                    break;
                }
                if (game[srcx][srcy-i]->pieceType != 0 && game[srcx][srcy-i]->color == piece.color){
                    break;
                }
                if (game[srcx][srcy-i]->pieceType == 0)moveArr.push_back(move);
            }
            move.attack = 0;
            for (int i = 0; i < 8; i++){
                move.x = srcx + i;
                move.y = srcy;
                if (srcx + i > 7)break;
                if (game[srcx+i][srcy]->pieceType != 0 && game[srcx+i][srcy]->color != piece.color){
                    move.attack = 1;
                    moveArr.push_back(move);
                    break;
                }
                if (game[srcx+i][srcy]->pieceType != 0 && game[srcx+i][srcy]->color == piece.color){
                    break;
                }
                if (game[srcx+i][srcy]->pieceType == 0)moveArr.push_back(move);
            }
            move.attack = 0;
            for (int i = 0; i < 8; i++){
                move.x = srcx - i;
                move.y = srcy;
                if (srcx - i < 0)break;
                if (game[srcx-i][srcy]->pieceType != 0 && game[srcx-i][srcy]->color != piece.color){
                    move.attack = 1;
                    moveArr.push_back(move);
                    break;
                }
                if (game[srcx-i][srcy]->pieceType != 0 && game[srcx-i][srcy]->color == piece.color){
                    break;
                }
                if (game[srcx-i][srcy]->pieceType == 0)moveArr.push_back(move);
            }
            move.attack = 0;
            for (int i = 0; i < 8; i++){
                move.x = srcx+i;
                move.y = srcy+i;
                if (srcx + i> 7 || srcy + i > 7)break;
                if (game[srcx+i][srcy+i]->pieceType != 0 && game[srcx+i][srcy+i]->color != piece.color){
                    move.attack = 1;
                    moveArr.push_back(move);
                    break;
                }
                if (game[srcx+i][srcy+i]->pieceType != 0 && game[srcx+i][srcy+i]->color == piece.color){
                    break;
                }
                if (game[srcx+i][srcy+i]->pieceType == 0)moveArr.push_back(move);
            }
            move.attack = 0;
            for (int i = 0; i < 8; i++){
                move.x = srcx+i;
                move.y = srcy-i;
                if (srcx + i > 7 || srcy - i < 0)break;
                if (game[srcx+i][srcy-i]->pieceType != 0 && game[srcx+i][srcy-i]->color != piece.color){
                    move.attack = 1;
                    moveArr.push_back(move);
                    break;
                }
                if (game[srcx+i][srcy-i]->pieceType != 0 && game[srcx+i][srcy-i]->color == piece.color){
                    break;
                }
                if (game[srcx+i][srcy-i]->pieceType == 0)moveArr.push_back(move);
                
            }
            move.attack = 0;
            for (int i = 0; i < 8; i++){
                move.x = srcx-i;
                move.y = srcy-i;
                if (srcx - i < 0 || srcy - i < 0)break;
                if (game[srcx-i][srcy-i]->pieceType != 0 && game[srcx-i][srcy-i]->color != piece.color){
                    move.attack = 1;
                    moveArr.push_back(move);
                    break;
                }
                if (game[srcx-i][srcy-i]->pieceType != 0 && game[srcx-i][srcy-i]->color == piece.color){
                    break;
                }
                if (game[srcx-i][srcy-i]->pieceType == 0)moveArr.push_back(move);
                
            }
            move.attack = 0;
            for (int i = 0; i < 8; i++){
               
                move.x = srcx-i;
                move.y = srcy+i;
                if (srcx - i < 0 || srcy + i > 7)break;
                if (game[srcx-i][srcy+i]->pieceType != 0 && game[srcx-i][srcy+i]->color != piece.color){
                    move.attack = 1;
                    moveArr.push_back(move);
                    break;
                }
                if (game[srcx-i][srcy+i]->pieceType != 0 && game[srcx-i][srcy+i]->color == piece.color){
                    break;
                }
                if (game[srcx-i][srcy+i]->pieceType == 0)moveArr.push_back(move);
            }
            break;
        case 6: //king
            if(piece.hasMovedFlag){ //king has moved
                // move.x = piece.x + 1;
                // move.y = piece.y;
                // if (move.valid = (isValidMove(piece, move))) moveArr.push_back(move);
                // move.x = piece.x - 1;
                // if (move.valid = (isValidMove(piece, move))) moveArr.push_back(move);
                // move.y = piece.y + 1;
                // if (move.valid = (isValidMove(piece, move))) moveArr.push_back(move);
                // move.x = piece.x + 1;
                // if (move.valid = (isValidMove(piece, move))) moveArr.push_back(move);
                // move.y = piece.y - 1;
                // if (move.valid = (isValidMove(piece, move))) moveArr.push_back(move);
                // move.x = piece.x - 1;
                // if (move.valid = (isValidMove(piece, move))) moveArr.push_back(move);
                // move.x = piece.x;
                // if (move.valid = (isValidMove(piece, move))) moveArr.push_back(move);
                // move.y = piece.y + 1;
                // if (move.valid = (isValidMove(piece, move))) moveArr.push_back(move);
            }
            else {

            }
            break;
        default:
            return {};
            break;
    }
    return moveArr;
}


int main(){
    initBoard();
    printBoard();
    vector<moves>QueenMoves = genMoves(*game[7][3]);
    for (auto it : QueenMoves){
        cout << "Can Move to: " << it.x << ", " << it.y << endl;
    } 
    for (int i = 0; i < BOARDHEIGHT; i++){
        for (int j = 0; j < BOARDWIDTH; j++){
            delete game[i][j];
        } 
    } 
}