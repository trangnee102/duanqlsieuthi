//
// Created by admin on 4/10/2026.
//

#ifndef DUANQLSIEUTHI_EMPLOYEECONTROLLER_H
#define DUANQLSIEUTHI_EMPLOYEECONTROLLER_H

#pragma once
#include "models/logic/AuthModel.h"
#include "views/EmployeeView.h"

class EmployeeController {
private:
    // Dùng tham chiếu để dùng chung dữ liệu với hệ thống đăng nhập
    AuthModel& model;
    EmployeeView& view;

public:
    // Constructor nhận vào model và view
    EmployeeController(AuthModel& m, EmployeeView& v);

    // Vòng lặp quản lý nhân sự
    void run(Employee* currentUser);
};

#endif //DUANQLSIEUTHI_EMPLOYEECONTROLLER_H