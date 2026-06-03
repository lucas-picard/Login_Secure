#include <iostream>
#include <string>
#include <cstring>   // Pour strlen()
#include <sodium.h>


std::string hash_mdp(const char* mdp){
    // Buffer qui va contenir le hash final
    char hash[crypto_pwhash_STRBYTES];

    // Création du hash
    // Retourne 0 si succès
    // Retourne -1 si erreur
    if (crypto_pwhash_str(
        hash,   // Buffer de sortie
        mdp,   // Mot de passe
        strlen(mdp),   // Taille du mot de passe
        crypto_pwhash_OPSLIMIT_SENSITIVE, // Coût CPU
        crypto_pwhash_MEMLIMIT_SENSITIVE  // Coût mémoire
    ) != 0) {
        std::cout << "Erreur hashage" << std::endl;
        return std::string("Erreur de hashage !");
    }
   
    return std::string(hash);
}

std::string hash_login(const char* login){
    // Buffer qui va contenir le hash final
    char hash[crypto_pwhash_STRBYTES];

    // Création du hash
    // Retourne 0 si succès
    // Retourne -1 si erreur
    if (crypto_pwhash_str(
        hash,   // Buffer de sortie
        login,   // Mot de passe
        strlen(login),   // Taille du mot de passe
        crypto_pwhash_OPSLIMIT_MODERATE, // Coût CPU
        crypto_pwhash_MEMLIMIT_MODERATE  // Coût mémoire
    ) != 0) {
        std::cout << "Erreur hashage" << std::endl;
        return std::string("Erreur de hashage !");
    }
   
    return std::string(hash);
}

int main() {
     if (sodium_init() < 0) {
        return 1;
    }
    
    std::string log;
    std::cout<<"Entrez un login: ";
    getline(std::cin, log);
    std::string passwd;
    std::cout<<"Entrez un mot de passe: ";
    getline(std::cin, passwd);

    if(crypto_pwhash_str_verify(hash_login("lucas").c_str(), log.c_str(), strlen("lucas")) == 0 && 
        crypto_pwhash_str_verify(hash_mdp("CIELAR2026").c_str(), passwd.c_str(), strlen("CIELAR2026")) == 0 ){
        std::cout<<"Mot de passe valide"<<std::endl;
    }else{
        std::cout<<"Mot de passe invalide"<<std::endl;
        std::cout<<"Veuillez reesayer"<<std::endl;
    }
    

    return (0);
}