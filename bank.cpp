//
// Created by Aye MIn Aung on 11/18/2022.
//

#include "bank.h"
#include "iostream"
#include "fstream"
using namespace N;
using namespace std;

void bank::welcome() {
    cout<<"Welcome From Our Bank"<<endl;
    loadingAdminData();
    loadingUserData();
    loadingBanUser();
//    ban_list();
    toShowUserList();
    toShowAdminList();
    mainMenu();
}

void bank::mainMenu() {
    string main_option;
    cout<<"Press 1 to Login\nPress 2 to Register\nPress 3 to Quit"<<endl;
    cin>>main_option;
    if(main_option == "1"){
        login();
    }else if(main_option == "2"){
        Register();
    }else if(main_option == "3"){
        cout<<"Bye Bye\nThank You"<<endl;
        exit(1);
    }else{
        cout<<"Invalid Input"<<endl;
        mainMenu();
    }
}

void bank::login() {
    string admin_pass;
    int count = 0;
    cout<<"Login Page"<<endl;
    cout<<"This is Login Page"<<endl;
    cout<<"Enter your username to Login"<<endl;
    cin>>lusername;
    int admin_status = toCheckAdmin(lusername);
    while (admin_status == -1){
        int ban_status = toCheckBanUser(lusername);
        if(ban_status == -1){
            int status = toCheckUserName(lusername);
            if (status != -1){
                cout<<"Found username..\nEnter password to login for "<<lusername<<endl;
                cin>>lpassword;
                while (count != 3){
                    if(lpassword == arrPassword[status]){
                        cout<<"Login Success"<<endl;
                        current_index = status;
                        user_view();
                    }else{
                        cout<<"Wrong Password..Login Failed Try again!"<<endl;
                        count++;
                        break;
                    }
                }
                if(count == 3){
                    cout<<"You wrong 3 times"<<endl;
                    count =0;
                    option_login();
                }
            }else{
                cout<<"Username not Found.."<<endl;
                option_login();
            }
        }else{
            cout<<"********This account is banned by admin********\nContact Customer Service.. "<<endl;
            option_login();
        }
    }
    while (admin_status != -1){
        cout<<"You are Admin...\nEnter your password for "<<_arr_admin_username[admin_status]<<endl;
        cin>>admin_pass;
        while (count != 3){
            if(admin_pass == _arr_admin_password[admin_status]){
                cout<<"Login Success "<<endl;
                current_index = admin_status;
                admin_view();
            }else{
                cout<<"Wrong Password Login Failed Try again!"<<endl;
                count++;
                break;
            }
        }
        if (count == 3){
            cout<<"You wrong 3 times"<<endl;
            count =0;
            option_login();
        }
    }
}

void bank::option_login() {
    cout<<"Press 1 to login again\nPress 2 to go main menu\nPress 3 to Quit"<<endl;
    string l_option;
    cin>>l_option;
    if(l_option == "1"){
        login();
    }else if(l_option == "2"){
        mainMenu();
    }else if(l_option == "3"){
        cout<<"Bye Bye"<<endl;
        exit(1);
    }else{
        cout<<"Invalid Input"<<endl;
        option_login();
    }
}

void bank::Register() {
    string r_option;
    cout<<"Register Page"<<endl;
    cout<<"Enter username to Register : "<<endl;
    cin>>r_username;
    int status = toCheckUserName(r_username);
    while (status == -1){
        cout<<"Enter password for : "<<r_username<<endl;
        cin>>r_password;
        cout<<"Confirm your password "<<endl;
        cin>>c_password;

        while (true){
            if(r_password == c_password){
                cout<<"Register Success"<<endl;
                cout<<"Enter your amount :"<<endl;
                cin>>r_amount;
                arrUsername[userNameIndex] = r_username;
                arrPassword[passwordIndex] = r_password;
                arrAmount[amountIndex] = r_amount;
                userNameIndex++;
                passwordIndex++;
                amountIndex++;
                idIndex++;
                toRecordUserData();
                mainMenu();
            }else{
                cout<<"Password not match"<<endl;
                break;
            }
        }
    }
    cout<<"Username Already exits"<<endl;
    cout<<"Press 1 to login\nPress 2 to Register\nPress 3 to Quit"<<endl;
    cin>>r_option;
    if(r_option == "1"){
        login();
    }else if(r_option == "2") {
        Register();
    }else{
        cout<<"Bye Bye "<<endl;
        exit(1);
    }

}

