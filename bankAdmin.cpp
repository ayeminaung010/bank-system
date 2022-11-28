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
        for (int j = 1; j < _admin_nameIndex ; ++j) {
            string toRecord = to_string(j)+" " + _arr_admin_username[j]+" " + _arr_admin_password[j]+" \n";
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
    for (int j = 1; j < _admin_nameIndex; ++j) {
        cout<<"admin name: "<<_arr_admin_username[j]<<" password: "<<_arr_admin_password[j]<<endl;
    }
}


void bank::admin_view() {
    string admin_option;
    cout<<"This is Admin Dashboard"<<endl;
    cout<<"Press 1 to manage user\nPress 2 to see admin Lists\nPress 3 to see Transition Details\nPress 4 to Add new Admin\nPress 5 to Update account\nPress 6 to log out\nPress 7 to exit "<<endl;
    cin>>admin_option;
    if(admin_option == "1"){
        manage_user();
    }else if(admin_option == "2"){
        toShowAdminList();
        admin_view();
    }else if(admin_option == "3"){
        transitionDetails();
        admin_view();
    }else if(admin_option == "4"){
        addNewAdmin();
    }else if(admin_option == "5"){
        admin_update_acc();
    }else if(admin_option == "6"){
        mainMenu();
    }else if(admin_option == "7"){
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

void bank::toShowUserList() {
    for (int i = 0; i < userNameIndex; ++i) {
        cout<<"Username is :"<<arrUsername[i]<<" "<<"Password : "<<arrPassword[i]<<endl;
    }
}

void bank::transitionDetails() {
    string AdminDataFile = "RecordTransitionAll.txt";

    string allTransition;
    ifstream History(AdminDataFile);
    if(History.is_open()){
        while (getline(History,allTransition)){
            cout<<allTransition<<endl;
        }
        cout<<"__________________________________"<<endl;
        History.close();
    }else{
        cout<<"No data found!!\nCannot open file!"<<endl;
        exchange();
    }
}

void bank::manage_user() {
    string  mn_option;
    cout<<"*********Manage User Setting*******"<<endl;
    cout<<"Press 1 to remove user\nPress 2 to ban user\nPress 3 to unban user\nPress 4 to see Ban lists\nPress 5 to update user data\nPress 6 to go back\nPress 7 to Quit"<<endl;
    cin>>mn_option;
    if(mn_option == "1"){
        remove_user();
    }else if(mn_option == "2"){
        ban_user();
    }else if(mn_option == "3"){
        unban_user();
    }else if(mn_option == "4"){
        ban_list();
    }else if(mn_option == "5"){
        update_userData();
    }else if(mn_option == "6"){
        admin_view();
    }else if(mn_option == "7"){
        cout<<"Bye Bye Admin"<<endl;
        exit(1);
    }
}
void bank::remove_user() {
    string rm_username;
    string rm_option;
    cout<<"Enter username to remove :"<<endl;
    cin>>rm_username;
    int status = toCheckUserName(rm_username);
    if(status != -1){
        cout<<"Found User.."<<arrUsername[status]<<endl;
        cout<<"Press 1 to remove\nPress any number to go back"<<endl;
        cin>>rm_option;
        if(rm_option == "1"){
            for (int i = 0; i <  userNameIndex; ++i) {
                arrUsername[status] = arrUsername[status +1];
                arrPassword[status] = arrPassword[status +1];
                arrAmount[status] = arrAmount[status +1];
                arrId[status] = arrId[status];
            }
            userNameIndex--;
            passwordIndex--;
            amountIndex--;
            idIndex--;
            toRecordUserData();
            cout<<"Success Removed..."<<endl;
            option_remove_user();
        }else{
            manage_user();
        }
    }else {
        cout<<"Username not found..."<<endl;
        option_remove_user();
    }
}

void bank::option_remove_user() {
    string op_rm;
    cout<<"Press 1 to remove again\nPress 2 to go back"<<endl;
    cin>>op_rm;
    if(op_rm == "1"){
        remove_user();
    }else if(op_rm == "2"){
        manage_user();
    }else {
      cout<<"Invalid Input"<<endl;
      option_remove_user();
    }
}

void bank::ban_user() {
    string  b_username;
    string  b_option;
    cout<<"Enter username to Ban :"<<endl;
    cin>>b_username;
    int status = toCheckUserName(b_username);
    if(status != -1){
        cout<<"Found User.."<<arrUsername[status]<<endl;
        cout<<"Press 1 to ban\nPress any number to go back"<<endl;
        cin>>b_option;
        if(b_option == "1"){
            arr_ban_u[ban_index] = arrUsername[status];
            ban_index++;
            toRecordBanUser();
            option_ban_user();
        }else{
            manage_user();
        }
    }else{
        cout<<"Username not found..."<<endl;
        option_ban_user();
    }
}
void bank::toRecordBanUser() {
    string banDataFile = "ban.txt";
    ofstream outfile;
    outfile.open(banDataFile,ios::out);
    if(outfile.is_open()){
        for (int j = 0; j < ban_index ; ++j) {
            string toRecord = to_string(j+1)+"."+" " + arr_ban_u[j]+" "+"\n";
            outfile<<toRecord;
        }
    }else{
        cout<<"cannot open file"<<endl;
        exit(1);
    }
}


void bank::loadingBanUser() {
    string banDataFile = "ban.txt";
    int count = 0;
    string data_line; // to store data from one line
    string data ;//temp data
    ifstream userFile(banDataFile);
    if(userFile.is_open()){
        while (getline(userFile,data_line)){
            for(auto &ch :data_line){
                if(ch == ' '){
                    if(count == 0){
                        data = "";
                        count++;
                    }else if(count == 1){
                        arr_ban_u[ban_index] = data;
                        ban_index++;
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

void bank::ban_list() {
    cout<<"This is ban List"<<endl;
    for (int i = 0; i < ban_index; ++i) {
        cout<<i+1<<". "<<arr_ban_u[i]<<endl;
    }
    manage_user();
}
int bank::toCheckBanUser(string uname) {
    for (int j = 0; j <  ban_index; ++j) {
        if(arr_ban_u[j] == uname ){
            return j;
        }
    }
    return -1;
}

void bank::unban_user() {
    string  b_username;
    string ub_option;
    cout<<"Enter username to remove from ban list"<<endl;
    cin>>b_username;
    int status  = toCheckBanUser(b_username);
    if(status == -1){
        cout<<"User not found in Bna list"<<endl;
        cout<<"Press 1 to find again\nPress any number to go back"<<endl;
        cin>>ub_option;
        if(ub_option == "1"){
            unban_user();
        }else{
            manage_user();
        }
    }else{
        cout<<"User found "<<arr_ban_u[status]<<endl;
        cout<<"Press 1 to unban\nPress any number to go back"<<endl;
        cin>>ub_option;
        if(ub_option == "1"){
            for (int k = 0; k < ban_index; ++k) {
                arr_ban_u[status] = arr_ban_u[status +1];
            }
            ban_index--;
            toRecordBanUser();
            cout<<"Remove Success from ban list"<<endl;
            manage_user();
        }else{
            manage_user();
        }
    }
}

void bank::option_ban_user() {
    string b_option;
    cout<<"Press 1 to ban again\nPress 2 to go back"<<endl;
    cin>>b_option;
    if(b_option == "1"){
        ban_user();
    }else if(b_option == "2"){
        manage_user();
    }else {
        cout<<"Invalid Input"<<endl;
        option_ban_user();
    }
}


void  bank::admin_update_acc() {
    string up_option;
    cout<<"Press 1 to update username\nPress 2 to update password\nPress 3 to go back\nPress 4 to Quit"<<endl;
    cin>>up_option;
    if(up_option == "1"){
        change_username(_arr_admin_username[current_index]);
    }else if(up_option == "2"){
        change_password(_arr_admin_username[current_index]);
    }else if(up_option == "3"){
        admin_view();
    }else if(up_option == "4"){
        cout<<"Bye Bye Admin"<<endl;
    }else {
        cout<<"Invalid Input"<<endl;
        admin_update_acc();
    }
}


void bank::update_userData() {
    string up_option;
    cout<<"Press 1 to change user's name\nPress 2 to change user's password\nPress 3 to go back\nPress 4 to Quit"<<endl;
    cin>>up_option;
    if(up_option == "1"){
        admin_ch_username();
    }else if(up_option == "2"){
        admin_ch_pass();
    }else if(up_option == "3"){
        manage_user();
    }else if(up_option == "4"){
        cout<<"Bye Bye Admin"<<endl;
        exit(1);
    }else{
        cout<<"Invalid Input"<<endl;
        update_userData();
    }
}

void bank::admin_ch_username() {
    string  ch_username;
    string n_username;
    cout<<"Enter username you want to find user "<<endl;
    cin>>ch_username;
    int status = toCheckUserName(ch_username);
    if (status == -1){
        cout<<"Username not found"<<endl;
        update_userData();
    }else{
        cout<<"Enter new username for :"<<ch_username<<endl;
        cin>>n_username;
        int check_status = toCheckUserName(n_username);
        if(check_status == -1){
            arrUsername[status] = n_username;
            toRecordUserData();
            cout<<"Success changed username..."<<endl;
            update_userData();
        }else{
            cout<<"Username already exits.."<<endl;
            update_userData();
        }
    }
}

void bank::admin_ch_pass() {
    string ch_username;
    string n_password;
    string c_pass;
    cout<<"Enter username to Find user :"<<endl;
    cin>>ch_username;
    int status = toCheckUserName(ch_username);
    if(status == -1){
        cout<<"Username not found.."<<endl;
        update_userData();
    }
    while (status != -1){
        cout<<"Enter new password to change password for : "<<ch_username<<endl;
        cin>>n_password;
        cout<<"Confirm password:"<<endl;
        cin>>c_pass;
        if(n_password == c_pass){
            arrPassword[status] = n_password;
            toRecordUserData();
            cout<<"Password changed Success..."<<endl;
            update_userData();
        }
        while (n_password != c_pass){
            cout<<"Password not match"<<endl;
            break;
        }
    }
}