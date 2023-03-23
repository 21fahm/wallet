#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void registration();

void deposit();

void withdraw();

void printBalance();

void myFunction();

int main() {
    cout << "\t\t\t________________________________________\n\n\n" << endl;
    cout << "\t\t\t      WELCOME TO CENTRALIZED WALLET       \n\n\n" << endl;
    cout << "\t\t\t____________      MENU       _____________\n\n" << endl;
    int choiceNum;
    Menu:
    cout << "Choose the option you want to proceed with" << endl;
    cout << "1.Create New Account" << endl;
    cout << "2.Deposit to existing Account" << endl;
    cout << "3.Withdraw from existing Account" << endl;
    cout << "4.Print all balances" << endl;
    cout << "5.Exit" << endl;
    cout << "Option:";
    cin >> choiceNum;
    switch (choiceNum) {
        case 1:
            registration();
            goto Menu;
        case 2:
            deposit();
            goto Menu;
            case 3:
                withdraw();
                goto Menu;
            case 4:
                printBalance();
                goto Menu;
        case 5:
            return 0;
        default:
            cout << "Invalid input" << endl;
            goto Menu;
    }
}

void registration() {
    string name;
    int accNum, onlyPass;
    double accBalance = 0.0;
    cout << "\nEnter account number:";
    cin >> accNum;
    cout << "Enter your Name:";
    cin>>name;
    cout << "Enter Password:";
    cin >> onlyPass;
    cout << "\n Registration Successful!!!" << endl;
    cout << "\nYour Name is " << name << endl;
    cout << "Your account Number is " << accNum << endl;
    cout << "Your password is " << onlyPass << endl << endl;
    ofstream accountDetails;
    accountDetails.open("account_details.csv");
    accountDetails << accNum << "," << name << "," << accBalance << "," << onlyPass << endl;
    accountDetails.close();
    ofstream accountTransaction("account_transaction.csv");
    accountTransaction << "No Transactions Available."<< endl;
    accountTransaction.close();
}

void deposit() {
    int accNum, id, Password,onlyPass;
    double deposit;
    double total,balance;
    string data, name;
    time_t now=time(nullptr);
    string date= ctime(&now);
    Try:
    cout << "\nEnter account number below" << endl;
    cout << "Account Number:";
    cin >> accNum;
    ifstream accDetail("account_details.csv");
    while (accDetail >> data) {
        stringstream stream(data);
        int count = 0;
        while (count < 4) {
            string read;
            getline(stream, read, ',');
            if (count == 0) id = stoi(read);
            if (count == 1) name = read;
            if (count == 2) balance = stod(read);
            if (count == 3) onlyPass = stoi(read);
            count++;
        }

        if (accNum == id) {
            dep:
            cout << "\nHow much do you want to deposit" << endl;
            cout << "Deposit:";
            cin >> deposit;
            if(deposit<=0){
                cout<<"\nDeposit must be greater than 0"<<endl;
                goto dep;
            }
            cout << "\nEnter password to confirm.(You have 3 tries only)\n";
            cout << "Enter password:";
            cin >> Password;
            } else {
            int tryNum;
            cout << "\nAccount number does not exist. Try again or begin by Creating New Account." << endl << endl;
            invalid:
            cout<<"1.Try again."<<endl;
            cout<<"2.Create account."<<endl;
            cout<<"Choice:";
            cin>>tryNum;
            switch (tryNum) {
                case 1:
                    goto Try;
                case 2:
                    registration();
                    continue;
                default:
                    cout<<"\nInvalid Choice. Try again."<<endl<<endl;
                    goto invalid;
            }
            }
        if (Password == onlyPass) {
            access:
        total=balance+deposit;
            ofstream accDetails("account_details.csv");
            accDetails << accNum << "," << name << "," << total << "," << onlyPass;
            accDetails.close();
            cout << "\nDeposit successful. Balance: " << total << endl << endl;
            ofstream accountTransaction("account_transaction.csv");
            accountTransaction << accNum << "," << date << "," << deposit << "," << total << "," << onlyPass;
            accountTransaction.close();
        }else{
            int guess=1;
            while(guess<3 && Password!= onlyPass){
                cout<<"\nIncorrect Password. ";
                cout<<"Enter Password:";
                cin>>Password;
                guess++;
            } if(guess==3 && Password!=onlyPass){
                string accName;
                cout<<"\nSeems You forgot your password."<<endl;
                cout<<"No worries lets try and recover it."<<endl;
                cout<<"\nEnter Name and Account number below"<<endl;
                cout<<"Account number:";
                cin>>accNum;
                cout<<"Name:";
                cin>>accName;
                if(accNum==id && accName==name){
                    cout<<"\nYour password is "<<onlyPass<<endl<<endl;
                }else{
                    cout<<"\nSeems you don\'t have an account. Try Creating one."<<endl<<endl;
                }
            } if(guess<=3 && Password==onlyPass){
                goto access;
            }
        }
    }
    accDetail.close();
}

