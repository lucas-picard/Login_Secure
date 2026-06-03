#include <iostream>
#include <fstream>
#include "httplib.h"

int main() {

    httplib::Server svr;        // Creer le serveur HTTP
    svr.set_mount_point("/", "./");     // Fait en sorte que le navigateur puisse accepter plusieurs requettes "index.html", "style.css", etc...

    svr.Get("/", [](const httplib::Request&, httplib::Response& res) {        // Prends les requettes du client et envoie celle du serveur
        std::ifstream file("index.html");       // Creer juste une variable qui lit le fichier

        if (!file.is_open()) {      // Si le fichier "index.html" n'est pas ouvert ont affiche une erreur dans le navigateur
            res.status = 404;
            res.set_content("index.html introuvable", "text/plain");
            return;
        }

        std::string content(        // Permet de mettre le fichier lu sous forme de string et le lit entierement
            (std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>()
        );
        res.set_content(content, "text/html");      // "set_content" envoie au navigateur, "text/html" dit au navigateur le type de "content"
    });

    svr.Get("/api/test", [](const httplib::Request&, httplib::Response& res) {        
        std::cout<<"Bouton clique, let's Gooo !!!"<<std::endl;      // Lorsque le serveur recois la requette il affiche un message dans la console
        res.set_content("OK action executée", "text/plain");
    });

     svr.Get("/api/authentification", [](const httplib::Request& req, httplib::Response& res) {
        const std::string l = "test";
        const std::string p = "test";

        std::string login = req.get_param_value("login");
        std::string password = req.get_param_value("password");
        
        if(login == l && password == p){
            res.set_content("OK action executée", "text/plain");
            std::cout << "Login: " << login << std::endl;
            std::cout << "Password: " << password << std::endl;
        }else{
            res.set_content("Login ou mot de passe incorrect", "text/plain");
        }
            
    });

    std::cout << "Serveur sur http://localhost:8080" << std::endl;      

    svr.listen("0.0.0.0", 8080);        // Ecoute le port 8080
}