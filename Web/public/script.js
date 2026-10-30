const userLogin = document.querySelector(".login");
const userPassword = document.querySelector(".password");

function authentification(){
  const req = new XMLHttpRequest();
  const params = new URLSearchParams({
    login: userLogin.value,
    password: userPassword.value
  });

  req.open("GET", "/api/authentification?" + params.toString());
  req.onload = function(){
    if (req.status === 200) {
      window.location.assign("/head.html");
      return;
    }

    alert(req.responseText || "Erreur du serveur (" + req.status + ")");
  };
  req.onerror = function(){
    alert("Impossible de contacter le serveur.");
  };
  req.send();
}
