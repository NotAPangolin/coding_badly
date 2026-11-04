function loadFile(filePath) {
  var result = null;
  var xmlhttp = new XMLHttpRequest();
  xmlhttp.open("GET", filePath, false);
  xmlhttp.send();
  if (xmlhttp.status==200) {
    result = xmlhttp.responseText;
  } else {
    throw Error("get shader no worky")
  }
  return result;
}

var _instance;
class Plane {
  constructor() {
    this.uniforms = {
      time : { type: 'f', value: 0 },
      ucolor : { type: 'v3', value: new THREE.Vector3(1.,1.,1.) },
      uopacity : { type: 'f', value: 1.0 }
    };
    this.mesh = this.createMesh();
    this.time = 1;
    _instance = this;
  }
  createMesh() {
    vert = loadFile("shaders/shader.vert")
    frag = loadFile("shaders/shader.frag")

    return new THREE.Mesh(
      new THREE.PlaneGeometry(256, 256, 256, 256),
      new THREE.RawShaderMaterial({
        uniforms: this.uniforms,
        vertexShader: vert,
        fragmentShader: frag,
        transparent: true
      })
    );
  }
  render(time) {
    this.uniforms.time.value += time * this.time;
  }
}

const canvas = document.getElementById('canvas-webgl');
const renderer = new THREE.WebGLRenderer({
  antialias: false,
  canvas: canvas,
});
const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(45, window.innerWidth / window.innerHeight, 1, 10000);
const clock = new THREE.Clock();

const plane = new Plane();

const resizeWindow = () => {
  canvas.width = window.innerWidth;
  canvas.height = window.innerHeight;
  camera.aspect = window.innerWidth / window.innerHeight;
  camera.updateProjectionMatrix();
  renderer.setSize(window.innerWidth, window.innerHeight);
}
const on = () => {
  $(window).on('resize', () => {
    resizeWindow();
  });
}
const render = () => {
  plane.render(clock.getDelta());
  renderer.render(scene, camera);
}
let raf;
const renderLoop = () => {
  render();
  raf=requestAnimationFrame(renderLoop);
}

//lively stuffs

let noClock = false;
let _12hour =true;
let noDate=false;
let mmddyy=true;

const dayArr=["Sunday","Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"];


let background = "#0e0e0e";
const init = () => {
  renderer.setSize(window.innerWidth, window.innerHeight);
  renderer.setClearColor(parseInt(background.replace('#','0x')), 1.0);
  camera.position.set(0, 16, 128);
  camera.lookAt(new THREE.Vector3(0, 28, 0));
  
  while(scene.children.length > 0){ 
    scene.remove(scene.children[0]); 
  }
  if(raf){
    cancelAnimationFrame(raf);
  }
  scene.add(plane.mesh);
  on();
  resizeWindow();
  renderLoop();
}
init();

window.onresize = e =>{
  clockPos();
}

function clockPos(){
  const clockEl = document.querySelector('.p-summary');
  clockEl.style.left= window.innerWidth/2-clockEl.clientWidth/2 + "px";
}

function UpdateClock() {
  const time = new Date();

  let timeEl = document.getElementById('clock');
  let dateEl = document.getElementById('date');
  let dayEl = document.getElementById('day');

  /*
  if(noDate && noClock){
    dateEl.style.display="none";
    dayEl.style.display="none";
    timeEl.style.display="none";
    return
  }
  */
  
  if(noClock)
    timeEl.style.display="none";
  else
    timeEl.style.display="block";

  if(noDate){
    dateEl.style.display="none";
    dayEl.style.display="none";
  }else{
    dateEl.style.display="block";
    dayEl.style.display="block";
  }
  
  let d = new Date();

  if(_12hour)
    timeEl.innerHTML=`- ${new Intl.DateTimeFormat('en-US',{'hour':'2-digit','minute':'2-digit','hour12':true}).format(d)} -`.replace("AM",'').replace("PM",'');
  else
    timeEl.innerHTML=`- ${new Intl.DateTimeFormat('en-US',{'hour':'2-digit','minute':'2-digit','hour12':false}).format(d)} -`;

  if(mmddyy)
    dateEl.innerText=new Intl.DateTimeFormat('en-US',{'month':'short','day':'2-digit','year':'2-digit'}).format(d).replace(',','');
  else
    dateEl.innerText=new Intl.DateTimeFormat('en-GB',{'day':'2-digit','month':'2-digit','year':'2-digit'}).format(d).replace(',','');
  
  dayEl.innerText = dayArr[d.getDay()];

  setTimeout(UpdateClock, 1000);
}
UpdateClock();
clockPos();

function livelyPropertyListener(name, val)
{
  switch(name) {
    case "timeToggle":
      noClock=!val;
      break;
    case "dateToggle":
      noDate=!val;
      break;
    case "_12hour":
      _12hour=val;
      break;
    case "mmddyy":
      mmddyy=!val;
      break;
    case "fontColor":
      document.querySelector(".p-summary").style.color = val; 
      break;
    case "hillColor":
      tmp = hexToRgb(val);
      _instance.uniforms.ucolor.value  = new THREE.Vector3(tmp.r/255, tmp.g/255, tmp.b/255);
      break;
    case "bgColor":
      background = val;
      init();
      break; 
    case "hillOpacityFac":
      _instance.uniforms.uopacity.value = val/100;
      break;
  }
}

function hexToRgb(hex) {
  var result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
  return result ? {
    r: parseInt(result[1], 16),
    g: parseInt(result[2], 16),
    b: parseInt(result[3], 16)
  } : null;
}
