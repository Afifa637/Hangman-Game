//ABSTRACT CLASS
//POLYMORPHISM RUN TIME
//OPERATOR OVERLOADING
//FILE
//FRIEND FUNCTION
//FRIEND CLASS
//TEMPLATE CLASS
//STL VECTOR, PAIR

#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <conio.h>

using namespace std;

template <typename first, typename second>
class MyPair
{
    first f;
    second s;
public:
    MyPair() {}
    MyPair(first _f, second _s)
    {
        f = _f;
        s = _s;
    }
    friend bool operator < (const MyPair &o1, const MyPair &o2)
    {
        return (o1.s > o2.s);
    }
    friend class Game;
};


class Game
{
public:
    virtual void Play() = 0;
protected:
    string wordToGuess;
    vector<char> guessedLetters;
    string playerName;
    int tries;
    int score;
    string LoadRandomWord(string path)
    {
        int lineCount = 0;
        string word;
        vector<string> v;
        ifstream reader(path);

        if (reader.is_open())
        {
            while (getline(reader, word))
                v.push_back(word);
            int randomLine = rand() % v.size();
            word = v.at(randomLine);
            reader.close();
        }
        return word;
    }
    int TriesLeft()
    {
        int error = 0;
        for (int i = 0; i < guessedLetters.size(); i++)
        {
            if (wordToGuess.find(guessedLetters[i]) == string::npos)
                error++;
        }
        return error;
    }

public:
    Game() : tries(0), score(0)
    {
        srand(time(0));
        wordToGuess = LoadRandomWord("word.txt");
    }
    void PrintMessage(string message, bool printTop = true, bool printBottom = true)
    {
        if (printTop)
        {
            cout << "+---------------------------------+" << endl;
            cout << "|";
        }
        else
        {
            cout << "|";
        }
        bool front = true;
        for (int i = message.length(); i < 33; i++)
        {
            if (front)
            {
                message = " " + message;
            }
            else
            {
                message = message + " ";
            }
            front = !front;
        }
        cout << message.c_str();
        if (printBottom)
        {
            cout << "|" << endl;
            cout << "+---------------------------------+" << endl;
        }
        else
        {
            cout << "|" << endl;
        }
    }

    void DrawHangman(int guessCount = 0)
    {
        if (guessCount >= 1)
            PrintMessage("|", false, false);
        else
            PrintMessage("", false, false);

        if (guessCount >= 2)
            PrintMessage("|", false, false);
        else
            PrintMessage("", false, false);

        if (guessCount >= 3)
            PrintMessage("O", false, false);
        else
            PrintMessage("", false, false);

        if (guessCount == 4)
            PrintMessage("/  ", false, false);

        if (guessCount == 5)
            PrintMessage("/| ", false, false);

        if (guessCount >= 6)
            PrintMessage("/|\\", false, false);
        else
            PrintMessage("", false, false);

        if (guessCount >= 7)
            PrintMessage("|", false, false);
        else
            PrintMessage("", false, false);

        if (guessCount == 8)
            PrintMessage("/", false, false);

        if (guessCount >= 9)
            PrintMessage("/ \\", false, false);
        else
            PrintMessage("", false, false);
    }

    void PrintLetters(char from, char to)
    {
        string s;
        for (char i = from; i <= to; i++)
        {
            if (find(guessedLetters.begin(), guessedLetters.end(), i) == guessedLetters.end())
            {
                s += i;
                s += " ";
            }
            else
                s += "  ";
        }
        PrintMessage(s, false, false);
    }
    void PrintAvailableLetters()
    {
        PrintMessage("Available letters");
        PrintLetters('A', 'M');
        PrintLetters('N', 'Z');
    }
    bool PrintWordAndCheckWin()
    {
        bool won = true;
        string s;
        for (int i = 0; i < wordToGuess.length(); i++)
        {
            if (find(guessedLetters.begin(), guessedLetters.end(), wordToGuess[i]) == guessedLetters.end())
            {
                won = false;
                s += "_ ";
            }
            else
            {
                s += wordToGuess[i];
                s += " ";
            }
        }
        PrintMessage(s, false);
        return won;
    }

