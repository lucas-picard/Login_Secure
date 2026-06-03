const btn = document.querySelector(".button");
const userLogin = document.querySelector(".login");
const userPassword = document.querySelector(".password");


//btn.addEventListener("click", updateButton);

function authentification(){
  const req = new XMLHttpRequest();
  const Login = userLogin.value;
  const Password = userPassword.value;

  req.open(
    "GET", 
    "http://localhost:8080/api/authentification?login=" +
    encodeURIComponent(Login) +
    "&password=" +
    encodeURIComponent(Password)
  );
  
  req.onreadystatechange = function(){
    if(req.readyState == 4 && req.status == 200){
      const message = req.responseText;
      if(message == "OK action executée"){
        window.location.href = "head.html";
        alert("J'ai reussi a te hack")
      }else{
        alert(message);
      }
    }
  }

  req.send();
}

