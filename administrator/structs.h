//
// Created by Axuuuu on 2024/12/20.
//

#ifndef CODE_LEARN_STRUCTS_H
#define CODE_LEARN_STRUCTS_H
#include <string>
struct Role {
    int roleCode;  // 角色代码（唯一）
    std::string roleName;  // 角色名称
    std::string rolePermissions;  // 角色权限
};
//操作员：
struct Operator {
    int operatorId;  // 操作员工号(唯一)
    std::string operatorName;  // 操作员姓名
    std::string password;  // 操作员密码
    int roleCode;  // 角色代码
};
//菜品：
struct Dish {
    std::string dishId;  // 菜品ID（唯一）
    std::string dishName;  // 菜品名称
    double largePortionPrice = 0;  // 大份菜品价格
    double smallPortionPrice = 0; //小份菜品价格
    double mediumPortionPrice = 0; //中份菜品价格
    bool dishStatus;  //菜品状态//
};
//订单：
struct Order {
    int orderId;  // 订单编号（唯一）
    std::string orderTime;  // 点餐时间
    int customerId;  // 顾客ID
    int tableNumber;  // 桌号
    bool isReserved;  // 是否为预订订单
    Dish dishes[100];  // 订单包含的菜品信息
    double totalPrice;  // 订单总价
};
//顾客：
struct Customer {
    int customerId;  // 顾客ID(唯一)
    std::string customerName;  // 顾客姓名
    std::string contactNumber;  // 顾客联系电话
};
//餐桌：
struct Table {
    int tableNumber;  // 桌号(唯一)
    std::string tableStatus;  // 餐桌状态，如空闲、占用、预订等
};

//支付方式：
struct PaymentMethod {
    int paymentMethodId;  // 支付方式ID
    std::string paymentMethodName;  // 支付方式名称,如现金、微信支付、支付宝支付等
};

//结算：
struct Settlement {
    int settlementId;  // 结算ID
    int orderId;  //订单表
    std::string settlementTime;  // 结算时间
    int paymentMethodId;  // 支付方式ID
    double amount;  // 结算金额
};
//厨师：
struct Chef {
    int chefId;  // 厨师ID（唯一）
    std::string chefName;  // 厨师姓名
};

#endif //CODE_LEARN_STRUCTS_H
