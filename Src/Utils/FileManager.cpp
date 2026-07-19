#include "Utils/FileManager.h"

#include <fstream>
#include <sstream>
#include <iomanip>

#include "Utils/Utils.h"

using namespace std;




StClient ConvertLineDataToRecord(string Text)
{
	StClient Client;
	const string Delim = "#//#";
	vector <string> Data = SplitWords(Text, Delim);

	int I = 0;
	if (Data.size() < 5)
		return Client;

	Client.AccountNumber = Data[I++];

	Client.PinCode = Data[I++];

	Client.Name = Data[I++];

	Client.Phone = Data[I++];

	try {
		Client.AccountBalance = stod(Data[I++]);
	}
	catch (...) {
		Client.AccountBalance = 0;
	}


	return Client;
}
StUser ConvertLineUserDataToRecord(string Text)
{
	StUser User;
	const string Delim = "#//#";
	vector <string> Data = SplitWords(Text, Delim);

	int I = 0;
	if (Data.size() < 3)
		return User;

	User.UserName = Data[I++];

	User.Passowrd = Data[I++];

	User.Permissions = stod(Data[I++]);

	return User;
}

string ConvertRecordToLine(const StClient& Client)
{
	ostringstream out;

	const string Delim = "#//#";
	out << Client.AccountNumber + Delim
		<< Client.PinCode + Delim
		<< Client.Name + Delim
		<< Client.Phone + Delim
		<< fixed << setprecision(2) << (Client.AccountBalance);


	return out.str();
}
string ConvertUserRecordToLine(const StUser& User)
{
	ostringstream out;

	const string Delim = "#//#";
	out << User.UserName + Delim
		<< User.Passowrd + Delim
		<< User.Permissions;

	return out.str();
}


vector <StClient> LoadClientDataFromFile(const string& FileName)
{
	vector <StClient> ClientsData;
	fstream ClientsFile;

	ClientsFile.open(FileName, ios::in);

	if (ClientsFile.is_open())
	{
		string Line;
		StClient Client;

		while (getline(ClientsFile, Line))
		{
			Client = ConvertLineDataToRecord(Line);
			if (!Client.AccountNumber.empty())
				ClientsData.push_back(Client);

		}
		ClientsFile.close();
	}
	return ClientsData;

}
vector <StUser> LoadUserDataFromFile(const string& FileName)
{
	vector <StUser> UsersData;
	fstream UsersFile;

	UsersFile.open(FileName, ios::in);

	if (UsersFile.is_open())
	{
		string Line;
		StUser User;

		while (getline(UsersFile, Line))
		{
			User = ConvertLineUserDataToRecord(Line);
			if (!User.UserName.empty())
				UsersData.push_back(User);

		}
		UsersFile.close();
	}
	return UsersData;

}

void LoadDataToFile(const string& FileName, const string& Data)
{
	fstream ClientsFile;

	ClientsFile.open(FileName, ios::out | ios::app);

	if (ClientsFile.is_open())
	{
		ClientsFile << Data << endl;
		ClientsFile.close();
	}
}
void LoadUserDataToFile(const string& FileName, const string& Data)
{
	fstream UsersFile;

	UsersFile.open(FileName, ios::out | ios::app);

	if (UsersFile.is_open())
	{
		UsersFile << Data << endl;
		UsersFile.close();
	}
}

void SaveUsersToFile(const string& FileName, const vector<StUser>& Users)
{
	fstream File;
	File.open(FileName, ios::out);

	if (File.is_open())
	{
		for (const StUser& User : Users)
		{
			File << ConvertUserRecordToLine(User) << endl;
		}
		File.close();
	}
}
void SaveClientsToFile(const string& FileName, const vector<StClient>& Clients)
{
	fstream File;
	File.open(FileName, ios::out);

	if (File.is_open())
	{
		for (const StClient& Client : Clients)
		{
			File << ConvertRecordToLine(Client) << endl;
		}
		File.close();
	}
}
