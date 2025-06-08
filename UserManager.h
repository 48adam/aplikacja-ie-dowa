#pragma once
#include <string>
#include <map>
#include <fstream>
#include <filesystem>
#include <regex>


class UserManager {
public:
    UserManager(const std::string& folder);

    bool validateLogin(const std::string& login, const std::string& password) ;
    bool userExists(const std::string& login) const;
    void registerUser(const std::string& login, const std::string& password);
    bool isValidEmail(const std::string& email) const;
    std::string getCurrentLogin() const;
    std::string getCurrentPassword() const;


private:
    void loadUsers();

    std::string currentLogin;
    std::string currentPassword;

    std::string usersFolder;
    std::map<std::string, std::string> users;
};