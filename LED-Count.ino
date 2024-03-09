// Felix Sawicki
// See README for usage
// Include necessary libraries
#include <ESP8266WiFi.h> // Library for ESP8266 WiFi functionality
#include <ESP8266WebServer.h> // Web server library for ESP8266
#include <FastLED.h> // Library for controlling LEDs

#define LED_PIN     4 // GPIO pin connected to the LED strip data line
#define NUM_LEDS    1000 // Number of LEDs in the strip

CRGB leds[NUM_LEDS]; // Array to hold the current color of each LED

const char* ssid = "WS2812"; // SSID for the WiFi Access Point
ESP8266WebServer server(80); // Create a web server on port 80

void setup() {
  Serial.begin(115200); // Start serial communication at 115200 baud
  delay(100); // Short delay after serial communication begins

  // Set up the LEDs
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS); // Initialize the LED strip
  FastLED.setBrightness(50); // Set the brightness of the LEDs
  
  // Set up Wi-Fi Access Point
  WiFi.softAP(ssid); // Create an open WiFi network with the specified SSID

  // Define web server routes
  server.on("/", HTTP_GET, []() {
    server.send(200, "text/html", getWebPage()); // Serve the main HTML page
  });

  server.on("/set", HTTP_GET, []() {
    // Parse the RGB values from the GET request
    String slider1 = server.arg("slider1");
    String slider2 = server.arg("slider2");
    String slider3 = server.arg("slider3");
    int position = slider1.toInt() + slider2.toInt() + slider3.toInt(); // Calculate position

    // Ensure position is within the bounds of the LED array
    position = max(0, min(NUM_LEDS - 1, position));
    setLED(position); // Set the LED at the calculated position
    
    server.send(200, "text/plain", String(position)); // Respond with the new position
  });

  server.begin(); // Start the web server
}

void loop() {
  server.handleClient(); // Handle incoming web requests
}

// Function to set a specific LED to red and turn off all others
void setLED(int position) {
  Serial.print("Setting LED position to: ");
  Serial.println(position);
  
  // Turn all LEDs off
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }

  // Set specified LED to red
  leds[position] = CRGB::Red;
  FastLED.show(); // Update the LED strip with the new colors
}

// Function to generate the main web page HTML
String getWebPage() {
  // HTML content with JavaScript for the sliders that control the LED strip
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
