window.addEventListener("DOMContentLoaded", function(event){
let but = document.getElementById("showbutton");
let wra = document.getElementById("wrapper");
let x = document.getElementById("close");
x.addEventListener("click",(event)=>{wra.style.display = "none";})
but.onclick = function() {
  wra.style.display = "flex";};
    window.onclick = function(event) {
  if (event.target == wra) {
    wra.style.display = "none";
  }
}
let chl = document.getElementsByName("check");
let b = document.getElementsByName("subbutton");
chl[0].addEventListener("change", (event)=>
{(event.target.checked)?b[0].disabled=false:b[0].disabled=true;})
let form = document.getElementById("contact")
form.addEventListener("submit", function(event){
  event.preventDefault();
  fetch("https://formcarry.com/s/KAkRhB37_6s",{method:"POST", body:new FormData(form)})
  .then((response)=>alert("Успешная отправка"),(error)=>alert("Ошибка отправки"));
  /*let xhrhttml = new XMLHttpRequest();
  let FD = new FormData(event.target);
  xhrhttml.addEventListener("load", ()=>alert("Успешная отправка"))
  xhrhttml.addEventListener("error", ()=>alert("Ошибка отправки!"))
  xhrhttml.open("POST", "https://formcarry.com/s/KAkRhB37_6s", true);
  xhrhttml.send(FD);
  */
})
  });