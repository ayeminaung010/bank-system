//
// Created by Aye MIn Aung on 11/19/2022.
//

#include "iostream"
#include "bank.h"
#include "fstream"
using namespace std;
using namespace N;

int bank::toCheckAdmin(string u_name) {
    for (int j = 0; j < _admin_idIndex; ++j) {
        if(_arr_admin_username[j] == u_name){
            return j; //found
        }
    }
    return -1; // not found
}

void bank::toRecordAdminData() {
    string adminDataFile = "admin.txt";
    ofstream outfile;
    outfile.open(adminDataFile,ios::out);
    if(outfile.is_open()){
        for (int j = 0; j < _admin_nameIndex ; ++j) {
            string toRecord = to_string(j+1)+" " + _arr_admin_username[j]+" " + _arr_admin_password[j]+" \n";
            outfile<<toRecord;
        }
    }else{
        cout<<"cannot open file"<<endl;
        exit(1);
    }

}
void bank::loadingAdminData() {
    string userDataFile = "admin.txt";
    int count = 0;
    string data_line; // to store data from one line
    string data ;//temp data
    ifstream userFile(userDataFile);
    if(userFile.is_open()){
        while (getline(userFile,data_line)){
            for(auto &ch :data_line){
                if(ch == ' '){
                    if(count == 0){
                        _arr_admin_id[_admin_idIndex] = data;
                        _admin_idIndex++;
                        data = "";
                        count++;
                    }else if(count == 1){
                        _arr_admin_username[_admin_nameIndex] = data;
                        _admin_nameIndex++;
                        data = "";
                        count++;
                    }else if(count == 2){
                        _arr_admin_password[_admin_passIndex] = data;
                        _admin_passIndex++;
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

void bank::toShowAdminList() {
    for (int j = 0; j < _admin_nameIndex; ++j) {
        cout<<"admin name: "<<_arr_admin_username[j]<<" pw: "<<_arr_admin_password[j]<<endl;
    }
}


void bank::admin_view() {
    string admin_option;
    cout<<"This is Admin Dashboard"<<endl;
    cout<<"Press 1 to manage user\nPress 2 to see admin Lists\nPress 3 to see Transition Details\nPress 4 to Add new Admin\nPress 5 to exit "<<endl;
    cin>>admin_option;
    if(admin_option == "1"){

    }else if(admin_option == "2"){
        toShowAdminList();
    }else if(admin_option == "3"){

    }else if(admin_option == "4"){
        addNewAdmin();
    }else if(admin_option == "5"){
        cout<<"Bye By Admin"<<endl;
        exit(1);
    }else{
        cout<<"Invalid Input"<<endl;
        admin_view();
    }
}

void bank::addNewAdmin() {
    string ad_username;
    string ad_pass;
    string c_pass;
    cout<<"Enter username to add Admin"<<endl;
    cin>>ad_username;
    int admin_status = toCheckAdmin(ad_username);
    if(admin_status == -1){
        int status = toCheckUserName(ad_username);
        if(status == -1){
            cout<<"Enter password for : "<<ad_username<<endl;
            cin>>ad_pass;
            cout<<"Confirm your password :"<<endl;
            cin>>c_pass;
            if(ad_pass == c_pass){
                _arr_admin_username[_admin_nameIndex] = ad_username;
                _arr_admin_password[_admin_passIndex] = ad_pass;
                _admin_nameIndex++;
                _admin_passIndex++;
                _admin_idIndex++;
                cout<<"Added New Admin SuccessFully..."<<endl;
                toRecordAdminData();
            }else{
                cout<<"Password not match"<<endl;
                option_addNewAdmin();
            }
        }else{
            cout<<"Username already exits"<<endl;
            option_addNewAdmin();
        }
    }else{
        cout<<"Username already exits in Admin Team"<<endl;
        option_addNewAdmin();
    }
}

void bank::option_addNewAdmin() {
    string u_option;
    cout<<"Press 1 to add new admin again\nPress 2 to go back\nPress 3 to Quit"<<endl;
    if(u_option == "1"){
        addNewAdmin();
    }else if(u_option == "2"){
        admin_view();
    }else if(u_option == "3"){
        cout<<"Bye Bye Admin"<<endl;
        exit(1);
    }else {
        cout<<"Invalid input"<<endl;
        option_addNewAdmin();
    }
}
