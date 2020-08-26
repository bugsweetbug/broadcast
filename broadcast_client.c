#include "sock_include.h"
#define CLIENT_PORT 9000
#define BROADCAST_IP "192.168.161.255"
int main()
{
	int sockfd, ret,len;
	char buf[1024];
	struct sockaddr_in clie_addr;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd < 0)
		err("socket error");
	bzero(&clie_addr, sizeof(clie_addr));
	clie_addr.sin_family = AF_INET;
	clie_addr.sin_port = htons(CLIENT_PORT);/*端口要与服务器广播端口一致*/
	inet_pton(AF_INET, "0.0.0.0", &clie_addr.sin_addr.s_addr);
	ret = bind(sockfd, (struct sockaddr *)&clie_addr, sizeof(clie_addr));
	if(ret < 0)
		err("bind error");
	while(1)
		{
			len = recvfrom(sockfd, buf, sizeof(buf), 0, NULL, 0);
			write(STDOUT_FILENO, buf, len);
		}
	close(sockfd);
	return 0;
}