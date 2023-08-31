#include <iostream>
#include <vector>

using namespace std;

const int SIZE = 3;

// Function to print the Tic Tac Toe board
void printBoard(const vector<vector<char>> &board) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cout << board[i][j] << "\t";
        }
        cout << endl;
    }
}

// Function to check if the game is over
bool isGameOver(const vector<vector<char>> &board) {
    // Check rows, columns, and diagonals
    for (int i = 0; i < SIZE; ++i) {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][0] == board[i][2])
            return true;
        
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[0][i] == board[2][i])
            return true;
    }
    
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[0][0] == board[2][2])
        return true;
    
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[0][2] == board[2][0])
        return true;
    
    // Check for a draw
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == ' ')
                return false;
        }
    }
    
    return true;
}

// Function to evaluate the current board state
int evaluateBoard(const vector<vector<char>> &board) {
    // Check rows, columns, and diagonals for a win
    for (int i = 0; i < SIZE; ++i) {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
            if (board[i][0] == 'X')
                return -10;
            else if (board[i][0] == 'O')
                return 10;
        }
        
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i]) {
            if (board[0][i] == 'X')
                return -10;
            else if (board[0][i] == 'O')
                return 10;
        }
    }
    
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
        if (board[0][0] == 'X')
            return -10;
        else if (board[0][0] == 'O')
            return 10;
    }
    
    if (board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
        if (board[0][2] == 'X')
            return -10;
        else if (board[0][2] == 'O')
            return 10;
    }
    
    // No winner, it's a draw
    return 0;
}

// Minimax function for finding the best move
int minimax(vector<vector<char>> &board, bool isMaximizer) {
    int score = evaluateBoard(board);
    
    if (score == 10)
        return score;
    
    if (score == -10)
        return score;
    
    if (isGameOver(board))
        return 0;
    
    if (isMaximizer) {
        int best = -1000;
        
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    best = max(best, minimax(board, !isMaximizer));
                    board[i][j] = ' ';
                }
            }
        }
        
        return best;
    } else {
        int best = 1000;
        
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    best = min(best, minimax(board, !isMaximizer));
                    board[i][j] = ' ';
                }
            }
        }
        
        return best;
    }
}

// Function to make the computer's move using the Minimax algorithm
void makeComputerMove(vector<vector<char>> &board) {
    int bestMove = -1;
    int bestScore = -1000;

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                int moveScore = minimax(board, false);
                board[i][j] = ' ';

                if (moveScore > bestScore) {
                    bestScore = moveScore;
                    bestMove = i * SIZE + j;
                }
            }
        }
    }

    int row = bestMove / SIZE;
    int col = bestMove % SIZE;
    board[row][col] = 'O';
}

int main() {
    vector<vector<char>> board(SIZE, vector<char>(SIZE, ' ')); // Initialize an empty board

    cout << "Welcome to Tic Tac Toe!" << endl;
    cout << "You are X and the computer is O." << endl;
    cout << "----------------------------------" << endl;

    while (!isGameOver(board)) {
        // Player's move
        int playerMove;
        cout << "Enter your move (1-9): ";
        cin >> playerMove;
        
        int row = (playerMove - 1) / SIZE;
        int col = (playerMove - 1) % SIZE;
        
        if (playerMove < 1 || playerMove > 9 || board[row][col] != ' ') {
            cout << "Invalid move. Try again." << endl;
            continue;
        }
        board[row][col] = 'X';

        printBoard(board);
        cout << "-------------------------" << endl;

        if (isGameOver(board)) {
            if (evaluateBoard(board) == 10)
                cout << "Computer wins!" << endl;
            else if (evaluateBoard(board) == -10)
                cout << "You win!" << endl;
            else
                cout << "It's a draw!" << endl;
            break;
        }

        // Computer's move
        makeComputerMove(board);

        printBoard(board);
        cout << "-------------------------" << endl;

        if (isGameOver(board)) {
            if (evaluateBoard(board) == 10)
                cout << "Computer wins!" << endl;
            else if (evaluateBoard(board) == -10)
                cout << "You win!" << endl;
            else
                cout << "It's a draw!" << endl;
            break;
        }
    }

    return 0;
}
