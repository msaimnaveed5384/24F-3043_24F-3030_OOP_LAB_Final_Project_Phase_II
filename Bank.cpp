#include "Stronghold.h"
Bank::Bank() {
	loan_amount = 0;
	interest_rate = 5;
}
void Bank::take_loan(Economy& eco) {
	int loan = rand() % 300 + 200;
	loan_amount += loan;
	eco.treasury += loan;
	cout << "Took a loan of " << loan << " gold." << endl;
}
void Bank::repay_loan(Economy& eco) {
	int repayment = (loan_amount * (100 + interest_rate)) / 100;
	if (eco.treasury >= repayment) {
		eco.treasury -= repayment;
		loan_amount = 0;
		cout << "Loan repaid with interest. Total paid: " << repayment << endl;
	}
	else {
		cout << "Not enough treasury to repay the loan." << endl;
	}
}

void Bank::status_report() const {
	cout << "Loan: " << loan_amount << " gold, Interest Rate: " << interest_rate << "%" << endl;
}