void bank::toRecordUserData() {
    string userDataFile = "user.txt";
    ofstream outfile;
    outfile.open(userDataFile,ios::out);
    if(outfile.is_open()){
        for (int j = 0; j < idIndex ; ++j) {
            string  toRecord = to_string(j+1)+" " + arrUsername[j]+" " + arrPassword[j]+" " + arrAmount[j]+" " + to_string(1900 + ltm->tm_year )+"/"+
                                to_string( 1 + ltm->tm_mon) +"/"+ to_string(ltm->tm_mday) + "/"+ to_string(ltm->tm_hour) +":" +
                                to_string(ltm->tm_min) + ":" + to_string(ltm->tm_sec) +" \n";
            outfile<<toRecord;
        }
    }else{
        cout<<"cannot open file"<<endl;
        exit(1);
    }
}

void bank::loadingUserData() {
    cout<<"User data are Loading___________"<<endl;
    string userDataFile = "user.txt";
    int count = 0;
    string data_line; // to store data from one line
    string data ;//temp data
    ifstream userFile(userDataFile);
    if(userFile.is_open()){
        while (getline(userFile,data_line)){
            for(auto &ch :data_line){
                if(ch == ' '){
                    if(count == 0){
                        arrId[idIndex] = data;
                        idIndex++;
                        data = "";
                        count++;
                    }else if(count == 1){
                        arrUsername[userNameIndex] = data;
                        userNameIndex++;
                        data = "";
                        count++;
                    }else if(count == 2){
                        arrPassword[passwordIndex] = data;
                        passwordIndex++;
                        data = "";
                        count++;
                    }else if(count == 3){
                        arrAmount[amountIndex] = data;
                        amountIndex++;
                        data = "";
                        count++;
                    }else if(count == 4){
                        arrTime[timeIndex] = data;
                        timeIndex++;
                        data = "";
                        count = 0;
                    }
                }else{
                    string st(1,ch);
                    data += st;
                }
            }
        }
    }else{
        cout<<"File cannot open"<<endl;
        exit(1);
    }
}

int bank::toCheckUserName(string u_name) {
    for (int i = 0; i < idIndex; ++i) {
        if(arrUsername[i] == u_name ){
            return i;
        }
    }
    return -1;
}

void bank::user_view() {
    string user_option;
    cout<<"Welcome Page "<<endl;
    cout<<"Press 1 to go Exchange\nPress 2 to manage account\nPress 3 to see balance\nPress 4 to see account details\nPress 5 to log out\nPress 6 to  Quit"<<endl;
    cin>>user_option;
    if(user_option == "1"){
        exchange();
    }else if(user_option == "2"){
        manageAcc();
    }else if(user_option == "3"){
        showBalance();
    }else if(user_option == "4"){
        accountDetails();
    }else if(user_option == "5"){
        mainMenu();
    }else if(user_option == "6"){
        cout<<"Bye Bye\nThank You"<<endl;
        exit(1);
    }else{
        cout<<"Invalid Input"<<endl;
        user_view();
    }
}

void bank::exchange() {
    string exchange_option;
    cout<<"This is exchange page"<<endl;
    cout<<"Press 1 to Withdraws money\nPress 2 Transfer money\nPress 3 to Top up Bills\nPress 4 see Transition History\nPress 5 to fill money\nPress 6 to go back\nPress 7 to Quit"<<endl;
    cin>>exchange_option;
    if(exchange_option == "1"){
        withdrawsMoney();
    }else if(exchange_option == "2"){
        transferMoney();
    }else if(exchange_option == "3"){
        topUpBills();
    }else if(exchange_option == "4"){
        user_transition();
    }else if(exchange_option == "5"){
        fill_money();
    }else if(exchange_option == "6"){
        user_view();
    }else if (exchange_option == "7"){
        cout<<"Bye Bye\nThank you"<<endl;
        exit(1);
    }else {
        cout<<"Invalid Input"<<endl;
        exchange();
    }
}

void bank::withdrawsMoney() {
    string w_amount;
    cout<<"This is Withdraws Page"<<endl;
    cout<<"Your balance is : "<<arrAmount[current_index]<<endl;
    if(stoi(arrAmount[current_index] ) != 1000){
        cout<<"Enter amount you want withdraws..."<<endl;
        cin>>w_amount;
        if(stoi(w_amount) <= stoi(arrAmount[current_index])- 1000){
            int newAmount = stoi(arrAmount[current_index]) - stoi(w_amount);
            arrAmount[current_index] = to_string(newAmount);
            toRecordUserData();
            cout<<"Successfully Withdraws"<<endl;
            exchange();
        }else{
            cout<<"You cannot withdraws "<<endl;
            exchange();
        }
    }else{
        cout<<"You don't have sufficient balance to Withdraws"<<endl;
        exchange();
    }
}

