#include <stdio.h>
#include "otp.h"

int main(int argc, char** argv) {
	int err = 0;
	struct chip_info info;
    if((err = i2c_open()) < OK)
		printf("Error opening /dev/i2c interface\n");
	
    if((err = otp_program()) < OK) {
		printf("Error in programming OTP\n");
		i2c_close();
		return err;
	}
	
    else
		printf("OTP programmed successfully\n");
	
	get_chip_info(&info);
	
	printf("Config Id: 0x%04X, Patch Id: 0x%04X\n", info->config_id, info->patch_id);
    
    return 0;
}

