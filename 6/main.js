let regex = /^\s*[+-]?\d+\s*$/;
function recalc(base,check, rad){
    var chk = Number(check);
    var rd = Number(rad);
    var bs = Number(base);
    if (bs == 1000) rd = 0;
    if (bs == 150) chk=0;
    if (bs == 50) rd=chk=0;
    let r = document.getElementById("result2");
    let amount = document.getElementById("field3");
    if (regex.test(amount.value) && regex.test(base) && regex.test(check) && regex.test(rad))
        r.innerHTML = "Стоимость покупки: " + amount.value*(bs+chk+rd);
    else
    r.innerHTML = "Стоимость покупки неверна "
}
window.addEventListener('DOMContentLoaded', function (event) {
    let checkbuf = 0;
    let radiobuf = 0;
    let b = document.getElementById("mybutt");
    b.addEventListener("click", function (event) {
        //let regex = /[./n]*/
        let f1 = document.getElementById("field1");
        let f2 = document.getElementById("field2");
        let r = document.getElementById("result");
        if (regex.test(f1.value) && regex.test(f2.value))
            r.innerHTML = "Стоимость покупки: " + f1.value * f2.value;
        else
        r.innerHTML = "Стоимость покупки неверна "
        });
    let s = document.getElementsByName("myselect");
    let baseprice = s[0].value;
    s[0].addEventListener("change", function(event) {
        let select = event.target;
        let radios = document.getElementById("myradios");
        let chbx = document.getElementById("mycheck");
        baseprice = select.value;
        let sw = Number(select.value);
        switch(sw){
            case 50:
                radios.style.display = "none";
                chbx.style.display = "none";
            break;
            case 150:
                radios.style.display = "block";
                chbx.style.display = "none";
            break;
            case 1000:
                radios.style.display = "none";
                chbx.style.display = "block";
            break;
            default:
        }
        recalc(baseprice,checkbuf, radiobuf)
        });
    let r = document.querySelectorAll(".mycheck input[type=checkbox");
    r.forEach(function(checkbox) {
        if(r.checked) checkbuf+=Number(r.value)
        checkbox.addEventListener("change", function(event) {
        let r = event.target;
        (r.checked)? checkbuf+=Number(r.value) : checkbuf-= Number(r.value);
        recalc(baseprice,checkbuf, radiobuf)
          });    
        });
    let r1 = document.querySelectorAll(".myradios input[type=radio]");
    r1.forEach(function(radio) {
        if(r.checked) radiobuf = r.value;
        radio.addEventListener("change", function(event) {
        let r = event.target;
        radiobuf = r.value;
        recalc(baseprice,checkbuf, radiobuf)
         });    
     });
     let f = document.getElementById("field3")
     f.addEventListener("input", function(event){
            recalc(baseprice,checkbuf, radiobuf);
     });
     let radios = document.getElementById("myradios");
     let chbx = document.getElementById("mycheck");
     switch(Number(baseprice)){
        case 50:
            radios.style.display = "none";
            chbx.style.display = "none";
        break;
        case 150:
            radios.style.display = "block";
            chbx.style.display = "none";
        break;
        case 1000:
            radios.style.display = "none";
            chbx.style.display = "block";
        break;
        default:
    }
    recalc(baseprice,checkbuf, radiobuf)
    });