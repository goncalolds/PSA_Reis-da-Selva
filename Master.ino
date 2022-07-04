// MASTER

// PARTE INICIAL

#include <SPI.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h" 
#include <Servo.h>
#define Servo1_PWM 5
#define Servo2_PWM 3
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                // your network key index number (needed only for WEP)


int status = WL_IDLE_STATUS;
WiFiServer server(80);

Servo servo1;//definir servos
Servo servo2;

#define RELAY 6
int counter = 90;

void setup() {
  
   Serial.begin(9600,SERIAL_8E1);
   Serial1.begin(9600,SERIAL_8E1);

   
   servo1.attach(Servo1_PWM); //definir entrada do servos
   servo2.attach(Servo2_PWM);
   
   pinMode(RELAY,OUTPUT); //definir relé




while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Access Point Web Server");

        // set the LED pin mode

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }
  // by default the local IP address will be 192.168.4.1
  // you can override it with the following:
  // WiFi.config(IPAddress(10, 0, 0, 1));
  // print the network name (SSID);
  Serial.print("Creating access point named: ");
  Serial.println(ssid);
  // Create open network. Change this line if you want to create an WEP network:
  status = WiFi.beginAP(ssid, pass);
  if (status != WL_AP_LISTENING) {
    Serial.println("Creating access point failed");
    // don't continue
    while (true);
  }

  // wait 10 seconds for connection:
  delay(10000);

  // start the web server on port 80
  server.begin();
}



void loop() {

String readString;
String Q;

//Duration will be the input pulse width and distance will be the distance to the obstacle in centimeters
    int duration, distance;
    
  // Estabelecimento das comunicações
  // compare the previous status to the current status
  if (status != WiFi.status()) {
    // it has changed update the variable
    status = WiFi.status();

    if (status == WL_AP_CONNECTED) {
      // a device has connected to the AP
      Serial.println("Device connected to AP");
    } else {
      // a device has disconnected from the AP, and we are back in listening mode
      Serial.println("Device disconnected from AP");
    }
  }

  
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      delayMicroseconds(10);                // This is required for the Arduino Nano RP2040 Connect - otherwise it will loop so fast that SPI will never be served.
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            // the content of the HTTP response follows the header:
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          }
          else {      // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        }
        else if (c != '\r') {    // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

while (Serial1.available()){
  delay(1);
  if(Serial1.available()>0){
  char c = Serial1.read();
    Serial.print(c);
   if (isControl(c)){
  break;
  }
   
  }
 
 }
 
  
 while (Serial.available()) {
     delay(1);
    if (Serial.available() >0) {
      char c = Serial.read();  //gets one byte from serial buffer
    if (isControl(c)) {
      //'Serial.println("it's a control character");
      break;
    }
      readString += c; //makes the string readString    
    }
 }  

          if (currentLine.endsWith("GET /front")) {
         Serial1.print("1"); 
         Serial.println("Front");
         
        }
         if (currentLine.endsWith("GET /back")) {    
         Serial1.print("2");
         Serial.println("Back");      

        }
         if (currentLine.endsWith("GET /left")) {          // Para andar para Lado esquerdo
         Serial1.print("3");  
         Serial.println("Left");

        }

         if (currentLine.endsWith("GET /left360")) {       // Rodar para Lado esquerdo
         Serial1.print("4");  
         Serial.println("Left 360");      

        }
         if (currentLine.endsWith("GET /right")) {         // Para andar para para Lado direito
         Serial1.print("5"); 
         Serial.println("Right");

        }
        
         if (currentLine.endsWith("GET /right360")) {      // Para andar para para Lado direito
         Serial1.print("6"); 
         Serial.println("Right 360");

          }
         if (currentLine.endsWith("GET /stop")) {          // Parar O carro
         Serial1.print("7"); 
         Serial.println("Stop");
          }

         if (currentLine.endsWith("GET /manual")) {          // Parar O carro
         Serial1.print("8"); 
         Serial.println("manual");
          }         
         if (currentLine.endsWith("GET /automatico")) {          // Parar O carro
         Serial1.print("9"); 
         Serial.println("automatico");
          }

         if (currentLine.endsWith("GET /on")) {          // Ativar iman
         Serial.println("Iman ON"); 
         digitalWrite(RELAY,HIGH);
          }

         if (currentLine.endsWith("GET /off")) {          // Desativar iman
         Serial.println("Iman OFF"); 
         digitalWrite(RELAY,LOW);
          }


         if (currentLine.endsWith("GET /rodarR")) {          // Servo braço rodar direita
         Serial.println("Rodar Servo1 direita"); 
         servo1.attach(5); 
         servo1.write(80);
          }
         
         if(currentLine.endsWith("GET /rodarL")) {          // Servo braço rodar esquerda
         Serial.println("Rodar Servo1 esquerda"); 
         servo1.attach(5); 
         servo1.write(100);
          }

         if (currentLine.endsWith("GET /levantar")) {          // Servo posição baixar
         Serial.println("Rodar Servo cima");
         counter = counter +10;
         servo2.write(counter);
          }
         
         if (currentLine.endsWith("GET /baixar")) {          // Servo posição levantar
         Serial.println("Rodar Servo baixo"); 
         counter = counter - 10;
         servo2.write(counter);
         
          }

         if (currentLine.endsWith("GET /stopservo")) {          // Servo 1 parar rodar
         Serial.println("Parar Servo1"); 
         servo1.write(90);
         servo1.detach();
         servo1.attach(5);
          }      
         
        }
      }
      
    }
    // close the connection:
    client.stop();
}


void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}

void app(){


String readString;
String Q;
String currentLine = "";
 
}
