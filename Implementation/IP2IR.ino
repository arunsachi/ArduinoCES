#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>
#include <SPI.h>
#include <IRremote.h>

/*
  IP2IR

 A webserver that issues get requests to Arduino Ethernet
 and initiates IR led to send IR codes corresponding 
 to the particular get requests.

 */

//Power on code for Sony devices
#define POWER1 0xa90

IRsend irsend;

//MAC of Arduino Ethernet
byte mac[] = {
0x90, 0xA2, 0xDA, 0x00, 0x91, 0x0C
};

//Static IP assigned to Arduino
IPAddress ip(169, 254, 247, 127);

// Initializing the Ethernet server library
EthernetServer server(80);

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  
  // Starting the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  
  // listening for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("IP2IR client");
    
    // Checking for end of HTTP request
    boolean currentLineIsBlank = true;
    String buffer = "",msg="",time="";
    int index1,index2,index3;
    char getArray[40] = "";
    int len =0,i=0;
    
    while (client.connected()) 
    {
      if (client.available()) {
        char c = client.read();
        //Serial.write(c);
        //Serial.print(c);
        if (c == '\n') {
           break;
          // currentLineIsBlank = true;
        }
        
        buffer+=c;
        getArray[len++]=c;
      }
    }
     char c;
        Serial.println("Buffer : "+buffer);
        Serial.println("Array : ");
         index1=buffer.indexOf("/");
         index2=buffer.indexOf("/",index1+1);
         index3=buffer.indexOf("/",index2+1);
         
         msg = buffer.substring(index2+1,index3);
         time = buffer.substring(index3+1,index3+3);
         Serial.println("Msg: "+msg);
         Serial.println("Time: "+time);
         
          
          //Sending IR codes (switch case to be implemented)
           irsend.sendSony(POWER1, 12);
           digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
           delay(1000);              // wait for a second
           digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
           delay(1000);              // wait for a second
           
          
          //Sending HTTP response
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          //client.println("Refresh: 5");  // refresh the page so that otput is constant
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("IP2IR : ");
          client.println("IR code is being emitted");
          client.println("</html>");
          //break;
        
        if (c == '\n') {
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    //Serial.println("client disconnected");
} 
