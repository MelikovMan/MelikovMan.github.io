window.addEventListener('DOMContentLoaded',(e)=>{
    let centerCanvasPosition = function(){
        canvas.width = window.innerWidth / 2;
        canvas.height =window.innerHeight / 2;
      };
    let clearCanvas = function(e) {
        e.preventDefault();
        ctx.fillStyle='white';
        ctx.fillRect(0,0,canvas.width,canvas.height);
    }
    let pos = {x:0,y:0};
    let getCanvasRelative = function (e) {
        let canvas = e.target,
        bx = canvas.getBoundingClientRect();
        let x = (e.changedTouches ? e.changedTouches[0].clientX : e.clientX) - bx.left,
        y = (e.changedTouches ? e.changedTouches[0].clientY : e.clientY) - bx.top;
        pos.x=x;
        pos.y=y;
    };
    let drawMouse = function(e) {
        if (e.buttons !== 1) return;

        ctx.beginPath(); // begin
      
        ctx.lineWidth = 5;
        ctx.lineCap = 'round';
        ctx.strokeStyle = '#c0392b';
      
        ctx.moveTo(pos.x, pos.y); // from
        getCanvasRelative(e);
        ctx.lineTo(pos.x, pos.y); // to
      
        ctx.stroke();
    };
      let canvas = document.getElementById('the-canvas'),
      ctx = canvas.getContext('2d');
      canvas.addEventListener('mouseup',getCanvasRelative);
      canvas.addEventListener('mousedown',getCanvasRelative);
      canvas.addEventListener("touchstart", getCanvasRelative);
      canvas.addEventListener("touchend", getCanvasRelative);
      canvas.addEventListener("mousemove",drawMouse);
      canvas.addEventListener("touchmove",drawMouse);
      let clear = document.getElementById('clear');
      clear.addEventListener("click",clearCanvas);
      window.addEventListener('resize',centerCanvasPosition);
      const form = document.getElementById("contact")
      form.addEventListener("submit",(e)=>{
        e.preventDefault();
          let select = document.getElementById("lang-field");
          let obj = {
              base64: canvas.toDataURL().replace('data:', '').replace(/^.+,/, ''),
              language: select.options[select.selectedIndex].value
          }
          document
              .getElementById('submitbutton')
              .setAttribute('disabled', '1');
          fetch("https://functions.yandexcloud.net/d4et655ongl4sskem62s",
              {
                  method: "POST",
                  body: JSON.stringify(obj)
              })
              .then(function (response) {
                  if (!response.ok) {
                      throw new Error(response);
                  }
                  return response;
              })
              .then((response) => {
                  alert("Success");
                  return response.json();
              }).then((results) => {
		          //console.log(results);
                  //console.log(results.results[0].results[0].textDetection);
                  const textarr = new Array();
                  const textResults = results.results[0].results[0].textDetection;
                  textResults.pages?.forEach((page) =>
                      page.blocks?.forEach((block) =>
                          block.lines?.forEach((line) =>
                              line.words?.forEach((word) =>
                                  textarr.push(word.text))
                          )
                      )
                  );
                  let textNodeQuery = document.getElementById("recognized-text");
                  if (!textNodeQuery) {
                      let link = document.createElement("a");
                      let wrap = document.getElementById("wrapper");
                      let textNode = document.createElement("div");
                      textNode.id = "recognized-text";
                      textNode.innerHTML = (textarr.length === 0) ? "Not recognized" : `Recognized: ${textarr.join(" ")}`;
                      link.id = "bucket-link";
                      link.innerHTML = "Download JSON";
                      link.href = `https://testbucker.hb.ru-msk.vkcs.cloud/${results.link}.json`;
                      textNode.appendChild(document.createElement("br"));
                      textNode.appendChild(link)
                      wrap.appendChild(textNode)
                  }
                  else {
                      let link = document.createElement("a");
                      textNodeQuery.innerHTML = (textarr.length === 0) ? "Not recognized!" : `Recognized: ${textarr.join(" ")}`;
                      link.href = `https://testbucker.hb.ru-msk.vkcs.cloud/${results.link}.json`;
                      link.innerHTML = "Download JSON";
                      link.id = "bucket-link";
                      textNodeQuery.appendChild(document.createElement("br"));
                      textNodeQuery.appendChild(link);
                  }
                  
		      }) 
              .catch((error) => {
                  alert("Failure");
                  console.log(error);
              }).finally(() => document
                  .getElementById('submitbutton')
                  .removeAttribute('disabled'));

      })     


})