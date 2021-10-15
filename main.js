window.addEventListener('DOMContentLoaded', function (event) {
    let regex = /^\s*\d+\s*$/;
    let b = document.getElementById("mybutt");
    b.addEventListener("click", function (event) {
        //let regex = /[./n]*/
        let f1 = document.getElementById("field1");
        let f2 = document.getElementById("field2");
        let r = document.getElementById("result");
        if (regex.test(f1.value) && regex.test(f2.value))
            r.innerHTML = "Стоимость покупки: " + f1.value * f2.value;
        else
            alert("Invalid input!");
        });
    let s = document.getElementsByName("myselect");
    let baseprice = s.value;
    s[0].addEventListener("change", function(event) {
        let select = event.target;
        let radios = document.getElementById("myradios");
        let chbx = document.getElementById("mycheck");
        checkbuf = 0;
        radiobuf = 0;
        switch(select.value){
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
        });
    let r = document.querySelectorAll(".mycheck input[type=checkbox");
    r.forEach(function(checkbox) {
        checkbox.addEventListener("change", function(event) {
        let r = event.target;
        (r.checked)? checkbuf+=r.value : checkbuf-= r.value;
          });    
        });
    let r1 = document.querySelectorAll(".myradios input[type=radio]");
    r1.forEach(function(radio) {
        radio.addEventListener("change", function(event) {
        let r = event.target;
        radiobuf = r.value;
         });    
     });
     let b2 = document.getElementById("mybutt2");
     b2.addEventListener("click", function (event) {
        //let regex = /[./n]*/
        let f1 = document.getElementById("field1");
        let f2 = document.getElementById("field2");
        let r = document.getElementById("result2");
        let amount = document.getElementById("field2");
        if (regex.test(amount))
            r.innerHTML = "Стоимость покупки: " + amount*(baseprice+radiobuf);
        else
            alert("Invalid input!");
        });
    });