 #include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
enum enQuestionLevel { Easy = 1, Med = 2, Hard = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5 };
struct stRoundInfo {
	enQuestionLevel QuestionLevel;
	enOperationType OperationType;
	enOperationType ActualOperation;
	int Number1;
	int Number2;
	int Result;
	string ProcessSign;
};
struct stGameResult {
	short HowManyRounds;
	string NameLevel;
	string NameType;
	short RightAnswer;
	short WrongAnswer;


};
int CreateRandomNumber(int from, int to) {
	int random = rand() % (to - from + 1) + from;
	return random;

}

string Tab(short number) {
	string tab = "";
	for (int i = 1; i < number; i++)
	{
		tab = tab + "\t";
	}return tab;
}
short HowManyRounds() {
	short Question = 0;
	do {
		cout << " How many questions do you want to answer ? ";
		cin >> Question;
	} while (Question < 0 || Question>25);
	return Question;
}
void ResetScreen() {
	system("cls");
	system("color 0f");
}
enQuestionLevel ChoiceQuestionLevel() {
	short Level;
	do {
		cout << " Enter Question level [1] Easy , [2] Med , [3] Hard , [4] Mix ? ";
		cin >> Level;
	} while (Level < 1 || Level > 4);
	return(enQuestionLevel)Level;

}
enOperationType ChoiceOperationType() {
	short Type;
	do {
		cout << " Enter Operation Type : [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
		cin >> Type;
	} while (Type < 1 || Type > 5);
	return (enOperationType)Type;
}
int GetNumbers(stRoundInfo RoundInfo) {
	if (RoundInfo.QuestionLevel == enQuestionLevel::Easy) {
		return CreateRandomNumber(1, 10);
	}
	else if (RoundInfo.QuestionLevel == enQuestionLevel::Med) {
		return CreateRandomNumber(1, 50);
	}
	else if (RoundInfo.QuestionLevel == enQuestionLevel::Hard) {
		return CreateRandomNumber(50, 100);
	}
	else if (RoundInfo.QuestionLevel == enQuestionLevel::Mix) {
		return CreateRandomNumber(1, 100);
	}
}

enOperationType GetMixProcessSign() {
	return (enOperationType)CreateRandomNumber(1, 4);
}
string GetProcessSign(stRoundInfo RoundInfo) {
	
		switch (RoundInfo.ActualOperation) {
		case enOperationType::Add:
			return "+";
			break;
		case enOperationType::Sub:
			return "-";
			break;
		case enOperationType::Mul:
			return "*";
			break;
		case enOperationType::Div:
			return "/";
			break;
		}
	
}

