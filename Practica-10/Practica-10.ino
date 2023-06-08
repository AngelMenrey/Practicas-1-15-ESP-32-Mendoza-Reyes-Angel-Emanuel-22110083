#include <WiFi.h>

// Replace with your network credentials
const char* ssid     = "ESP32-Access-Point";
const char* password = "123456789";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String a_a = "off";
String b_b = "off";
String c_c = "off";
String d_d = "off";
String e_e = "off";
String f_f = "off";
String g_g = "off";

// Assign output variables to GPIO pins
const int a = 2;
const int b = 4;
const int c = 5;
const int d = 15;
const int e = 23;
const int f = 22;
const int g = 21;
void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  // Set outputs to LOW
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /a/on") >= 0) {
              Serial.println("GPIO a on");
              a_a = "on";
              digitalWrite(a, HIGH);
            } else if (header.indexOf("GET /a/off") >= 0) {
              Serial.println("GPIO a off");
              a_a = "off";
              digitalWrite(a, LOW);
            } else if (header.indexOf("GET /b/on") >= 0) {
              Serial.println("GPIO b on");
              b_b = "on";
              digitalWrite(b, HIGH);
            } else if (header.indexOf("GET /b/off") >= 0) {
              Serial.println("GPIO b off");
              b_b = "off";
              digitalWrite(b, LOW);
            }else if (header.indexOf("GET /c/on") >= 0) {
              Serial.println("GPIO c on");
              c_c = "on";
              digitalWrite(c, HIGH);
            } else if (header.indexOf("GET /c/off") >= 0) {
              Serial.println("GPIO c off");
              c_c = "off";
              digitalWrite(c, LOW);
            } else if (header.indexOf("GET /d/on") >= 0) {
              Serial.println("GPIO d on");
              d_d = "on";
              digitalWrite(d, HIGH);
            } else if (header.indexOf("GET /d/off") >= 0) {
              Serial.println("GPIO d off");
              d_d = "off";
              digitalWrite(d, LOW);
            } else if (header.indexOf("GET /e/on") >= 0) {
              Serial.println("GPIO e on");
              e_e = "on";
              digitalWrite(e, HIGH);
            } else if (header.indexOf("GET /e/off") >= 0) {
              Serial.println("GPIO e off");
              e_e = "off";
              digitalWrite(e, LOW);
            } else if (header.indexOf("GET /f/on") >= 0) {
              Serial.println("GPIO f on");
              f_f = "on";
              digitalWrite(f, HIGH);
            } else if (header.indexOf("GET /f/off") >= 0) {
              Serial.println("GPIO f off");
              f_f = "off";
              digitalWrite(f, LOW);
            } else if (header.indexOf("GET /g/on") >= 0) {
              Serial.println("GPIO g on");
              g_g = "on";
              digitalWrite(g, HIGH);
            } else if (header.indexOf("GET /g/off") >= 0) {
              Serial.println("GPIO g off");
              g_g = "off";
              digitalWrite(g, LOW);
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>display 7 segmentos</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO a  
            client.println("<p>GPIO a - State " + a_a + "</p>");
            // If the output26State is off, it displays the ON button       
            if (a_a=="off") {
              client.println("<p><a href=\"/a/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/a/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO b  
            client.println("<p>GPIO b - State " + b_b + "</p>");
            // If the output27State is off, it displays the ON button       
            if (b_b=="off") {
              client.println("<p><a href=\"/b/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/b/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            // Display current state, and ON/OFF buttons for GPIO c  
            client.println("<p>GPIO c - State " + c_c + "</p>");
            // If the output26State is off, it displays the ON button       
            if (c_c=="off") {
              client.println("<p><a href=\"/c/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/c/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO d  
            client.println("<p>GPIO d - State " + d_d + "</p>");
            // If the output27State is off, it displays the ON button       
            if (d_d=="off") {
              client.println("<p><a href=\"/d/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/d/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            // Display current state, and ON/OFF buttons for GPIO c  
            client.println("<p>GPIO e - State " + e_e + "</p>");
            // If the output26State is off, it displays the ON button       
            if (e_e=="off") {
              client.println("<p><a href=\"/e/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/e/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO d  
            client.println("<p>GPIO f - State " + f_f + "</p>");
            // If the output27State is off, it displays the ON button       
            if (f_f=="off") {
              client.println("<p><a href=\"/f/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/f/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            // Display current state, and ON/OFF buttons for GPIO d  
            client.println("<p>GPIO g - State " + g_g + "</p>");
            // If the output27State is off, it displays the ON button       
            if (g_g=="off") {
              client.println("<p><a href=\"/g/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/g/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
