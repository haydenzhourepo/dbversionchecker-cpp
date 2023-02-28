#include "SQLServerChecker.h"

using namespace DBVersionChecker;

// SQLServerVersion
SQLServerVersion::SQLServerVersion(const std::string &name, const std::string &servicePack,
                                   const std::string &minBuildVersionNum)
    : name_(name), minBuildVersionNum_(minBuildVersionNum), servicePack_(servicePack) {}

SQLServerVersion::SQLServerVersion(const SQLServerVersion &other)
{
    this->name_ = other.name_;
    this->minBuildVersionNum_ = other.minBuildVersionNum_;
    this->servicePack_ = other.servicePack_;
}

std::shared_ptr<SQLServerVersion> SQLServerVersion::getPreVersion() const
{
    int i = 0;
    for (; i < SQLServerVersion::SQLServerVersionList_.size(); i++)
    {
        if (SQLServerVersion::SQLServerVersionList_[i].getName() == this->name_)
        {
            break;
        }
    }

    if (i == 0)
    {
        return std::make_shared<SQLServerVersion>(SQLServerVersion::SQL_SERVER_MINIMAL);
    }

    return std::make_shared<SQLServerVersion>(SQLServerVersion::SQLServerVersionList_[i - 1]);
}
std::shared_ptr<SQLServerVersion> SQLServerVersion::getNextVersion() const
{
    int i = 0;
    for (; i < SQLServerVersion::SQLServerVersionList_.size(); i++)
    {
        if (SQLServerVersion::SQLServerVersionList_[i].getName() == this->name_)
        {
            break;
        }
    }

    if (i == SQLServerVersion::SQLServerVersionList_.size() || i == (SQLServerVersion::SQLServerVersionList_.size() - 1))
    {
        return std::make_shared<SQLServerVersion>(
            SQLServerVersion::SQLServerVersionList_[SQLServerVersion::SQLServerVersionList_.size() - 1]);
    }

    return std::make_shared<SQLServerVersion>(SQLServerVersion::SQLServerVersionList_[i + 1]);
};

int SQLServerVersion::versionCompare(const std::string &str1, const std::string &str2)
{
    auto pos1l = 0;
    auto pos2l = 0;
    auto pos1r = str1.find('.');
    auto pos2r = str2.find('.');

    int rst = 0;
    while (pos1r != std::string::npos && pos2r != std::string::npos)
    {
        rst = std::stoi(str1.substr(pos1l, pos1r - pos1l)) - std::stoi((str2.substr(pos2l, pos2r - pos2l)));
        if (rst != 0)
        {
            return rst;
        }

        pos1l = pos1r + 1;
        pos2l = pos2r + 1;
        pos1r = str1.find('.', pos1l);
        pos2r = str2.find('.', pos2l);
    }

    if (pos1r != std::string::npos)
        return -1;

    if (pos1r != std::string::npos)
        return 1;

    return 0;
}

const SQLServerVersion SQLServerVersion::SQL_SERVER_6_5{"SQL Server 6.5", "", "6.50.201"};
const SQLServerVersion SQLServerVersion::SQL_SERVER_7_0{"SQL Server 7.0", "", "7.00.623"};
const SQLServerVersion SQLServerVersion::SQL_SERVER_2000{"SQL Server 2000", "", "8.00.194"};
const SQLServerVersion SQLServerVersion::SQL_SERVER_2005{"SQL Server 2005", "", "9.00.1399"};
const SQLServerVersion SQLServerVersion::SQL_SERVER_2008{"SQL Server 2008", "", "10.00.1600.22"};
const SQLServerVersion SQLServerVersion::SQL_SERVER_2008_R2{"SQL Server 2008 R2", "", "10.50.1600.1"};
const SQLServerVersion SQLServerVersion::SQL_SERVER_2012{"SQL Server 2012", "", "11.0.2100.60"};
const SQLServerVersion SQLServerVersion::SQL_SERVER_2014{"SQL Server 2014", "", "12.0.2000.8"};
const SQLServerVersion SQLServerVersion::SQL_SERVER_2016{"SQL Server 2016", "", "13.0.2149.0"};
const SQLServerVersion SQLServerVersion::SQL_SERVER_2017{"SQL Server 2017", "", "14.0.3006.16"};
const SQLServerVersion SQLServerVersion::SQL_SERVER_2019{"SQL Server 2019", "", "15.0.2000.5"};
const SQLServerVersion SQLServerVersion::SQL_SERVER_2022{"SQL Server 2022", "", "16.0.1000.6"};
const SQLServerVersion SQLServerVersion::SQL_SERVER_MINIMAL{"SQL_SERVER_MINIMAL", "", "0.0.0"};

const std::vector<SQLServerVersion> SQLServerVersion::SQLServerVersionList_({SQLServerVersion::SQL_SERVER_6_5,
                                                                             SQLServerVersion::SQL_SERVER_7_0,
                                                                             SQLServerVersion::SQL_SERVER_2000,
                                                                             SQLServerVersion::SQL_SERVER_2005,
                                                                             SQLServerVersion::SQL_SERVER_2008,
                                                                             SQLServerVersion::SQL_SERVER_2008_R2,
                                                                             SQLServerVersion::SQL_SERVER_2012,
                                                                             SQLServerVersion::SQL_SERVER_2014,
                                                                             SQLServerVersion::SQL_SERVER_2016,
                                                                             SQLServerVersion::SQL_SERVER_2017,
                                                                             SQLServerVersion::SQL_SERVER_2019,
                                                                             SQLServerVersion::SQL_SERVER_2022});

// SQLServerBuildVersion
SQLServerBuildVersion::SQLServerBuildVersion(const std::string &buildVersionNumer)
    : buildVersionNum_(buildVersionNumer)
{
    auto preVersion = SQLServerVersion::SQLServerVersionList_[0];

    int i = 0;
    for (; i < SQLServerVersion::SQLServerVersionList_.size(); i++)
    {
        if (SQLServerVersion::versionCompare(buildVersionNum_, SQLServerVersion::SQLServerVersionList_[i].getMinBuildVersionNum()) < 0)
        {
            break;
        }
        preVersion = SQLServerVersion::SQLServerVersionList_[i];
    }

    if (i == 0)
    {

        this->version_ = std::make_shared<SQLServerVersion>(SQLServerVersion::SQL_SERVER_MINIMAL);
        return;
    }

    this->version_ = std::make_shared<SQLServerVersion>(SQLServerVersion::SQLServerVersionList_[i - 1]);
};
