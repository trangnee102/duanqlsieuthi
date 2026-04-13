cmake_minimum_required(VERSION 4.1)
project(duanqlsieuthi)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Bắt buộc: Chỉ định thư mục chứa các file Header (.h)
include_directories(include)

# Bắt buộc: Tự động tìm tất cả các file mã nguồn (.cpp) trong thư mục src
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Bắt buộc: Tạo file thực thi từ toàn bộ mã nguồn tìm được
add_executable(duanqlsieuthi ${SOURCES}
        include/models/entities/Product.h
        include/models/entities/Product.h
        src/models/entities/Product.cpp
        include/models/logic/InventoryModel.h
        src/models/logic/InventoryModel.cpp
        include/utils/FileHandler.h
        src/utils/FileHandler.cpp
        include/views/InventoryView.h
        src/views/InventoryView.cpp
        include/controllers/InventoryController.h
        src/controllers/InventoryController.cpp
        include/models/entities/Person.h
        src/models/entities/Person.cpp
        include/models/entities/Employee.h
        src/models/entities/Employee.cpp
        include/models/logic/AuthModel.h
        src/models/logic/AuthModel.cpp
        include/views/EmployeeView.h
        src/views/EmployeeView.cpp
        include/controllers/EmployeeController.h
        src/controllers/EmployeeController.cpp
        include/utils/DateUtils.h
        src/utils/DateUtils.cpp
        include/models/entities/Customer.h
        src/models/logic/CustomerModel.cpp
        include/utils/StringUtils.h
        src/utils/StringUtils.cpp
        include/models/logic/CategoryModel.h
        src/models/logic/CategoryModel.cpp)