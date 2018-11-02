#define _CRT_SECURE_NO_WARNINGS //To disable deprecation and secure warning
//libariries need for the project

#include <iostream>//Header that defines the standard input/output stream objects
#include <string.h>//This header file defines several functions to manipulate strings and arrays
#include <fstream>//Input/output stream class to operate on files
#include<conio.h>//manages input/output on console based application
#include<sstream>//Header providing string stream classes
#include <ctime> // time_t, struct tm, difftime, time, mktime 
using namespace std;
struct Date
{
	int Day, Month, Year;
};
struct Transictions
{
	string TypeOfTrans; //withdraw or deposite or Transfer
	int Amount; // the amount of withdraw or deposite or transfer
	Date D1;
};
struct Users
{
	string UserName;
	string UserPasword;
	int Balance;
	string Id;
	Transictions Tran[100];
	int NumberOfTrans;
};

struct Employee
{
	string EmployeeName;
	string EmployeePassword;
};
//to compare between entered value and struct value of the user
int  checkUsers(Users AllUsers[], int size, string Name, string Pass)
{
	int IndexOfUser; // is the number of user in array "ID"
	bool AccountExist = false;
	while (AccountExist == false){

		cout << "Enter your name : " << endl;
		cin >> Name;
		cout << "Enter your password : " << endl;
		char ch;
		ch = _getch();
		while (ch != 13){ //character 13 is enter
			Pass.push_back(ch);//The Pass is a string variable. The push_back() method puts the character specified as parameter at the end of the string.
			cout << '*';
			ch = _getch();
		}

		for (int i = 0; i < size; i++)
		{
			if (AllUsers[i].UserName == Name  && AllUsers[i].UserPasword == Pass)
			{
				IndexOfUser = i;
				AccountExist = true;
				break;
			}
		}
		if (AccountExist == false)
		{
			cout << endl;
			cout << "Wrong userName OR Password Please Try again " << endl;
			cout << "***********************************************************" << endl;
		}
		Pass.clear();//Erases the contents of the pass, which becomes an empty string (with a length of 0 characters)
	}


	return IndexOfUser; //to access the user account 
}
//to compare between entered value and struct value of the employee
bool checkEmploye(Employee AllEmploye[], int size, string Name, string Pass)
{
	cout << "Enter your name : " << endl;
	cin >> Name;
	cout << "Enter your password : " << endl;
	char ch;
	ch = _getch();
	while (ch != 13){//character 13 is enter
		Pass.push_back(ch);//The Pass is a string variable. The push_back() method puts the character specified as parameter at the end of the string.
		cout << '*';
		ch = _getch();
	}

	for (int i = 0; i < size; i++)
	{
		if (AllEmploye[i].EmployeeName == Name  && AllEmploye[i].EmployeePassword == Pass)
		{
			return true;
		}

	}
	cout << endl;
	cout << "Wrong userName OR Password Please Try again " << endl;
	cout << "***********************************************************" << endl;
	Pass.clear();//Erases the contents of the pass, which becomes an empty string (with a length of 0 characters)
	return false; 
}
//Get current date/time, format is YYYY-MM-DD
Date Time(){
	Date D;
	time_t now;
	struct tm  nowlocal;
	now = time(NULL);
	nowlocal = *localtime(&now);
	D.Day = nowlocal.tm_mday;
	D.Month = nowlocal.tm_mon + 1;
	D.Year = nowlocal.tm_year + 1900;

	return D;
}
//to access user account by his index in the array to know  his current balance
void BalanceOfUser(Users AllUsers[], int indexOfUser)
{
	cout << AllUsers[indexOfUser].Balance << "$" << endl;
}
//to access user account by his index in the array to make withdraw transaction
void  Withdraw(Users AllUsers[], int indexOfUser)
{
	int WithdrawAount;
	cin >> WithdrawAount; // the amount entered the user want to withdraw
	if (WithdrawAount > AllUsers[indexOfUser].Balance){
		cout << "****** Insufficient Funds! *******" << endl;
		cout << "****** please Check your Balance and Then Try again *******" << endl;
	}
	else{
		AllUsers[indexOfUser].Tran[AllUsers[indexOfUser].NumberOfTrans].TypeOfTrans = "Withdraw";
		AllUsers[indexOfUser].Tran[AllUsers[indexOfUser].NumberOfTrans].Amount = WithdrawAount;
		AllUsers[indexOfUser].Balance -= AllUsers[indexOfUser].Tran[AllUsers[indexOfUser].NumberOfTrans].Amount;
		AllUsers[indexOfUser].Tran[AllUsers[indexOfUser].NumberOfTrans].D1 = Time();
		AllUsers[indexOfUser].NumberOfTrans += 1;
		Date D = Time();
		ofstream updating;  
		updating.open("transactions.txt", std::ios_base::app); //upload in the file of transactions
		updating << indexOfUser + 1 << " " << "withdraw" << " " << WithdrawAount << " " << D.Day << " " << D.Month << " " << D.Year << endl;
		updating.close();
	}
}
//to access user account by his index in the array to make deposite transaction
void Deposit(Users AllUsers[], int indexOfUser)
{
	int DepositAmount;
	cin >> DepositAmount; // the amount entered the user want to deposite
	AllUsers[indexOfUser].Tran[AllUsers[indexOfUser].NumberOfTrans].TypeOfTrans = "Deposite";
	AllUsers[indexOfUser].Tran[AllUsers[indexOfUser].NumberOfTrans].Amount = DepositAmount;
	AllUsers[indexOfUser].Balance -= AllUsers[indexOfUser].Tran[AllUsers[indexOfUser].NumberOfTrans].Amount;
	AllUsers[indexOfUser].Tran[AllUsers[indexOfUser].NumberOfTrans].D1 = Time();
	AllUsers[indexOfUser].NumberOfTrans += 1;
	Date D = Time();
	ofstream updating;
	updating.open("transactions.txt", std::ios_base::app); //upload in the file of transactions
	updating << indexOfUser + 1 << " " << "Deposit" << " " << DepositAmount << " " << D.Day << " " << D.Month << " " << D.Year << endl;
	updating.close();
}
//last five transactions of the each user
void TransUser(Users AllUsers[], int indexOfUser)
{
	int LastTrans = 5;
	if (AllUsers[indexOfUser].NumberOfTrans<LastTrans){ LastTrans = AllUsers[indexOfUser].NumberOfTrans; }
	for (int i = AllUsers[indexOfUser].NumberOfTrans - 1, j = 0; j <LastTrans; j++, i--)
	{
		cout << AllUsers[indexOfUser].Tran[i].TypeOfTrans << " ";
		cout << AllUsers[indexOfUser].Tran[i].Amount << "   ";
		cout << AllUsers[indexOfUser].Tran[i].D1.Day << " "
			<< AllUsers[indexOfUser].Tran[i].D1.Month << " "
			<< AllUsers[indexOfUser].Tran[i].D1.Year << endl;

	}
}
//To transfer from one account to another user account
void Transfer(Users AllUsers[], int size, int indexofuser)
{
	string name;
	int amount;
	int indexOfOther;
	cin >> name;
	cout << "enter the amount you want to transfer " << endl;
	cin >> amount;
	for (int i = 0; i<size; i++){
		if (AllUsers[i].UserName == name){
			AllUsers[i].Tran[AllUsers[i].NumberOfTrans].Amount = amount;
			indexOfOther = i;
			break;
		}
	}
	AllUsers[indexofuser].Balance -= amount;
	AllUsers[indexOfOther].Balance += amount;
	AllUsers[indexofuser].Tran[AllUsers[indexofuser].NumberOfTrans].Amount = amount;
	AllUsers[indexofuser].Tran[AllUsers[indexofuser].NumberOfTrans].TypeOfTrans = "Transfer";
	AllUsers[indexofuser].Tran[AllUsers[indexofuser].NumberOfTrans].D1 = Time();
	AllUsers[indexofuser].NumberOfTrans += 1;
	Date D = Time();
	ofstream updating;
	updating.open("transactions.txt", std::ios_base::app); //upload in the file of transactions
	updating << indexofuser + 1 << " " << "Transfer" << " " << amount << " " << D.Day << " " << D.Month << " " << D.Year << endl;
	updating.close();
	updating.open("users.txt", std::ios_base::app);//upload in the file of users
	updating << AllUsers[indexofuser].UserName << " " << AllUsers[indexofuser].UserPasword << " " << AllUsers[indexofuser].Id << " " << AllUsers[indexofuser].Balance << endl;
	updating << AllUsers[indexOfOther].UserName << " " << AllUsers[indexOfOther].UserPasword << " " << AllUsers[indexOfOther].Id << " " << AllUsers[indexOfOther].Balance << endl;
	updating.close();

}
//daily transactions of the each user
void DailyTrans(Users AllUsers[], int size){
	Date D2 = Time();
	for (int i = 0; i<size; i++){
		for (int j = 0; j<AllUsers[i].NumberOfTrans; j++){
			if (D2.Day == AllUsers[i].Tran[j].D1.Day
				&& D2.Month == AllUsers[i].Tran[j].D1.Month
				&& D2.Year == AllUsers[i].Tran[j].D1.Year)  {

				cout << AllUsers[i].UserName << " " << AllUsers[i].Tran[j].TypeOfTrans << " ";
				cout << AllUsers[i].Tran[j].Amount << endl;
			}
		}
	}
}
//transactions of the user for the employee search
void TranForOneUser(Users AllUsers[], int size, string name){
	cin >> name; //the name of the user the employee want to search for his transactions
	for (int i = 0; i<size; i++){
		if (AllUsers[i].UserName == name){
			for (int j = 0; j <AllUsers[i].NumberOfTrans; j++){
				cout << AllUsers[i].Tran[j].TypeOfTrans << " " <<
					AllUsers[i].Tran[j].Amount << " " <<
					AllUsers[i].Tran[j].D1.Day << " " <<
					AllUsers[i].Tran[j].D1.Month << " " <<
					AllUsers[i].Tran[j].D1.Year << endl;
			}
			break;
		}
	}
}