void bank::transferMoney() {
    string t_name;
    string t_amount;
    cout<<"Your Balance is :"<<arrAmount[current_index]<<endl;
    cout<<"Enter username you want transfer :"<<endl;
    cin>>t_name;
    int status = toCheckUserName(t_name);

    if(status == -1){
        cout<<"Username not found"<<endl;
        exchange();
    }else if(arrUsername[current_index] == arrUsername[status]){
        cout<<"You cannot Transfer yourself"<<endl;
        exchange();
    }else {
        while (true){
            cout<<"Found username..:"<<arrUsername[status]<<endl;
            cout<<"Enter amount :"<<endl;
            cin>>t_amount;
            while (stoi(t_amount) >= stoi(arrAmount[current_index]) - 1000){
                cout<<"You cannot transfer your all amounts"<<endl;
                break;
            }
            if(stoi(t_amount) < stoi(arrAmount[current_index]) - 1000){
                cout<<"Successfully Transferred to =>"<<t_name<<endl;
                toRecordTransition(t_amount,t_name);
                int n_amount = stoi(arrAmount[current_index]) - stoi(t_amount);
                arrAmount[current_index] = to_string(n_amount); //current user

                int t_user_amount  = stoi(arrAmount[status]) + stoi(t_amount);
                arrAmount[status] = to_string(t_user_amount);//transfer user
                toRecordUserData();
                exchange();
            }
        }
    }
}

void bank::toRecordTransition(string tamount,string tname) {

    string AdminDataFile = "RecordTransitionAll.txt";
    ofstream outfile;
    outfile.open(AdminDataFile,ios::app);
    if(outfile.is_open()){
        string  toRecord = arrUsername[current_index] +" : "+ tamount+" " + "SuccessFully Transferred to ==>>"+ tname +" " + to_string(1900 + ltm->tm_year )+"-"+
                           to_string( 1 + ltm->tm_mon) +"-"+ to_string(ltm->tm_mday) + "-"+ to_string(ltm->tm_hour) +":" +
                           to_string(ltm->tm_min) + ":" + to_string(ltm->tm_sec) +" \n";
        outfile<<toRecord;
    }else{
        cout<<"cannot open file"<<endl;
        exit(1);
    }
    //for user
    string userDataFile = arrId[current_index]+"-ForTransition.txt";
    ofstream outfile1;
    outfile1.open(userDataFile,ios::app);
    if(outfile1.is_open()){
        string  toRecord = arrUsername[current_index] +" : "+ tamount+" " + "SuccessFully Transferred to ==>>"+ tname +" " + to_string(1900 + ltm->tm_year )+"/"+
                           to_string( 1 + ltm->tm_mon) +"/"+ to_string(ltm->tm_mday) + "/"+ to_string(ltm->tm_hour) +":" +
                           to_string(ltm->tm_min) + ":" + to_string(ltm->tm_sec) +" \n";
        outfile1<<toRecord;
    }else{
        cout<<"cannot open file"<<endl;
        exit(1);
    }
}

void bank::topUpBills() {
    string ph_num;
    string amount;
    cout<<"Your Balance is :"<<arrAmount[current_index]<<endl;
    cout<<"Enter Phone number :"<<endl;
    cin>>ph_num;
    cout<<"Enter amount :"<<endl;
    cin>>amount;
    if (stoi(arrAmount[current_index]) != 1000){
        int n_amount = stoi(arrAmount[current_index]) - stoi(amount);
        arrAmount[current_index] = to_string(n_amount);
        toRecordUserData();
        cout<<"Top up Success ... "<<endl;
        exchange();
    }else{
        cout<<"You don't have sufficient balance to top up"<<endl;
        exchange();
    }
}

void bank::fill_money() {
    string amount;
    cout<<"Enter amount you want to Fill"<<endl;
    cin>>amount;
    int n_amount = stoi(arrAmount[current_index]) + stoi(amount);
    arrAmount[current_index] = to_string(n_amount);
    cout<<"Filled amount Successfully"<<endl;
    toRecordUserData();
    exchange();
}

void bank::manageAcc() {
    string m_option;
    cout<<"Press 1 to Quit\nPress 2 to change username\nPress 3 to change password\nPress 4 to delete account\nPress 5 to go back"<<endl;
    cin>>m_option;
    if(m_option == "1"){
        cout<<"Bye Bye"<<endl;
        exit(1);
    }else if(m_option == "2"){
        change_username(arrUsername[current_index]);
    }else if(m_option == "3"){
        change_password(arrUsername[current_index]);
    }else if(m_option == "4"){
        delete_acc();
    }else if(m_option == "5"){
        user_view();
    }else{
        cout<<"Invalid input"<<endl;
        manageAcc();
    }
}

