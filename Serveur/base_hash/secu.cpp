#include "secu.hpp"

SECU::SECU(){
}

std::string SECU::hash_log(const char* log){
    // Buffer qui va contenir le hash final
    char hash[crypto_pwhash_STRBYTES];

    // Création du hash
    // Retourne 0 si succès
    // Retourne -1 si erreur
    if (crypto_pwhash_str(
        hash,   // Buffer de sortie
        log,   // Mot de passe
        strlen(log),   // Taille du mot de passe
        crypto_pwhash_OPSLIMIT_MODERATE, // Coût CPU
        crypto_pwhash_MEMLIMIT_MODERATE  // Coût mémoire
    ) != 0) {
        std::cout << "Erreur hashage" << std::endl;
        return std::string("Erreur de hashage !");
    }
   
    return std::string(hash);
}

std::string SECU::hash_mdp(const char* mdp){
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


SECU::~SECU(){
}