function closeModal(wrapper){
    wrapper.style.display = "none";
    history.pushState({"formtoggle": false},"","8.html");
}
function openModal(wrapper){
  wrapper.style.display = "flex";
  history.pushState({"formtoggle": true}, "", "#form");
}
window.addEventListener("DOMContentLoaded", function(event){
let but = document.getElementById("showbutton");
let wra = document.getElementById("wrapper");
let x = document.getElementById("close");
let fiel = document.querySelectorAll(".fields");
fiel.forEach((element) => {                                                       // LOCAL STORAGE REALIZATION
    element.value = localStorage.getItem(element.name);
    element.addEventListener("blur", 
    (event)=>localStorage.setItem(event.target.name, event.target.value));        
});
x.addEventListener("click",(event)=>{closeModal(wrapper);})                       // CLOSES WINDOW ON X HIT
but.onclick = function(){
  openModal(wra);
};
window.onclick = function(event) {                                                //CLOSES WINDOW ON CLICKING OUTSIDE IT
  if (event.target == wra) 
  closeModal(wrapper);
 };
history.pushState({"formtoggle": false},"","8.html");                             // HISTORY API REALIZATION
window.addEventListener("popstate",(event) => {
  (event.state.formtoggle)? wra.style.display = "flex" : wrapper.style.display = "none";
  });
window.addEventListener("keydown",function(event){                                //CLOSES WINDOW ON ESC HIT
    if(wra.style.display!="none")
    switch(event.key){
        case "Escape":
        case "Esc":
            closeModal(wrapper);
            break;
        default:
    }
});
let chl = document.getElementsByName("check");
let b = document.getElementsByName("subbutton");
chl[0].addEventListener("change", (event)=>
{(event.target.checked)? b[0].disabled=false: b[0].disabled=true;})               //BUTTON IS ENABLED ONLY IF YOU HAVE TERMS CHECKMARK CHECKED
let form = document.getElementById("contact");
form.addEventListener("submit", function(event){                                  //AJAX USING FETCH
  event.preventDefault();
  fetch("https://formcarry.com/s/KAkRhB37_6s",{method:"POST",
  headers: new Headers({"Content-type": "application/json", 'Accept': 'application/json'}), 
  body: JSON.stringify(Object.fromEntries(new FormData(form)))})
  .then(function(response){
      if (!response.ok) throw new Error(response.status);
      return response;
  })
  .then((response)=>{alert("Успешная отправка");
    console.log(response.text());})
  .catch((error)=>{alert("Ошибка отправки");
    console.log(error);});
    fiel.forEach((element) => {element.value = ""});
    localStorage.clear();
  /*let xhrhttml = new XMLHttpRequest();
  let FD = new FormData(event.target);
  xhrhttml.addEventListener("load", ()=>alert("Успешная отправка"))
  xhrhttml.addEventListener("error", ()=>alert("Ошибка отправки!"))
  xhrhttml.open("POST", "https://formcarry.com/s/KAkRhB37_6s", true);
  xhrhttml.send(FD);
  */
})
  });