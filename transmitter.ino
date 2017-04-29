// transmitter.pde
//
// Simple example of how to use VirtualWire to transmit messages
// Implements a simplex (one-way) transmitter with an TX-C1 module
//
// See VirtualWire.h for detailed API docs
// Author: Mike McCauley (mikem@open.com.au)
// Copyright (C) 2008 Mike McCauley
// $Id: transmitter.pde,v 1.3 2009/03/30 00:07:24 mikem Exp $

#include <VirtualWire.h>

String data;

int counter = 0;
long old_time = 0;
int tx_period = 200;

void setup()
{
    Serial.begin(9600);	  // Debugging only
    Serial.println("setup");

    // Initialise the IO and ISR
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);	 // Bits per sec

    old_time = millis();
}

void loop()
{
    if (millis() - old_time > tx_period){
      updateData();
      Serial.println(data);
      transmitData();
    }
    

}

void updateData(){
  data = "";
  counter++;
  data.concat(counter);
}

void transmitData(){
    Serial.print("TX: ");
    Serial.println(data.c_str());
    digitalWrite(13, true); // Flash a light to show transmitting
    vw_send((uint8_t *)data.c_str(), data.length());
    vw_wait_tx(); // Wait until the whole message is gone
    digitalWrite(13, false);
    delay(200);
}

