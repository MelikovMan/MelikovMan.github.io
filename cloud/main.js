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
        console.log(canvas.toDataURL().replace('data:', '')
        .replace(/^.+,/, ''));
      })     


})