#include <iostream>
#include "windows.h"
#include "structs.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
vector<Role>roles;
vector<Operator>operators;

//角色部分
//从文件中获得初始化角色数据
void getRoles(){
    ifstream file;
    file.open("roleClassification.txt",ios::in);
    if (file.is_open()){
        string line;
        while (getline(file,line)){
            istringstream iss(line);
            string mark;
            Role role;

            getline(iss,mark,';');
            role.roleCode = stoi(mark.substr(13));

            getline(iss,mark,';');
            role.roleName = mark.substr(7);

            getline(iss,mark,';');
            role.rolePermissions = mark.substr(7);
            //将角色储存到数组中
            roles.push_back(role);
        }
        file.close();
    } else cout << "无法打开角色文件！"<<endl;
}
//同步修改
void RolesSync(){
    ofstream file("roleClassification.txt");
    if (file.is_open()){
        for (const auto& role : roles) {
            file << "角色代码:" << role.roleCode << ";"
                 << "角色:" << role.roleName << ";"
                 << "权限:" << role.rolePermissions << ";" << endl;
        }
        file.close();
    } else cout << "无法同步角色文件！"<<endl;
}
//添加新的角色
void addRole(){
    Role newRole;
    cout << "请输入新职位代码: ";
    cin >> newRole.roleCode;
    cout << "请输入新职位名称: ";
    cin >> newRole.roleName;
    cout << "请输入新职位权限（以逗号分隔）: ";
    cin >> newRole.rolePermissions;

    roles.push_back(newRole);
    RolesSync();
}
//修改角色
void ModifyTheRole (int roleCode,const Role& modifyRole ){
    for (auto& role : roles){
        if (role.roleCode == roleCode) {
            role = modifyRole;
            break;
        }
    }
}
//修改角色权限
void ModifyTheRolePermissions (int roleCode,const string& permissions){
    for (auto& role : roles){
        if (role.roleCode == roleCode) {
            role.rolePermissions = permissions;
            break;
        }
    }
}
//打印角色
void printRoles() {
    for (const auto& role : roles) {
        cout << "职位代码:" << role.roleCode << "；职位:" << role.roleName << "；权限:" << role.rolePermissions << std::endl;
    }
}

//操作员部分
//从文件中获得初始化操作员数据
void getOperators() {
    ifstream file;
    file.open("Operators.txt", ios::in);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            Operator operatorData;
            string key, value;


            getline(iss, key, ':');
            getline(iss, value, ' ');
            operatorData.operatorId = stoi(value);

            getline(iss, key, ':');
            getline(iss, value, ' ');
            operatorData.operatorName = value;

            getline(iss, key, ':');
            getline(iss, value, ' ');
            operatorData.password = value;

            getline(iss, key, ':');
            getline(iss, value, ' ');
            string position = value;

            for (const auto& role : roles) {
                if (role.roleName == position) {
                    operatorData.roleCode = role.roleCode;
                    break;
                }
            }

            operators.push_back(operatorData);
        }
        file.close();
    } else {
        cout << "无法打开操作员文件！" << endl;
    }
}
//同步操作员修改
void OperatorsSync(){
    ofstream file("Operators.txt");
    if (file.is_open()){
        for (const auto& newOperator : operators) {
            file <<"工号:"<< newOperator.operatorId << " "
                 <<"姓名:"<< newOperator.operatorName << " "
                 <<"密码:"<< newOperator.password << " ";
            for (const auto& role:roles) {
                if (newOperator.roleCode == role.roleCode){
                    file << "职位:" << role.roleName<<endl;
                    break;
                }
            }
        }
        file.close();
    } else {
        cerr << "无法同步操作员文件！" << endl;

        }
    }
