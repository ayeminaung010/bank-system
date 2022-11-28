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

        void user_view(); //user landing view
        void exchange();
        void withdrawsMoney(); // withdraws money

        void transferMoney(); // transfer money from people to people
        void topUpBills(); // top up ph bills
        void manageAcc(); //user options to manage acc
        void change_username(string uname);// for user /admin
        void change_password(string uname);//for user/admin
        void delete_acc(); //delete acc for user **
        void showBalance(); // show balance
        void accountDetails(); // user acc details
        void user_transition(); // show user's own transition
        void fill_money(); // adding money

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

        string arr_ban_u[100];
        int ban_index = 0;

        int toCheckAdmin(string u_name);//check admin or not
        void toRecordAdminData(); //record admin data
        void loadingAdminData(); //admin acc data loading
        void admin_view(); //admin dashboard
        void toShowAdminList(); //show admin lists
        void addNewAdmin(); //add new admin
        void option_addNewAdmin();
        void toShowUserList(); //user lists
        void toRecordTransition(string tamount,string tname);
        void transitionDetails(); //show transition data
        void manage_user(); //user managing options
        void admin_update_acc(); //admin change username /pass
        void remove_user(); //remove user
        void option_remove_user();
        void ban_user(); //ban user
        void unban_user(); // unban user
        void ban_list(); // show ban list
        int toCheckBanUser(string uname); //check ban user or not
        void update_userData(); // //update user's data options for admin
        void toRecordBanUser(); //record data for ban user
        void loadingBanUser();// loading ban user
        void option_ban_user();
        void admin_ch_username(); //admin change user's username
        void admin_ch_pass();//admin change user's pass
    };
}



#endif //BANK_BANK_H
