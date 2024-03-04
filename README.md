# ESP8266 WS2812 Determine the number of LEDs in a string

This program  allows me to quickly determine how many LEDs are in a WS2812 type string.  There are three sliders that increment by 100,  10,  and 1.  Adjust the 100 slider until the LED just disappears off the end,  and then back it off by one so you can see the LED.  Repeat the process with the 10s slider,  and then the 1s slider.  The LED should be set to the last LED and the number of LEDs can be read off the web page. The maximum number of LEDs is currently set to 1000 but could be adjusted.

This project turns an ESP8266 into a wireless access point with a web interface for controlling WS2812 LEDs. It features a simple web page with sliders that allow users to select the position of an LED to light up on the strip. The project uses the FastLED library to control the LEDs and demonstrates a basic implementation of a web server on the ESP8266.


## Features

- **Wireless Control**: Set up the ESP8266 as an access point to control the LEDs wirelessly.
- **Web Interface**: A simple web interface with sliders to control the LED position.
- **Dynamic LED Control**: Change which LED is lit in real-time via the web interface.

## Hardware Requirements

- ESP8266 module (e.g., NodeMCU, Wemos D1 Mini)
- WS2812 LED Strip
- Power Supply for the LED strip
- Connecting wires

## Software Requirements

- Arduino IDE
- ESP8266 Board package for Arduino IDE
- FastLED library

## Setup

### Hardware Connections

1. Connect the data input of your WS2812 LED strip to GPIO 2 (D4 on NodeMCU) of the ESP8266.
2. Connect the power and ground lines of the LED strip to a suitable power supply.
3. Ensure the ESP8266 is also powered appropriately.

### Software Configuration

1. Install the ESP8266 board package in the Arduino IDE.
2. Install the FastLED library via the Library Manager in the Arduino IDE.
3. Open the provided sketch and adjust the `NUM_LEDS` constant to match the number of LEDs in your strip.
4. Upload the sketch to your ESP8266.

## Usage

1. After uploading the sketch, the ESP8266 will broadcast a WiFi network with the SSID "WS2812".
2. Connect to this network from a device with a web browser.
3. Open a web browser and navigate to `http://192.168.4.1`.
4. Use the sliders on the web page to control the LEDs on the strip. The "LED index" field shows the sum of the sliders, and the "Number of LEDs" shows the number of LEDs you have when that last one is lit (index +1).

## Customization

The sketch and web interface can be customized to add more functionality, such as changing LED colors, adding patterns, or controlling multiple LED strips.

## Troubleshooting

- If the LEDs do not light up, check your power supply and connections.
- Ensure the LED strip is compatible with the FastLED library.
- If the web interface does not load, ensure your device is connected to the "WS2812" WiFi network and the ESP8266 is powered on.



## License

This project is open-source and available under the MIT License. See the LICENSE file for more details.
