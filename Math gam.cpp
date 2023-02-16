#include <iostream>
#include <string>
#include <ctime>
using namespace std;
enum enResult { Pass = 1, Fail = 2, Draw = 3};
enum enTestLevel { Easy = 1, Medium = 2, Hard = 3, _Mix = 4 };
enum enOperation { Addition = 1, Subtraction = 2, Multiplication = 3, Division = 4, Mix = 5};
struct stGameInfo
{
	enResult FinalResult;
	int NumberOfRightAnswers = 0;
	int NumberofWrongAnswers = 0;
	enOperation OpType;
	enTestLevel QuestionsLevel;
	int TotalQuestions = 0;
};
struct stQuestionInfo
{
	int CurrentQuestion = 0;
	int Answer = 0;
};
int RandomNumber(int From, int To)
{
	return (rand() % (To - From + 1) + From);
}
enTestLevel AskForTestLevel()
{
	int choice = 0;
	do
	{
		cout << "Enter the Test level: Easy [1], Medium [2], Hard [3]: ";
		cin >> choice;
	} while (choice < 1 || choice > 3);
	return (enTestLevel)choice;
}
enOperation AskForOperationType()
{
	int choice = 0;
	do
	{
		cout << "Enter the Test level: Addition [1], Subtraction [2], Multiplication [3], Division[4], Mix [5]: ";
		cin >> choice;
	} while (choice < 1 || choice > 5);
	return (enOperation)choice;
}
int AskForHowManyQuestions()
{
	int questions;
	cout << "Enter how many question do you want to answer?\n";
	cin >> questions;
	return questions;
}
string PrintOperationType(enOperation opType)
{
	string Operations[5] = { "Addition", "Subtraction", "Multiplication", "Division", "Mix" };
	return Operations[(int)opType - 1];
}
char GenerateOperation()
{
	char AllOperations[4] = { '+', '-', '*', '/' };
	return AllOperations[RandomNumber(1, 4) - 1];
}
enTestLevel GenerateLevel()
{
	return enTestLevel(RandomNumber(1, 3));
}
enOperation GenerateOp()
{
	return enOperation(RandomNumber(1, 4));
}
void GetAnswer(int num1, int num2, enOperation op, char& operation, int& answer)
{
	switch (op)
	{
	case enOperation::Addition:
		answer = num1 + num2;
		operation = '+';
		break;
	case enOperation::Subtraction:
		answer = num1 - num2;
		operation = '-';
		break;
	case enOperation::Multiplication:
		answer = num1 * num2;
		operation = 'x';
		break;
	case enOperation::Division:
		answer = num1 / num2;
		operation = '/';
		break;
	}
}
void CheckTestLevel(enTestLevel level, int& num1, int& num2)
{
	switch (level)
	{
	case enTestLevel::Easy:
		num1 = RandomNumber(1, 10);
		num2 = RandomNumber(1, 10);
		break;
	case enTestLevel::Medium:
		num1 = RandomNumber(10, 100);
		num2 = RandomNumber(1, 10);
		break;
	case enTestLevel::Hard:
		num1 = RandomNumber(10, 100);
		num2 = RandomNumber(10, 100);
		break;
	}
}
bool GenerateQuestion(stGameInfo GameInfo)
{
	if (GameInfo.OpType == enOperation::Mix)
		GameInfo.OpType = GenerateOp();
	if (GameInfo.QuestionsLevel == enTestLevel::_Mix)
		GameInfo.QuestionsLevel = GenerateLevel();
	int num1 = 0, num2 = 0, answer = 0;
	char operation;
	CheckTestLevel(GameInfo.QuestionsLevel, num1, num2);
	GetAnswer(num1, num2, GameInfo.OpType, operation, answer);
	cout << num1 << endl;
	cout << num2 << "   " << operation << "\n";
	cout << "__________________________\n";
	int PlayerAnswer = 0;
	cin >> PlayerAnswer;
	if (PlayerAnswer != answer)
	{
		system("color 4F");
		cout << "Wrong Answer :-(\n";
		cout << "The right answer: " << answer << '\n';
		return false;
	}
	else
	{
		system("color 2F");
		cout << "Right Answer :-)\n";
		return true;
	}

}
string PrintFinalResult(enResult result)
{
	string Results[3] = { "Pass :-)", "Fail :-(", "Draw :-|" };
	return Results[(int)result - 1];
}
enResult CheckFinalResult(stGameInfo Quizz)
{
	if (Quizz.NumberOfRightAnswers > Quizz.NumberofWrongAnswers)
		return enResult::Pass;
	else if (Quizz.NumberOfRightAnswers == Quizz.NumberofWrongAnswers)
		return enResult::Draw;
	return enResult::Fail;
}
string PrintLevel(enTestLevel level)
{
	string levels[4] = {"Easy" , "Medium", "Hard", "Mix"};
	return levels[(int)level - 1];
}
void ResetScreen()
{
	system("cls");
	system("color 0F");
}
bool IsGameEnd()
{
	char choice;
	cout << "\n\nDo you want to play again? Y/N\n";
	cin >> choice;
	if (choice == 'Y' || choice == 'y')
	{
		ResetScreen();
		return true;
	}

	return false;
}
void ShowFinalResults(stGameInfo GameInfo)
{
	system("cls");
	cout << "\n\n";
	cout << "_______________________________________\n\n";
	cout << "  Final Results is " << PrintFinalResult(GameInfo.FinalResult) << '\n';
	cout << "_______________________________________" << "\n\n";
	cout << "Number of Questions    : " << GameInfo.TotalQuestions << '\n';
	cout << "Questions   Level      : " << PrintLevel(GameInfo.QuestionsLevel) << '\n';
	cout << "Operation   Type       : " << PrintOperationType(GameInfo.OpType) << '\n';
	cout << "Number of Right Answers: " << GameInfo.NumberOfRightAnswers << '\n';
	cout << "Number of Wrong Answers: " << GameInfo.NumberofWrongAnswers << '\n';
	cout << "_______________________________________\n";



}
void GameSetup()
{
	stQuestionInfo QuestionInfo;
	stGameInfo GameInfo;
	GameInfo.TotalQuestions = AskForHowManyQuestions();
	GameInfo.QuestionsLevel = AskForTestLevel();
	GameInfo.OpType = AskForOperationType();
	GameInfo.NumberOfRightAnswers = 0;
	GameInfo.NumberofWrongAnswers = 0;
	for (int Question = 1; Question <= GameInfo.TotalQuestions; Question++)
	{
		QuestionInfo.CurrentQuestion = Question;

		cout << "\nQuestion [" << QuestionInfo.CurrentQuestion << '/' << GameInfo.TotalQuestions << ']' << "\n\n";
		
		if (GenerateQuestion(GameInfo))
			GameInfo.NumberOfRightAnswers++;
		else
			GameInfo.NumberofWrongAnswers++;
		GameInfo.FinalResult = CheckFinalResult(GameInfo);
	}

	ShowFinalResults(GameInfo);
}

int main()
{
	srand(unsigned(time(NULL)));

	do
	{
		GameSetup();
	} while (IsGameEnd());
	return 0;
}