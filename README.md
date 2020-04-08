"# stwlc68-otp" 

To Compile:

            gcc -o "name of the output executable" -I "path to libgpiod include directory" main.c 
	    	otp.c i2c_interface.c -L"path to libgpiod lib directory" -lgpiod
			  
	example: 
			gcc -o otp_tool -I export/rootfs/include main.c otp.c i2c_interface.c -L export/rootfs/lib -lgpiod
	
To Run:	

			./"name of the executable"
	
	example:
			./otp_tool
			 
