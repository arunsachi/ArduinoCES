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
 to received get requests.

 */

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
  
  // Listening for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("IP2IR client");
    
    // Checking for end of HTTP request
    boolean currentLineIsBlank = true;
    
    // Initialising required variables
    String buffer = "",msg="",time="",freq="";
    int index1,index2,index3,index4,index5,index6;
    unsigned int* buf;
    int len = 0,i = 0, timeint = 0;
    long msgint=0;
    char c;
    boolean TRANSMITTED = false;
    
    while (client.connected()) 
    {
      if (client.available()) {
          c = client.read();
          if (c == '\n') {
          break;
          // currentLineIsBlank = true;
      }
      buffer+=c;
        
      // Turning on LED as a connection indicator
      digitalWrite(13, HIGH);   
      }
    }
     Serial.println("GET Request : "+buffer);     
    
     // Getting Code,Time,Frequency from GET request using the message index
     index1=buffer.indexOf("/");
     index2=buffer.indexOf("/",index1+1);
     index3=buffer.indexOf("/",index2+1);
     index4=buffer.indexOf("/",index3+1);
     index5=buffer.indexOf(" ");
     index6=buffer.indexOf(" ",index5+1);
     
     msg = buffer.substring(index2+1,index3);
     time = buffer.substring(index3+1,index4);
     freq = buffer.substring(index4+1,index6);
      
     Serial.println("Msg: "+msg);
     Serial.println("Time: "+time);
     Serial.println("Freq: "+freq);  
              
     len=msg.length();
     msgint = msg.toInt();
     timeint = time.toInt();
     buf =(unsigned int*) msgint;
     
     //Example for Sending Vendor specific IR codes (switch case to be implemented)
     // irsend.sendSony(POWER1, 12); //POWER1 would be the sony specific IR code
          
     //Checking if get request message is empty
     if( (index6-index2) > 1) {
       
       //Sending IR code the required number of times
       while(i<timeint){
             
          //Sending raw IR code 
          irsend.sendRaw(buf,len,freq.toInt());
          TRANSMITTED = true;
              
          //Turning Off LED as a code transmission indicator
          digitalWrite(13, LOW);    
          //delay(1000);            // wait for a second
             
          i++;
        }
      }
      //Turning on LED as a transmission finished indicator
      digitalWrite(13, HIGH);  
         
      //Sending HTTP response 
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("Connection: close");  // the connection will be closed after completion of the response
      //client.println("Refresh: 5");  // refresh the page so that otput is constant
      client.println();
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("IP2IR : ");
      
      if(TRANSMITTED){
        client.println("IR code was transmitted successfully");
      }
      else{
        client.println("Transmission Failure! <br />");
        client.println("Please enter correct message format.");
        
      }
      
      client.println("</html>");
    }
    
    // give the web browser time to receive the data
    delay(1);
    
    // close the connection:
    client.stop();
    //Serial.println("client disconnected");
} 
