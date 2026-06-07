#include "api.hpp"

API::API(){
}


void API::page(httplib::Response& res) const{
    std::ifstream file("../index.html");       // Creer juste une variable qui lit le fichier
    
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
}

void API::button(httplib::Response& res) const{
    std::cout<<"Bouton clique, let's Gooo !!!"<<std::endl;      // Lorsque le serveur recois la requette il affiche un message dans la console
    res.set_content("OK action executée", "text/plain");
}

void API::log(const httplib::Request& req, httplib::Response& res){
        std::string login = req.get_param_value("login");
        std::string password = req.get_param_value("password");
        
        if(checkLog(login, password) == true){
            res.set_content("OK action executée", "text/plain");
            std::cout << "Login: " << login << std::endl;
            std::cout << "Password: " << password << std::endl;
        }else{
            res.set_content("Login ou mot de passe incorrect", "text/plain");
        }
}

API::~API(){
}