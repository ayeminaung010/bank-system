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
        cout<<"admin name: "<<_arr_admin_username[j]<<endl;
        cout<<"admin pw: "<<_arr_admin_password[j]<<endl;
    }
}

void bank::admin_view() {
    cout<<"This is Admin Dashboard"<<endl;

}

