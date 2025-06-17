#include <iostream>
using namespace std;

// Game board
char board[3][3];

// Player markers
char player1_marker;
char player2_marker;
char current_marker;
int current_player;

// Draw the board
void drawBoard() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << "\n";
        if (i < 2) cout << "-----------\n";
    }
    cout << "\n";
}

// Place marker on board
bool placeMarker(int slot) {
    int row = (slot - 1) / 3;
    int col = (slot - 1) % 3;

    if (board[row][col] != '1' + (slot - 1)) {
        return false; // Slot already taken
    }

    board[row][col] = current_marker;
    return true;
}

// Check for a winner
int winner() {
    // Rows and Columns
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == board[i][1] && board[i][1] == board[i][2]) ||
            (board[0][i] == board[1][i] && board[1][i] == board[2][i])) {
            return current_player;
        }
    }

    // Diagonals
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2]) ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0])) {
        return current_player;
    }

    return 0; // No winner yet
}

// Swap player and marker
void swap_player_and_marker() {
    if (current_player == 1) {
        current_player = 2;
        current_marker = player2_marker;
    } else {
        current_player = 1;
        current_marker = player1_marker;
    }
}

// Game loop
void game() {
    // Initialize board with numbers 1–9
    char num = '1';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = num++;
        }
    }

    // Player 1 chooses marker
    cout << "Player 1, choose your marker (X or O): ";
    cin >> player1_marker;

    while (player1_marker != 'X' && player1_marker != 'O') {
        cout << "Invalid choice! Please enter X or O: ";
        cin >> player1_marker;
    }

    player2_marker = (player1_marker == 'X') ? 'O' : 'X';

    current_marker = player1_marker;
    current_player = 1;

    drawBoard();

    int move_count = 0;

    // Game loop
    while (true) {
        int slot;
        cout << "Player " << current_player << " (" << current_marker << ") - Enter slot (1-9): ";
        cin >> slot;

        if (slot < 1 || slot > 9 || !placeMarker(slot)) {
            cout << "Invalid move! Try again.\n";
            continue;
        }

        move_count++;
        drawBoard();

        if (winner()) {
            cout << "🎉 Player " << current_player << " wins the game!\n";
            break;
        }

        if (move_count == 9) {
            cout << "🤝 It's a draw!\n";
            break;
        }

        swap_player_and_marker();
    }
}

int main() {
    game();
    return 0;
}
