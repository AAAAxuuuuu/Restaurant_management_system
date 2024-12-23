#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "windows.h"

using namespace std;

// 角色结构体
struct Role {
    int roleCode;
    string roleName;
    string rolePermissions;
};

// 操作员结构体
struct Operator {
    int operatorId;
    string operatorName;
    string password;
    int roleCode;
};

// 全局变量，用于存储角色和操作员信息
vector<Role> roles;
vector<Operator> operators;

// 从roleClassification.txt文件读取角色信息并初始化角色数据
void initRolesFromFile() {
    ifstream roleFile("roleClassification.txt");
    if (roleFile.is_open()) {
        string line;
        while (getline(roleFile, line)) {
            istringstream iss(line);
            string mark;
            Role role;

            getline(iss, mark, ';');
            role.roleCode = stoi(mark.substr(13));

            getline(iss, mark, ';');
            role.roleName = mark.substr(7);

            getline(iss, mark, ';');
            role.rolePermissions = mark.substr(7);

            roles.push_back(role);
        }
        roleFile.close();
    } else {
        cerr << "无法打开roleClassification.txt文件！" << endl;
    }
}

// 将角色信息同步回roleClassification.txt文件
void saveRolesToFile() {
    ofstream roleFile("roleClassification.txt");
    if (roleFile.is_open()) {
        for (const auto& role : roles) {
            roleFile << "角色代码:" << role.roleCode << ";"
                     << "角色:" << role.roleName << ";"
                     << "权限:" << role.rolePermissions << ";" << endl;
        }
        roleFile.close();
    } else {
        cerr << "无法打开roleClassification.txt文件进行保存！" << endl;
    }
}

// 从Operators.txt文件读取操作员信息并初始化操作员数据，同时转换职位为角色代码
void initOperatorsFromFile() {
    ifstream operatorFile("Operators.txt");
    if (operatorFile.is_open()) {
        string line;
        while (getline(operatorFile, line)) {
            istringstream iss(line);
            Operator operatorData;

            iss >> operatorData.operatorId >> operatorData.operatorName >> operatorData.password;
            string position;
            iss >> position;

            // 根据职位查找对应的角色代码
            for (const auto& role : roles) {
                if (role.roleName == position) {
                    operatorData.roleCode = role.roleCode;
                    break;
                }
            }

            operators.push_back(operatorData);
        }
        operatorFile.close();
    } else {
        cerr << "无法打开Operators.txt文件！" << endl;
    }
}

// 将操作员信息同步回Operators.txt文件（根据操作类型决定打开模式，覆盖写入时保留第一行）
void saveOperatorsToFile() {
    ofstream operatorFile("Operators.txt");
    if (operatorFile.is_open()) {
        for (const auto& operatorData : operators) {
            operatorFile << operatorData.operatorId << " "
                         << operatorData.operatorName << " "
                         << operatorData.password << " "
                         << operatorData.roleCode << ";" << endl;
        }
        operatorFile.close();
    } else {
        cerr << "无法打开Operators.txt文件进行保存！" << endl;
    }
}

// 角色录入函数（从文件读取后添加到角色列表）
void addRoleFromFile() {
    Role newRole;
    cout << "请输入角色代码: ";
    cin >> newRole.roleCode;
    cout << "请输入角色名称: ";
    cin >> newRole.roleName;
    cout << "请输入角色权限（以逗号分隔）: ";
    cin >> newRole.rolePermissions;

    roles.push_back(newRole);
    saveRolesToFile();
}

// 角色修改函数
void modifyRole(int roleCode, const Role& modifiedRole) {
    for (auto& role : roles) {
        if (role.roleCode == roleCode) {
            role = modifiedRole;
            break;
        }
    }
    saveRolesToFile();
}

// 角色权限设置函数
void setRolePermissions(int roleCode, const string& permissions) {
    for (auto& role : roles) {
        if (role.roleCode == roleCode) {
            role.rolePermissions = permissions;
            break;
        }
    }
    saveRolesToFile();
}