void bank::change_username(string uname) {
    string n_username;
    int admin_status = toCheckAdmin(uname);

    while (admin_status == -1 ){
        cout<<"Enter new username for :"<<uname<<endl;
        cin>>n_username;
        int status = toCheckUserName(n_username);
        while (true){
            if(status == -1 ){
                arrUsername[current_index] = n_username;
                cout<<"Updated username Successs..:"<<arrUsername[current_index]<<endl;
                toRecordUserData();
                manageAcc();
            }else{
                cout<<"Username already exits"<<endl;
                break;
            }
        }
    }
    while (admin_status != -1){
        cout<<"Enter new username for :"<<_arr_admin_username[admin_status]<<endl;
        cin>>n_username;
        int status = toCheckAdmin(n_username);
        while (true){
            if(status == -1){
                _arr_admin_username[admin_status] = n_username;
                cout<<"Updated admin's username :"<<_arr_admin_username[admin_status]<<endl;
                toRecordAdminData();
                admin_view();
            }else{
                cout<<"Username already exits in Admin Team"<<endl;
                break;
            }
        }
    }
}

void bank::change_password(string uname) {
    string n_pass;
    string c_pass;
    string confirm_pass;
    int admin_status = toCheckAdmin(uname);

    while (admin_status == -1 ){
        cout<<"Enter current password for :"<<uname<<endl;
        cin>>c_pass;
        while (c_pass == arrPassword[current_index]){
            cout<<"Enter new password :"<<endl;
            cin>>n_pass;
            cout<<"Confirm new password :"<<endl;
            cin>>confirm_pass;
            if(n_pass == confirm_pass){
                arrPassword[current_index] = n_pass;
                cout<<"Updated password Success..:"<<endl;
                toRecordUserData();
                manageAcc();
            }else{
                cout<<"Password not match.."<<endl;
                break;
            }
        }
    }
    while (admin_status != -1){
        cout<<"Enter current password for :"<<uname<<endl;
        cin>>c_pass;
        while (c_pass == _arr_admin_password[admin_status]){
            cout<<"Enter new password :"<<endl;
            cin>>n_pass;
            cout<<"Confirm new password :"<<endl;
            cin>>confirm_pass;
            if(n_pass == confirm_pass){
                _arr_admin_password[admin_status] = n_pass;
                cout<<"Updated password Success..:"<<endl;
                toRecordAdminData();
                admin_view();
            }else{
                cout<<"Password not match.."<<endl;
                break;
            }
        }
    }

}

void bank::delete_acc() {
    string d_option;
    cout<<"Type YES or NO to delete your account for sure"<<endl;
    cin>>d_option;

    if(d_option == "YES"){
        for (int i = 0; i < userNameIndex ; ++i) {
            arrUsername[current_index] = arrUsername[current_index+1];
            arrPassword[current_index] = arrPassword[current_index+1];
            arrAmount[current_index] = arrAmount[current_index+1];
            arrId[current_index] = arrId[current_index+1];
        }
        userNameIndex--;
        idIndex--;
        amountIndex--;
        passwordIndex--;
        toRecordUserData();
        cout<<"Successfully deleted...."<<endl;
        manageAcc();
    }else if(d_option == "NO"){
        cout<<"You canceled ..."<<endl;
        manageAcc();
    }else{
        cout<<"Invalid input"<<endl;
        manageAcc();
    }
}

void bank::showBalance() {
    cout<<"Your Balance is :"<<arrAmount[current_index]<<endl;

    exchange();
}

void bank::accountDetails() {
    cout<<"Username :"<<arrUsername[current_index]<<endl;
    cout<<"Password :"<<arrPassword[current_index]<<endl;
    cout<<"Balance :"<<arrAmount[current_index]<<endl;
    cout<<"_____________________________________"<<endl;
    user_view();
}

void bank::user_transition() {
    string userDataFile = arrId[current_index]+"-ForTransition.txt";

    string userTransition;
    ifstream History(userDataFile);
    if(History.is_open()){
        while (getline(History,userTransition)){
            cout<<userTransition<<endl;
        }
        cout<<"__________________________________"<<endl;
        History.close();
    }else{
        cout<<"No data found!!\nCannot open file!"<<endl;
        exchange();
    }
}
