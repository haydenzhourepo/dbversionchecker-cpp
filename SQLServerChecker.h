#ifndef SQLSERVERCHECKER_H
#define SQLSERVERCHECKER_H

#pragma once

#include <memory>
#include "iostream"
#include <vector>

namespace DBVersionChecker
{

    // SQLServerVersion
    class SQLServerVersion
    {
    public:
        SQLServerVersion();
        SQLServerVersion(const std::string &name,
                         const std::string &servicePack, const std::string &minBuildVersionNum);

        SQLServerVersion(const SQLServerVersion &other);

        inline const bool operator==(const SQLServerVersion &other) const
        {
            return this->getName() == other.getName();
        }

        inline const bool operator==(const std::shared_ptr<SQLServerVersion> other) const
        {
            return this->getName() == other->getName();
        }

        inline const std::string &getName() const
        {
            return name_;
        }

        inline const std::string &getMinBuildVersionNum() const
        {
            return minBuildVersionNum_;
        }

        std::shared_ptr<SQLServerVersion> getPreVersion() const;
        std::shared_ptr<SQLServerVersion> getNextVersion() const;

        const static SQLServerVersion SQL_SERVER_6_5;
        const static SQLServerVersion SQL_SERVER_7_0;
        const static SQLServerVersion SQL_SERVER_2000;
        const static SQLServerVersion SQL_SERVER_2005;
        const static SQLServerVersion SQL_SERVER_2008;
        const static SQLServerVersion SQL_SERVER_2008_R2;
        const static SQLServerVersion SQL_SERVER_2012;
        const static SQLServerVersion SQL_SERVER_2014;
        const static SQLServerVersion SQL_SERVER_2016;
        const static SQLServerVersion SQL_SERVER_2017;
        const static SQLServerVersion SQL_SERVER_2019;
        const static SQLServerVersion SQL_SERVER_2022;
        const static SQLServerVersion SQL_SERVER_MINIMAL;

        const static std::vector<SQLServerVersion> SQLServerVersionList_;

        static int versionCompare(const std::string &str1, const std::string &str2);

    private:
        std::string name_;
        std::string minBuildVersionNum_;
        std::string servicePack_;
    };

    // SQLServerBuildVersion
    class SQLServerBuildVersion
    {
    public:
        SQLServerBuildVersion(const std::string &buildVersionNumer);

        inline const std::shared_ptr<SQLServerVersion> getVersion() const
        {
            return version_;
        }

        inline bool operator<(const SQLServerVersion &other) const
        {

            return SQLServerVersion::versionCompare(this->buildVersionNum_,
                                                    other.getMinBuildVersionNum()) < 0;
        }
        inline bool operator<=(const SQLServerVersion &other) const
        {

            return *(other.getNextVersion()) == other ? true : SQLServerVersion::versionCompare(this->buildVersionNum_, other.getNextVersion()->getMinBuildVersionNum()) < 0;
        }

        inline bool operator>(const SQLServerVersion &other) const
        {

            return *(other.getNextVersion()) == other ? false : SQLServerVersion::versionCompare(this->buildVersionNum_, other.getNextVersion()->getMinBuildVersionNum()) >= 0;
        }

        inline bool operator>=(const SQLServerVersion &other) const
        {

            return SQLServerVersion::versionCompare(this->buildVersionNum_,
                                                    other.getMinBuildVersionNum()) >= 0;
        }

        inline bool operator==(const SQLServerVersion &other) const
        {
            return this->getVersion()->getName() == other.getName();
        }

        inline bool operator<(const std::string &buildVersionNum) const
        {
            return SQLServerVersion::versionCompare(this->buildVersionNum_, buildVersionNum) < 0;
        }

        inline bool operator<=(const std::string &buildVersionNum) const
        {
            return SQLServerVersion::versionCompare(this->buildVersionNum_, buildVersionNum) <= 0;
        }

        inline bool operator>(const std::string &buildVersionNum) const
        {
            return SQLServerVersion::versionCompare(this->buildVersionNum_, buildVersionNum) > 0;
        }

        inline bool operator>=(const std::string &buildVersionNum) const
        {
            return SQLServerVersion::versionCompare(this->buildVersionNum_, buildVersionNum) >= 0;
        }

        inline bool operator==(const std::string &buildVersionNum) const
        {
            return SQLServerVersion::versionCompare(this->buildVersionNum_, buildVersionNum) == 0;
        }

    private:
        std::shared_ptr<SQLServerVersion> version_;
        std::string buildVersionNum_;
    };

}
#endif