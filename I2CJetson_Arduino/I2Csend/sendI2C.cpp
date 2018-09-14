#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <string>
#include <stdio.h>

using namespace std;

int addr1 = 0x40;
int addr2 = 0x04;

int file_i2c;
int file_i2c2;

char *filename = (char*)"/dev/i2c-1";

bool writeStream(int file_i2c, string output) {
  if(write(file_i2c, output.c_str(), output.length()) != output.length()) {
    printf("\tFailed to write to the i2c bus.\n");
  }
  return true;
}

int main() {
	
	//Open i2c bus
	if((file_i2c = open(filename, O_RDWR)) < 0) {
	printf("\tFailed to open the i2c bus\n");
	
	}
	if(ioctl(file_i2c, I2C_SLAVE, addr2) < 0) {
	printf("\tFailed to acquire bus access and/or talk to slave.\n");
	
	}
	string input;
	
	//send data
	while(1){
		cin >> input;
		writeStream(file_i2c, input);
	}
	
	return 0;
}
