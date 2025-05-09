#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

import toys.random;

using namespace std;

constexpr auto WELCOME_MESSAGE = R"(Welcome to the Picos shell!
Bagels, a deductive logic game.
By Al Sweigart al@inventwithpython.com
I am thinking of a 3-digit number. Try to guess what it is.
Here are some clues:
    When I say:     That means:
    Pico            One digit is correct but in the wrong position.
    Fermi           One digit is correct and in the right position.
    Bagels          No digit is correct.
I have thought up a number.
You have 10 guesses to get it.
)";

void prompt(int times)
{
    cout << "Guess#" << times
         << "\n> " << flush;
}

// int random(int min, int max)
// {
//     static random_device engine{};
//     static mt19937 generator{ engine() };
//     uniform_int_distribution<int> distribution{ min, max };
//     return distribution(generator);
// }

string read_input()
{
    string input;
    getline(cin, input);
    return input;
}

bool is_all_digits(const string_view digits)
{
    for (const auto& digit : digits) {
        if (!isdigit(digit))
            return false;
    }
    return true;
}

vector<string> check_answer(const string_view guess, const string_view answer)
{
    vector<string> clues{};
    for (int i = 0; i < guess.length(); ++i) {
        if (guess[i] == answer[i])
            clues.push_back("Fermi");
        else if (answer.find(guess[i]) != string::npos)
            clues.push_back("Pico");
    }

    if (clues.empty())
        clues.push_back("Bagels");
    return clues;
}

string generate_secret_number(int numbers)
{
    constexpr auto digits = "0123456789";

    string secret_digits{};
    for (int i = 0; i < numbers; ++i) {
        char digit = digits[toys::random(0, 9)];
        if (secret_digits.find(digit) == string::npos)
            secret_digits.push_back(digit);
        else
            --i; // Retry if duplicate
    }

    return secret_digits;
}

bool replay_or_not()
{
    cout << "do you want to play again? (yes/no): \n> ";
    string input = read_input();
    if (input == "yes")
        return true;
    else
        return false;
}

int main(int argc, char* argv[])
{
    ios::sync_with_stdio(false);

    cout << WELCOME_MESSAGE;

    auto secret_number = generate_secret_number(3);
    bool should_exit = false;
    int times = 1;
    cout << "secret_number: " << secret_number << endl; // For debugging
    while (!should_exit) {
        prompt(times);

        auto guess = read_input();

        if (guess == "exit")
            should_exit = true;

        if (!is_all_digits(guess) || guess.length() != 3) {
            cout << "Please enter a 3-digit number." << endl;
            continue;
        }

        if (guess == secret_number) {
            cout << "You got it!" << endl;
            if (replay_or_not()) {
                secret_number = generate_secret_number(3);
                times = 1;
            } else {
                should_exit = true;
            }
        }

        auto clues = check_answer(guess, secret_number);
        for (const auto& clue : clues)
            cout << clue << " ";
        cout << endl;
        ++times;

        if (times > 10) {
            cout << "You have used all your guesses. The number was: " << secret_number << endl;
            if (replay_or_not()) {
                secret_number = generate_secret_number(3);
                times = 1;
            } else {
                should_exit = true;
            }
        }
    }

    cout << "Thanks for playing!" << endl;

    return EXIT_SUCCESS;
}