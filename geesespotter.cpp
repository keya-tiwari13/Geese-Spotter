#include "geesespotter_lib.h"
#include <iostream>

char *createBoard(std::size_t xdim, std::size_t ydim) {
    
    char * board{ new char[xdim * ydim]};
    for (int k{0}; k <= ((xdim * ydim) - 1); ++k) {
        board[k] = 0;
    }
    return board;
}

void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim) {

    int position{};
    for (int i{}; i< xdim*ydim; i++) {
        if (board[i] == 9) {
            for (int k{-1}; k <= 1; ++k) {
                for ( int n{-1}; n <= 1; ++ n) {
                    position = i + (xdim*k + n);

                    int xloc = (i%xdim);
                    int yloc = (i/xdim);

                    if ( xloc + n >= 0 && xloc + n < xdim) {

                        if ( yloc + k >= 0 && yloc + k < ydim) {
                            
                            if ( board[position] != 9) {
                                board[position] += 1;
                            }
                        }
                    }
                }
            }

        }
    }
}

void hideBoard(char *board, std::size_t xdim, std::size_t ydim) {

    for (int i{0}; i <= ((xdim * ydim) - 1); ++i) {
        board[i] ^= hiddenBit();

    }

}

void cleanBoard(char *board) {

    delete[] board;
    board = nullptr;
}

void printBoard( char *board, std::size_t xdim, std::size_t ydim) {

    for (int i{0}; i < ydim; ++i) {
        for (int k{0}; k < xdim; ++k) {
            if (board[(i*xdim) + k] & markedBit()) {
                std::cout << "M";
            } else if (board[(i*xdim) + k] & hiddenBit()){
                std::cout << "*";
            } else {
                board[(i*xdim) + k] += 48;
                std::cout << board[(i*xdim) + k];
                board[(i*xdim) + k] -= 48;
            }
        }
        std::cout << std::endl;
    }

}

int reveal(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc) {

    int element = ((yloc*xdim) + xloc);

    if (board[element] & markedBit()) {
        return 1;

    } else if (!(board[element] & hiddenBit())) {
        return 2;

    } else if ((valueMask() & board[element]) == 9) {
        board[element] = board[element]&~ hiddenBit();
        return 9;
    } else {
        board[element] &= valueMask();
        if (board[element] == 0) {

            for (int k{-1}; k <= 1; ++k) {
                for ( int n{-1}; n <= 1; ++ n) {
                    int position = element + (xdim*k + n);

                    int xloc = (element%xdim);
                    int yloc = (element/xdim);

                    if ( xloc + n >= 0 && xloc + n < xdim) {

                        if ( yloc + k >= 0 && yloc + k < ydim) {
                            
                            board[position] &= valueMask();
                        }
                    }
                }
            }
            
        }
        return 0;
    }
    
    
}

int mark( char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc) {
    
    int element = ((yloc*xdim) + xloc); 

    // checks if the element is hidden
    if (board[element] & hiddenBit()) {
        board[element] ^= markedBit();
        return 0;
    } else {
        return 2;
    }


}

bool isGameWon(char *board, std::size_t xdim, std::size_t ydim) {

    for (int i{}; i < xdim*ydim; ++i) {

        if ( (board[i] & hiddenBit()) && ((valueMask() & board[i]) != 9) ) {
            return false;
        }
    }
    return true;

}

