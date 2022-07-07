
  #include <ESP8266WiFi.h>
  #include <ESPAsyncWebServer.h>


String temperatureC = "";

//Biến thời gian
unsigned long lastTime = 0;  
unsigned long timerDelay = 30000;

char* ssid = "ss";
char* password = "1234567891";

const int in1 = D5;
const int in2 = D6;
String sliderValue = "0";
const char* PARAM_INPUT = "value";

//const char* ssid = "Phong 6";
//const char* password = "TuyenTienYen06";

//Tạo đối tượng AsyncWebServer trên cổng 80
AsyncWebServer server(80);

String readTemperatureC() {
  String tempC = "";
  while(Serial.available()) {
      char c = Serial.read();
      tempC = tempC + c;
  }
  return tempC;
//  return "30";
}

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .ds-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
    .slider { -webkit-appearance: none; margin: 14px; width: 360px; height: 25px; background: #FFD65C;
      outline: none; -webkit-transition: .2s; transition: opacity .2s;}
    .slider::-webkit-slider-thumb {-webkit-appearance: none; appearance: none; width: 35px; height: 35px; background: #003249; cursor: pointer;}
    .slider::-moz-range-thumb { width: 35px; height: 35px; background: #003249; cursor: pointer; } 
  </style>
</head>
<body>
  <h2>ESP Web Server</h2>
  <p>
    <i class="fas fa-thermometer-half" style="color:#059e8a;"></i> 
    <span class="ds-labels">Temperature Celsius</span> 
    <span id="temperaturec">%TEMPERATUREC%</span>
    <sup class="units">&deg;C</sup>
  </p>
  <h3>Motor speed control</h3>
  <p><span id="textSliderValue">%SLIDERVALUE%</span></p>
  <p><input type="range" onchange="updateSliderPWM(this)" id="pwmSlider" min="0" max="255" value="%SLIDERVALUE%" step="1" class="slider"></p>
  <script>
    function updateSliderPWM(element) {
      var sliderValue = document.getElementById("pwmSlider").value;
      var xhr = new XMLHttpRequest();
      xhr.open("GET", "/slider?value="+sliderValue, true);
      xhr.send();
    }
  </script>
</body>
<script>
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperaturec").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperaturec", true);
  xhttp.send();
}, 10000) ;
 
</script>
</html>)rawliteral";

//Thay thế các placeholder bằng giá trị cảm biến hoặc giá trị slider
String processor(const String& var){
  //Serial.println(var);
  if(var == "TEMPERATUREC"){
    return temperatureC;
  }
  return String();
}
void setup() {
//  pinMode(pin, INPUT); 
  Serial.begin(9600);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  temperatureC = readTemperatureC();
  //Kết nối Wi-Fi
  WiFi.disconnect();
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
//  while (!WiFi.localIP().isSet()) {
    delay(500);
    Serial.println("no connect");
  }
  Serial.println();
  
  //In ra dia chi IP cuc bo
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/temperaturec", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", temperatureC.c_str());
  });
  
  // Send a GET request to <ESP_IP>/slider?value=<inputMessage>
  server.on("/slider", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    // GET input1 value on <ESP_IP>/slider?value=<inputMessage>
    if (request->hasParam(PARAM_INPUT)) {
        inputMessage = request->getParam(PARAM_INPUT)->value();
        sliderValue = inputMessage;
  //      analogWrite(output, sliderValue.toInt());
      digitalWrite(in1,LOW);
      analogWrite(in2,sliderValue.toInt());
    }
    else {
      inputMessage = "No message sent";
    }
//    Serial.println("slider");
    Serial.println(inputMessage);
    request->send(200, "text/plain", "OK");
  });
  
  // Start server
  server.begin();
}
 
void loop(){
    temperatureC = "";
    temperatureC = readTemperatureC();
    Serial.println(temperatureC);
    Serial.println("\n");
    lastTime = millis();
    delay(1000); 
}
