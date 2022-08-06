# soapDispenser
Making a touchless soap dispenser usring an esp32 and blynk cloud.

So this project started out as a reminder to myself because  often after sneezing I forget to wash my hands. So I installed a simple microphone module on a esp32 so just give me a reminder for when I do sneeze. after a while it just got tedious so i thougth well why not just add a soap dispenser to the project to make my life easyer I still had a sharp 2Y0A21 and just had to order a small pump online while I was still waiting on this pump I could already test using a small fan instead. 

needed for this project:
1 x esp32 (you could use any arduino controller i just used the esp because i wanted to use blynk to keep expanding the project)
1 x microphone module KY-037
1 x sharp 2Y0A21
1 x small pump or motor (5V you could use more i just use 5 for convenience)
1 x diode for the motor or pump (Flyback diode)
1 x BC548 transistor
2 x led's (you yoursef can choose the collor i used red and green)
2 x 220ohm resistances 
1 x RGB LED (you can just ignore this if you dont want to add rgb to the casing lateron) 
1 x OLED display (just to display weather you are doing a good job or not)

Now just connect everything like shown in the includded schematic (made using ealge). Most of the pins are just chosen at random so you dont realy have to worry if you want to use different ones.  

Then in the code itsellf you have to change you auth to your given blynk autentication code and ssid as wel as pass to your WIFI network name  and password respectivly. And if you have a costume blynk server you chould also set this up by changing te Blynk.begin if you don't have your own blynk server change it to "Blynk.begin(auth, ssid, pass);" 

Then after uploading this project it chould work. To setup the blynk app you can just use the vertual pins V4 and V5 for the data and on V6 you can find a motivational message and V0 is used for the rgb zebra.

If you have any questions about the project feel free to dm me
