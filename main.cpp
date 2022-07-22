#include "BankApp.h"
#include <iostream>
#include <iomanip>

using namespace std;

// function prototypes
void getInput(BankApp& account);
void programPause();
void clearWindow();

int main() {

    // variable declaration/intialization
    char userInput = 'y';
    auto bankAccount = make_unique<BankApp>();

    // main program loop
    while(tolower(userInput) == 'y'){
        clearWindow();

        getInput(*bankAccount);

        bankAccount->PrintValues();
        bankAccount->WithoutDeposit();
        bankAccount->WithDeposit();

        // test that the correct balance and interest values are being calculated
        //test->ByMonth();

        cout << "Input new values? [Y/N] ";
        cin >> userInput;
    }
    
    cout << "\nThe program has ended" << endl;

    return 0;
}



