#ifndef BANKINGAPP_BANKAPP_H
#define BANKINGAPP_BANKAPP_H
#include <iostream>
using namespace std;

class BankApp{
public:

    //constructor
    BankApp();

    //setters
    void SetInitInvestment(double t_investment);
    void SetMonthlyDeposit(double t_deposit);
    void SetAnnualInterest(double t_interest);
    void SetNumYears(int years);

    //getters
    double GetInitInvestment();
    double GetMonthlyDeposit();
    double GetAnnualInterest();
    int GetNumYears();

    //object specific functions
    void PrintValues();
    void WithoutDeposit();
    void WithDeposit();
    void ByMonth();

private:

    // class variables
    double* m_initInvestment;
    double* m_monthlyDeposit;
    double* m_annualInterest;
    int* m_numYears;

};


#endif //BANKINGAPP_BANKAPP_H
