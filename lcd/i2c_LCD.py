#! /usr/bin/python

import time

i2cDeviceID_LCD = 0x31;

def Setup(i2cBus, Rows, Columns):
   i2cBus.write_byte(i2cDeviceID_LCD, 0x1b);
   i2cBus.write_byte(i2cDeviceID_LCD, 0x30);
   i2cBus.write_byte(i2cDeviceID_LCD, Rows);
   time.sleep(0.1);
   i2cBus.write_byte(i2cDeviceID_LCD, 0x1b);
   i2cBus.write_byte(i2cDeviceID_LCD, 0x31);
   i2cBus.write_byte(i2cDeviceID_LCD, Columns);
   time.sleep(0.1);


def Clear(i2cBus):
   i2cBus.write_byte(i2cDeviceID_LCD, 0x1b);
   i2cBus.write_byte(i2cDeviceID_LCD, 0x50);
   time.sleep(0.01);

def Print(i2cBus, StringToPrint):
   for Char in StringToPrint:
      i2cBus.write_byte(i2cDeviceID_LCD, ord(Char));
   time.sleep(0.01);

def PrintAt(i2cBus, Row, Column, StringToPrint):
   i2cBus.write_byte(i2cDeviceID_LCD, 0x1b);
   i2cBus.write_byte(i2cDeviceID_LCD, 0x24);
   i2cBus.write_byte(i2cDeviceID_LCD, Row);
   i2cBus.write_byte(i2cDeviceID_LCD, Column);
   Print(i2cBus, StringToPrint);