int MixResult(stRoundInfo RoundInfo) {
	
		switch (RoundInfo.ActualOperation) {
		case enOperationType::Add:
			return RoundInfo.Number1 + RoundInfo.Number2;
			break;
		case enOperationType::Sub:
			return RoundInfo.Number1 - RoundInfo.Number2;
			break;
		case enOperationType::Mul:
			return RoundInfo.Number1 * RoundInfo.Number2;
			break;
		case enOperationType::Div:
			return RoundInfo.Number1 / RoundInfo.Number2;
			break;
		}
	
}
void PrintRoundInfo(stRoundInfo RoundInfo) {
	cout << "\n  " << RoundInfo.Number1 << endl;
	cout << "  " << RoundInfo.Number2 << " " << RoundInfo.ProcessSign << endl;
	cout << "_______________" << endl;
	cout << "  ";
}
bool CheckResult(stRoundInfo RoundInfo, int Input) {
	if (Input == RoundInfo.Result) {
		return true;
	}
	else
		return false;
}
string GetLevelName(stRoundInfo RoundInfo) {
	switch (RoundInfo.QuestionLevel) {
	case enQuestionLevel::Easy:
		return " Easy";
		break;
	case enQuestionLevel::Med:
		return " Med";
		break;
	case enQuestionLevel::Hard:
		return " Hard";
		break;
	case enQuestionLevel::Mix:
		return " Mix";
		break;
	}
}
string GetNameOfOperation(stRoundInfo RoundInfo) {
	switch (RoundInfo.OperationType) {
	case enOperationType::Add:
		return "+";
		break;
	case enOperationType::Sub:
		return "-";
		break;
	case enOperationType::Mul:
		return "*";
		break;
	case enOperationType::Div:
		return "/";
		break;
	case enOperationType::MixOp:
		return "Mix";
		break;
	}
}
stGameResult FillGameResult(stRoundInfo RoundInfo, short HowManyRounds, short WrongAnswer, short RightAnswer) {
	stGameResult GameResult;
	GameResult.HowManyRounds = HowManyRounds;
	GameResult.NameLevel = GetLevelName(RoundInfo);
	GameResult.NameType = GetNameOfOperation(RoundInfo);
	GameResult.RightAnswer = RightAnswer;
	GameResult.WrongAnswer = WrongAnswer;

	return  GameResult;
}
stGameResult PlayGame(short HowManyRounds) {
	short WrongAnswer = 0, RightAnswer = 0;
	stRoundInfo RoundInfo;
	RoundInfo.QuestionLevel = ChoiceQuestionLevel();
	RoundInfo.OperationType = ChoiceOperationType();
	for (int i = 1; i <= HowManyRounds; i++) {
		cout << endl << Tab(1) << "Question [" << i << "/" << HowManyRounds << "]" << endl;
		
		
		if (RoundInfo.OperationType == enOperationType::MixOp) {
			RoundInfo.ActualOperation = GetMixProcessSign();
		}
		else {
			RoundInfo.ActualOperation = RoundInfo.OperationType;
		}


		RoundInfo.Number1 = GetNumbers(RoundInfo);
		RoundInfo.Number2 = GetNumbers(RoundInfo);
		RoundInfo.ProcessSign = GetProcessSign(RoundInfo);
		RoundInfo.Result = MixResult(RoundInfo);
		//////////////////////////////////////////////////////////////
		PrintRoundInfo(RoundInfo);

		int Input = 0;
		cin >> Input;
		if (CheckResult(RoundInfo, Input) == true) {
			system("color 2f");
			cout << "\n Right Answer :-)\n";
			RightAnswer++;
		}
		else {
			system("color 4f");
			cout << "\a";
			cout << "\n Wrong Answer :-(\n";
			cout << " The Right Answer Is : " << RoundInfo.Result << endl;
			WrongAnswer++;
		}
	}
	return FillGameResult(RoundInfo, HowManyRounds, WrongAnswer, RightAnswer);
}
string PassOrFail(stGameResult GameResult) {
	if (GameResult.RightAnswer < GameResult.WrongAnswer) {
		system("color 4f");
		cout << "\a";
		return  "Final Results Is Fail :-(";

	}
	else if (GameResult.RightAnswer > GameResult.WrongAnswer) {
		system("color 2f");
		return "Final Results Is Pass :-)";
	}
	else
		system("color 6f");
	return  "Final Results Is Draw ::";
}
void ShowGameOverScreen(stGameResult GameResult) {
	cout  << "_________________________________________________\n";
	cout << Tab(2) << "    R E S U L T  \n\n";
	cout  << "  "<<PassOrFail(GameResult) << endl;
	cout  << "_________________________________________________\n\n";

}
void ShowFinalGameResults(stGameResult GameResult) {
	cout  << "  Number Of Question : " << GameResult.HowManyRounds << endl;
	cout  << "  Question Level : " << GameResult.NameLevel << endl;
	cout  << "  Operation Type : " << GameResult.NameType << endl;
	cout  << "  Number Of Right Answer : " << GameResult.RightAnswer << endl;
	cout  << "  Number Of Wrong Answer : " << GameResult.WrongAnswer << endl;
	cout  << "_________________________________________________\n\n\n";

}
void StartGame() {
	string PlayAgain = "yes";
	do {
		ResetScreen();
		stGameResult GameResult = PlayGame(HowManyRounds());
		ShowGameOverScreen(GameResult);
		ShowFinalGameResults(GameResult);


		cout << " If you want to play again  enter : [ yes ] ? \n";
		cin >> PlayAgain;

	} while (PlayAgain == "yes" || PlayAgain == "y" || PlayAgain == "Yes");

	cout << "\n"<<Tab(2) << "+++ G A M E   O V E R +++ \n\n" << endl;
}
int main() {
	srand((unsigned)time(NULL));
	StartGame();
	return 0;
}


