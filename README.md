Source code for STWLC68 OTP procedure.

libgpiod library: 

	https://github.com/brgl/libgpiod/blob/master/README 
	
To Compile: 

	gcc -o 'name of the output executable' -I 'path to libgpiod includes directory' main.c  otp.c i2c_interface.c -L 'path to libgpiod lib directory' -lgpiod

To Run: 

	./'name of the output executable'
	



			 
