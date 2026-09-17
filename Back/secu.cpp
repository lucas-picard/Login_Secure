#include "secu.hpp"

SECU::SECU(){
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
        return std::string("Erreur de hashage !");
    }
   
    return std::string(hash);
}

bool SECU::checkLog(const std::string& username, const std::string& password) const{
    const char* sql =
        "SELECT password FROM infos WHERE login=?;";        // Permet de recupéré hash de mot de passe pour le login

    sqlite3_stmt* stmt;     // Créer la requete
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);        // Prepare l'envoie de la requette
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);        // Ajoute le login a la requete

    bool ok = false;        
    if (sqlite3_step(stmt) == SQLITE_ROW)       // Si la ligne existe alors
    {
        const char* db_hash = (const char*)sqlite3_column_text(stmt, 0);        // Recupere hash password colone 0

        ok = crypto_pwhash_str_verify(      // Verifie si le hash trouvé 
                 db_hash,       // Le hash du mot de passe a vérifier
                 password.c_str(),      // Password a vérifier
                 password.size()        // Taille du password a vérifier
             ) == 0;
    }

    sqlite3_finalize(stmt);
    return ok;      // Retourne 0 si la vérif est OK et -1 si une erreur
}

SECU::~SECU(){
}