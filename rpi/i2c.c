#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int file_i2c;

int i2c_init(int addr) {
	char *filename = (char*)"/dev/i2c-1";
	if ((file_i2c = open(filename, O_RDWR)) < 0)
	{
		printf("Failed to open the i2c bus");
		return 1;
	}
	if (ioctl(file_i2c, I2C_SLAVE, addr) < 0)
	{
		printf("Failed to acquire bus access and/or talk to slave.\n");
		return 1;
	}
}

int i2c_read(int length, char *buffer) {
	//read() returns the number of bytes actually read, if it doesn't match
	//then an error occurred (e.g. no response from the device)
	if (read(file_i2c, buffer, length) != length)
	{
		printf("Failed to read from the i2c bus.\n");
		return 1;
	}


}

int i2c_write(int length, char* buffer) {
	//write() returns the number of bytes actually written, if it doesn't
	//match then an error occurred (e.g. no response from the device)
	if (write(file_i2c, buffer, length) != length) {
		/* ERROR HANDLING: i2c transaction failed */
		printf("Failed to write to the i2c bus.\n");
		return 1;
	}
}

int usage() {
	printf("i2c: read write bytes to i2c devices\n\n");
	printf("\tget <addr DEC>\n\t\tread one byte from <addr>\n");
	printf("\tset <addr DEC> <value>\n\t\twrite byte <value> to <addr>\n");
	return 1;
}

int main(int argc, char* argv[]) {
	if (argc <= 1) return usage();

	if (0 == strcmp(argv[1], "get")) {
		if (argc <= 2) return usage();
		int addr = strtol(argv[2], NULL, 10);
		i2c_init(addr);
		char value = 0;
		i2c_read(1, &value);
		printf("%hhu\n", value);
	} else if (0 == strcmp(argv[1], "set")) {
		if (argc <= 3) return usage();

		int addr = strtol(argv[2], NULL, 10);
		i2c_init(addr);

		int val = strtol(argv[3], NULL, 10);
		char cval = (char)val;
		i2c_write(1, &cval);
	} else {
		printf("unknown mode %s\n", argv[1]);
		return 1;
	}
}