//添加新的操作员
void addOperator(){
    Operator newOperator;
    cout << "请输入操新员工工号: ";
    cin >> newOperator.operatorId;
    cout << "请输入新员工姓名: ";
    cin >> newOperator.operatorName;
    cout << "请输入新员工密码: ";
    cin >> newOperator.password;

    string position;
    cout << "请输入新员工职位: ";
    cin >> position;
    for (const auto& role : roles) {
        if (role.roleName == position) {
            newOperator.roleCode = role.roleCode;
            break;
        }
    }

    operators.push_back(newOperator);
    OperatorsSync();
}
//操作员修改
void modifyOperator(int operatorId, const Operator& modifiedOperator) {
    for (auto& operatorData : operators) {
        if (operatorData.operatorId == operatorId) {
            operatorData = modifiedOperator;
            break;
        }
    }
    OperatorsSync();
}
//操作员角色修改（即职位改变
void assignOperatorRole(int operatorId, int roleCode) {
    for (auto& operatorData : operators) {
        if (operatorData.operatorId == operatorId) {
            operatorData.roleCode = roleCode;
            break;
        }
    }
    OperatorsSync();
}
//打印操作员
void printOperators() {
    for (const auto& operatorData : operators) {
        if (operatorData.operatorId != 0)
        cout << "员工ID:" << operatorData.operatorId << "；姓名:" << operatorData.operatorName << "；职位代码:" << operatorData.roleCode;
        for (const auto& role:roles) {
            if (operatorData.roleCode == role.roleCode) {
                cout << "；职位:" << role.roleName << endl;
                break;
            }
        }
    }
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    getRoles();
    getOperators();

    int choice;
    do {
        cout << "管理员子系统功能菜单(本菜单中的权限均指进入某个子系统的权限）：" << endl;
        cout << "1. 添加职位" << endl;
        cout << "2. 修改职位" << endl;
        cout << "3. 修改职位权限" << endl;
        cout << "4. 添加员工" << endl;
        cout << "5. 修改员工" << endl;
        cout << "6. 修改员工职位" << endl;
        cout << "7. 打印职位信息" << endl;
        cout << "8. 打印员工信息" << endl;
        cout << "0. 退出" << endl;
        cout << "请选择操作: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addRole();
                break;
            case 2: {
                int roleCode;
                cout << "请输入要修改的职位的代码: ";
                cin >> roleCode;
                Role modifiedRole;
                cout << "请输入新的职位的名称: ";
                cin >> modifiedRole.roleName;
                cout << "请输入新的职位的权限（以逗号分隔）: ";
                cin >> modifiedRole.rolePermissions;
                ModifyTheRole(roleCode, modifiedRole);
                break;
            }
            case 3: {
                int roleCode;
                cout << "请输入要修改权限的职位代码: ";
                cin >> roleCode;
                string permissions;
                cout << "请输入职位权限（以逗号分隔）: ";
                cin >> permissions;
                ModifyTheRolePermissions(roleCode, permissions);
                break;
            }
            case 4:
                addOperator();
                break;
            case 5: {
                int operatorId;
                cout << "请输入要修改的员工ID: ";
                cin >> operatorId;
                Operator modifiedOperator;
                cout << "请输入新的员工姓名: ";
                cin >> modifiedOperator.operatorName;
                cout << "请输入新的员工密码: ";
                cin >> modifiedOperator.password;
                cout << "请输入新的职位代码: ";
                cin >> modifiedOperator.roleCode;
                modifyOperator(operatorId, modifiedOperator);
                break;
            }
            case 6: {
                int operatorId;
                cout << "请输入要修改职位的员工ID: ";
                cin >> operatorId;
                int roleCode;
                cout << "请输入职位代码: ";
                cin >> roleCode;
                assignOperatorRole(operatorId, roleCode);
                break;
            }
            case 7:
                printRoles();
                break;
            case 8:
                printOperators();
                break;
            case 0:
                cout << "管理员子系统已退出。" << endl;
                break;
            default:
                cout << "无效输入，请重新输入。" << endl;
        }
    } while (choice!= 0);

    return 0;
}
//
// Created by Axuuuu on 2024/12/20.
//
