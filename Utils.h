#pragma once

#include <vector>
#include <string>

#include "Client.h"
#include "User.h"
#include "Enum.h"

using namespace std;


// String Functions
vector<string> SplitWords(
    string Text,
    string Delim
);


// Client Input
StClient ReadClientDataToAdd(
    const vector<StClient>& Clients
);

StClient ReadClientDataToUpdate();


// User Input
StUser ReadUserDataToAdd(
    const vector<StUser>& Users
);

StUser ReadUserDataToUpdate();

StUser ReadUserDataToLogin();


// Reading Data
string ReadAccountNumber();

string ReadUesrName();

string ReadUserPassword();

double ReadValidBalance();

short ReadValidOperationNum(
    const short& NumberOfOperations
);

short ReadPermissions();


// Menus Reading
short ReadOperationType();

short ReadTransactionType();

short ReadManageUsersType();


// Validation
bool IsClientExisting(
    const string& AccountNumber,
    const vector<StClient>& Clients
);

bool IsUserExisting(
    const string& UserName,
    const vector<StUser>& Users
);

bool IsUserDataValid(
    const StUser& UserToCheck,
    const vector<StUser>& Users
);


// Permission
bool CheckPermission(
    StUser& User,
    short Permission
);

short GetPermission(
    short OperationType
);


// Confirmations
bool ConfirmOperation(
    string OperationType,
    string Name
);

bool ConfirmTransaction();

bool AddAnotherClient();

bool AddAnotherUser();


// Printing Clients
void PrintClientRecord(
    const StClient& Client
);

void PrintClientRecordOfLine(
    const StClient& Client
);

void PrintClientBalanceOfLine(
    const StClient& Client
);

void PrintClientsOfList(
    const vector<StClient>& Clients
);

void PrintBalancesOfList(
    const vector<StClient>& Clients
);


// Printing Users
void PrintUserRecord(
    const StUser& User
);

void PrintUserRecordOfLine(
    const StUser& User
);

void PrintUsersOfList(
    const vector<StUser>& Users
);


// Other
double TotalBalances(
    const vector<StClient>& Clients
);

void NoPermission();


// Screens
void MainMenuScreen();

void TransactionsMenuScreen();

void ManageUsersMenuScreen();


void ReturnMainMenuScreen();

void ReturnTransactionsMenuScreen();

void ReturnManageUsersMenuScreen();

