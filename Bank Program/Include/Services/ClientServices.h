#pragma once

#include <vector>
#include <string>

#include "Model/Client.h"
#include "Utils/Enum.h"

using namespace std;


// Client Operations
void AddClient(vector<StClient>& Clients);

void DeleteClient(vector<StClient>& Clients);

void UpdateClientData(vector<StClient>& Clients);

void ShowClientsList(vector<StClient>& Clients);


// Search
StClient FindClient(
    const vector<StClient>& Clients,
    string AccountNumber
);

bool IsClientExisting(
    const string& AccountNumber,
    const vector<StClient>& Clients
);


// Transactions
void Deposit(
    vector<StClient>& Clients,
    const short& Maximum
);

void Withdraw(
    vector<StClient>& Clients,
    const short& Maximum
);

void ShowBalancesList(vector<StClient>& Clients);

double TotalBalances(
    const vector<StClient>& Clients
);


// Screens
void AddClientScreen(vector<StClient>& Clients);

void DeleteClientScreen(vector<StClient>& Clients);

void UpdateClientScreen(vector<StClient>& Clients);

void FindClientScreen(vector<StClient>& Clients);

void DepositScreen(vector<StClient>& Clients);

void WithdrawScreen(vector<StClient>& Clients);