
#ifndef I2C_INTERFACE_H
#define I2C_INTERFACE_H
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>


#define I2C_SLAVE_ADDR 		0x61
#define I2C_DEV_PATH 		"/dev/i2c-1"
#define PI_GPIO_CHIP_PATH 	"/dev/gpiochip0"
#define PI_GPIO_26 			26   // pin 37

int i2c_open();
int i2c_write(uint8_t* data, int data_length);
int i2c_write_read(uint8_t* cmd, int cmd_length, uint8_t* read_data, int count);
void i2c_close();
int gpio_get_value();
int gpio_configure();


#endif /* I2C_INTERFACE_H */
