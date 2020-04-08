/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "i2c_interface.h"
#include <gpiod.h>
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

struct gpiod_chip *chip;
struct gpiod_line *gpio;
static int file_handle = 0;

int i2c_open() {

    if ((file_handle = open(I2C_DEV_PATH, O_RDWR)) < 0) {
        /* ERROR HANDLING: you can check errno to see what went wrong */
        printf("[ERR] Failed to open the i2c bus, %s", strerror(errno));
        return -1;
    }

    printf("%s opened successfully, fid: %d\n", I2C_DEV_PATH, file_handle);
    
   if(gpio_configure() < 0)
        printf("Error configuring the gpio\n");

    return 0;
}

void i2c_close() {

    close(file_handle);
    printf("%s closed\n", I2C_DEV_PATH);
    gpiod_chip_close(chip);
}

int i2c_write(uint8_t* data, int data_length) {
    
    struct i2c_msg msg[1];
    struct i2c_rdwr_ioctl_data ioctl_data;
    
    msg[0].addr = (__u16)I2C_SLAVE_ADDR;
    msg[0].buf = (__u8*)data;
    msg[0].len = (__u16)data_length;
    msg[0].flags = 0;
        
    ioctl_data.msgs = msg;
    ioctl_data.nmsgs = 1;
    
    int err = ioctl(file_handle, I2C_RDWR, &ioctl_data);
    
    if (err < 0) {
        printf("ioctl error: %s\n", strerror(errno));
        return err;
    }
    
    return 0;
}

int i2c_write_read(uint8_t* cmd, int cmd_length, uint8_t* read_data, int count) {

    struct i2c_msg msg[2];
    struct i2c_rdwr_ioctl_data ioctl_data;
    
    msg[0].addr = (__u16)I2C_SLAVE_ADDR;
    msg[0].buf = (__u8*)cmd;
    msg[0].len = (__u16)cmd_length;
    msg[0].flags = 0;
    
    msg[1].addr = (__u16)I2C_SLAVE_ADDR;
    msg[1].buf = (__u8*)read_data;
    msg[1].len = (__u16)count;
    msg[1].flags = I2C_M_RD;
    
    ioctl_data.msgs = msg;
    ioctl_data.nmsgs = 2;
    
    int err = ioctl(file_handle, I2C_RDWR, &ioctl_data);
    
    if (err < 0) {
        printf("ioctl error: %s\n", strerror(errno));  
        return err;
    }
    
    return 0;
}

int gpio_configure()
{
    int rv;
    
    printf("libgpiod version: %s\n", gpiod_version_string());
 
    chip = gpiod_chip_open(PI_GPIO_CHIP_PATH);
    if (!chip) {
        printf("could not open %s\n", PI_GPIO_CHIP_PATH);
        gpiod_chip_close(chip);
        return -EFAULT;
    }
    
    printf("%s opened successfully\n", gpiod_chip_label(chip));
                   
    gpio = gpiod_chip_get_line(chip, PI_GPIO_26);
    if (!gpio) {
        printf("could not get GPIO26\n");
        gpiod_chip_close(chip);
        return -EFAULT;
    }
    struct gpiod_line_request_config gpio_cfg;
    gpio_cfg.flags = 0;
    gpio_cfg.request_type = GPIOD_LINE_REQUEST_DIRECTION_INPUT;
    
    rv = gpiod_line_request(gpio, &gpio_cfg, 0);
    if (rv < 0) {
        printf("could not config GPIO\n");
        gpiod_chip_close(chip);
        return -EFAULT;
    }
    
    printf("GPIO requested and configured successfully\n");  
    return 0; 
}

int gpio_get_value()
{
    int pin_value =  gpiod_line_get_value(gpio); 
    return pin_value;
}
