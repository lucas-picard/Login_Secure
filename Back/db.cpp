#include "db.hpp"

DB::DB(){
}

void DB::adds(const char* l, const char* m, const char* r){
    const char* insert_users =
        "INSERT INTO infos (login, password, role) VALUES (?, ?, ?);";

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, insert_users, -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, l, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, m, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, r, -1, SQLITE_STATIC);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

void DB::tableL(){
    
    sqlite3_open("mdp.db", &db);        // Si il n'y a pas déja de db existant ont la créer et l'ouvre

    const char* create_table =          // String sous forme de "char*" car en C il n'y a pas de std::string
    "CREATE TABLE IF NOT EXISTS infos("     // code sql pour créer une table
    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
    "login TEXT UNIQUE NOT NULL,"
    "password TEXT NOT NULL,"
    "role TEXT NOT NULL)";
    sqlite3_exec(db, create_table, nullptr, nullptr, nullptr);      // On fait une requete au pret de la base de donner pour "create_table"
}


void DB::close(){
    sqlite3_close(db);
}

DB::~DB(){
}
