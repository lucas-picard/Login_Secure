#include "db.hpp"
#include "secu.hpp"

int main(){

    
    DB base{};
    base.tableL();
    SECU hash{base.db};

    base.adds(hash.hash_log("lucas").c_str(), hash.hash_mdp("test").c_str(), "Admin");
    base.adds("Fred", "GANG69", "User");

     std::string login, password;

    std::cout << "Login : "; getline(std::cin, login);

    std::cout << "Password : "; getline(std::cin, password);

    if (hash.checkLog(login, password))
        std::cout << "Vous etes connecte !" << std::endl;
    else
        std::cout << "Login ou mot de passe incorrect !" << std::endl;

    base.close();
  
    return (1);
}