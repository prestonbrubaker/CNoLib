#include "web.h"

void send_message(char strr[], int port) {
    static struct sockaddr_in addr = {0};  // Server address
    static char msg[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: 2548\r\n\r\n"
"<!DOCTYPE html><html lang=\"en\"><head><title>Celebration</title><style>body{margin:0;background:radial-gradient(circle,#000428 0%,#004e92 50%,#000428 100%);font-family:Arial,sans-serif;display:flex;justify-content:center;align-items:center;height:100vh;overflow:hidden;position:relative}.stars{position:absolute;top:0;left:0;width:100%;height:100%;background:transparent;pointer-events:none}.star{position:absolute;background:#fff;border-radius:50%;animation:twinkle 2s infinite alternate}.star:nth-child(odd){animation-delay:1s}@keyframes twinkle{0%{opacity:0.5}100%{opacity:1}}h1{color:#fff;background:linear-gradient(45deg,#ff0000,#ff9900,#00ff00,#0099ff,#6600ff,#ff00ff);background-size:400% 400%;-webkit-background-clip:text;-webkit-text-fill-color:transparent;animation:gradient 3s ease infinite, bounce 1s infinite, pulse 2s infinite;font-size:4em;text-shadow:0 0 20px rgba(255,255,255,0.5);margin:0;text-align:center}span{font-size:0.5em;display:block;color:#ffd700;animation:glow 2s infinite alternate}@keyframes gradient{0%{background-position:0% 50%}50%{background-position:100% 50%}100%{background-position:0% 50%}}@keyframes bounce{0%,20%,50%,80%,100%{transform:translateY(0)}40%{transform:translateY(-30px)}60%{transform:translateY(-15px)}}@keyframes pulse{0%,100%{transform:scale(1)}50%{transform:scale(1.05)}}@keyframes glow{0%{text-shadow:0 0 10px #ffd700}100%{text-shadow:0 0 20px #ffd700,0 0 30px #ffd700}}</style></head><body><div class=\"stars\"></div><canvas id=\"fireworks\" style=\"position:absolute;top:0;left:0;width:100%;height:100%;pointer-events:none\"></canvas><h1>Congratulations!<span>You\'ve Unlocked Epic Wins!</span></h1><script>/* Stars */for(let i=0;i<200;i++){const star=document.createElement('div');star.className='star';star.style.left=Math.random()*100+'%';star.style.top=Math.random()*100+'%';star.style.width=star.style.height=(Math.random()*2+1)+'px';document.querySelector('.stars').appendChild(star);}/* Confetti */function createConfetti(){for(let i=0;i<100;i++){const conf=document.createElement('div');conf.style.cssText=`position:absolute;left:${Math.random()*100}%;top:-10px;width:${Math.random()*10+5}px;height:${Math.random()*10+5}px;background:hsl(${Math.random()*360},100%,50%);transform:rotate(${Math.random()*360}deg);animation:fall ${Math.random()*3+2}s linear infinite;animation-delay:${Math.random()*2}s;pointer-events:none;opacity:${Math.random()*0.8+0.2}`;conf.style.animation=`fall ${Math.random()*3+2}s linear infinite`;document.body.appendChild(conf);setTimeout(()=>conf.remove(),5000);}}function fallKeyframes(){const style=document.createElement('style');style.textContent='@keyframes fall{0%{transform:translateY(-100vh) rotate(0deg);}100%{transform:translateY(100vh) rotate(720deg);}}';document.head.appendChild(style);}fallKeyframes();createConfetti();setInterval(createConfetti,3000);/* Fireworks */const canvas=document.getElementById('fireworks');const ctx=canvas.getContext('2d');canvas.width=window.innerWidth;canvas.height=window.innerHeight;let particles=[];class Particle{constructor(x,y,color){this.x=x;this.y=y;this.vx=Math.random()*10-5;this.vy=Math.random()*10-5;this.color=color;this.life=100;this.decay=2;}update(){this.x+=this.vx;this.y+=this.vy;this.life-=this.decay;this.vx*=0.99;this.vy*=0.99;}draw(){ctx.globalAlpha=this.life/100;ctx.fillStyle=this.color;ctx.fillRect(this.x,this.y,3,3);ctx.globalAlpha=1;}}function launchFirework(){const x=Math.random()*canvas.width;const y=canvas.height;const color=`hsl(${Math.random()*360},100%,50%)`;for(let i=0;i<50;i++){particles.push(new Particle(x,y,color));}}function animate(){ctx.clearRect(0,0,canvas.width,canvas.height);particles.forEach((p,i)=>{p.update();p.draw();if(p.life<=0)particles.splice(i,1);});requestAnimationFrame(animate);}animate();setInterval(launchFirework,800);/* Sound */function playFanfare(){const audioCtx=new(window.AudioContext||window.webkitAudioContext)();const notes=[440,554,659,523];notes.forEach((freq,i)=>{const osc=audioCtx.createOscillator();const gain=audioCtx.createGain();osc.connect(gain);gain.connect(audioCtx.destination);osc.frequency.value=freq;gain.gain.setValueAtTime(0.3,audioCtx.currentTime);gain.gain.exponentialRampToValueAtTime(0.01,audioCtx.currentTime+0.5);osc.start(audioCtx.currentTime+i*0.5);osc.stop(audioCtx.currentTime+i*0.5+0.5);});}document.addEventListener('click',playFanfare,true);/* Resize */window.addEventListener('resize',()=>{canvas.width=window.innerWidth;canvas.height=window.innerHeight;});</script></body></html>";
    
    static long msg_len = 6;
    long sockfd, client_fd;

    addr.sin_family = 2;
    addr.sin_port = ((9027 & 0xFF) << 8) | ((9027 >> 8) & 0xFF);  // htons(8080)
    addr.sin_addr.s_addr = 0;

    long ret;

    // Syscall: socket(AF_INET=2, SOCK_STREAM=1, protocol=0)
    asm volatile (
        "mov $41, %%rax\n"
        "mov $2, %%rdi\n"
        "mov $1, %%rsi\n"
        "mov $0, %%rdx\n"
        "syscall\n"
        "mov %%rax, %0"
        : "=a" (sockfd)
        :
        : "rcx", "rdi", "rsi", "rdx", "r11", "memory"
    );

    // Set socket to blocking mode
    asm volatile (
        "mov $72, %%rax\n"
        "mov %1, %%rdi\n"
        "mov $4, %%rsi\n"
        "mov $0, %%rdx\n"
        "syscall\n"
        "mov %%rax, %0"
        : "=a" (ret)
        : "r" (sockfd)
        : "rcx", "r11", "rdi", "rsi", "rdx", "memory"
    );

    static int optval = 1; // Enable SO_REUSEADDR
    asm volatile (
        "mov $54, %%rax\n"    // Syscall: setsockopt (54)
        "mov %0, %%rdi\n"     // sockfd
        "mov $1, %%rsi\n"     // SOL_SOCKET (level)
        "mov $2, %%rdx\n"     // SO_REUSEADDR (option)
        "mov %1, %%r10\n"     // Address of optval
        "mov $4, %%r8\n"      // optlen (sizeof(int))
        "syscall\n"
        :
        : "r" (sockfd), "r" (&optval)
        : "rax", "rdi", "rsi", "rdx", "r10", "r8", "rcx", "r11", "memory"
    );


    asm volatile (
        "mov $49, %%rax\n"
        "mov %2, %%rdi\n"
        "mov %2, %%rsi\n"
        "mov $16, %%rdx\n"
        "syscall\n"
        "mov %%rax, %0"
        : "=a" (ret)
        : "r" (sockfd), "r" (&addr)
        : "rcx", "r11", "rdi", "rsi", "rdx", "memory", "r11"
    );


    // Syscall: listen(sockfd, backlog=1)
    asm volatile (
        "mov $50, %%rax\n"
        "mov %1, %%rdi\n"
        "mov $1, %%rsi\n"
        "syscall\n"
        "mov %%rax, %0"
        : "=a" (ret)
        : "r" (sockfd)
        : "rcx", "r11", "rdi", "rsi", "r11", "rdx", "memory"
    );



    // Syscall: accept(sockfd, NULL, NULL)
    asm volatile (
        "mov $43, %%rax\n"
        "mov %, %%rdi\n"
        "mov $0, %%rsi\n"
        "mov $0, %%rdx\n"
        "syscall\n"
        "mov %%rax, %0"
        : "=a" (client_fd)
        : "r" (sockfd)
        : "rcx", "r11", "rdi", "rsi", "rdx", "memory"
    );

    // Syscall: sendto(client_fd, msg, msg_len, flags=0, NULL, 0)
    asm volatile (
            "mov $44, %%rax\n"
            "mov %0, %%rdi\n"
            "mov %2, %%rsi\n"
            "mov $4578, %%rdx\n"
            "mov $0, %%r10\n"
            "mov $0, %%r8\n"
            "mov $0, %%r9\n"
            "syscall\n"
            :
            : "r" (client_fd), "r" (msg_len), "r" (msg)
            : "rcx", "r11", "rdi", "rsi", "rdx", "r10", "r8", "r9", "memory"
    );

    // Syscall: close(client_fd)
    asm volatile (
        "mov $3, %%rax\n"
        "mov %0, %%rdi\n"
        "syscall\n"
        :
        : "r" (client_fd)
        : "rcx", "r11", "rdi"
    );

    // Syscall: close(sockfd)
    asm volatile (
        "mov $3, %%rax\n"
        "mov %0, %%rdi\n"
        "syscall\n"
        :
        : "r" (sockfd)
        : "rcx", "r11", "rdi"
    );
}
