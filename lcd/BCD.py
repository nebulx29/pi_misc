#! /usr/bin/python

import smbus
import sys
import time
import socket
import i2c_LCD

def FromBCD(BCDNumber):
    _HighNibble, _LowNibble = divmod(BCDNumber, 16)
    if not all(0 <= _Nibble <= 9 for _Nibble in [_HighNibble, _LowNibble]):
        raise ValueError('%02x is not a valid BCD byte value' % BCDNumber)
    return _HighNibble * 10 + _LowNibble

__I2CBus = smbus.SMBus(0)
__ErrorCount = 0

i2c_LCD.Setup(__I2CBus, 4, 20)
time.sleep(0.5)
i2c_LCD.Clear(__I2CBus)
time.sleep(0.5)

Socket_IPAddress = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
Socket_IPAddress.connect(("google.com", 80))
__IPAddress = Socket_IPAddress.getsockname()[0]
Socket_IPAddress.close()

i2c_LCD.PrintAt(__I2CBus, 1, 1, "RPi:")
i2c_LCD.PrintAt(__I2CBus, 1, 6, __IPAddress)

while (True):
   try:
      _Day = FromBCD(__I2CBus.read_byte_data(0x68, 0x04))
      _Month = FromBCD(__I2CBus.read_byte_data(0x68, 0x05))
      _Year = FromBCD(__I2CBus.read_byte_data(0x68, 0x06))

      _Hours = FromBCD(__I2CBus.read_byte_data(0x68, 0x02))
      _Minutes = FromBCD(__I2CBus.read_byte_data(0x68, 0x01))
      _Seconds = FromBCD(__I2CBus.read_byte_data(0x68, 0x00))

      _Temperature1 = __I2CBus.read_byte_data(0x48, 0x00);
      _Temperature2 = __I2CBus.read_byte_data(0x49, 0x00);

   except Exception as _Error:
            __ErrorCount  += 1
            print 'Error ocurred (Count: {0}): {1}'.format(__ErrorCount, _Error)
            time.sleep(1)

   i2c_LCD.PrintAt(__I2CBus, 3, 1, '{0:02d}/{1:02d}/20{2:02d}'.format(_Day, _Month, _Year));
   i2c_LCD.PrintAt(__I2CBus, 3, 15, '{0} C'.format(_Temperature1));
   time.sleep(0.5);

   i2c_LCD.PrintAt(__I2CBus, 4, 1, '{0:02d}:{1:02d}:{2:02d}'.format(_Hours, _Minutes, _Seconds));
   i2c_LCD.PrintAt(__I2CBus, 4, 15, '{0} C'.format(_Temperature2));
   time.sleep(0.5);
