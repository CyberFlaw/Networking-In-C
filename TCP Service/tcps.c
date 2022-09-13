#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>

int main()
{
	struct sockaddr_in saddr, caddr;
	int sid, cid, k;
	u_int length;
	char buf[32], buff[32];
	int l;
	
	sid=socket(PF_INET, SOCK_STREAM, 0);
	if(sid == -1)
	perror("Socket Failed\n");
	memset(&saddr, 0, sizeof(saddr));
	
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(8080);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	if(bind(sid, (struct sockaddr *)&saddr, sizeof(saddr)) == -1)
		perror("Bind Failed!");
	printf("Server started at port 5000\nWaiting for connection...\n");
	
	if(listen(sid, 0) == -1)
		perror("\nServer Busy!");
	
	length = sizeof(caddr);
	if((cid = accept(sid, (struct sockaddr *)&caddr, &length)) == -1 )
		perror("\nConnection Establishment Failed!");
	
	do 
	{
		strncpy(buf, "", 32);
		if(l = (recv(cid, buf, 31, 0)) == -1)
			perror("\nFailed to receive data");
		if(strcmp(buf, "quit") == 0)
			break;
		printf("\n[Client]: %s", buf);
		l = strlen(buf);
		
		strncpy(buff, "", 31);
		for(int i = 0; i <= strlen(buf) + 1 && buf[i] !=; i++)
		{
			if(buf[i] == '\0')
			{
				for (int j = 0; j < strlen(buf); j++)
				{
					buff[j] = buf[i];
					i--;
				}
				break;
			}
		}
		
		
		if(send(cid, buff, strlen(buff), 0) == -1)
			perror("\nSending Failed!");
		else
			printf("\nMessage sent!");
	} while(1);
	
	shutdown(sid, SHUT_RDWR);
	close(sid);
	
	return 0;
}
