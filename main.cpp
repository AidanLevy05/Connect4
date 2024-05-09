#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

// enums
enum class Color {
    RESET = 0,
    BLACK = 30,
    RED = 31,
    GREEN = 32,
    YELLOW = 33,
    BLUE = 34,
    MAGENTA = 35,
    CYAN = 36,
    WHITE = 37
};

const int RMAX = 6;
const int CMAX = 7;

void welcome();
void setColor(Color color);
void resetColor();
void getName(string&, string&);
void clearConsole();
int nextTurn(int);
void printBoard(int[RMAX][CMAX]);
bool isWin(int[RMAX][CMAX]);
void playGame(int[RMAX][CMAX], int, int);
void dropChip(int, int board[RMAX][CMAX], int col, int team);

int main() {

  srand(time(0));

  // get both players
  welcome();
  string p1, p2;
  getName(p1, p2);

  // variables
  int board[RMAX][CMAX];
  int turn = rand() % 2;
  bool play = true;

  // initialize board
  for (int i = 0; i < RMAX; i++) 
    for (int j = 0; j < CMAX; j++)
      board[i][j] = -1;

  // print board
  printBoard(board);

  while (play) {

    // 1 = Yellow
    // 2 = Red
    
    if (turn == 0) { // player 1
      setColor(Color::YELLOW);
      cout << p1 << ", it is your turn!" << endl;
      resetColor();

      int choice;
      cout << "Please enter your choice [1-7]" << endl;
      cin >> choice;

      //validate
      while (choice < 1 || choice > 7 || board[0][choice-1] != -1) {
        cout << "Try again." << endl;
        cin >> choice;
      }

      // update at board
      playGame(board, choice, 1);
      play = isWin(board);
      if (!play) cout << p1 << " has won!" << endl;

      turn = nextTurn(0);
      
    } else if (turn == 1) { // player 2
      setColor(Color::RED);
      cout << p2 << ", it is your turn!" << endl;
      resetColor();

      int choice;
      cout << "Please enter your choice [1-7]" << endl;
      cin >> choice;

      //validate
      while (choice < 1 || choice > 7 || board[0][choice-1] != -1) {
        cout << "Try again." << endl;
        cin >> choice;
      }

      // update at board
      playGame(board, choice, 2);
      play = isWin(board);
      if (!play) cout << p2 << " has won!" << endl;

      turn = nextTurn(1);
    }
  }
  
  return 0;
}
void welcome() {
  setColor(Color::YELLOW);
  cout << "   ____                            _  " << endl;
  cout << "  / ___|___  _ __  _ __   ___  ___| |_" << endl;
  cout << " | |   / _ \\| '_ \\| '_ \\ / _ \\/ __| __|" << endl;
  cout << " | |__| (_) | | | | | | |  __/ (__| |_" << endl;
  cout << "  \\____\\___/|_| |_|_| |_|\\___|\\___|\\__|" << endl;
  setColor(Color::RED);
  cout << "                 " << "   ___ " << endl;
  cout << "                 " << "  /   |" << endl;
  cout << "                 " << " / /| |" << endl;
  cout << "                 " << "/ /_| |" << endl;
  cout << "                 " << "\\___  |" << endl;
  cout << "                 " << "    |_/" << endl;
  cout << "\n\n" << endl;
  resetColor();
}
void setColor(Color color) {
  cout << "\033[" << static_cast<int>(color) << "m";
}
void resetColor() {
  setColor(Color::RESET);
}
void getName(string &p1, string &p2) {
  setColor(Color::YELLOW);
  cout << "Player 1, please enter your name!" << endl;
  cin >> p1;
  setColor(Color::RED);
  cout << "Player 2, please enter your name!" << endl;
  cin >> p2;
  resetColor();
  clearConsole();
}
void clearConsole() {
  int success = system("clear");
  if (success != 0) cout << "Error clearing console" << endl;
}
int nextTurn(int current) {
  if (current == 0) return 1;
  else return 0;
}
void printBoard(int board[RMAX][CMAX]) {
  cout << "\n\n";
  cout << "-1--2--3--4--5--6--7-" << endl;
  for (int i = 0 ; i < RMAX; i++) {
    for (int j = 0; j < CMAX; j++) {
      if (board[i][j] == -1) cout << " - ";
      else if (board[i][j] == 1) {
        setColor(Color::YELLOW);
        cout << " ● ";
        resetColor();
      } else if (board[i][j] == 2) {
        setColor(Color::RED);
        cout << " ● ";
        resetColor();
      }
    }
    cout << endl;
  }
  cout << "\n\n";
}
bool isWin(int board[RMAX][CMAX]) {
  for (int i = 0; i < RMAX; i++) {
    for (int j = 0; j < CMAX; j++) {
      // check number horizontal red
      if (board[i][j]==1&&board[i][j+1]==1&&board[i][j+2]==1&&board[i][j+3]==1) return false;
      if (board[i][j]==2&&board[i][j+1]==2&&board[i][j+2]==2&&board[i][j+3]==2) return false;

      // check vertical
      if (board[i][j]==1&&board[i+1][j]==1&&board[i+2][j]==1&&board[i+3][j]==1) return false;
      if (board[i][j]==2&&board[i+1][j]==2&&board[i+2][j]==2&&board[i+3][j]==2) return false;

      // check diagonal
      if (board[i][j]==1&&board[i+1][j+1]==1&&board[i+2][j+2]==1&&board[i+3][j+3]==1) return false;
      if (board[i][j]==2&&board[i+1][j+1]==2&&board[i+2][j+2]==2&&board[i+3][j+3]==2) return false;
    }
  }
  return true;
}
void playGame(int board[RMAX][CMAX], int col, int team) {
  // adjust to array notation
  col -= 1;

  // Start the chip dropping from the top of the column
  dropChip(0, board, col, team);
}
// Recursively simulate the board falling
void dropChip(int row, int board[RMAX][CMAX], int col, int team) {
  if (row == RMAX) // Base case
    return;
  if (board[row][col] == -1) { 
    
    board[row][col] = team; 
    clearConsole();
    printBoard(board); 
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    if (row + 1 < RMAX && board[row + 1][col] == -1) { 
      board[row][col] = -1; 
      dropChip(row + 1, board, col, team);
    }
    
  }
}