    void GuessWord(char letter)
    {
        tries++;
        guessedLetters.push_back(letter);
        if (wordToGuess.find(letter) != string::npos)
        {
            score += 10;
            tries--;
        }
    }

    void ResetGame()
    {
        wordToGuess = LoadRandomWord("word.txt");
        guessedLetters.clear();
        tries = 0;
        score = 0;
    }

    int GetScore() const
    {
        return score;
    }

    static void DisplayLeaderboard()
    {
        ifstream file("leaderboard.txt");
        vector<MyPair<string, int>> scores;

        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                size_t pos = line.find(":");
                if (pos != string::npos)
                {
                    string name = line.substr(0, pos);
                    int score = stoi(line.substr(pos + 1));
                    MyPair<string, int> mypair = {name, score};
                    scores.push_back(mypair);
                }
            }
            file.close();
        }

        sort(scores.begin(), scores.end());
            system("cls");
              cout << "\n\n\n\n";
              cout << setw(65);
        cout << "Leaderboard:" << endl;
        for(int i = 0; i < scores.size(); i++)
        {
              cout << setw(60);
            cout << scores[i].f << " " << scores[i].s << "\n";
        }
    }
};

class HangmanGame : public Game
{
public:
    void Play() override
    {
        char letter;
        bool isDone = false;
        system("cls");
        cout << "Enter Your Name: ";
        cin >> playerName;
        while (!isDone)
        {
            system("cls");
            PrintMessage("HANGMAN");
            DrawHangman(tries);
            PrintAvailableLetters();
            isDone = PrintWordAndCheckWin();
            cout << "Your score: " << GetScore() << endl;
            if (isDone)
            {
                PrintMessage("YOU WON!");
                cout << "Your Final score: " << GetScore() << endl;
                SaveScore(playerName);
                break;
            }
            if (tries >= 10)
            {
                PrintMessage("GAME OVER");
                cout << "The word was: " << wordToGuess << endl;
                cout << "Your score: " << GetScore() << endl;
                system("pause");
                break;
            }
            cout << "Enter a letter: ";
            cin >> letter;
            GuessWord(letter);
        }
    }

    void SaveScore(string str)
    {
        ofstream file("leaderboard.txt", ios::app);
        if (file.is_open())
        {
            file << str  << ": " << GetScore() << endl;
            file.close();
        }
    }
};

void instructions()
{
    system("cls");
    cout << "\t\t     Instructions";
    cout << "\n\t\t------------------";
    cout << "\n\t\t1. Guess one letter of the secret word at a time";
    cout << "\n\t\t2. Press 'Enter' to input the letter ";
    cout << "\n\t\t3. If your guessed letter is not in the word, a part of the hangman figure is drawn.";
    cout << "\n\t\t4. Try to guess the entire word or phrase before the hangman is fully drawn";
    cout << "\n\nPress any key to go back to menu\n";
}

int main()
{
    int choice;
    do
    {
            system("cls");
        Game* game;
        cout << "\t\t\t-----------------------------\n";
        cout << "\t\t\t|        HANGMAN GAME       |\n";
        cout << "\t\t\t-----------------------------\n";
        cout << "\t\t\t1 - Start game\n";
        cout << "\t\t\t2 - Instructions\n";
        cout << "\t\t\t3 - Leaderboard\n";
        cout << "\t\t\t4 - Quit\n";
        cout << "\t\t\tSelection: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            game = new HangmanGame();
            game->Play();
            delete game;
            break;
        case 2:
            instructions();
            break;
        case 3:
            Game::DisplayLeaderboard();
            break;
        case 4:
            cout << "Goodbye!";
            exit(0);
            break;
        default:
            cout << "Invalid selection. Please try again." << endl;
        }
        getch();
    }
    while (1);
    return 0;
}
