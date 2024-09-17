/*
	ATM System
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;

string ClientFileName = "Clients.txt";

enum enATMMainMenuOption
{
	enQuickWithdraw = 1, enNormalWithdraw = 2, enDeposit = 3,
	enCheckBalance = 4, enLogout = 5
};

struct stClient
{
	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	double Balance = 0;
	bool MarkForDelete = false;
};

stClient CurrentClient;

void Login();
void ShowATMMainMenuScreen();
vector <stClient> LoadClientsDateFromFile(string FileName);
void ShowQuickWithdrawScreen();
void ShowNormalWithdrawScreen();

short ReadATMOption()
{
	short Option = 0;

	cout << "Choose what do you want to do? [1 to 5]? ";
	cin >> Option;

	return Option;
}

string ReadAccountNumber()
{
	string AccountNumber;

	cout << "Enter Account Number? ";
	cin >> AccountNumber;

	return AccountNumber;
}

string ReadPinCode()
{
	string PinCode;

	cout << "Enter Pin? ";
	cin >> PinCode;

	return PinCode;
}

short ReadQuickWithdrawOption()
{
	short Option = 0;

	while (Option < 1 || Option > 9)
	{
		cout << "Choose what to do from[1] to [9] ? ";
		cin >> Option;
	}

	return Option;
}

int ReadAmountWithdraw()
{
	int Amount = 0;

	do
	{
		cout << "\nEnter an amount multiple of 5's ? ";
		cin >> Amount;

	} while (Amount % 5 != 0);

	return Amount;
}

double ReadAmountDeposit()
{
	double Amount = 0;

	do
	{
		cout << "\nEnter a Positive Deposit Amount? ";
		cin >> Amount;

	} while (Amount <= 0);

	return Amount;
}

void GoBackToATMMainMenu()
{
	cout << "\n\nPress any key to go back to Main Menu...\n";
	system("pause > 0");
	ShowATMMainMenuScreen();
}

void ShowErrorBalanceMessage()
{
	cout << "\nThe amount exceeds your balance, make another choice.\n";
	cout << "Press AnyKey to continue...\n";
	system("pause > 0");
	ShowQuickWithdrawScreen();
}

string ConvertRecordToLine(stClient Client, string Separator = "#//#")
{
	string stLine = "";

	stLine += Client.AccountNumber + Separator;
	stLine += Client.PinCode + Separator;
	stLine += Client.Name + Separator;
	stLine += Client.Phone + Separator;
	stLine += to_string(Client.Balance);

	return stLine;
}

void SaveDataFileToRecord(vector <stClient> vClients, string FileName)
{
	fstream MyFile;

	MyFile.open(FileName, ios::out);

	if (MyFile.is_open())
	{
		for (stClient& C : vClients)
		{
			string stLine = ConvertRecordToLine(C);
			MyFile << stLine << endl;
		}
		MyFile.close();
	}
}

void UpdateRecordInFile(string FileName)
{
	vector <stClient> vClients = LoadClientsDateFromFile(FileName);

	for (stClient& C : vClients)
	{
		if (C.AccountNumber == CurrentClient.AccountNumber)
		{
			C.Balance = CurrentClient.Balance;
			break;
		}
	}

	SaveDataFileToRecord(vClients, FileName);
}

short GetWithDrawBalance(short OptionChoice)
{
	switch (OptionChoice)
	{
	case 1:
		return 20;
	case 2:
		return 50;
	case 3:
		return 100;
	case 4:
		return 200;
	case 5:
		return 400;
	case 6:
		return 600;
	case 7:
		return 800;
	case 8:
		return 1000;
	}
}

void PerformQuickWithdrawOption(short OptionChoice)
{
	if (OptionChoice == 9)
		return;

	short WithDrawBalance = GetWithDrawBalance(OptionChoice);

	if (WithDrawBalance > CurrentClient.Balance)
	{
		cout << "\nThe amount exceeds your balance, make another choice.\n";
		cout << "Press AnyKey to continue...";
		system("pause > 0");
		ShowQuickWithdrawScreen();
		return;
	}

	char Answer = 'n';

	cout << "\n\nAre you sure you want perform this transactions? y/n? ";
	cin >> Answer;

	if (toupper(Answer) == 'Y')
	{
		CurrentClient.Balance -= WithDrawBalance;
		UpdateRecordInFile(ClientFileName);
		cout << "\n\nDone Successfully. New balance is: " << CurrentClient.Balance << endl;
	}

}

void PerformNormalWithdraw()
{
	int AmountWithDraw = ReadAmountWithdraw();

	if (AmountWithDraw > CurrentClient.Balance)
	{
		cout << "\nThe amount exceeds your balance, make another choice.\n";
		cout << "Press Anykey to continue...\n";
		system("pause > 0");
		ShowNormalWithdrawScreen();
		return;
	}

	char Answer = 'n';
	cout << "\n\nAre you sure you want perform this transaction? y/n? ";
	cin >> Answer;

	if (toupper(Answer) == 'Y')
	{
		CurrentClient.Balance -= AmountWithDraw;
		UpdateRecordInFile(ClientFileName);
		cout << "\n\nDone Successfully. New balance is: " << CurrentClient.Balance << endl;

	}

}

void PerformDeposit()
{
	int Amount = ReadAmountDeposit();
	char Answer = 'n';

	cout << "\n\nAre you sure you want perfrom this transaction? y/n? ";
	cin >> Answer;

	if (toupper(Answer) == 'Y')
	{
		CurrentClient.Balance += Amount;
		UpdateRecordInFile(ClientFileName);
		cout << "\n\nDone Successfully. New balance is: " << CurrentClient.Balance << endl;
	}

}

void ShowDepositScreen()
{
	cout << "============================================ \n";
	cout << "\t\tNormal Withdraw Screen";
	cout << "\n============================================ \n";
	PerformDeposit();
}

void ShowNormalWithdrawScreen()
{
	cout << "============================================ \n";
	cout << "\t\tNormal Withdraw Screen";
	cout << "\n============================================ \n";
	PerformNormalWithdraw();
}

void ShowBalanceScreen()
{
	cout << "============================================ \n";
	cout << "\t\tShow Balance Screen";
	cout << "\n============================================ \n";

	cout << "Your Balance is " << CurrentClient.Balance << endl;
}

void ShowQuickWithdrawScreen()
{
	system("cls");
	cout << "============================================ \n";
	cout << "\t\tQuick Withdraw";
	cout << "\n============================================ \n";
	cout << "\t[1] 20\t\t[2] 50\n";
	cout << "\t[3] 100\t\t[4] 200\n";
	cout << "\t[5] 400\t\t[6] 600\n";
	cout << "\t[7] 800\t\t[8] 1000\n";
	cout << "\t[9] Exit\n";
	cout << "============================================ \n";
	cout << "Your Balance is " << CurrentClient.Balance << endl;
	PerformQuickWithdrawOption(ReadQuickWithdrawOption());
}

void PerformATMMainMenuOption(enATMMainMenuOption ATMMainMenuOption)
{
	switch (ATMMainMenuOption)
	{
	case enATMMainMenuOption::enQuickWithdraw:

		system("cls");
		ShowQuickWithdrawScreen();
		GoBackToATMMainMenu();
		break;

	case enATMMainMenuOption::enNormalWithdraw:

		system("cls");
		ShowNormalWithdrawScreen();
		GoBackToATMMainMenu();
		break;

	case enATMMainMenuOption::enDeposit:

		system("cls");
		ShowDepositScreen();
		GoBackToATMMainMenu();
		break;

	case enATMMainMenuOption::enCheckBalance:

		system("cls");
		ShowBalanceScreen();
		GoBackToATMMainMenu();
		break;

	case enATMMainMenuOption::enLogout:

		system("cls");
		Login();
		break;

	default:

		system("cls");
		cout << "Error!Not Correct Number Enter Valid Number...\n";
		GoBackToATMMainMenu();
		break;
	}
}

void ShowATMMainMenuScreen()
{
	system("cls");
	cout << "============================================ \n";
	cout << "\t\tATM Main Menu Screen";
	cout << "\n============================================ \n";
	cout << "\t[1] Quick Withdraw.\n";
	cout << "\t[2] Normal Withdraw.\n";
	cout << "\t[3] Deposit.\n";
	cout << "\t[4] Check Balance.\n";
	cout << "\t[5] Logout.\n";
	cout << "============================================ \n";
	PerformATMMainMenuOption((enATMMainMenuOption)ReadATMOption());
}

vector <string> splittingString(string stLine, string Separator)
{
	vector <string> vString;
	short FindPos;
	string sWord;

	while ((FindPos = stLine.find(Separator)) != stLine.npos)
	{
		sWord = stLine.substr(0, FindPos);

		if (sWord != "")
			vString.push_back(sWord);

		stLine.erase(0, FindPos + Separator.length());
	}

	if (stLine != "")
		vString.push_back(stLine);

	return vString;
}

stClient ConvertLineToRecord(string stLine, string Delim = "#//#")
{
	stClient Client;
	vector <string> vString = splittingString(stLine, Delim);

	Client.AccountNumber = vString[0];
	Client.PinCode = vString[1];
	Client.Name = vString[2];
	Client.Phone = vString[3];
	Client.Balance = stod(vString[4]);

	return Client;
}

vector <stClient> LoadClientsDateFromFile(string FileName)
{
	vector <stClient> vClients;
	fstream MyFile;

	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		string stLine;
		while (getline(MyFile, stLine))
		{
			stClient Client = ConvertLineToRecord(stLine);
			vClients.push_back(Client);
		}

		MyFile.close();
	}

	return vClients;
}

bool FindClientByAountNumbeAndPinCode(string AccountNumber, string PinCode)
{
	vector <stClient> vClients = LoadClientsDateFromFile(ClientFileName);
	for (stClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber && C.PinCode == PinCode)
		{
			CurrentClient = C;
			return true;
		}
	}

	return false;
}

void ShowLoginScreen()
{
	cout << "--------------------------------------------- \n";
	cout << "\t\tLogin Screen";
	cout << "\n--------------------------------------------- \n";
}

bool CheckLogin()
{
	string AccountNumber, PinCode;
	bool LoginFailed = false;

	do
	{
		system("cls");
		ShowLoginScreen();

		if (LoginFailed)
		{
			cout << "Invlaid Account Number/PinCode!\n";
		}

		AccountNumber = ReadAccountNumber();
		PinCode = ReadPinCode();

		LoginFailed = !FindClientByAountNumbeAndPinCode(AccountNumber, PinCode);

	} while (LoginFailed);

	return true;
}

void Login()
{
	if (CheckLogin())
	{
		ShowATMMainMenuScreen();
	}
}

int main()
{
	Login();

	system("pause > 0");
	return 0;
}