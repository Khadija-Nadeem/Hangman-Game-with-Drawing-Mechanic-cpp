#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// Function to show the hangman drawing based on wrong guesses
void displayHangman(int wrongGuesses) {
    switch (wrongGuesses) {
        case 0:
            cout << " \n\n\n\n\n\n"; // No parts drawn
            break;
        case 1:
            cout << " O \n\n\n\n\n"; // Head only
            break;
        case 2:
            cout << " O \n |\n\n\n\n"; // Head and torso
            break;
        case 3:
            cout << " O \n/|\n\n\n\n"; // Head, torso, and left arm
            break;
        case 4:
            cout << " O \n/|\\\n\n\n\n"; // Head, torso, and both arms
            break;
        case 5:
            cout << " O \n/|\\\n/\n\n\n"; // Head, torso, arms, and left leg
            break;
        case 6:
            cout << " O \n/|\\\n/ \\\n\n\n"; // Full hangman figure
            break;
    }
}

// Function to reveal some letters initially
void revealSomeLetters(string& guessedWord, const string& word, int numLettersToReveal) {
    int wordLength = word.size();
    bool* revealed = new bool[wordLength](); // Track revealed positions
    int revealedCount = 0;
    
    while (revealedCount < numLettersToReveal) {
        int index = rand() % wordLength;
        if (word[index] != '_' && !revealed[index]) {
            guessedWord[index] = word[index];
            revealed[index] = true;
            revealedCount++;
        }
    }
    
    delete[] revealed; // Clean up
}

int main() {
    srand(time(0)); // Set up random number generator

    // Categories and words
    string categories[] = {"Animals", "Programming Languages", "Fruits"};
    string words[][10] = {
        {"elephant", "giraffe", "kangaroo", "penguin", "dolphin"},
        {"python", "javascript", "cplusplus", "java", "swift"},
        {"apple", "banana", "strawberry", "mango", "pineapple"}
    };

    // Pick a random category and word
    int categoryIndex = rand() % 3;  // Randomly choose a category
    int wordIndex = rand() % 5;      // Randomly choose a word
    string word = words[categoryIndex][wordIndex]; // The selected word

    // Set up guessed word with underscores
    string guessedWord(word.size(), '_');

    // Reveal some letters initially
    int numLettersToReveal = word.size() / 3; // Reveal roughly one-third of the letters
    revealSomeLetters(guessedWord, word, numLettersToReveal);

    // Initialize attempts and wrong guesses
    int maxAttempts = 6;
    int attempts = 0;
    int wrongGuesses = 0;

    cout << "Welcome to Hangman! Get ready for a fun challenge. You have " << maxAttempts << " attempts to guess the word.\n" << endl;
    cout << "Category: " << categories[categoryIndex] << endl; // Show category

    // Game loop
    while (attempts < maxAttempts) {
        cout << "\nCurrent word: ";
        for (int i = 0; i < word.size(); i++) {
            cout << guessedWord[i] << " "; // Show current guesses
        }
        cout << endl;

        char guess;
        cout << "Enter your guess: ";
        cin >> guess; // Get user guess

        bool correctGuess = false;
        // Check if the guessed letter is in the word
        for (int i = 0; i < word.size(); i++) {
            if (word[i] == guess && guessedWord[i] == '_') {
                guessedWord[i] = guess; // Update guessed word
                correctGuess = true;
            }
        }

        // Handle wrong guesses
        if (!correctGuess) {
            wrongGuesses++;
            attempts++;
            cout << "Oops! That guess didn't hit the mark. Keep trying!" << endl;
            displayHangman(wrongGuesses); // Show hangman drawing
        } else {
            cout << "Well done! You've uncovered a letter. Keep it up!" << endl;

        }

        // Check if the word is fully guessed
        bool wordGuessed = true;
        for (int i = 0; i < word.size(); i++) {
            if (guessedWord[i] == '_') {
                wordGuessed = false; // Not all letters guessed
                break;
            }
        }

        // End game if word is guessed
        if (wordGuessed) {
            cout << "\nCongratulations! You've cracked the code! The word was: " << word << "!" << endl;
            return 0; // Exit program
        }
    }

    // Game over
    cout << "\nOh no! You've run out of attempts. The word was: " << word << ". Better luck next time!" << endl;
    displayHangman(wrongGuesses); // Show final hangman state

    return 0; // End program
}
