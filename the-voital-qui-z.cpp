#include <iostream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

// Structure to hold each quiz question
struct Question {
    string questionText;
    vector<string> options;
    char correctOption;
};

// Function to display a single question
void displayQuestion(const Question &q) {
    cout << "\n" << q.questionText << endl;
    for (size_t i = 0; i < q.options.size(); i++) {
        cout << char('A' + i) << ". " << q.options[i] << endl;
    }
}

// Function to run a quiz for a given category
void runQuiz(const vector<Question> &quiz) {
    int score = 0;
    char userAnswer;

    for (size_t i = 0; i < quiz.size(); i++) {
        displayQuestion(quiz[i]);
        cout << "Your answer (A/B/C/D): ";
        cin >> userAnswer;
        userAnswer = toupper(userAnswer);

        // Input validation
        while (userAnswer < 'A' || userAnswer >= 'A' + quiz[i].options.size()) {
            cout << "Invalid input. Enter again (A/B/C/D): ";
            cin >> userAnswer;
            userAnswer = toupper(userAnswer);
        }

        if (userAnswer == quiz[i].correctOption) {
            cout << "Correct!\n";
            score++;
        } else {
            cout << "Incorrect. Correct answer: " << quiz[i].correctOption << "\n";
        }
    }

    cout << "\nQuiz Completed! Your score: " << score << " out of " << quiz.size() << endl;
}

// Function to display the homepage
void showHomePage() {
    cout << "=============================\n";
    cout << "      Welcome to Quiz Hub    \n";
    cout << "=============================\n";
    cout << "Choose a quiz category:\n";
    cout << "1. Mathematics\n";
    cout << "2. General Knowledge (GK)\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    int choice;

    // Sample Maths Quiz
    vector<Question> mathsQuiz = {
        {"What is 12 * 8?", {"80", "96", "108", "112"}, 'B'},
        {"The square root of 144 is?", {"10", "12", "14", "16"}, 'B'},
        {"What is 15 + 27?", {"40", "42", "44", "45"}, 'B'}
    };

    // Sample GK Quiz
    vector<Question> gkQuiz = {
        {"Who is known as the Father of India?", {"Mahatma Gandhi", "Jawaharlal Nehru", "Subhash Chandra Bose", "Bhagat Singh"}, 'A'},
        {"What is the capital of France?", {"Berlin", "Paris", "Madrid", "Rome"}, 'B'},
        {"Which planet is known as the Red Planet?", {"Venus", "Mars", "Jupiter", "Saturn"}, 'B'}
    };

    while (true) {
        showHomePage();
        cin >> choice;

        if (choice == 1) {
            cout << "\nStarting Mathematics Quiz...\n";
            runQuiz(mathsQuiz);
        } else if (choice == 2) {
            cout << "\nStarting General Knowledge Quiz...\n";
            runQuiz(gkQuiz);
        } else if (choice == 3) {
            cout << "Thank you for visiting Quiz Hub. Goodbye!\n";
            break;
        } else {
            cout << "Invalid choice! Please try again.\n";
        }

        cout << "\nPress Enter to return to the homepage...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    return 0;
}
