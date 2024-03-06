#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FastLED.h>

#define LED_PIN     4
#define NUM_LEDS    1000

CRGB leds[NUM_LEDS];

const char* ssid = "WS2812";
ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  delay(100);

  // Set up the LEDs
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
   // Initialize the first LED to be lit
  setLED(0); // Add this line to light up the first LED

  
  
  // Set up Wi-Fi Access Point
  WiFi.softAP(ssid);

  // Web server routes
  server.on("/", HTTP_GET, []() {
    server.send(200, "text/html", getWebPage());
  });

  server.on("/set", HTTP_GET, []() {
    String slider1 = server.arg("slider1");
    String slider2 = server.arg("slider2");
    String slider3 = server.arg("slider3");
    int position = slider1.toInt() + slider2.toInt() + slider3.toInt();

    // Ensure position is within the bounds of the LED array
    position = max(0, min(NUM_LEDS - 1, position));
    setLED(position);
    
    server.send(200, "text/plain", String(position));
  });

  server.begin();
}

void loop() {
  server.handleClient();
}

void setLED(int position) {
  Serial.print("Setting LED position to: ");
  Serial.println(position);
  // Turn all LEDs off
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }

  // Set specified LED to red
  leds[position] = CRGB::Red;
  FastLED.show();
}

String getWebPage() {
  return String(
    "<!DOCTYPE html><html><body>"
    "<h2>LED Control</h2>"
    "<p>Adjust sliders until last LED of string is on</p>"
    "<p>Slider 1 (0-900): <input type='range' min='0' max='900' step='100' onchange='updateLED()' id='slider1' value='0'></p>"
    "<p>Slider 2 (0-90): <input type='range' min='0' max='90' step='10' onchange='updateLED()' id='slider2' value='0'></p>"
    "<p>Slider 3 (0-9): <input type='range' min='0' max='9' step='1' onchange='updateLED()' id='slider3' value='0'></p>"
    "<p>LED Index: <span id='output'>0</span></p>"
    "<p>Number of LEDs: <span id='numLEDs'>1</span></p>"
    "<script>"
    "async function updateLED() {"
    "  var slider1 = document.getElementById('slider1').value;"
    "  var slider2 = document.getElementById('slider2').value;"
    "  var slider3 = document.getElementById('slider3').value;"
    "  var sum = parseInt(slider1) + parseInt(slider2) + parseInt(slider3);"
    "  document.getElementById('output').innerHTML = sum;"
    "  document.getElementById('numLEDs').innerHTML = sum + 1;"
    "  await fetch('set?slider1=' + slider1 + '&slider2=' + slider2 + '&slider3=' + slider3);"
    "}"
    "</script>"
    "</body></html>"
  );
}
