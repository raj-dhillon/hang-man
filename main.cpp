/**
 * Title:   Hangman
 *
 * Purpose: ** Simple Hangman game which prompts the user, asking if they want to play. If they say yes, it proceeds to
 * select a random word from the array, and begins the game. The user is given five attempts, after which, they either
 * lose or win. The game then ends. **
 * Author:  ** Rajdeep Dhillon **
 */

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <cctype>

using std::cout;
using std::cin;
using std::endl;
using std::string;

bool StartGame();
void GameLogic(const string& word);
string SelectWord();
bool InputCheck(const string& guess);
void DrawHangman(int strikes);

int main() {
    bool start = StartGame();
    if (!start) {
        return 0;
    }
    string selectedWord = SelectWord();
    GameLogic(selectedWord);


    return 0;
}

/**
 * Function to start the game, asks the user if they would like to play, and if they respond with:
 * yes, YES, y, or Y, then it starts the game. If not, it ends the game.
 * @param
 * @return bool, with false ending the game and true beginning it.
 */
bool StartGame() {
    string userDecision;
    cout << "Would you like to play Hangman? " << endl;
    cin >> userDecision;
    if (!((userDecision == "YES") || (userDecision[0] == 'Y') || (userDecision == "yes") || (userDecision[0] == 'y'))) {
        cout << "Game Over";
        return false;
    }
    return true;
}

/**
 * Function to select a word. Selects a random word from the array, which is then used for the hangman game.
 * @param
 * @return string, returns the selected word from the array for the hangman game.
 */
string SelectWord() {
    string potentialWords[] = {"abruptly", "beekeeper", "caliph", "disavow", "embezzle",
                               "espionage", "kayak", "quorum",
                               "wellspring", "vaporize", "mnemonic"};
    srand(time(0));
    int randomNum = rand() % 10;
    return potentialWords[randomNum];
}

/**
 * Function containing the game logic. Keeps track of strikes, updating the word as letters are found, and ensuring
 * the game continues until the user finds out the word, or runs out of tries.
 * @param word the word chosen for the hangman game.
 * @return
 */
void GameLogic(const string& word) {
    string hiddenWord(word.length(), '*');
    bool continuePlaying = true;
    int numStrikes = 0;
    string guess;
    bool foundLetter = false;

    cout << "The word is: " << hiddenWord << endl;
    while (continuePlaying){
        cout << endl;
        cout << "Guess a letter: ";
        cin >> guess;

        while (!InputCheck(guess)) {
            cout << "Invalid letter, go again: ";
            cin >> guess;
        }
        for (int i = 0; i < hiddenWord.length(); i++) {
            if (word.at(i) == guess[0]) {
                hiddenWord[i] = guess[0];
                foundLetter = true;
            }
        }
        cout << "The word so far: " << hiddenWord << endl;

        if (foundLetter) {
            DrawHangman(numStrikes);
            cout << "The letter \'" << guess << "\' is in the word." << endl;
        } else {
            numStrikes++;
            DrawHangman(numStrikes);
            cout << "The letter \'" << guess << "\' is not in the word. Strike number: " << numStrikes << endl;
        }
        foundLetter = false;

        if ((numStrikes > 4) || (hiddenWord == word)) {
            continuePlaying = false;
        }

    }
    if (hiddenWord == word) {
        cout << endl << "CONGRATS, YOU WIN!" << endl;
    }
    else {
        cout << endl << "YOU LOSE!" << endl << "The word was: " << word << "." << endl;
    }
}

/**
 * This function checks the input provided by the user in order to ensure that its valid.
 * It checks to see if it was one letter and whether it was an alphabetical character.
 * @param guess the input provided by the user to be tested.
 * @return bool, returns false if the input is invalid, and returns true if it is valid.
 */
bool InputCheck(const string& guess) {
    if (guess.length() != 1) {
        return false;
    }
    if (!isalpha(guess[0])) {
        return false;
    }
    return true;
}

/**
 * Function draws and updates the hangman, accounting for the amount of strikes accrued.
 * @param strikes the amount of wrong characters chosen by the user.
 * @return
 */
void DrawHangman(int strikes) {
    if (strikes == 0) {

    }
    switch(strikes) {
        case 1:
            cout << "|-" << endl;
            break;
        case 2:
            cout << "|-O-" << endl;
            break;
        case 3:
            cout << "|-O-|" << endl;
            break;
        case 4:
            cout << "|-O-|--" << endl;
            break;
        case 5:
            cout << "|-O-|--<" << endl;
            break;
    }
}