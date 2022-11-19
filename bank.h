//
// Created by Aye MIn Aung on 11/18/2022.
//

#include "iostream"
#include "ctime"
using namespace std;
#ifndef BANK_BANK_H
#define BANK_BANK_H

namespace N{
    class bank {
        public:
        //time
        time_t now = time(0);
        tm *ltm = localtime(&now);

        //variable declare
        //for user
        int idIndex = 0;
        int userNameIndex = 0;
        int passwordIndex = 0;
        int amountIndex = 0;
        int current_index = 0;
        int timeIndex = 0;

        string arrId[100];
        string arrUsername[100];
        string arrPassword[100];
        string arrAmount[100];
        string arrTime[100];

        string r_username;
        string r_password;
        string c_password;
        string r_amount;


        string lusername;
        string lpassword;

        void welcome();
        void mainMenu();

        void login();
        void Register();
        void toRecordUserData();
        int toCheckUserName(string u_name);
        void loadingUserData();
        void option_login();

        void user_view();
        void exchange();
        void withdrawsMoney();
        void transferMoney();
        void topUpBills();
        void manageAcc();
        void showBalance();
        void accountDetails();

        //for admin
        //variable declare
        int _admin_nameIndex = 1;
        int _admin_passIndex = 1;
        int _admin_idIndex = 1;

        string admin_username;
        string admin_password;
        string _arr_admin_username[10] = {"admin"};
        string _arr_admin_password[10] = {"admin123"};
        string _arr_admin_id[10];

        int toCheckAdmin(string u_name);
        void toRecordAdminData();
        void loadingAdminData();
        void admin_view();
        void toShowAdminList();
        void addNewAdmin();
        void option_addNewAdmin();
    };
}



#endif //BANK_BANK_H
