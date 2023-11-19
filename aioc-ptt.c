#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("AIOC-PTT v0.1\n\n");
    printf("Usage:\n");
    printf("%s <device> <command>\n\n", argv[0]);
    printf("Examples:\n");
    printf("# hold the PTT for 5 seconds\n");
    printf("%s /dev/ttyACM1 'sleep 5'\n\n", argv[0]);
    printf("# execute command while holding the PTT.\n");
    printf("%s /dev/ttyACM1 'aplay -D hw:AllInOneCable "
           "/usr/share/sounds/alsa/Front_Center.wav'\n\n",
           argv[0]);
    exit(1);
  }

  int fd;
  fd = open(argv[1], O_RDWR | O_NOCTTY);
  if (fd < 0) {
    perror("Cannot open device");
    exit(1);
  }

  int DTR_flag = TIOCM_DTR;
  int RTS_flag = TIOCM_RTS;
  // PTT: on
  ioctl(fd, TIOCMBIS, &DTR_flag);
  ioctl(fd, TIOCMBIC, &RTS_flag);

  system(argv[2]);

  // PTT: off
  ioctl(fd, TIOCMBIC, &DTR_flag);
  ioctl(fd, TIOCMBIS, &RTS_flag);

  close(fd);

  return 0;
}
