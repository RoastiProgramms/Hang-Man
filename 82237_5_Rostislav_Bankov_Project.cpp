#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
using namespace std;

bool isLoggedIn(string username, string password)
{
	string un, pw;
	ifstream read(username + ".txt");
	getline(read, un);//basicly compares the first line of the txt file(it's the username that the person that created it put) with the username that the user puts 
	getline(read, pw);//the same but for the password
	if (un == username && pw == password)
	{
		return true;
	}
	return false;
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
void PrintLetters(string input, char from, char to)
{
	string s;
	for (char i = from; i <= to; i++)
	{
		if (input.find(i) == string::npos)
		{
			s += i;
			s += " ";
		}
		else
			s += "  ";
	}
	PrintMessage(s, false, false);
}
void PrintAvailableLetters(string taken)
{
	PrintMessage("Available letters");
	PrintLetters(taken, 'a', 'm');
	PrintLetters(taken, 'n', 'z');
}
bool PrintWordAndCheckWin(string word, string guessed)
{
	bool won = true;
	string s;
	for (int i = 0; i < word.length(); i++)
	{
		if (guessed.find(word[i]) == string::npos)
		{
			won = false;
			s += "_ ";
		}
		else
		{
			s += word[i];
			s += " ";
		}
	}
	PrintMessage(s, false);
	return won;
}
string LoadRandomWord(string path)
{
	string word;
	vector<string> v;
	ifstream reader(path);
	if (reader.is_open())
	{
		while (std::getline(reader, word))
			v.push_back(word);

		int randomLine = rand() % (v.size() - 3) + 3;

		word = v.at(randomLine);
		reader.close();
	}
	return word;
}
int TriesLeft(string word, string guessed)
{
	int error = 0;
	for (int i = 0; i < guessed.length(); i++)
	{
		if (word.find(guessed[i]) == string::npos)
			error++;
	}
	return error;
}

int main()
{
	int n;
	cout << "Press:" << endl;
	cout << "1 for Registration." << endl;
	cout << "2 for Log in." << endl;
	cout << "3 for Playing single player without an account." << endl;
	do
	{
		cin >> n;
	} while (n<1||n>3);

	if (n == 1)
	{
		int number;
		string username, password, email;
		cout << "Select username: "; cin >> username;
		cout << "Select password: "; cin >> password;
		cout << "Type your email: "; cin >> email;
		cout << "Press 1 for plane file. (You will have to add all words by yourself)" << endl;
		cout << "Press 2 for file with default words. (You can still add words, but you will also have the default ones.)" << endl;
		do
		{
			cin >> number;
		} while (number<1||number>2);

		if (number == 1)
		{
			ofstream file;
			file.open(username + ".txt");
			file << username << endl << password << endl << email << endl;
			file.close();
			cout << "Your account is created.";
			main();//Here we will return to main ,so the person can chose whether he wants to create another acc or so on.
		}
		else if (number == 2)
		{
			ifstream hangman("words.txt");
			string randomWord;
			ofstream file;
			file.open(username + ".txt");
			file << username << endl << password << endl << email << endl;
			while (hangman >> randomWord)
			{
				file << randomWord << endl;
			}
			main();
		}
		else
		{
			cout << "Don't try to bypass my system(it's still not valid symbol)" << endl;
		}
	}
	else if (n == 2)
	{
		cout << "Type your username." << endl;
		string username1, password1, email;
		cin >> username1;
		cout << "Type your password." << endl;
		cin >> password1;
		bool status = isLoggedIn(username1, password1);
		if (!status)
		{
			cout << "Wrong username or password." << endl;
			cout << "Type your username" << endl;
			cin >> username1;
			ifstream account(username1 + ".txt");
			if (!account.good())
			{
				cout << "Invalid username";
			}
			else
			{
				cout << "Type your email";
				cin >> email;
				string email1;
				account >> email1;
				account >> email1;
				account >> email1;
				if (email != email1)
				{
					cout << "Wrong email." << endl;
					cin >> email;
					if (email != email1)
					{
						cout << "Wrong email again!" << endl;
						main();
					}
				}
				else
				{
					string newpass;
					cout << "Type new password" << endl;
					cin >> newpass;
					password1 = newpass;
					account.close();
					fstream file(username1 + ".txt", ios::in | ios::out);
					string word;
					file >> word;
					file.seekp(file.tellg());
					file << newpass << endl;
				}
			}

		}
		else
		{
			cout << "Log in is succesfull" << endl;
		playMenu:int command;
			cout << "1:Play" << endl;
			cout << "2:Add new word" << endl;
			cout << "3:Exit" << endl;
			do
			{
				cin >> command;
			} while (command > 3 || command < 1);
			if (command == 1)
			{
				srand(time(0));
				string guesses;
				string wordToGuess;
				wordToGuess = LoadRandomWord(username1 + ".txt");
				int tries = 0;
				bool win = false;
				do
				{
					system("cls");
					PrintMessage("HANGMAN");
					DrawHangman(tries);
					PrintAvailableLetters(guesses);
					PrintMessage("Guess the word");
					win = PrintWordAndCheckWin(wordToGuess, guesses);

					if (win)
						break;

					char x;
					cout << ">"; cin >> x;

					if (guesses.find(x) == string::npos)
						guesses += x;

					tries = TriesLeft(wordToGuess, guesses);

				} while (tries < 10);

				if (win)
					PrintMessage("YOU WON!");

				else
					PrintMessage("GAME OVER");

				system("pause");
				getchar();
				return 0;
			}
			if (command == 2)
			{
				cout << "Type the word you want to add." << endl;
				string word;
				cin >> word;
				ofstream addword(username1 + ".txt", ios::app);
				addword << word << endl;
				goto playMenu;
			}
			if (command == 3)
			{
				exit(0);
			}
		}
	}
	else if (n == 3)
	{
		srand(time(0));
		string guesses;
		string wordToGuess;
		wordToGuess = LoadRandomWord("words.txt");
		int tries = 0;
		bool win = false;
		do
		{
			system("cls");
			PrintMessage("HANGMAN");
			DrawHangman(tries);
			PrintAvailableLetters(guesses);
			PrintMessage("Guess the word");
			win = PrintWordAndCheckWin(wordToGuess, guesses);

			if (win)
				break;

			char x;
			cout << ">"; cin >> x;

			if (guesses.find(x) == string::npos)
				guesses += x;

			tries = TriesLeft(wordToGuess, guesses);

		} while (tries < 10);

		if (win)
			PrintMessage("YOU WON!");
		else
			PrintMessage("GAME OVER");

		system("pause");
		return 0;
	}
	else
	{
		cout << "Invalid symbol";
	}
}