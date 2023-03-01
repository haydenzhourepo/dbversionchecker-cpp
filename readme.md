## DBVersionChecker

## introduction
this is a helper library for those who need compare db version and determin db version by db buildVersionNum.

## build
```
mkdir build && cd build
cmake ..
sudo cmake --build .

#sudo cmake --install .
```
## test
src/dbVersionChecker_test.cpp
```
./checker_test
```

## demo
```
int main(int argc, char *argv[])
{

    auto buildVersion = SQLServerBuildVersion("1.0");

    CHECK_MSG(SQLServerBuildVersion("10.0.6814.4") < SQLServerVersion::SQL_SERVER_2012, "1 should be less than SQL_SERVER_2012\n");
    CHECK_MSG(SQLServerBuildVersion("10.0.6814.4") <= SQLServerVersion::SQL_SERVER_2008, "2 should be less than or equal SQL_SERVER_2008\n");
    CHECK_MSG(SQLServerBuildVersion("16.0.4003.1") <= SQLServerVersion::SQL_SERVER_2022, "3 should be less than or equal SQL_SERVER_2022\n");
    CHECK_MSG(SQLServerBuildVersion("16.0.4003.1") >= SQLServerVersion::SQL_SERVER_2022, "4 should be grater than or equal SQL_SERVER_2022\n");
    CHECK_MSG(SQLServerBuildVersion("16.0.1000.6") > SQLServerVersion::SQL_SERVER_2019, "5 should be grater than SQL_SERVER_2019\n");

    auto mydbversion = SQLServerBuildVersion("15.0.4280.7");
    CHECK_MSG(mydbversion < "15.0.4298.1", "6 should be less than 15.0.4298.1\n");
    CHECK_MSG(mydbversion > "15.0.2101.7", "7 should be grater than 15.0.2101.7\n");
    CHECK_MSG(mydbversion > SQLServerVersion::SQL_SERVER_2008, "8 should be grater than SQL_SERVER_2008\n");
    CHECK_MSG(mydbversion <= SQLServerVersion::SQL_SERVER_2019, "9 should be less than or equal SQL_SERVER_2019\n");
    CHECK_MSG(mydbversion == SQLServerVersion::SQL_SERVER_2019, "10 should be  equal SQL_SERVER_2019\n");
}
```

## how to use
### after install use without find_package
```cmake
add_executable(dbchker t.cpp)
target_link_libraries(dbchker dbversionchecker)
```

### after install use with find_package
```cmake
#// if installed with intall_prefix, add camke search path
#// list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
find_package(dbversionchecker)
add_executable(dbchecker t.cpp)
target_link_libraries(dbchecker dbversionchecker)

```

use case

```cpp
#include <iostream>
#include <SQLServerChecker.h>

int main()
{

    auto buildversion = DBVersionChecker::SQLServerBuildVersion("7.0");
    if (buildversion <= DBVersionChecker::SQLServerVersion::SQL_SERVER_2008)
    {
        std::cout << "do something compatible to sqlserver 2008\n";
    }
} 
```