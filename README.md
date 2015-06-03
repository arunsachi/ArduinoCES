# ArduinoCES
Arduino Sketches for CES Lab

# IP2IR
This program sends IR signals using Arduino Ethernet corresponding to get requests from a web server.

## Version - 2.00

## Folders: 
1. Design - Schematic Circuit Diagram
2. Implementation - Source code
3. Testing - Output Screenshots

## IP and MAC configuration:
1. MAC of Arduino Ethernet is hard coded in the sketch
2. An IP belonging to the same local network as the Web Server is assigned to the Arduino.

## External library configuration: 
1. IRremote Arduino Library (https://github.com/shirriff/Arduino-IRremote/releases) page. 
2. Download the latest release. 
3. Extract the zip file 
4. Move the "IRremote" folder that has been extracted to your libraries directory already.

## Implementation details:
The current implementation sends raw IR code whenever a get request is received from web server. <br />
The format of get request is :  <ip of Arduino>/command/<code>/<repeat-time>/<frequency>.  <br />

## Further Extensions possible: 
1. Issuing different vendor specific codes on get request.
2. Switch case for different vendor specific consumer devices.

## Testing Serial Communication:
This can be done using a loopback test in Windows Hyperterminal or Arduino Serial Monitor.
Screenshots provided in the Testing folder

## Troubleshooting:
1. Get request does not reach Arduino - Try pinging the Arduino IP to check if connection is okay.
2. Serial connection to Arduino does not work when Hyperterminal is being used to monitor.

## Contributors
Arun Sachidanandan  <br />
Muhammad Umair 
