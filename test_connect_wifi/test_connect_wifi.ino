#ifdef ESP32
  #include <WiFi.h>
  #include <ESPAsyncWebServer.h>
#else
  #include <Arduino.h>
  #include <ESP8266WiFi.h>
  #include <Hash.h>
  #include <ESPAsyncTCP.h>
  #include <ESPAsyncWebServer.h>
#endif

String temperatureC = "";

//Biến thời gian
unsigned long lastTime = 0;  
unsigned long timerDelay = 30000;

const char* ssid = "Phong 6";
const char* password = "TuyenTienYen06";

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
  </style>
</head>
<body>
  <h2>ESP DS18B20 Server</h2>
  <p>
    <i class="fas fa-thermometer-half" style="color:#059e8a;"></i> 
    <span class="ds-labels">Temperature Celsius</span> 
    <span id="temperaturec">%TEMPERATUREC%</span>
    <sup class="units">&deg;C</sup>
  </p>
  <p>
    <i class="fas fa-thermometer-half" style="color:#059e8a;"></i> 
    <span class="ds-labels">Temperature Fahrenheit</span>
    <span id="temperaturef">%TEMPERATUREF%</span>
    <sup class="units">&deg;F</sup>
  </p>
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
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperaturef").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperaturef", true);
  xhttp.send();
}, 10000) ;
</script>
</html>)rawliteral";

//Thay thế các placeholder bằng giá trị cảm biến
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
  // Start server
  server.begin();
}
 
void loop(){
//    if ((millis() - lastTime) > timerDelay) {
//    temperatureC = readTemperatureC();
//    lastTime = millis();

    temperatureC = "";
    temperatureC = readTemperatureC();
    Serial.println(temperatureC);
    Serial.println("\n");
    lastTime = millis();
    delay(3000);
//  }  
}



//#include <Arduino.h>
//#include <WiFi.h>
//
//void setup() {
//  Serial.begin(9600);
//  WiFi.begin("AndroidAPD32B", "123456788");
//  while (WiFi.status() != WL_CONNECTED) {
//    Serial.println("Wifi connecting...");
//    delay(500);
//  }
//  Serial.println("Wifi connected");
//}
//void loop() {
//  // put your main code here, to run repeatedly:
//}
