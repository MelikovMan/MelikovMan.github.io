function closeModal(wrapper){
    wrapper.style.display = "none";
    history.pushState({"formtoggle": false});
}
window.addEventListener("DOMContentLoaded", function(event){
let but = document.getElementById("showbutton");
let wra = document.getElementById("wrapper");
let x = document.getElementById("close");
let fiel = document.querySelectorAll(".fields");
fiel.forEach((element) => {
    element.value = localStorage.getItem(element.name)
    element.addEventListener("blur", 
    (event)=>localStorage.setItem(event.target.name, event.target.value));
});
x.addEventListener("click",(event)=>{closeModal(wrapper);})
but.onclick = function() {
  wra.style.display = "flex";
  history.pushState({"formtoggle": true}, "", "#form")};
window.onclick = function(event) {
  if (event.target == wra) 
  closeModal(wrapper);
 };
window.addEventListener("popstate",(event)=>
{(event.state.formtoggle) ? wra.style.display="none": wra.style.display="flex";})
window.addEventListener("keydown",function(event){
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
{(event.target.checked)? b[0].disabled=false: b[0].disabled=true;})
let form = document.getElementById("contact");
form.addEventListener("submit", function(event){
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