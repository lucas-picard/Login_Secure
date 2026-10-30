#include "../Back/api.hpp"
#include <filesystem>

API api{};      

int main(int, char* argv[]) {
    std::error_code error;
    const auto executable_path = std::filesystem::absolute(argv[0], error);
    if (error) {
        std::cerr << "Impossible de déterminer le chemin de l'exécutable : "
                  << error.message() << std::endl;
        return 1;
    }

    std::filesystem::current_path(executable_path.parent_path(), error);
    if (error) {
        std::cerr << "Impossible d'accéder au dossier de l'exécutable : "
                  << error.message() << std::endl;
        return 1;
    }

    if (sodium_init() < 0) {        // Initialise libsodium (obligatoire avant de hasher ou de générer de l'aléatoire)
        std::cerr << "Erreur sodium_init" << std::endl;
        return 1;       // Le programme s'arrête si libsodium ne démarre pas
    }

    api.tableL();       // Ouvre (ou crée) la base mdp.db et crée la table "infos" si elle n'existe pas
    api.adds("lucas", api.hash_mdp("test").c_str(), "Admin");       

    httplib::SSLServer svr("cert.pem", "key.pem");      // Crée un serveur HTTPS avec le certificat et la clé privée
    if (!svr.set_mount_point("/static", "./public")) {
        std::cerr << "Impossible de trouver le dossier public" << std::endl;
        return 1;
    }
                                                // Les autres fichiers (key.pem, mdp.db, head.html...) ne sont plus accessibles depuis le navigateur
                                        

    svr.Get("/", [](const httplib::Request&, httplib::Response& res) { api.page(res); });       // Route "/" : envoie la page de connexion index.html
    svr.Get("/head.html", [](const httplib::Request&, httplib::Response& res) {
        std::ifstream file("head.html");
        if (!file.is_open()) {
            res.status = 404;
            res.set_content("head.html introuvable", "text/plain");
            return;
        }

        std::string content(
            (std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>()
        );
        res.set_content(content, "text/html");
    });
    svr.Get("/api/test", [](const httplib::Request&, httplib::Response& res) { api.button(res); });     // Route "/api/test" : appelée par le bouton de head.html
    svr.Get("/api/authentification", [](const httplib::Request& req, httplib::Response& res) { api.log(req, res); });      // Route de connexion : vérifie le login et le mot de passe reçus dans l'URL

    std::cout << "Serveur sur https://localhost:8080" << std::endl;     
    svr.listen("0.0.0.0", 8080);        // Lance le serveur sur le port 8080, accessible depuis toutes les interfaces réseau (bloque ici tant que le serveur tourne)
}