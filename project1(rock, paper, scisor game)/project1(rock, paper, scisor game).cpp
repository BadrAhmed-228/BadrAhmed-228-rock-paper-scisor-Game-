#include <iostream>
#include <string>

using namespace std;

enum enRPC { rock = 1, paper = 2, csisor = 3 };

enum enRoundWiner { userWin = 1, computerWin = 2, draw = 3 };

struct stGameData {
	
	short numberOfRounds = 0;
	short userPoints = 0;
	short computerPoints = 0;
	short drawTimes = 0;
};

short randomNumber(short from, short to) {

	return rand() % (to - from + 1) + from;
}

string tabs(short n) {

	string t = "";

	for (int i = 1; i <= n; i++) {
		t = t + "\t";
	}
	return t;
}

short readNumberOfRounds() {

	short numberOfRounds;

	do
	{
		cout << "Enter number of rounds : ";
		cin >> numberOfRounds;

	} while (numberOfRounds < 0);
	
	return numberOfRounds;
}

enRPC readUserChoice() {

	short choice;

	do
	{
		cout << "Your choice:  [1]: rock,  [2]: paper,  [3]: scisor ? ";
		cin >> choice;
		cout << endl;

	} while (choice < 1 || choice > 3);

	return enRPC(choice);
}

enRPC getComputerChoice() {

	return enRPC(randomNumber(1, 3));
}

char isPlayAgain() {

	char YN;

	cout << "\nDo you want to play again ? Y/N" << endl;
	cout << "\nEnter your choice ---> ";
	cin >> YN;

	return YN;
}

enRoundWiner RoundWiner(enRPC userChoice, enRPC computerChoice) {

	if (userChoice == computerChoice) {
		return draw;
	}
	else if (userChoice == enRPC::rock && computerChoice == enRPC::csisor) {
		return userWin;
	}
	else if (userChoice == enRPC::rock && computerChoice == enRPC::paper) {
		return computerWin;
	}
	else if (userChoice == enRPC::paper && computerChoice == enRPC::rock) {
		return userWin;
	}
	else if (userChoice == enRPC::paper && computerChoice == enRPC::csisor) {
		return computerWin;
	}
	else if (userChoice == enRPC::csisor && computerChoice == enRPC::paper) {
		return userWin;
	}
	else if (userChoice == enRPC::csisor && computerChoice == enRPC::rock) {
		return computerWin;
	}
}

string printPlayerWin(enRoundWiner roundWiner) {

	string arr[3] = { "Player 1 wins :-)", "Computer wins :-(", "No winner :-|" };

	return arr[roundWiner - 1];
}

string printChoice(enRPC RPC) {

	string arr[3] = { "Rock", "Paper", "Csisor" };
	
	return arr[RPC - 1];
}

stGameData fillGameData(enRoundWiner roundWiner, stGameData& gameData) {

	if (roundWiner == enRoundWiner::draw) {
		gameData.drawTimes++;
	}
	else if (roundWiner == enRoundWiner::computerWin) {
		gameData.computerPoints++;
	}
	else if (roundWiner == enRoundWiner::userWin) {
		gameData.userPoints++;
	}
	return gameData;
}

void winSitiuations(enRoundWiner roundWiner) {

	if (roundWiner == enRoundWiner::userWin) {
		system("color 2F");
	}
	else if (roundWiner == enRoundWiner::computerWin) {
		system("color 4F");
		cout << "\a";
	}
	else {
		system("color 6F");
	}
}

void gameHeaderResults() {

	cout << endl;
	cout << tabs(2) << "------------------------------------------\n" << endl;
	cout << tabs(2) << "          +++ GAME OVER +++\n\n";
	cout << tabs(2) << "------------------------------------------\n" << endl;
}

void showGameResults(stGameData GameData) {

	cout << tabs(2) << "---------------------[Game Results]---------------------" << endl;

	cout << tabs(2) << "Number of rounds: " << GameData.numberOfRounds << endl;
	cout << tabs(2) << "Player 1 points : " << GameData.userPoints << endl;
	cout << tabs(2) << "Computer points : " << GameData.computerPoints << endl;
	cout << tabs(2) << "Draw times      : " << GameData.drawTimes << endl;
}

enRoundWiner whoWinTheGame(stGameData gameData) {

	if (gameData.computerPoints > gameData.userPoints) {
		system("color 4F");
		return enRoundWiner::computerWin;
	}
	else if (gameData.userPoints > gameData.computerPoints) {
		system("color 2F");
		return enRoundWiner::userWin;
	}
	else {
		system("color 6F");
		return enRoundWiner::draw;
	}
}

void resetScreen() {

	system("cls");
	system("color 0F");
}

stGameData resetGameData(stGameData& gameData) {

	gameData.computerPoints = 0;
	gameData.drawTimes = 0;
	gameData.userPoints = 0;
	gameData.numberOfRounds = 0;

	return gameData;
}

void playRound(stGameData& gameData) {

	enRPC userChoice = readUserChoice();
	enRPC computerChoice = getComputerChoice();
	enRoundWiner roundWinner = RoundWiner(userChoice, computerChoice);
	fillGameData(roundWinner, gameData);

	cout << "Player 1 choice: " << printChoice(userChoice) << endl;
	cout << "Computer choice: " << printChoice(computerChoice) << endl;
	cout << "Round winner: " << printPlayerWin(roundWinner) << endl;
	winSitiuations(roundWinner);
}

void playRounds(stGameData& gameData) {

	short numberOfRounds = readNumberOfRounds();

	for (short i = 1; i <= numberOfRounds; i++) {

		cout << "\n----------round[" << i << "] begins----------\n" << endl;
		playRound(gameData);
		cout << "------------------------------------------------\n" << endl;
	}
	gameData.numberOfRounds = numberOfRounds;
}

void startGame() {

	stGameData GameData;

	char yesNo = 'y';

	do
	{
		playRounds(GameData);
		gameHeaderResults();
		showGameResults(GameData);
		cout << tabs(2) << printPlayerWin(whoWinTheGame(GameData)) << endl;
		
		yesNo = isPlayAgain();

		if (yesNo == 'y' || yesNo == 'Y') {
			resetScreen();
			resetGameData(GameData);
		}

	} while (yesNo == 'y' || yesNo == 'Y');
}

int main() {

	srand((unsigned)time(NULL));

	startGame();
	
	return 0;
}