ESP8266WebServer server(80);


    
  static const char xyz[] PROGMEM  =   R"(
      <html>
      
        <head>
          <meta charset="UTF-8">
          <meta content='minimum-scale=1.0, width=device-width, maximum-scale=0.6667, user-scalable=no' name='viewport' />
          <script src="https://code.jquery.com/jquery-3.3.1.min.js"></script>
          
          <script>
           
$(document).ready(function(){
      
var progressbar1 = new Jprogres("#p1",'progress1',90);
var progressbar2 = new Jprogres("#p2",'progress2',90);
      
progressbar1.color("#2989b5");//color  de barra
progressbar1.backcolor("#ddd")//color de fondo de barra
    
progressbar2.color("#2989b5");//color  de barra
progressbar2.backcolor("#ddd")//color de fondo de barra
    
function Jprogres(id,name,radio,funcion){
	   var  contenedor = $(id);var  name = name;contenedor.append('<div data-pct="0" id="'+name+'"></div>');var strokercicle = Math.PI*(radio*2);$("#"+name).click(funcion);$("#"+name).css({
		"display": "block",
       
		"margin": "10 auto",
		"border-radius": "100%",
		"width":"300px",
        "height":"300px",   
		"display":"flex",
		"justify-content":"center",
		"align-items":"center",
		"font-size":"24px",
		"font-family":"verdana",
		"-webkit-user-select":"none",
		"cursor":"default"
	});
	$("#"+name).html(`
	<div id="${name}_percent">0</div>
	<svg id="${name}_svg" width="210" height="210" viewPort="0 0 100 100" version="1.1" xmlns="http://www.w3.org/2000/svg">
	
		<circle id="${name}_back" r="${radio}" cx="100" cy="100" fill="transparent" stroke-dasharray="${strokercicle}" stroke-dashoffset="0"></circle>
		<circle id="${name}_bar" r="${radio}" cx="100" cy="100" fill="transparent" stroke-dasharray="${strokercicle}" stroke-dashoffset="0"></circle>
	
	</svg>
	`);
	$("#"+name+"_percent").css({
		"position":"absolute"
	});
	var colorback = "#eee";
	this.color = function(color){
		$("#"+name+"_svg "+ " #"+name+"_bar").css({
			"stroke": color
		});
	};
	this.backcolor = function(color){	
		$("#"+name+"_back").css({
			"stroke": color
		});			
	}
	
	$("#"+name+"_svg "+ "circle").css({
		"stroke-dashoffset": "0",
		"transition": "stroke-dashoffset .5s ease",
		"stroke": colorback,
		"stroke-width": ".7em"
	});
	$("#"+name+"_svg "+ " #"+name+"_bar").css({
		"stroke-dashoffset": "0",
		"transition": "stroke-dashoffset .5s ease",
		"stroke": "#727272",
		"stroke-width": ".7em"
	});	
	this.val = function(val,text){
	var val = val;
	var $circle = $('#'+name+'_bar');
	
	if (isNaN(val)) {val = 0; }else
	{  var r = $circle.attr('r');var c = Math.PI*(r*2);
	if (val < 0) { val = 0;}
    if (val > 100) { val = 100;}
    var pct = ((100-val)/100)*c;
    $circle.css({strokeDashoffset: pct});
     $("#"+name).attr('data-pct',val);
	 $("#"+name+"_percent").html(val+text);
	}
	}

}


var socket = new WebSocket("ws://192.168.100.13:81");
socket.onopen = function (event) {
    console.log("Servidor Conectado");
};

socket.onmessage = function (event) {
    var data =  event.data.split("|");
    console.log(data);
    
    progressbar1.val(data[1],"C");
    
    progressbar2.val(data[0],"/100%");
    //console.log(temp);
    
}
      
});             
</script>
<style>
    body{
        font-family:verdana;
        margin:0px;
        background:rgba(31,31,31,1);
        color:white;
        display:flex;
        flex-direction:column;
        justify-content: center;
        align-items: center
            
    }
    h2{
        
    }
</style>
</head>
<body>
    <h2>Temperatura</h2>
    <div id="p1"></div>
    <h2>Humedad</h2>
    <div id="p2"></div>
</body>
</html>
)";
    


void handleRoot() {                         // When URI / is requested, send a web page with a button to toggle the LED
  server.send(200, "text/html", String(xyz));
}