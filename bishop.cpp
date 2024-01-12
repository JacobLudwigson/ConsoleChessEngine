#include <iostream>
#include <bitset>
#include <cstdint>

using namespace std;
void printBitboard(uint64_t bitboard) {
    for (int rank = 0; rank <= 7; ++rank) {
        for (int file = 0; file < 8; ++file) {
            int index = (rank << 3) + file;
            cout << ((bitboard & (1ULL << index)) ? 1 : 0) << " ";
        }
        cout << endl;
    }
}

bool isValidSquare(int square) {
    return square >= 0 && square < 64;
}

uint64_t generateBishopMoves(uint64_t bitboard, int bishopSquare) {
    uint64_t moves = 0;

    // Diagonal moves
    for (int i = 1; i < 8; ++i) {
        int possibleSquare;
        //The bishop can move up right, up left, down right, down left: meaning we can populate a bitboard of its possible moves using a loop
        //In this loop we can check at each index diagonal to the source moving outwards (bishopSquare) if the move is valid
        //Each possible square is calculated by moving a rank up (+/- i*8)(which is optimized to a logical right by 3) and a rank sideways (+/- i) from the source (bishopSquare)
        //In each if we check if the square is on the board by calling isValidSquare and then we check that it is indeed either to the down right, down left, up left, or up right of the source
        //We do this using a modulo operation with the possible square and the bishop square (%8) since there are 8 files we just need to check that the desired square is in the desired direction
        //The modulo 8 was able to be optimized to a AND 7 since 8 is a power of 2, we are able to just mask the upper bits
        //The reason we need to check the squares generated are in the correct direction with && (possibleSquare & 7) > (bishopSquare & 7) a comparison like this is because
        //as i gets large, the possible square calculations possibleSquare = bishopSquare - (i << 3) + i; that involve subtraction get weird since if we take square 22 for example, 
        //on the 3rd iteration of our loop, we get possiblesquare = 22 - 24 + 3 = 1. Even though square one is NOT diagonal to square 22. Thus we need the Modulo comparison
        // Down-right
        possibleSquare = bishopSquare + (i << 3) + i;
        if (isValidSquare(possibleSquare) && (possibleSquare & 7) > (bishopSquare & 7)) {
            moves |= 1ULL << possibleSquare;
        }

        // Down-left

        possibleSquare = bishopSquare + (i << 3) - i;
        if (isValidSquare(possibleSquare) && (possibleSquare & 7) < (bishopSquare & 7)) {
            moves |= 1ULL << possibleSquare;
        }

        // Up-right
        possibleSquare = bishopSquare - (i << 3) + i;
        if (isValidSquare(possibleSquare) && (possibleSquare & 7) > (bishopSquare & 7)) {
            moves |= 1ULL << possibleSquare;
        }

        // Up-left
        possibleSquare = bishopSquare - (i << 3) - i;
        if (isValidSquare(possibleSquare) && (possibleSquare & 7) < (bishopSquare & 7)) {
            moves |= 1ULL << possibleSquare;
        }
    }

    return moves;
}

int main() {
    uint64_t bitmapBM = 0x0000000000000042ULL;  // Centered at 34th

    cout << "Initial Bitboard:" << endl;
    printBitboard(bitmapBM);

    int bishopSquare = 22;
    bitmapBM = generateBishopMoves(bitmapBM, bishopSquare);

    cout << "\nPossible moves for bishop centered at square " << bishopSquare << ":" << endl;
    
    printBitboard(bitmapBM);

    cout << "\nPossible moves for bishop centered at square " << bitset<64>(bitmapBM) << ":" << endl;

    return 0;
}
