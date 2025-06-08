#include "UserManager.h"
#include <sstream>

UserManager::UserManager(const std::string& folder)
    : usersFolder(folder)
{
    if (!std::filesystem::exists(usersFolder)) {
        std::filesystem::create_directory(usersFolder);
    }
    loadUsers();
}

void UserManager::loadUsers()
{
    users.clear();

    for (const auto& entry : std::filesystem::directory_iterator(usersFolder)) {
        if (entry.path().extension() == ".txt") {
            std::ifstream file(entry.path());
            std::string password;
            if (file >> password) {
                std::string login = entry.path().stem().string(); // np. "adam" z "adam.txt"
                users[login] = password;
            }
        }
    }
}
bool UserManager::isValidEmail(const std::string& email) const
{
    const std::regex pattern(R"(^[\w.-]+@[\w.-]+\.[a-zA-Z]{2,}$)");
    return std::regex_match(email, pattern);
}

bool UserManager::validateLogin(const std::string& login, const std::string& password)
{
    auto it = users.find(login);
    if (it != users.end() && it->second == password) {
        currentLogin = login;
        currentPassword = password;
        return true;
    }
    return false;
}

bool UserManager::userExists(const std::string& login) const
{
    return users.find(login) != users.end();
}

void UserManager::registerUser(const std::string& login, const std::string& password)
{
    if (!isValidEmail(login)) {
        return;
    }

    users[login] = password;
    std::ofstream file(usersFolder + "/" + login + ".txt");
    if (file.is_open()) {
        file << password;
    }
}
std::string UserManager::getCurrentLogin() const
{
    return currentLogin;
}

std::string UserManager::getCurrentPassword() const
{
    return currentPassword;
}
