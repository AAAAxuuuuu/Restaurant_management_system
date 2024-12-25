#include <iostream>
#include <string>
#include <vector>
#include "windows.h"
#include "structs.h"
using namespace std;

vector<Operator> operators;

// 登录函数
void login() {
    int Id;
    string password;

    cout << "请输入工号: ";
    cin >> Id;
    cout << "请输入密码: ";
    cin >> password;

    for (const auto& operatorData : operators) {
        if (operatorData.operatorId == Id && operatorData.password == password) {
            int roleCode = operatorData.roleCode;
            bossChoice:
            switch (roleCode) {
                case 1:
                    cout << "欢迎进入消费者系统！" << endl;
                    cout << "系统还未完善请稍后再试！！！！" <<endl;
                    break;
                case 2:
                    cout << "欢迎进入消费者系统！" << endl;
                    cout << "系统还未完善请稍后再试！！！！" <<endl;
                    break;
                case 3:
                    cout << "欢迎进入厨师子系统！" << endl;
                    cout << "系统还没写出来喵，去鞭打我的组员让他快点写出来谢谢喵" <<endl;
                    system("pause");
                    break;
                case 4:
                    cout << "欢迎进入收银员子系统！" << endl;
                    cout << "系统还没写出来喵，去鞭打我的组员让他快点写出来谢谢喵" <<endl;
                    system("pause");
                    break;
                case 5:
                    cout << "欢迎进入服务员子系统！" << endl;
                    cout << "系统还没写出来喵，去鞭打我的组员让他快点写出来谢谢喵" <<endl;
                    system("pause");
                    break;
                case 6:
                    int System;
                    cout << "欢迎老板大驾光临，请选择你要查看的系统(1：管理员，2：消费者，3：厨师，4：收银员，5：服务员)：";
                    cin >> System;
                    roleCode = System;
                    goto bossChoice;
                default:
                    cout << "无效的角色代码。" << endl;
            }
            return;
        }
    }

    cout << "工号或密码错误，请重新登录。" << endl;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    getRoles();   //与管理员子系统中的初始化函数为同意函数
    getOperators(); //与管理员子系统中的初始化函数为同意函数
    bool isContinue = true;
    char Login ;
    do {
        cout << "欢迎来到登录系统"<<endl;
        login();
        cout << "是否退出登录系统？（y/n）：";
        cin >> Login;
        if (Login == 'n') isContinue = true;
        else
        {
            isContinue = false;
            cout << "登陆系统已退出！";
        }

    } while (isContinue);

    return 0;
}//
// Created by Axuuuu on 2024/12/25.
//
