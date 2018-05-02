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

#include "logit.h"

#define STDBUF_SIZE 256
#define GCAN_INIT_SOCKET_ERROR -4
#define GCAN_MAX_IF_NAME 10

extern int socket(int domain, int type, int protocol);

int main(int argc, char *argv[])
{
  int sockfd, ret = 0;
  char buf[STDBUF_SIZE];
  struct sockaddr_can addr;
  struct ifreq ifr;
  struct can_frame frame;

  logit("logit version: %s", logit_version());

  sockfd = socket(PF_CAN, SOCK_RAW, CAN_RAW);
  if (sockfd < 0)
    syserr("socket");

  strncpy(ifr.ifr_name, "vcan0", 6);
  ioctl(sockfd, SIOCGIFINDEX, &ifr);

  addr.can_family = AF_CAN;
  addr.can_ifindex = ifr.ifr_ifindex;

  ret = bind(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr));
  if (ret < 0)
    syserr("bind");

  do {
    ret = recv(sockfd, &frame, sizeof(frame), 0);
    if (ret < 0)
      syserr("recv");

    logit_r("Received (%d): ", frame.can_dlc);
    for (int j = 0; j < frame.can_dlc; j++) {
      logit_r("%d", frame.data[j]);
    }
    logit_r("\n");

    if (frame.can_dlc == 1 && frame.data[0] == 255) {
      logit("Received termination message.");
      return 0;
    }

  } while (ret); /* ret contains nb of rcvd bytes */

  return 0;
}


/**
 * @name  gcan_init
 * @brief initializes and binds a socket to interface name `ifname`
 *
int gcan_init(char *ifname) 
{
  struct ifreq ifr = {0};
  int fd = socket(PF_CAN, SOCK_RAW, CAN_RAW);
  if (fd < 0) {
    _err("socket");
    return GCAN_INIT_SOCKET_ERROR;
  }
  *sockfd = fd;
  strncpy(ifr.ifr_name, ifname, strnlen(ifname, GCAN_MAX_IF_NAME) + 1); 
  ioctl(fd, SIOCGIFINDEX, &ifr);
  struct 

}
*/
