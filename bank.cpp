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
    loadingUserData();
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
        exit(1);
    }else{
        cout<<"Invalid Input"<<endl;
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
        int status = toCheckUserName(lusername);
        while (status != -1){
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
        }
    }
    while (admin_status != -1){
        cout<<"You are Admin...\nEnter your password for "<<_arr_admin_username[admin_status]<<endl;
        cin>>admin_pass;
        while (count != 3){
            if(admin_pass == _arr_admin_password[admin_status]){
                cout<<"Login Success "<<endl;
                admin_view();
            }else{
                cout<<"Wrong Password Login Failed Try again!"<<endl;
                count++;
                break;
            }
        }
        if(count == 3){
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
                login();
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
                        count++;
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
    cout<<"Welcome Page "<<endl;

}

