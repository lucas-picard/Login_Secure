#include <iostream>
#include <string>
#include <sqlite3.h>

void adds(sqlite3* db, const char* login, const char* password){
    const char* sql =
        "INSERT OR IGNORE INTO infos (login, password) VALUES (?, ?);";

    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, login, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_TRANSIENT);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

bool checkLogin(sqlite3* db, const std::string& login, const std::string& password){
    const char* sql =
        "SELECT 1 FROM infos WHERE login=? AND password=? LIMIT 1;";

    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, login.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_TRANSIENT);

    bool found = (sqlite3_step(stmt) == SQLITE_ROW);

    sqlite3_finalize(stmt);

    return found;
}

int main(){
    sqlite3* db;

    sqlite3_open("mdp.db", &db);

    const char* create_table =
        "CREATE TABLE IF NOT EXISTS infos("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "login TEXT UNIQUE NOT NULL,"
        "password TEXT NOT NULL)";

    sqlite3_exec(db, create_table, nullptr, nullptr, nullptr);

    adds(db, "Lucas", "MotDePasse");
    adds(db, "Fred", "GANG69");

    std::string login, password;

    std::cout << "Login : "; getline(std::cin, login);

    std::cout << "Password : "; getline(std::cin, password);

    if (checkLogin(db, login, password))
        std::cout << "Vous etes connecte !" << std::endl;
    else
        std::cout << "Login ou mot de passe incorrect !" << std::endl;

    sqlite3_close(db);

    return 0;
}