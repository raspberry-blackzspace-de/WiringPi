﻿// WiringPi test program: Kernel char device interface / sysfs successor
// Compile: gcc -Wall wiringpi_test3_device.c -o wiringpi_test3_device -lwiringPi

#include "wpi_test.h"
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>


const int GPIO = 24; //BCM 19
const int GPIOIN = 25; //BCM 26;
const int ToggleValue = 4;


int main (void) {

	printf("WiringPi GPIO test program 2 (using WiringPi GPIO%d (output) and GPIO%d (input) via GPIO device)\n", GPIO, GPIOIN);
    printf(" testing pullUpDnControl and pinMode PM_OFF\n");

	if (wiringPiSetupGpioDevice(WPI_PIN_WPI)  == -1) {
		printf("wiringPiSetupGpioDevice failed\n\n");
		exit(EXIT_FAILURE);
	}
	pinMode(GPIOIN, INPUT);
	pinMode(GPIO, OUTPUT);

	printf("\nTest output\n");
	digitalWriteEx(GPIO, GPIOIN, HIGH);
	delayMicroseconds(600000);
	digitalWriteEx(GPIO, GPIOIN, LOW);
	delayMicroseconds(600000);

    printf("\nTest output off with pull up\n");
    pinMode(GPIO, OUTPUT);
    digitalWriteEx(GPIO, GPIOIN, LOW);
    pullUpDnControl (GPIO, PUD_UP);
    pinMode(GPIO, PM_OFF);
    delayMicroseconds(600000);
    printf("out = off ");
    CheckGPIO(GPIO, GPIOIN, HIGH);
    delayMicroseconds(600000);

	printf("\nTest output off with pull down\n");
	pullUpDnControl (GPIO, PUD_DOWN);
	pinMode(GPIO, PM_OFF);
	delayMicroseconds(600000);
	printf("out = off ");
	CheckGPIO(GPIO, GPIOIN, LOW);
	delayMicroseconds(600000);

	return(EXIT_SUCCESS);
}
