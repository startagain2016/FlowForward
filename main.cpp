#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <winsock2.h>
#include "Forward.hpp"

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main(int argc, char *argv[])
{
  WSADATA wsa;
  if (!WSAStartup(MAKEWORD(2, 2), &wsa) == 0)
  {
    return 0;
  }
  if (argc <= 1)
  {
    printf("  _____ _                 _____                                _ \n");
    printf(" |  ___| | _____      __ |  ___|__  _ ____      ____ _ _ __ __| |\n");
    printf(" | |_  | |/ _ \ \ /\ / / | |_ / _ \| '__\ \ /\ / / _` | '__/ _` |\n");
    printf(" |  _| | | (_) \ V  V /  |  _| (_) | |   \ V  V / (_| | | | (_| |\n");
    printf(" |_|   |_|\___/ \_/\_/   |_|  \___/|_|    \_/\_/ \__,_|_|  \__,_|\n");
    printf("                                                                 \n\n");
    printf("E-Mail: me@lyshark.com \n\n");
    printf("Usage: \n\n");
    printf("\t --ListenPort          指定转发服务器侦听端口 \n");
    printf("\t --RemoteAddress       指定对端IP地址 \n");
    printf("\t --RemotePort          指定对端端口号 \n");
    printf("\t --LocalPort           指定本端端口号 \n");
    printf("\t --ServerAddress       指定服务端IP地址 \n");
    printf("\t --ServerPort          指定服务器Port端口号 \n");
    printf("\t --ConnectAddress      指定连接到对端IP地址 \n");
    printf("\t --ConnectPort         指定对端连接Port端口号 \n\n");
  }
  if (argc == 8)
  {
    if (strcmp(argv[1], "Forward") == 0 &&
      strcmp(argv[2], "--ListenPort") == 0 &&
      strcmp(argv[4], "--RemoteAddress") == 0 &&
      strcmp(argv[6], "--RemotePort") == 0
      )
    {
      printf("[*] 正向隧道模式 \n");
      printf("[+] 本机侦听端口: %s \n", argv[3]);
      printf("[+] 流量转发地址 %s:%s \n\n", argv[5], argv[7]);
      ForwardForwarding::Forwarding(atoi(argv[3]), argv[5], atoi(argv[7]));
    }
  }
  if (argc == 10)
  {
    if (strcmp(argv[1], "ReverseClient") == 0 &&
      strcmp(argv[2], "--ServerAddress") == 0 &&
      strcmp(argv[4], "--ServerPort") == 0 &&
      strcmp(argv[6], "--ConnectAddress") == 0 &&
      strcmp(argv[8], "--ConnectPort") == 0
      )
    {
      printf("[*] 反向纯流量隧道模式 (客户端) \n");
      printf("[+] 服务端地址 %s:%s \n", argv[3], argv[5]);
      printf("[+] 连接内网地址 %s:%s \n", argv[7], argv[9]);

      ReverseForwarding::PortTransferClient(argv[3], atoi(argv[5]), argv[7], atoi(argv[9]));
    }
  }
  if (argc == 6)
  {
    if (strcmp(argv[1], "ReverseServer") == 0 &&
      strcmp(argv[2], "--ListenPort") == 0 &&
      strcmp(argv[4], "--LocalPort") == 0
      )
    {
      printf("[*] 反向纯流量隧道模式 (服务端) \n");
      printf("[+] 侦听端口: %s \n", argv[3]);
      printf("[+] 本机连接地址: localhost:%s \n\n", argv[5]);

      ReverseForwarding::PortTransferServer(atoi(argv[3]), atoi(argv[5]));
    }
  }
  if (argc == 6)
  {
    if (strcmp(argv[1], "TwoForwardServer") == 0 &&
      strcmp(argv[2], "--ListenPort") == 0 &&
      strcmp(argv[4], "--LocalPort") == 0
      )
    {
      printf("[*] 双向隧道转发模式 (服务端) \n");
      printf("[+] 侦听端口: %s \n", argv[3]);
      printf("[+] 本机连接地址: localhost:%s \n\n", argv[5]);

      TwoForwarding::Server(atoi(argv[3]), atoi(argv[5]));
    }
  }
  if (argc == 10)
  {
    if (strcmp(argv[1], "TwoForwardClient") == 0 &&
      strcmp(argv[2], "--ServerAddress") == 0 &&
      strcmp(argv[4], "--ServerPort") == 0 &&
      strcmp(argv[6], "--ConnectAddress") == 0 &&
      strcmp(argv[8], "--ConnectPort") == 0
      )
    {
      printf("[*] 双向隧道转发模式 (客户端) \n");
      printf("[+] 服务端地址 %s:%s \n", argv[3], argv[5]);
      printf("[+] 连接内网地址 %s:%s \n", argv[7], argv[9]);
      TwoForwarding::Client(argv[3],argv[7],atoi(argv[5]),atoi(argv[9]));
    }
  }

  WSACleanup();
  return 0;
}
