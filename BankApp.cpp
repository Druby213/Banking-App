#include <iostream>
#include <iomanip>
#include "BankApp.h"

using namespace std;

//FREE FUNCTIONS

// convert double to string that can be printed in monetary format
string ToString(double numToConvert){
    stringstream stream;
    stream << fixed << setprecision(2) << setfill('0') << numToConvert;
    return "$" + stream.str();
}

// clear the terminal window
void clearWindow(){

    #ifdef _WIN32
        system("CLS");
    #endif

    #ifdef __unix__
        system("clear");
    #endif
}

// pause the program until the user presses enter
void programPause(){
    //string temp;
    #ifdef _WIN32
        system("pause");
    #endif

    #ifdef __unix__
        cin.ignore();
        cout << "Press enter to continue...";
        cin.get(); //"pause" the program until the user presses enter
        system("clear"); //clear the console
    #endif
}

// prompt user for input to initialize BankApp object
void getInput(BankApp& account){
    double doubleInput;
    int intInput;

    cout << "**********************************" << endl;
    cout << "********** Data Input ************" << endl;

    cout << "Initial Investment Amount: $";
    cin >> doubleInput;
    account.SetInitInvestment(doubleInput);

    cout << "Monthly Deposit: $";
    cin >> doubleInput;
    account.SetMonthlyDeposit(doubleInput);

    cout << "Annual Interest: %";
    cin >> doubleInput;
    account.SetAnnualInterest(doubleInput);

    cout << "Number of years: ";
    cin >> intInput;
    account.SetNumYears(intInput);

    programPause();
}

//BANKAPP CLASS FUNCTIONS

//constructor
BankApp::BankApp(){
    m_initInvestment = new double;
    *m_initInvestment = 1.00;
    m_monthlyDeposit = new double;
    *m_monthlyDeposit = 1.00;
    m_annualInterest = new double;
    *m_annualInterest = 1.00;
    m_numYears = new int;
    *m_numYears = 1;
}

//SETTERS

//set initial investment
void BankApp::SetInitInvestment(double t_investment){
    *m_initInvestment = t_investment;
}

//set monthly deposits
void BankApp::SetMonthlyDeposit(double t_deposit){
    *m_monthlyDeposit = t_deposit;
}

//set annual interest percentage
void BankApp::SetAnnualInterest(double t_interest){
    *m_annualInterest = t_interest;
}

//set number of years to calculate
void BankApp::SetNumYears(int t_years){
    *m_numYears = t_years;
}

//GETTERS

//get the initial investment value
double BankApp::GetInitInvestment(){
    return *m_initInvestment;
}

// get the monthly deposit value
double BankApp::GetMonthlyDeposit(){
    return *m_monthlyDeposit;
}

//get the annual interest value
double BankApp::GetAnnualInterest(){
    return *m_annualInterest;
}

//get the number of years to calculate
int BankApp::GetNumYears(){
    return *m_numYears;
}

//OBJECT RELATED FUNCTIONS

//print the values that the user entered
void BankApp::PrintValues() {
    cout << "**********************************" << endl;
    cout << "********** Data Input ************" << endl;
    cout << fixed << setprecision(2) << setfill('0');
    cout << "Initial Investment Amount: $" << *m_initInvestment << endl;
    cout << "Monthly Deposit: $" << *m_monthlyDeposit << endl;
    cout << "Annual Interest: %" << *m_annualInterest << endl;
    cout << "Number of years: " << *m_numYears << endl;
    cout << endl;
}

