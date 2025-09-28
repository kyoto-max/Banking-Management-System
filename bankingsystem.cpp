#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;

class Openaccount
{
private:
    string fname;
    string lname;
    float balance;
public:
    static int accountnumber;
    void setfname(string fname);
    string getfname();
    void setlname(string lname);
    string getlname();
    void setbalance(float balance);
    float getbalance();
    static int getaccnumber(){
        return accountnumber;
    }
    friend ofstream & operator<<(ofstream &ofs, Openaccount &o);
    friend ifstream & operator>>(ifstream &ifs, Openaccount &i);
    void setaccountnumber();
    void showaccount();
    void balanceenquiry();
    void withdraw();
    void deposit();
    void deleteacc();
};
int Openaccount::accountnumber=0;
void openaccountfunction();

int main(){
    Openaccount o;
    o.setaccountnumber();
    int choice;
    cout<<endl<<"********** Banking System **********"<<endl;

    do
    {
        cout<<"\n\tSelect one option below ";
        cout<<"\n\t1 Open an Account";
        cout<<"\n\t2 Balance Enquiry";
        cout<<"\n\t3 Deposit";
        cout<<"\n\t4 Withdrawal";
        cout<<"\n\t5 Close an Account";
        cout<<"\n\t6 Show All Accounts";
        cout<<"\n\t7 Quit";
        cout<<"\nEnter your choice: ";
        cin>>choice;
        switch (choice)
        {

        case 1:
            openaccountfunction();
            break;
        case 2:
            o.balanceenquiry();
            break;
        case 3:
            o.deposit();
            break;
        case 4:
            o.withdraw();
            break; 
        case 5:
            o.deleteacc();
            break;
        case 6:
            o.showaccount();
            break;
        case 7:
            cout<<endl<<"Thanks for using the system"<<endl<<endl;
            exit(0);
        default:
            cout<<"No option found having number "<<choice<<endl;
            break;
        }
    }while(choice!=7);
    return 0;
}

void openaccountfunction(){
        string fname;
        string lname;
        float balance;
        Openaccount acc;
        Openaccount::accountnumber+=1;
        cout<<"Enter First Name : ";cin>>fname;acc.setfname(fname);
        cout<<"Enter Last Name : ";cin>>lname;acc.setlname(lname);
        cout<<"Enter Balance : ";cin>>balance;acc.setbalance(balance);
        ofstream ofs("Banking.txt",ios::app);
        ofs<<acc;
        ofs.close();
        cout<<"\n\tCongratulations! Account opened successfully."<<endl;
        cout<<"Name : "<<acc.getfname()<<" "<<acc.getlname()<<endl<<"Balance : "<<acc.getbalance()<<endl<<"Account Number : "<<acc.getaccnumber()<<endl;
}

void Openaccount::balanceenquiry(){
    int l;
    cout<<"Enter Account Number :";
    cin>>l;
    cout<<endl;
    ifstream ifs("Banking.txt");
    
    while(!ifs.eof()){
        Openaccount i;
        ifs>>i.fname>>i.lname>>i.balance>>i.accountnumber;
        if(i.accountnumber==l){
            cout<<"First Name : "<<i.fname<<endl<<"Last Name : "<<i.lname<<endl<<"Balance : "<<i.balance<<endl<<endl;
            ifs.close();
            break;
        }
    }     
}

void Openaccount::deleteacc(){
    int l;
    cout<<"Enter Account Number to be closed : ";
    cin>>l;
    Openaccount i;
    ifstream ifs("Banking.txt");
    ofstream tempfile("temp.txt",ios::app);
    bool recordupdate= false;
    while(ifs >> i.fname >> i.lname >> i.balance >> i.accountnumber){
        if(i.accountnumber!=l){
            tempfile<<i;
        }
        if(i.accountnumber==l){
            recordupdate=true;
        }
    }
    ifs.close();
    tempfile.close();
    if (recordupdate) {
        remove("Banking.txt");
        rename("temp.txt", "Banking.txt");
        cout << "Account closed successfully!" <<endl;
    } else {
        remove("temp.txt");  
        cout << "Account number not found!" <<endl;
    }  
}

void Openaccount::withdraw(){
    float money;
    int l;
    Openaccount i;
    cout<<"Enter Account Number : ";cin>>l;
    cout<<"Enter Money to be withdrawn : ";cin>>money;
    
    ifstream ifs("Banking.txt");
    ofstream tempfile("temp.txt",ios::app);
    bool recordupdate= false;
    while(ifs >> i.fname >> i.lname >> i.balance >> i.accountnumber){
        if(i.accountnumber==l){
            if(money>i.balance){
                cout<<"Insufficient Balance";
                ifs.close();
                tempfile.close();
                remove("temp.txt");
                return;    
            }
            else{
                i.balance=i.balance-money;
                recordupdate=true;
            }
        }
        tempfile<<i;
    }
    ifs.close();
    tempfile.close();
    if (recordupdate) {
        remove("Banking.txt");
        rename("temp.txt", "Banking.txt");
        cout << "Withdrawl successfull!" <<endl;
    } else {
        remove("temp.txt");  
        cout << "Account number not found!" <<endl;
    }   
}

void Openaccount::deposit(){
    float money;
    int l;
    Openaccount i;
    cout<<"Enter Account Number : ";cin>>l;
    cout<<"Enter Money to be deposited : ";cin>>money; 
    ifstream ifs("Banking.txt");
    ofstream tempfile("temp.txt",ios::app);
    bool recordupdate= false;
    while(ifs >> i.fname >> i.lname >> i.balance >> i.accountnumber){
        if(i.accountnumber==l){ 
            i.balance=i.balance+money;
            recordupdate=true;            
        }
        tempfile<<i;
    }
    ifs.close();
    tempfile.close();
    if (recordupdate) {
        remove("Banking.txt");
        rename("temp.txt", "Banking.txt");
        cout << "Deposit successfull" <<endl;
    } else {
        remove("temp.txt");  
        cout << "Account number not found!" <<endl;
    }     
}

void Openaccount::showaccount(){
    ifstream ifs("Banking.txt");
    Openaccount i;
    while(ifs >> i.fname >> i.lname >> i.balance >> i.accountnumber){        
        int m = Openaccount::accountnumber;
        cout<<"First Name : "<<i.fname<<endl<<"Last Name : "<<i.lname<<endl<<"Balance : "<<i.balance<<endl<<"Account Number : "<<i.accountnumber<<endl<<endl;
    }
    ifs.close();
}

void Openaccount::setaccountnumber(){
    ifstream ifs("Banking.txt");
    while(!ifs.eof()){
        Openaccount i;
        ifs>>i.fname>>i.lname>>i.balance>>i.accountnumber;
        Openaccount::accountnumber=i.accountnumber;
    }
    ifs.close();
}

void Openaccount::setfname(string fname){
    this->fname= fname;
}
string Openaccount::getfname(){
    return fname;
}

void Openaccount::setlname(string lname){
    this->lname= lname;
}
string Openaccount::getlname(){
    return lname;
}

void Openaccount::setbalance(float balance){
    this->balance= balance;
}
float Openaccount::getbalance(){
    return balance;
}

ofstream & operator<<(ofstream &ofs, Openaccount &o){
    ofs<<o.fname<<endl<<o.lname<<endl<<o.balance<<endl<<o.accountnumber<<endl;
    return ofs;
}
ifstream & operator>>(ifstream &ifs, Openaccount &i){
    ifs>>i.fname>>i.lname>>i.balance>>i.accountnumber;
    return ifs;
}