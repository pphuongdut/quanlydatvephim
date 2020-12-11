#pragma once
#include "DatabaseAccess.h"
class Account;
class AccountAccess :
    public DatabaseAccess
{
public:
    void Select(Account *&);
    int CountRow();
    bool Insert();
    int Search(int); // search theo id_number
    bool Update();
    bool Delete();
    void Show();
    int SearchName(string);

};

