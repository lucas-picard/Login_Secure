#include "db.hpp"
#include "secu.hpp"

int main(){

    
    DB base{};
    SECU hash{};


    base.tableL();
    base.adds(hash.hash_log("lucas").c_str(), hash.hash_mdp("test").c_str(), "Admin");
    base.adds("Fred", "GANG69", "User");

    base.close();
  
    return (1);
}