// 操作员录入函数（从文件读取后添加到操作员列表）
void addOperatorFromFile() {
    Operator newOperator;
    cout << "请输入操作员工号: ";
    cin >> newOperator.operatorId;
    cout << "请输入操作员姓名: ";
    cin >> newOperator.operatorName;
    cout << "请输入操作员密码: ";
    cin >> newOperator.password;

    // 根据职位查找对应的角色代码
    string position;
    cout << "请输入操作员职位: ";
    cin >> position;
    for (const auto& role : roles) {
        if (role.roleName == position) {
            newOperator.roleCode = role.roleCode;
            break;
        }
    }

    operators.push_back(newOperator);
    saveOperatorsToFile();
}

// 操作员修改函数
void modifyOperator(int operatorId, const Operator& modifiedOperator) {
    for (auto& operatorData : operators) {
        if (operatorData.operatorId == operatorId) {
            operatorData = modifiedOperator;
            break;
        }
    }
    saveOperatorsToFile();
}

// 操作员角色分配函数
void assignOperatorRole(int operatorId, int roleCode) {
    for (auto& operatorData : operators) {
        if (operatorData.operatorId == operatorId) {
            operatorData.roleCode = roleCode;
            break;
        }
    }
    saveOperatorsToFile();
}

// 打印角色信息函数
void printRoles() {
    for (const auto& role : roles) {
        cout << "角色代码: " << role.roleCode << "；角色: " << role.roleName << "；权限: " << role.rolePermissions << endl;
    }
}

// 打印操作员信息函数
void printOperators() {
    for (const auto& operatorData : operators) {
        cout << "操作员ID: " << operatorData.operatorId << "；操作员姓名: " << operatorData.operatorName << "；角色代码: " << operatorData.roleCode << endl;
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    // 初始化角色和操作员数据
    initRolesFromFile();
    initOperatorsFromFile();

    int choice;
    do {
        cout << "管理员子系统功能菜单：" << endl;
        cout << "1. 录入角色（从文件读取）" << endl;
        cout << "2. 修改角色" << endl;
        cout << "3. 设置角色权限" << endl;
        cout << "4. 录入操作员（从文件读取）" << endl;
        cout << "5. 修改操作员" << endl;
        cout << "6. 分配操作员角色" << endl;
        cout << "7. 打印角色信息" << endl;
        cout << "8. 打印操作员信息" << endl;
        cout << "0. 退出" << endl;
        cout << "请选择操作: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addRoleFromFile();
                break;
            case 2: {
                int roleCode;
                cout << "请输入要修改的角色代码: ";
                cin >> roleCode;
                Role modifiedRole;
                cout << "请输入新的角色名称: ";
                cin >> modifiedRole.roleName;
                cout << "请输入新的角色权限（以逗号分隔）: ";
                cin >> modifiedRole.rolePermissions;
                modifyRole(roleCode, modifiedRole);
                break;
            }
            case 3: {
                int roleCode;
                cout << "请输入要设置权限的角色代码: ";
                cin >> roleCode;
                string permissions;
                cout << "请输入角色权限（以逗号分隔）: ";
                cin >> permissions;
                setRolePermissions(roleCode, permissions);
                break;
            }
            case 4:
                addOperatorFromFile();
                break;
            case 5: {
                int operatorId;
                cout << "请输入要修改的操作员ID: ";
                cin >> operatorId;
                Operator modifiedOperator;
                cout << "请输入新的操作员姓名: ";
                cin >> modifiedOperator.operatorName;
                cout << "请输入新的操作员密码: ";
                cin >> modifiedOperator.password;
                cout << "请输入新的角色代码: ";
                cin >> modifiedOperator.roleCode;
                modifyOperator(operatorId, modifiedOperator);
                break;
            }
            case 6: {
                int operatorId;
                cout << "请输入要分配角色的操作员ID: ";
                cin >> operatorId;
                int roleCode;
                cout << "请输入角色代码: ";
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
                cout << "退出管理员子系统。" << endl;
                break;
            default:
                cout << "无效的选择，请重新输入。" << endl;
        }
    } while (choice!= 0);

    return 0;
}