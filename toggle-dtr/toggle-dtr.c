#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

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
	close(fd);
}


int main(int argc, char *argv[]) {
	// なせか2回送信しないとうまくいかなかった。原因は不明。
	// うまくいく場合は1回でOK
	toggle_dtr(argv[1]);
	usleep(10000);
	toggle_dtr(argv[1]);
}

