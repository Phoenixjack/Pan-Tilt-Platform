const char MAIN_page[] PROGMEM = R"=====(

<!DOCTYPE html>
<html>
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
      html {
        font-family: Arial;
        display: inline-block;
        margin: 0px auto;
        text-align: center;
      }
      .container {
        height: 150px;
        position: relative;
      }
      .centerA {
        margin: 0;
        position: absolute;
        -ms-transform: translate(-50%, -50%);
        transform: translate(-50%, -50%);
        top: 50%;
        left: 50%;
      }
      .slidecontainer {
        width: 100%;
      }
      .slider {
        -webkit-appearance: none;
        width: 75%;
        height: 15px;
        border-radius: 5px;
        background: #f3f3f3;
        outline: none;
        opacity: 0.7;
        -webkit-transition: .2s;
        transition: opacity .2s;
      }
      .slider:hover {
        opacity: 1;
      }
      .slider::-webkit-slider-thumb {
        -webkit-appearance: none;
        appearance: none;
        width: 25px;
        height: 25px;
        border-radius: 50%;
        background: #FF0000;
        cursor: pointer;
      }
      .slider::-moz-range-thumb {
        width: 25px;
        height: 25px;
        border-radius: 50%;
        background: #00FF00;
        cursor: pointer;
      }
	  .btn-group button {
  		background-color: #0000FF;
	  	border: 5px solid grey; 
		  color: white;
		  padding: 10px 10px;
		  cursor: pointer;
	  }
    .btn-group:after { /* Clear floats (clearfix hack) */
      content: "";
      clear: both;
      display: table;
    }
    .btn-group button:not(:last-child) {
      border-right: none;
    }
    .btn-group button:hover {
      background-color: #FF0000;
      color: black;
    }
    </style>
  </head>
  <body style="background-color:grey;">
    <h1>Azimuth/Inclination Control</h1>
    <p>Command : <span id="command"></span></p>
    <p>Azimuth Target : <span id="azvalue"></span></p>
    <p>Current Azimuth : <span id="currazvalue"></span></p>
	  <div class="slidecontainer">
      <input type="range" orient="vertical" min="0" max="360" value="0" class="slider" id="AzRange">
	  </div>
    <p>Inclination Target : <span id="incvalue"></span></p>
    <p>Current Inclination : <span id="currincvalue"></span></p>
	  <div class="slidecontainer">
      <input type="range" orient="vertical" min="-55" max="55" value="0" class="slider" id="IncRange">
	  </div>
    <p>Speed : <span id="spvalue"></span></p>
	  <div class="slidecontainer">
      <input type="range" orient="vertical" min="0" max="100" value="100" class="slider" id="SpRange">
	  </div>
   <div class="container">
      <div class="centerA"> 	
        	<div class="btn-group">
          <button Home onclick="home()"> HOME </button>
          <button Stop onclick= "stop()"> STOP </button>
          <button Level onclick="level()"> LEVEL </button>
          <button Forward onclick="forward()"> FORWARD </button>
        	</div>
	    </div>
    </div>
    <div class="container">
      <div class="centerA"> 	
        	<div class="btn-group">
          <button GetPos onclick="donothing()"> Get Position </button>
          <button SetAsHome onclick= "donothing()"> Set As Home </button>
          <button HomingSequence onclick= "donothing()"> Homing Sequence </button>
        	</div>
	    </div>
    </div>
    <script>
      function sendFlexData(packet, pos) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            console.log(this.responseText);
          }
        };
        if (packet == 1) { /* sending inclination */
            xhttp.open("GET", "setINC?val="+pos, true);
        }
        if (packet == 2) { /* sending azimuth */
            xhttp.open("GET", "setAZ?val="+pos, true);
        }
        if (packet == 3) { /* sending command. 0=stop 1=set zero 2=report pos */
            xhttp.open("GET", "command?val="+pos, true);
        }
        if (packet == 4) { /* sending speed */
            xhttp.open("GET", "setSP?val="+pos, true);
        }
        xhttp.send();
      }
      function getserverdata() {
        var xhttp = new XMLHttpRequest();
        command.innerHTML = "Retrieving server data";
      }
      function donothing() {
        /* placeholder */
        command.innerHTML = "placeholder, not implemented yet";
      }
      function home() {
        command.innerHTML = "HOME";
        incslider.value = 0;
        incoutput.innerHTML = incslider.value;
        sendFlexData(1, 0);
        azslider.value = 0;
        azoutput.innerHTML = azslider.value;
        sendFlexData(2, 0);
      }
      function stop() {
        command.innerHTML = "ALL STOP";
        sendFlexData(3, 0); /* send command. position 0 = all stop */
      }
      function level() {
        command.innerHTML = "Level Out";
        incslider.value = 0;
        incoutput.innerHTML = incslider.value;
        sendFlexData(1, 0);
      }
      function forward()	{
        command.innerHTML = "Face Forward";
        azslider.value = 0;
        azoutput.innerHTML = azslider.value;
        sendFlexData(2, 0);
      }

      var azslider = document.getElementById("AzRange");
      var azoutput = document.getElementById("azvalue");
      azoutput.innerHTML = azslider.value;
      var incslider = document.getElementById("IncRange");
      var incoutput = document.getElementById("incvalue");
      incoutput.innerHTML = incslider.value;
      var spslider = document.getElementById("SpRange");
      var spoutput = document.getElementById("spvalue");
      spoutput.innerHTML = spslider.value;

      azslider.oninput = function() {
        command.innerHTML = "Rotating";
        azoutput.innerHTML = this.value;
        sendFlexData(2, azoutput.innerHTML);
      }
      incslider.oninput = function() {
        command.innerHTML = "Inclining";
        incoutput.innerHTML = this.value;
        sendFlexData(1, incoutput.innerHTML);
      }
      spslider.oninput = function() {
        command.innerHTML = "Speed Change";
        spoutput.innerHTML = this.value;
        sendFlexData(4, spoutput.innerHTML);
      }
    </script>
  </body>
</html>

)=====";