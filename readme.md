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