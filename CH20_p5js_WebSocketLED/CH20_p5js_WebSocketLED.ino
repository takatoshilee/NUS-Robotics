                    
/* 
 *  C20 - p5.js WebSocket LED
 *  Creating a fancy interactive user interface 
 *  capable of communicating via WebSocket in p5.js
 *  
 *  
 */

// where the cockroach SocketServer is (your local machine):

// For Setup with LocalHost Run or Ngrok Reverse Proxy
var host = 'XXXXXXXX.lhr.life';   // Change this to your Assigned Address

// For Setup without Proxy
//var host = '192.168.0.XXX:81';  // Change this to your CockroachBot IP Address 

var socket; // the websocket
var ledValue = 0; // the sensor value

function setup() {
  createCanvas(400, 400);
  
  
  button = createButton('Toggle');
  button.position(150, 200);
  button.mousePressed(ToggleLED);
  
  // Connect to server Securely with Reverse Proxy
  socket = new WebSocket('wss://' + host);
  
  // Connect to server without a Secure Connection
  //socket = new WebSocket('ws://' + host);

  // socket connection listener:
  socket.onopen = sendIntro;
  // socket message listener:
  socket.onmessage = readMessage;
}

function draw() {
  if (ledValue == 1) {
    background("#2307AF");
  }
  else {
    background("#c30000");
  }
  text("CockroachBot WebSocket Server", 10, 20);
  fill(255);
  ellipse(100, 200, (ledValue * 10) + 5);
  
}

function ToggleLED() {
  socket.send("toggle");
}

function sendIntro() {
  // convert the message object to a string and send it:
  socket.send("toggle");
}

function readMessage(event) {
  var msg = event.data; // read data from the onmessage event
  if (event.data == "LED=1"){
    ledValue = 1; 
  }
  else if (event.data == "LED=0"){
    ledValue = 0; 
  }
}
                    
                