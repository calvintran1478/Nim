#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

int *split(string str, char del, int *len) {

    // Allocate memory for the array
    *len = getNumInput(str, del);
    int *arr = (int*) malloc(sizeof(int) * *len);
    if (!arr) {
        cout << "Memory Allocation Failed";
        exit(1);
    }

    // Parse data and store it into the array
    int i = 0;
    for (char c : str) {
        if (c != del) {
            arr[i] = c - 48;
            i++;
        }
    }
    return arr;
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

    // TODO: Add option for random nim game

    // Get input of from the user (no leading/trailing spaces)
    string nim_data;
    cout << "Enter a list of numbers representing a game of Nim\n";
    cout << "Example: 1 3 4\n";
    getline(cin, nim_data);

    // TODO: Check user input (array of ints with length >= 1)

    // Parse data into an array
    int len;
    char del = ' ';
    int *arr = split(nim_data, del, &len);
    NimGame nim(arr, len);

    // Continue making moves until there are no tokens left
    while(!nim.isGameOver()) {
        // TODO: Add option to go first or second
        
        // Player Move
        bool valid_move;
        do {
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
        while (!valid_move);

        // TODO: Computer Move
    }

    free(arr);

    return 0;
}