//calculate year-end balance and earned interest if monthly deposits are NOT made
void BankApp::WithoutDeposit(){
    double balance = *m_initInvestment;
    double monthlyRate = ((*m_annualInterest/100)/12);
    double yearlyInterestEarned;
    double tempInterest;
    unsigned int i;
    unsigned int j;

    cout << "    Balance and Interest With Additional Monthly Deposits       " << endl;
    cout << setfill('=') << setw(64) << '=' << endl;
    cout << setfill(' ') << setw(6) << "Year";
    cout << setw(23) << "Year End Balance";
    cout << setw(31) << "Year End Earned Interest" << endl;
    cout << setfill('-') << setw(64) << '-' << endl;

    // for each year in m_numYears calculate balance and yearly earned interest
    for (i = 1; i <= *m_numYears; ++i){

        // calculate the balance and earned interest for each month of the year
        // this should be calculated on a monthly bases otherwise the results will be incorrect
        for (j = 0; j < 12; ++j){

            tempInterest = balance * monthlyRate;
            yearlyInterestEarned = yearlyInterestEarned + tempInterest;
            balance = balance + tempInterest;
        }

        cout << setw(6) << setfill(' ') << i;
        cout << setw(23) << ToString(balance);
        cout << setw(31) << ToString(yearlyInterestEarned) << endl;

        yearlyInterestEarned = 0;
    }
    cout << endl;
}

//calculate year-end balance and earned interest if monthly deposits are made
void BankApp::WithDeposit(){
    double balance = *m_initInvestment;
    double monthlyRate = ((*m_annualInterest/100)/12);
    double yearlyInterestEarned;
    double tempInterest;
    unsigned int i;
    unsigned int j;

    cout << "    Balance and Interest With Additional Monthly Deposits       " << endl;
    cout << setfill('=') << setw(64) << '=' << endl;
    cout << setfill(' ') << setw(6) << "Year";
    cout << setw(23) << "Year End Balance";
    cout << setw(31) << "Year End Earned Interest" << endl;
    cout << setfill('-') << setw(64) << '-' << endl;

    // for each year in m_numYears calculate balance and yearly earned interest
    for (i = 1; i <= *m_numYears; ++i){
        
        // calculate the balance and earned interest for each month of the year
        // balance and earned interest must be calculated for each month in order to get the correct results for the yearly total
        for (j = 0; j < 12; ++j){

            balance = (balance + *m_monthlyDeposit);
            tempInterest = balance * monthlyRate;
            yearlyInterestEarned = yearlyInterestEarned + tempInterest;
            balance = balance + tempInterest;
        }

        cout << setw(6) << setfill(' ') << i;
        cout << setw(23) << ToString(balance);
        cout << setw(31) << ToString(yearlyInterestEarned) << endl;

        yearlyInterestEarned = 0;
    }
    cout << endl;
}

//calculate the current balance and earned interest at the end of each month
//this is only used for testing to confirm that the correct values are being calculated
void BankApp::ByMonth(){
    double balance = *m_initInvestment;
    double monthlyRate = ((*m_annualInterest/100)/12);
    int numMonths = *m_numYears * 12;
    double interestEarned;
    double tempInterest;
    unsigned int i;

    cout << "                   Balance and Interest Broken Down by Month" << endl;
    cout << setfill('=') << setw(100) << '=' << endl;
    cout << setfill(' ') << setw(6) << "Month";
    cout << "     Opening Amount";
    cout << "     Deposited Amount";
    cout << "         $Total";
    cout << "         $Interest";
    cout << "     Closing Balance" << endl;
    cout << setfill('-') << setw(100) << '-' << endl;

    for (i = 1; i <= numMonths; ++i){

        cout << setfill(' ');
        cout << setw(6) << i; //month
        cout << setw(19) << ToString(balance); //original balance
        cout << setw(21) << ToString(*m_monthlyDeposit); //deposit amount

        balance = (balance + *m_monthlyDeposit);

        cout << setw(15) << ToString(balance); //original balance + deposit amount

        tempInterest = balance * monthlyRate;

        cout << setw(18) << ToString(tempInterest); //combined interest amount

        interestEarned = interestEarned + tempInterest;
        balance = balance + tempInterest;

        cout << setw(20) << ToString(balance) << "\n\n"; //balance + deposit + interest
    }
    cout << endl;
}