void withdraw(){
    int accNum,password;
    int id,onlyPass;
    double balance;
    string data,name;
    time_t now=time(nullptr);
    string date= ctime(&now);
    double total,remove;
    Try:
    cout << "\nEnter account number below" << endl;
    cout << "Account Number:";
    cin >> accNum;
    ifstream accDetail("account_details.csv");
    while (accDetail>>data) {
        stringstream stream(data);
        int count = 0;
        while (count < 4) {
            string read;
            getline(stream, read, ',');
            if (count == 0) id = stoi(read);
            if (count == 1) name = read;
            if (count == 2) balance = stod(read);
            if (count == 3) onlyPass = stoi(read);
            count++;
        }

        if (accNum == id) {
            wit:
            cout << "\nHow much do you want to Withdraw." << endl;
            cout << "Withdraw:";
            cin >> remove;
            if(remove>balance){
                cout<<"\nNot enough funds. Your balance is "<<balance<<endl;
                goto wit;
            }
            if(remove==0){
                cout<<"\nWithdrawal must be greater than 0"<<endl;
                goto wit;
            }
            cout << "\nEnter password to confirm.(You have 3 tries only)\n";
            cout << "Enter password:";
            cin >> password;
        } else {
            int tryNum;
            cout << "\nAccount number does not exist. Try again or begin by Creating New Account." << endl << endl;
            invalid:
            cout<<"1.Try again."<<endl;
            cout<<"2.Create account."<<endl;
            cout<<"Choice:";
            cin>>tryNum;
            switch (tryNum) {
                case 1:
                    goto Try;
                case 2:
                    registration();
                    continue;
                default:
                    cout<<"\nInvalid Choice. Try again."<<endl<<endl;
                    goto invalid;
            }
        }
        if (password == onlyPass) {
            draw:
            total=balance-remove;
            ofstream accDetails("account_details.csv");
            accDetails << accNum << "," << name << "," << total << "," << onlyPass;
            accDetails.close();
            cout << "\nWithdraw successful. Balance: " << total << endl << endl;
            ofstream accountTransaction("account_transaction.csv");
            accountTransaction << accNum << "," << date << "," << total << "," << remove << "," << onlyPass;
            accountTransaction.close();
        }else{
            int guess=1;
            while(guess<3 && password!= onlyPass){
                cout<<"\nIncorrect Password. Try again."<<endl;
                cout<<"Password:";
                cin>>password;
                guess++;
            }
            if(guess==3 && password!=onlyPass){
                string accName;
                cout<<"\nSeems You forgot your password."<<endl;
                cout<<"No worries lets try and recover it."<<endl;
                cout<<"\nEnter Name and Account number below"<<endl;
                cout<<"Account number:";
                cin>>accNum;
                cout<<"Name:";
                cin>>accName;
                if(accNum==id && accName==name){
                    cout<<"\nYour password is "<<onlyPass<<endl<<endl;
                }else{
                    cout<<"\nSeems you don\'t have an account. Try Creating one."<<endl<<endl;
                }
            } if(guess<=3 && password==onlyPass){
                goto draw;
            }
        }
    }
    accDetail.close();
}
void printBalance() {
    int accNum, id, Password, onlyPass;
    double balance;
    string name, data;
    print:
    cout << "\nEnter account number and Password below" << endl;
    cout << "Account Number:";
    cin >> accNum;
    cout<<"Password:";
    cin>>Password;
    ifstream accDetail("account_details.csv");
    while (accDetail >> data) {
        stringstream stream(data);
        int count = 0;
        while (count < 4) {
            string read;
            getline(stream, read, ',');
            if (count == 0) id = stoi(read);
            if (count == 1) name = read;
            if (count == 2) balance = stod(read);
            if (count == 3) onlyPass = stoi(read);
            count++;
        }
        if(accNum==id && Password==onlyPass){
            cout<<"\nYour Account number is "<<id<<endl;
            cout<<"Your Name is "<<name<<endl;
            cout<<"Your Account balance is "<<balance<<endl<<endl;
        }else if(accNum==id && Password!=onlyPass){
            cout<<"\nAccount Number exist but the password is Invalid."<<endl;
            cout<<"Try again."<<endl<<endl;
            goto print;
        } else if(accNum!=id){
            string temp="does";
            int tryNum;
            cout<<"\nAccount number "<<temp.append("n\'t")<< " exist. Try again or Create an Account."<<endl<<endl;
            invalid:
            cout<<"1.Try again."<<endl;
            cout<<"2.Create account."<<endl;
            cout<<"Choice:";
            cin>>tryNum;
            switch (tryNum) {
                case 1:
                    goto print;
                case 2:
                    registration();
                    continue;
                default:
                    cout<<"\nInvalid Choice. Try again."<<endl<<endl;
                    goto invalid;
            }
        }
    }
    accDetail.close();
}

void myFunction(){
    for(int i=3;i>0;i--){
        cout<< "You have " + to_string(i) + " tries left";
    }
}
/**
* What we need to have:
 * Storage of Records. //Just add ios::app
 * Checking registration against the records.
 * Ignoring characters that have been capitalized during reading of records.
 * User not required to enter password or acc Number each time after registration ONLY! //Have the details under registration.
 * Check across what the user has entered when printing Balances.
 * ignore string to avoid program crash. //use the cin.ignore function
*/