int main()
{  //the variables needed for the code
	Users ArrayOfUsers[20];
	Employee ArrayOfEmployes[20];

	ifstream inFile1;
	string UserName, EmployeeName, TypeOfTrans;
	string UserPass, EmployeePass;
	string UserId, EmployeeId;
	Date DateOfTrans;
	double Balance, AmountOfTrans;
	inFile1.open("users.txt"); //opening the file of the users
	if (!inFile1)
	{
		cout << "Unable to open file!" << endl;
		return 0;
	}
	int IndexArrayOfUsers = 0;
	int IndexArrayOfEmployes = 0;
	while (!inFile1.eof())
	{
		Users u;
		inFile1 >> u.UserName;
		inFile1 >> u.UserPasword;
		inFile1 >> u.Id;
		inFile1 >> u.Balance;
		u.NumberOfTrans = 0;
		ArrayOfUsers[IndexArrayOfUsers] = u;
		IndexArrayOfUsers++;
	}
	inFile1.close();
	inFile1.open("employees.txt");//opening the file of the employees
	while (!inFile1.eof())
	{
		Employee e;
		inFile1 >> e.EmployeeName;
		inFile1 >> e.EmployeePassword;
		ArrayOfEmployes[IndexArrayOfEmployes] = e;
		IndexArrayOfEmployes++;
	}
	inFile1.close();
	inFile1.open("transactions.txt");//opening the file of the transactions
	while (!inFile1.eof())
	{
		string text;
		inFile1 >> text;
		for (int IndexTrans = 0; IndexTrans < IndexArrayOfUsers; IndexTrans++)
		{
			if (text == ArrayOfUsers[IndexTrans].Id)
			{

				Transictions T;
				inFile1 >> T.TypeOfTrans;
				inFile1 >> T.Amount;
				inFile1 >> T.D1.Day;
				inFile1 >> T.D1.Month;
				inFile1 >> T.D1.Year;
				ArrayOfUsers[IndexTrans].Tran[ArrayOfUsers[IndexTrans].NumberOfTrans] = T;
				ArrayOfUsers[IndexTrans].NumberOfTrans++;
				break;
			}


		}

	}
	inFile1.close();
	cout << "** Welcome to ATM machine ***" << endl;
	cout << "Please enter the number of The Account Type You Want To LogIn With : " << endl;
	cout << "***********************************************************" << endl;
	cout << " 1. User Account " << endl;
	cout << " 2. Employee Account " << endl;
	int AccountType, NumbOfActivity;
	cin >> AccountType;
	string XName, XPassword;

	int IndexOfUesr;
	switch (AccountType)
	{
	case 1:


		IndexOfUesr = checkUsers(ArrayOfUsers, 10, XName, XPassword);//calling the function of the checkuser
		cout << endl;
		cout << "******Welcome to the User Account******" << endl;
		cout << "*** MAIN MENU (enter number)*** : " << endl << endl;
		do{
			cout << "***********************************************************" << endl;
			cout << " 1. Deposit Cash " << endl;

			cout << " 2. Withdraw Cash " << endl;

			cout << " 3. Inquiry About Your Balance " << endl;

			cout << " 4. Report About Your Last 5 Transactions " << endl;
			cout << " 5. Transfer From Your Acount To Another" << endl;
			cout << " 6.Do you want to exit" << endl;
			cin >> NumbOfActivity;
			switch (NumbOfActivity)
			{
			case 1:
				cout << " *** Please Enter Sum You Wish To Deposit In Your account *** " << endl;
				Deposit(ArrayOfUsers, IndexOfUesr);//calling the function of the deposit
				break;
			case 2:
				cout << " *** Please Enter Sum You Wish To Withdraw From Your account *** " << endl;
				Withdraw(ArrayOfUsers, IndexOfUesr);//calling the function of withdraw
				break;
			case 3:
				cout << " *** Inquiry about you balance : *** " << endl;
				BalanceOfUser(ArrayOfUsers, IndexOfUesr);//calling the function of balanceofuser
				break;
			case 4:
				cout << "*** Last 5 Transactions ***" << endl;
				TransUser(ArrayOfUsers, IndexOfUesr);//calling the function of the transuser
				break;
			case 5:
				cout << "***enter the username of the account you want to Transfer the amount to:***" << endl;
				Transfer(ArrayOfUsers, 10, IndexOfUesr);//calling the function of the transfer

				break;
			case 6:
				cout << " *** Thank You for Using Our Service *** " << endl;
				return 0;// to view the main menu of the user again
			}
		} while (true);
		break;
	case 2:
		bool LogIn = checkEmploye(ArrayOfEmployes, 10, XName, XPassword);//calling the function of the chechemployee
		while (LogIn == false){ LogIn = checkEmploye(ArrayOfEmployes, 10, XName, XPassword); }
		cout << endl;
		cout << "******Welcome to the employee Account******" << endl;
		cout << "*** MAIN MENU (enter number) *** :" << endl << endl;
		do{
			cout << "1.Daily report transactions : " << endl;
			cout << "2.Search for all transactions for specific account : " << endl;
			cout << "3.Do you want to exit" << endl;
			cin >> NumbOfActivity;
			string name;
			switch (NumbOfActivity)
			{
			case 1: cout << "****Daily report transactions ****" << endl;
				DailyTrans(ArrayOfUsers, 10);//calling the function of dailytrans

				break;

			case 2:cout << "enter the name of the user to search for him " << endl;
				TranForOneUser(ArrayOfUsers, 10, name);//calling the function of transforoneuser
				break;

			case 3:
				cout << " *** Thank You for Using Our Service *** " << endl;
				return 0; // to view the main menu of the employee again

			}
		} while (true);


		return 0;
	}

}