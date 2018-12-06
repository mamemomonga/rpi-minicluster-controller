#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#include <errno.h>
#include <string.h>
#include <termios.h>
#include <stdarg.h>

#define RST_AVR 1
#define RST_PI1 2 
#define RST_PI2 3
#define RST_PI3 4
#define RST_PI4 5

void error_message(char* fmt,...) {
	va_list ap;
	va_start(ap,fmt);
	vfprintf(stderr,fmt,ap);
	fprintf(stderr, "\n");
	va_end(ap);
}

// https://stackoverflow.com/questions/6947413/how-to-open-read-and-write-from-serial-port-in-c
int set_interface_attribs(int fd, int speed, int parity) {
	struct termios tty;
	memset(&tty, 0, sizeof tty);
	if(tcgetattr(fd,&tty) != 0) {
		error_message("error %d from tcgetattr",errno);
		return -1;
	}
	cfsetospeed(&tty, speed);
	cfsetispeed(&tty, speed);
	tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
	tty.c_iflag &= ~IGNBRK;
	tty.c_lflag = 0;
	tty.c_oflag = 0;
	tty.c_cc[VMIN]  = 0;
	tty.c_cc[VTIME] = 5;
	tty.c_iflag &= ~(IXON | IXOFF | IXANY);
	tty.c_cflag |= (CLOCAL | CREAD);
	tty.c_cflag &= ~(PARENB | PARODD);
	tty.c_cflag |= parity;
	tty.c_cflag &= ~CSTOPB;
	tty.c_cflag &= ~CRTSCTS;
	if (tcsetattr (fd, TCSANOW, &tty) != 0) {
		error_message ("error %d from tcsetattr", errno);
		return -1;
	}
	return 0;
}

void set_blocking (int fd, int should_block) {
	struct termios tty;
	memset(&tty, 0, sizeof tty);
	if (tcgetattr (fd, &tty) != 0) {
		error_message ("error %d from tggetattr", errno);
		return;
	}
	tty.c_cc[VMIN]  = should_block ? 1 : 0;
	tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout
	if(tcsetattr (fd, TCSANOW, &tty) != 0) {
		error_message ("error %d setting term attributes", errno);
	}
}

void send_bytes(char* portname, char* wbuf) {
	int fd = open(portname,  O_RDWR | O_NOCTTY | O_SYNC);
	if (fd < 0) {
		error_message ("error %d opening %s: %s", errno, portname, strerror (errno));
		return;
	}
	set_interface_attribs (fd, B115200, 0);
	set_blocking (fd, 0);

	write(fd,wbuf,sizeof wbuf);
	usleep((sizeof wbuf+25)*100);
	char buf[125];
	int n = read(fd,buf,sizeof buf);
	close(fd);
}

void toggle_dtr(char* portname) {
	int fd;
	int modem = 0;

	fd = open(portname, O_RDWR | O_NOCTTY );
	ioctl(fd, TIOCMGET, &modem);

	modem |= TIOCM_DTR;
	ioctl(fd, TIOCMSET, &modem);

	usleep(100000);
	modem &= ~TIOCM_DTR;
	ioctl(fd, TIOCMSET, &modem);

	usleep(100000);
	modem |= TIOCM_DTR;
	ioctl(fd, TIOCMSET, &modem);

	close(fd);
}

void reset_pi(char* portname, char* id) {
	toggle_dtr(portname);
	sleep(3);
	send_bytes(portname,id);
	sleep(5);
	toggle_dtr(portname);
}

void usage(void) {
	printf("USAGE: pi-reset [ARGS] [PORT]\n");
	printf("ARGS:\n");
	printf("   -h  help\n");
	printf("   -a  Reset AVR\n");
	printf("   -1  Reset Pi1\n");
	printf("   -2  Reset Pi2\n");
	printf("   -3  Reset Pi3\n");
	printf("   -4  Reset Pi4\n");
}

int main(int argc, char *argv[]) {
	int i,opt;
	int action=0;
	char* serial="";
	while((opt = getopt(argc,argv,"ha1234")) != -1) {
		switch(opt) {
			case 'h':
				usage();
				return 1;
				break;
			case 'a':
				action = RST_AVR;
				break;
			case '1':
				action = RST_PI1;
				break;
			case '2':
				action = RST_PI2;
				break;
			case '3':
				action = RST_PI3;
				break;
			case '4':
				action = RST_PI4;
				break;
			default:
				usage();
				return 1;
				break;
		}
	}
	serial = argv[optind];

	if(&serial[0] == '\0') {
		usage();
		return 1;
	}
	if(action == 0) {
		usage();
		return 1;
	}

	switch(action) {
		case RST_AVR:
			toggle_dtr(serial);
			break;
		case RST_PI1:
			reset_pi(serial, "q");
			break;
		case RST_PI2:
			reset_pi(serial, "w");
			break;
		case RST_PI3:
			reset_pi(serial, "e");
			break;
		case RST_PI4:
			reset_pi(serial, "r");
			break;

	}
	return 0;
}

