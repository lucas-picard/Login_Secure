#include "../Back/api.hpp"

API api{};

int main() {
    if (sodium_init() < 0) { 
        std::cerr << "Erreur sodium_init" << std::endl;
        return 1;
    }

    api.tableL();                                              
    api.adds("lucas", api.hash_mdp("test").c_str(), "Admin");

    httplib::SSLServer svr("cert.pem", "key.pem");
    svr.set_mount_point("/", "./");

    svr.Get("/", [](const httplib::Request&, httplib::Response& res) { api.page(res); });
    svr.Get("/api/test", [](const httplib::Request&, httplib::Response& res) { api.button(res); });
    svr.Get("/api/authentification", [](const httplib::Request& req, httplib::Response& res) { api.log(req, res); });

    std::cout << "Serveur sur http://localhost:8080" << std::endl;
    svr.listen("0.0.0.0", 8080);
}