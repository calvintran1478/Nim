#include <bits/stdc++.h>

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int isNumeric(string str) {
  int len = str.length();
  for (int i = 0; i < len; i++) {
    if (!isdigit(str[i])) {
      return false;
    }
  }
  return true;
}

int getNumInput(string str, char del) {
  int len = str.length();
  int counter = 0;
  for (int i = 0; i < len; i++) {
    if (str[i] == del) {
      counter++;
    }
  }
  return counter + 1;
}

bool isValidDigit(char c) { return isdigit(c) && (c != 48); }

bool isValidGame(string str) {
  int len = str.length();

  // Check str starts and ends with an int
  if (!isValidDigit(str[0]) || !isValidDigit(str[len - 1])) {
    return false;
  }

  // Check for no consecutive spaces
  if (str.find("  ") != string::npos) {
    return false;
  }

  // Check each character is either a space or a digit
  for (char c : str) {
    if (c != ' ' && !isValidDigit(c)) {
      return false;
    }
  }
  return true;
}

class NimBoard {
 private:
  int *piles;
  int num_piles;

 public:
  int getNimSum() {
    int nim_sum = 0;
    for (int i = 0; i < num_piles; i++) {
      nim_sum = nim_sum ^ piles[i];
    }
    return nim_sum;
  }

  bool isGameOver() {
    for (int i = 0; i < num_piles; i++) {
      if (piles[i] != 0) {
        return false;
      }
    }
    return true;
  }

  bool move(int pile_index, int num_removed) {
    // Check for valid pile selection
    if (pile_index < 0 || pile_index >= num_piles) {
      cout << "Error: Pile does not exist\n";
      return false;
    }

    // Check for valid selection of tokens to remove
    if (num_removed < 1) {
      cout << "Invalid Move: Must remove at least one token\n";
      return false;
    } else if (num_removed > piles[pile_index]) {
      cout << "Invalid Move: Not enough tokens on the pile\n";
      return false;
    }

    // Perform the move
    piles[pile_index] -= num_removed;

    return true;
  }

  int getNumPiles() { return num_piles; }

  int getNumTokens(int pile_index) { return piles[pile_index]; }

  void setBoard(int arr[], int n_piles) {
    piles = arr;
    num_piles = n_piles;
  }

  string toString() {
    string result = "[";
    for (int i = 0; i < num_piles; i++) {
      result += to_string(piles[i]);
      result += ", ";
    }
    result.pop_back();
    result.pop_back();
    result += "]";

    return result;
  }
};

class NimPlayer {
 protected:
  NimBoard *board;

 public:
  string name;
  void setName(string s) { name = s; }
  void setGame(NimBoard *n) { board = n; }
  virtual void move() = 0;
};

class HumanPlayer : public NimPlayer {
 public:
  void move() {
    // Player Move
    bool valid_move = false;
    while (!valid_move) {
      string index;
      string to_remove;
      cout << name << "'s Turn\n";
      cout << board->toString() << endl;
      cout << "Select a pile: ";
      cin >> index;
      cout << "Enter number of tokens to remove: ";
      cin >> to_remove;
      cout << endl;

      // Error checking
      if (!isNumeric(index)) {
        cout << "Error: Pile choice must be an integer\n";
      } else if (!isNumeric(to_remove)) {
        cout << "Error: Tokens to remove must be an integer\n";
      } else {
        valid_move = board->move(stoi(index) - 1, stoi(to_remove));
      }
    }
  }
};

class NimGame {
 private:
  NimBoard board;
  vector<HumanPlayer> players;
  vector<HumanPlayer>::iterator curr;

 public:
  NimGame(int arr[], int n_piles, int nim_players = 2) {
    board.setBoard(arr, n_piles);
    HumanPlayer p;
    for (int i = 0; i < nim_players; i++) {
      p.setGame(&board);
      p.setName("Player " + to_string(i + 1));
      players.push_back(p);
    }
    curr = players.begin();
  }

  bool isGameOver() { return board.isGameOver(); }

  HumanPlayer getCurrentPlayer() { return *curr; }

  HumanPlayer getPreviousPlayer() {
    if (curr == players.begin()) {
      return *players.end();
    }
    return *prev(curr, 1);
  }

  void move() {
    // Move current player and update to the next player
    (*curr).move();
    curr++;
    if (curr == players.end()) {
      curr = players.begin();
    }
  }

  string toString() { return board.toString(); }
};

int main() {
  // Game introduction
  cout << "Welcome to Nim!\n";
  cout << endl;

  // Get number of players
  string user_input;
  int num_players;
  bool vaild_player_num = false;
  while (!vaild_player_num) {
    cout << "Enter number of players: ";
    getline(cin, user_input);
    cout << endl;

    if (!isNumeric(user_input)) {
      cout << "Error: Number of players must be an integer\n";
    } else if (stoi(user_input) < 2) {
      cout << "Error: Number of players must be at least 2\n";
    } else {
      num_players = stoi(user_input);
      vaild_player_num = true;
    }
  }

  // Get nim set up
  string nim_data;
  bool valid_game = false;
  while (!valid_game) {
    cout << "Enter a list of positive integers representing a game of Nim\n";
    cout << "Example: 1 3 4\n";
    getline(cin, nim_data);

    if (nim_data.length() == 0) {
      cout << "Error: List cannot be empty\n";
    } else if (!isValidGame(nim_data)) {
      cout << "\nError: Invalid format\n";
    } else {
      valid_game = true;
    }
  }
  cout << endl;

  // Parse data into an array
  char del = ' ';
  int len = getNumInput(nim_data, del);
  int arr[len];
  int counter = 0;

  string temp = "";
  for (char c : nim_data) {
    if (c == del) {
      arr[counter] = stoi(temp);
      temp = "";
      counter++;
    } else {
      temp += c;
    }
  }
  arr[counter] = stoi(temp);

  // Create the Nim Game
  NimGame nim(arr, len, num_players);

  // Continue making moves until there are no tokens left
  while (!nim.isGameOver()) {
    nim.move();
  }

  cout << nim.getPreviousPlayer().name << " wins!\n";

  return 0;
}