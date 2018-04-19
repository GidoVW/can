/** CAN Client-side */

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

  do {
    ret = recv(sockfd, &frame, sizeof(frame), 0);
    if (ret < 0)
      _err("recv");

    _log_r("Received (%d): ", frame.can_dlc);
    for (int j = 0; j < frame.can_dlc; j++) {
      _log_r("%d", frame.data[j]);
    }
    _log_r("\n");

    if (frame.can_dlc == 1 && frame.data[0] == 255) {
      _log("Received termination message.");
      return 0;
    }

  } while (ret); /* ret contains nb of rcvd bytes */

  return 0;
}
