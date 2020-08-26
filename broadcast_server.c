#include "sock_include.h"
#define BROADCAST_IP "192.168.161.255"
#define CLIENT_PORT 9000
int main()
{
	int sockfd, ret;
	char buf[1024];
	struct sockaddr_in serv_addr, clie_addr;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd < 0)
		err("socket error");
	bzero(&serv_addr,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);	                  /*服务器端口*/
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);				/*服务器IP可指定任意*/
	ret = bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if(ret < 0)
		err("bind error");
	int flag = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &flag, sizeof(flag));
	int i = 1;
	bzero(&clie_addr,sizeof(clie_addr));
	clie_addr.sin_family = AF_INET;						/*绑定广播IP和端口*/
	clie_addr.sin_port = htons(CLIENT_PORT);			/*该端口决定了客户端的哪个端口能收到广播*/
	inet_pton(AF_INET, BROADCAST_IP, &clie_addr.sin_addr.s_addr);
	while(1)
		{
			sprintf(buf, "This is %dth send\n",i++);
			sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&clie_addr, sizeof(clie_addr));
			sleep(1);
		}
	close(sockfd);
	return 0;
}
