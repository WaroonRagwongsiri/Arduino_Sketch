#include "LedControl.h"

LedControl lc = LedControl(11, 13, 10, 4);  // CLK, DIN, CS, Number of LED Module

unsigned long delaytime = 500;  // time to updates of the display

void	setup()
{
	int devices = lc.getDeviceCount();  // find no of LED modules
	//we have to init all devices in a loop
	for(int address = 0; address < devices; address++)
	{  // set up each device 
		lc.shutdown(address, false);
		lc.setIntensity(address, 8);
		lc.clearDisplay(address);
	}
}

void	loop(){ 
	int devices = lc.getDeviceCount();  // find no of LED modules
	int	row;
	int	col;
	int	address;

	// Line 1
	for (col = 0; col < 8; col++)
	{
		for(address = 0; address < devices; address++)
		{
			delay(delaytime);
			lc.setLed(address, 0, col, true);
			delay(delaytime);
			lc.setLed(address, 0, col, false);
		}
	}
	// Line 2
	for (row = 1; row < 8; row++)
	{
		for(address = 0; address < devices; address++)
		{
			delay(delaytime);
			lc.setLed(address, row, 7, true);
			delay(delaytime);
			lc.setLed(address, row, 7, false);
		}
	}
	// Line 3
	for (col = 6; col >= 0; col--)
	{
		for(address = 0; address < devices; address++)
		{
			delay(delaytime);
			lc.setLed(address, 7, col, true);
			delay(delaytime);
			lc.setLed(address, 7, col, false);
		}
	}
	// Line 4
	for (row = 6; row >= 1; row--)
	{
		for(address = 0; address < devices; address++)
		{
			delay(delaytime);
			lc.setLed(address, row, 0, true);
			delay(delaytime);
			lc.setLed(address, row, 0, false);
		}
	}
}
