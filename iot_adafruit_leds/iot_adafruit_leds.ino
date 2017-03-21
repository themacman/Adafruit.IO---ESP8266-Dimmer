//https://learn.adafruit.com/adafruit-io-basics-esp8266-arduino/
//Install Adafruit's MQTT library
//Install the Adafruit IO library
#include "AdafruitIO_WiFi.h"

/************************ Adafruit IO Config *******************************/

// Visit io.adafruit.com for an account and your IO_KEY
#define IO_USERNAME    "your username"
#define IO_KEY         "your key"

/******************************* WIFI Config **************************************/

#define WIFI_SSID       "VirtualRouter2"
#define WIFI_PASS       "password2"

/******************************* SETUP **************************************/

//Create an AdafruitIO_WiFi object
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
//Create your feed, source for data
AdafruitIO_Feed *welcomeFeed = io.feed("welcome-feed");

int ledPin = LED_BUILTIN;

void setup() {
  //Set up the LED
  pinMode(ledPin, OUTPUT);
  analogWrite(ledPin, 0);

  //Allow the NodeMCU to talk to the computer
  Serial.begin(115200);
  Serial.print("\n\n\nConnecting to Adafruit IO");
  io.connect();

  //Connect your function, handleMessage, to the feed
  welcomeFeed->onMessage(handleMessage);

  //Wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  //Connection established!
  Serial.println();
  Serial.println(io.statusText());
}

/******************************* LOOP **************************************/

void loop() {
  io.run();//This needs to be here to let Adafruit do its magic
}

/******************************* MESSAGE HANDLER **************************************/

//This is the function called whenever new data is recieved
void handleMessage(AdafruitIO_Data *data) {
  //Extract the number
  int value = atoi(data->value());

  //Print out the value
  Serial.print("received <- ");
  Serial.println(value);

  //Set the LED brightness (1023-0) from the value (0-100)
  analogWrite(ledPin, 1023-(value*10.23));

}
