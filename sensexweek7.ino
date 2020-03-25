//https://nl.aliexpress.com/item/33013657307.html?spm=a2g0s.9042311.0.0.27424c4dPyZ2EW

#include <arduino.h>
#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// OLED display
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "your blynk ID";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "your wifi";
char pass[] = "your password";

BlynkTimer timer;

// setting PWM properties
int freq = 5000;
int resolution = 8;
int ledChannel1 = 0;
int ledChannel2 = 1;
int ledChannel3 = 2;

int B = 14;     // GPIO14
int G = 27;     // GPIO27
int R = 13;     // GPIO13

int soundSensor=33;     // GPIO33
int LED = 4;            // GPIO4
int LEDG = 15;          // GPIO15
int dissens = 35;       // GPIO35
int pump = 32;          // GPIO32
int RGB[] = {0,0,0};
int sneez = 0;
int hand = 0;
unsigned long safe = 0;
int counter = 0;
String onscreen= "keep up the good work" ;
BLYNK_WRITE(V0)
{
    RGB[0] = param[0].asInt();
    RGB[1] = param[1].asInt();
    RGB[2] = param[2].asInt();
    ledcWrite(ledChannel1, RGB[0]);
    ledcWrite(ledChannel2, RGB[1]); 
    ledcWrite(ledChannel3, RGB[2]); 

}
void myTimerEvent()
{
    // sending the amount of times you washed your hands and the amount of times you have sneezed 
    // Please don't send more that 10 values per second.
    Blynk.virtualWrite(V5, counter);
    Blynk.virtualWrite(V4, sneez);
    if(sneez > counter){
        onscreen = "you should wash your hands more";
        Blynk.virtualWrite(V6, "you should wash your hands more");
    }
    else 
    {
        onscreen = "keep up the good work";
        Blynk.virtualWrite(V6, "keep up the good work");

    }
}

void setup() {
    
    Serial.begin(9600);

    pinMode(soundSensor,INPUT);
    pinMode(dissens,INPUT);
    pinMode(LED,OUTPUT);
    pinMode(LEDG,OUTPUT);
    pinMode(pump,OUTPUT);

    ledcSetup(ledChannel1, freq, resolution);
    ledcSetup(ledChannel2, freq, resolution);
    ledcSetup(ledChannel3, freq, resolution);

    // attach the channel to the GPIO to be controlled
    ledcAttachPin(R, ledChannel1);
    ledcAttachPin(G, ledChannel2);
    ledcAttachPin(B, ledChannel3);

    //SSD1306 OLED:
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }

    Blynk.begin(auth, ssid, pass, "server.wyns.it", 8081);

    timer.setInterval(1000L, myTimerEvent);

}

void loop() {

    Blynk.run();
    timer.run();
    int SensorData = digitalRead(soundSensor); 
    
    if(SensorData >= 1){
        sneez++;
        digitalWrite(LED,HIGH);
    }
    hand = analogRead(dissens);
    if(hand >= 1500){
        digitalWrite(LED,LOW);
        digitalWrite(LEDG,HIGH);
        digitalWrite(pump,HIGH);
        delay(5000);
        digitalWrite(pump, LOW);
        counter ++;
        digitalWrite(LEDG,HIGH);
        safe = millis()+2000;

    }
    if (millis() > safe ){
        digitalWrite(LEDG, LOW);
    }
    display.clearDisplay();
    display.setTextSize(1);

    display.setCursor(0, 16);
    display.setTextColor(WHITE);
    display.println(onscreen);
    display.display();

} 
