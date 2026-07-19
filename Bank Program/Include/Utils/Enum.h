#pragma once



enum enOperationType
{
    enShow = 1,
    enAdd = 2,
    enDelete = 3,
    enUpdate = 4,
    enFind = 5,
    enTransactions = 6,
    enManageUsers = 7,
    enLogout = 8
};


enum enTransactionsType
{
    enDeposit = 1,
    enWithdraw = 2,
    enShowBalances = 3,
    enMainMenu = 4
};


enum enManageType
{
    enUsersList = 1,
    enAddUser = 2,
    enDeleteUser = 3,
    enUpdateUser = 4,
    enFindUser = 5,
    enBackMainMenu = 6
};


enum enPermissions
{
    pShowClients = 1,
    pAddClient = 2,
    pDeleteClient = 4,
    pUpdateClient = 8,
    pFindClient = 16,
    pTransactions = 32,
    pManageUsers = 64
};