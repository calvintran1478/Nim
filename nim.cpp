#include <iostream>
#include <string>
#include <cstdlib>
#include <bits/stdc++.h>
using namespace std;

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

bool isValidGame(string str) {

    int len = str.length();

    // Check str starts and ends with an int
    if (!isdigit(str[0]) || !isdigit(str[len - 1])) {
        return false;
    }

    // Check for no consecutive spaces
    if (str.find("  ") != string::npos) {
        return false;
    }

    // Check each character is either a space or a digit
    for (char c : str) {
        if (c != ' ' && !isdigit(c)) {
            return false;
        }
    }
    return true;
}

class NimGame {
    private:
    int *piles;
    int num_piles;

    public:
    NimGame(int *arr, int len) {
        int *piles = arr;
        int num_piles = len;
    }

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
                return true;
            }
        }
        return false;
    }

    bool move(int pile_index, int num_removed) {
        if (num_removed > piles[pile_index]) {
            cout << "Invalid Move: Not enough tokens on the pile";
            return false;
        }
        piles[pile_index] -= num_removed;
        return true;
    }

    string toString() {
        string result = "[";
        for (int i = 0; i < num_piles; i++) {
            result += piles[i];
            result += ", ";
        }
        result.pop_back();
        result.pop_back();
        result += "]";

        return result;
    }
};

int main() {

    // Get input of from the user
    string nim_data;
    bool valid_game = false;
    while (!valid_game) {
        cout << "Enter a list of numbers representing a game of Nim\n";
        cout << "Example: 1 3 4\n";
        getline(cin, nim_data);

        if (nim_data.length() == 0) {
            cout << "Error: list cannot be empty";
        } else if (!isValidGame(nim_data)) {
            cout << "Error: Invalid format";
        } else {
            valid_game = true;
        }
    }

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
    NimGame nim(arr, len);

    // Continue making moves until there are no tokens left
    while(!nim.isGameOver()) {
        
        // Player Move
        bool valid_move = false;
        while (!valid_move) {
            int index;
            int to_remove;
            cout << nim.toString();
            cout << "Select a pile (index): ";
            cin >> index;
            cout << "\nEnter number of token to remove: ";
            cin >> to_remove;
            cout << endl;
            valid_move = nim.move(index, to_remove);
        }

        // TODO: Computer Move
    }

    return 0;
}