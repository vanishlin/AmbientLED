#define BLINKER_PRINT Serial
#define BLINKER_BLE
#include "Esp.h"
#include <Blinker.h>
#include <FastLED.h>
#define BUTTON_2 "btn-rs4"


// 新建组件对象
BlinkerButton Button1("btn-qfn");
BlinkerButton Button2(BUTTON_2);
BlinkerButton Button3("btn-vd3");
#define RGB_1 "LEDCON"
BlinkerRGB RGB1(RGB_1);

int counter = 0;
#define LED_PIN     4
#define NUM_LEDS    150
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define BRIGHTNESS  250

CRGB leds[NUM_LEDS];
uint8_t beginHue = 0;
uint8_t deltaHue = 1;

void rgb1_callback(uint8_t r_value, uint8_t g_value, uint8_t b_value, uint8_t bright_value)
{
   digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    BLINKER_LOG("R value: ", r_value);
    BLINKER_LOG("G value: ", g_value);
    BLINKER_LOG("B value: ", b_value);
    BLINKER_LOG("Rrightness value: ", bright_value);
   delay(100);
  FastLED.clear();
  fill_solid(leds, NUM_LEDS, CRGB(r_value,g_value,b_value));
  FastLED.show();
  //Serial.println(bright_value);
  
  
}

// 按下按键即会执行该函数
void button1_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    fadeToBlackBy(leds, NUM_LEDS, -50);
    FastLED.show();
}

void button2_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    if(state=="press")
    {
    fill_rainbow(leds, NUM_LEDS, 0, 1); 
    FastLED.show();
    delay(25);
    }
    else if(state=="tap")
    {
    if(beginHue<=255)
    {
     beginHue = beginHue+25 ;
    }
    else
    {
      beginHue = 0 ;
    }
    fill_rainbow(leds, NUM_LEDS, beginHue, deltaHue); 
    FastLED.show();
    delay(25);
    }
 
}
void button3_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    
}
// 如果未绑定的组件被触发，则会执行其中内容
/*void dataRead(const String & data)
{
    BLINKER_LOG("Blinker readString: ", data);
    counter++;
    Number1.print(counter);
}*/


void setup() {
    // 初始化串口
    Serial.begin(115200);

    #if defined(BLINKER_PRINT)
        BLINKER_DEBUG.stream(BLINKER_PRINT);
    #endif
    // 初始化blinker
    Blinker.begin();
   // Blinker.attachData(dataRead);
    Button1.attach(button1_callback);
    Button2.attach(button2_callback);
    Button3.attach(button3_callback);
    RGB1.attach(rgb1_callback);

   LEDS.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
//  LEDS.addLeds<LED_TYPE, LED_PIN, CLOCK_PIN COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
}


void loop() {
    Blinker.run();
    
}

  
