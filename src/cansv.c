/** CAN Server-side */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#include <errno.h>
#include <linux/can.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>

#include "log_it.h"

#define STDBUF_SIZE 256

extern int socket(int domain, int type, int protocol);

int main(int argc, char *argv[])
{
  int sockfd, ret = 0;
  char buf[STDBUF_SIZE];
  struct sockaddr_can addr;
  struct ifreq ifr;
  struct can_frame frame;

  sockfd = socket(PF_CAN, SOCK_RAW, CAN_RAW);
  if (sockfd < 0)
    _err("socket");

  strncpy(ifr.ifr_name, "vcan0", 6);
  ioctl(sockfd, SIOCGIFINDEX, &ifr);

  addr.can_family = AF_CAN;
  addr.can_ifindex = ifr.ifr_ifindex;

  ret = bind(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr));
  if (ret < 0)
    _err("bind");

  for(int j = 0; j < 5; j++) {

    frame.can_id = 1;
    frame.can_dlc = 4;
    frame.data[0] = j*10+1;
    frame.data[1] = j*10+2;
    frame.data[2] = j*10+3;
    frame.data[3] = j*10+4;

    _log("Writing (%d): %d%d%d%d", frame.can_dlc,
                                   frame.data[0],
                                   frame.data[1],
                                   frame.data[2],
                                   frame.data[3]);

    ret = send(sockfd, &frame, sizeof(frame), 0);
    if (ret < 0)
      _err("send");
    usleep(1); /* Return to scheduler */
  }

  /* Send termination */
  frame.data[0] = 255;
  frame.can_dlc = 1;
  _log("Closing communication - sending 255 termination code.");
  ret = send(sockfd, &frame, sizeof(frame), 0);
  if (ret < 0)
    _err("send");

  return 0;
}
