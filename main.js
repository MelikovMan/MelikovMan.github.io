/*function onClick(){
    let regex = /\d+/
    let f1 = document.getElementById("field1");
    let f2 = document.getElementById("field2");
    let r = document.getElementById("result");
    if(regex.exec(f1.value) && regex.exec(f2.value))
    r.innerHTML = "Стоимость покупки: " + f1.value*f2.value;
    else alert("Invalid input!");
}
*/
window.addEventListener('DOMContentLoaded', function (event) {
        let b = document.getElementById("mybutt");
        b.addEventListener("click", function (event) {
            let regex = /^\s*\d+\s*$/;
            //let regex = /[./n]*/
            let f1 = document.getElementById("field1");
            let f2 = document.getElementById("field2");
            let r = document.getElementById("result");
            if (regex.exec(f1.value) && regex.exec(f2.value))
                r.innerHTML = "Стоимость покупки: " + f1.value * f2.value;

            else
                alert("Invalid input!");
        });
    });