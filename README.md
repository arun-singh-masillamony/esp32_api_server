# ESP32 - Water level sensor with a server
This is just a side project. WHich can measure the water level and share the data through a API.

### Plan
- Create a server, which has host REST API. -- Done
- Connect the ESP32 with the ultrasonic sensor -- Inprogress
- Connect the ESP32 with the floating sensore -- TODO
- Create a APK to call this API and show the data -- TODO

### Explaination
- Ultrasonic sensor
  - It has 4 pins
    - VCC: It operated on +5V DC
    - GND: Connect to the ground
    - Trig: Trigger as an input Pin
    - Echo: Echo Pin as an output pin
   
- ESP 32
  - As per current code, I have conncted the "Trig" and "Echo" with pin "14" & "27"  (P14 & P27).
  - Connect the sensor's GND with the ESP32's GND.
  - Get the power from ESP32's "5v" pin.
 ![image](https://github.com/arun-singh-masillamony/esp32_api_server/assets/53141964/41f8ecbb-f8c5-4d5c-a653-6225a2c54830)

  - As per esp32_pin_image.png, we can see what are the pins we can use as a input or output or both.
  - As per that image, I came to the conclusion that we can use pin 14 & 27 for both input and output.
 
![image](https://github.com/arun-singh-masillamony/esp32_api_server/assets/53141964/95bc6233-0992-4be3-b17c-3fac5798f59f)


## Reference:
- https://www.electronicwings.com/esp32/ultrasonic-hc-sr04-sensor-interfacing-with-esp32
- esp32_pin_image.png (my current pin details)
