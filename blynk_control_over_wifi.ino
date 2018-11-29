#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <WidgetRTC.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "bc757fec10104759b7a9ec2e4f57478d";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "HOTBOX-72F6";
char pass[] = "10203040";

// -- timer
unsigned int i_on = 0;
unsigned int i_start = 0;
bool bCounting = false;
int idx = 0;

//-- pinout definitions
int buttonStateForward = 0;

#define pin_motorR_polar_a 14 
#define pin_motorR_polar_b 27 
#define pin_ForwardButton 12

WidgetTerminal terminal(V5);

  void setup() 
  {  
    pinMode(pin_motorR_polar_a, OUTPUT); 
    pinMode(pin_motorR_polar_b, OUTPUT);
    pinMode(pin_ForwardButton, INPUT);

    digitalWrite(pin_motorR_polar_a, LOW); 
    digitalWrite(pin_motorR_polar_b, LOW);
    
    Serial.begin(115200);
   //terminal
   // Clear the terminal content
  terminal.clear();

  // This will print Blynk Software version to the Terminal Widget when
  // your hardware gets connected to Blynk Server
  terminal.println(F("Blynk v" BLYNK_VERSION ": Device started"));
  terminal.println(F("-------------"));
  terminal.println(F("Type 'Marco' and get a reply, or type"));
  terminal.println(F("anything else and get it printed back."));
  terminal.flush();
   //__terminal
   
    
    delay(10);
    Serial.print("Connecting to ");
    Serial.println(ssid);
  
    WiFi.begin(ssid, pass);
    int wifi_ctr = 0;
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    
    i_start = micros();
    
    Serial.println("WiFi connected");  
  
    Blynk.begin("bc757fec10104759b7a9ec2e4f57478d", ssid, pass);
  
  }

  void loop()
  {
    Blynk.run();
       
    buttonStateForward = digitalRead (pin_ForwardButton);
    if (buttonStateForward == LOW && bCounting == true)
    {
      Serial.println("forward button -> low");  
      terminal.println("forward button -> low"); 
      digitalWrite (pin_motorR_polar_a, LOW); 
      digitalWrite (pin_motorR_polar_b, LOW); 
     
      Serial.print ("time = ");
      Serial.print (i_on - i_start);
      i_start = i_on;
      
      Serial.println ("");
      //track[index][0] = FORWARD; track[index][1] = i_on;
      
      Serial.print ("index=");
      Serial.println(idx);
      
      idx = idx + 1;
      
      bCounting = false;
    }
  
    if (buttonStateForward == HIGH && bCounting == false)
    {
      Serial.println("forward button -> high"); 
      terminal.println("forward button -> high"); 
      digitalWrite (pin_motorR_polar_a, HIGH); 
      digitalWrite (pin_motorR_polar_b, HIGH); 
      i_on = micros(); //start counting
      bCounting = true;
    }
    
  
  }//loop
