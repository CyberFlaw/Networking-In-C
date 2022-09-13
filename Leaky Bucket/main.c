#include <stdio.h>
#include <sys/types.h>

int main() 
{
	u_int incoming, outgoing, bucketSize, packetCount; 
	u_int store = 0;
	printf("Enter bucket size: ");
	scanf("%d", &bucketSize);
	printf("Enter outgoing rate: ");
	scanf("%d", &outgoing);
	printf("Enter number of packets to be sent: ");
	scanf("%d", &packetCount);
	
	while (packetCount != 0)
	{
		printf("Enter the size of incoming packet: ");
		scanf("%d", &incoming);
		
		if (incoming <= bucketSize)
		{
			store += incoming;
			printf("Bucket buffer %d out of %d \n", store, bucketSize);
		}	
		else
		{	
			printf("[Bucket Overflow]: Packet droped; The incoming packet size exceeds the buffer size \n");
			printf("Discarded %d out of %d of incoming packet \n", (incoming - store), incoming);
			
			store = bucketSize;
			printf("Bucket buffer %d out of %d \n", store, bucketSize);
		}
		
		store -= outgoing;
		printf("Bucket buffer %d out of %d after one cycle \n", store, bucketSize);
		
		packetCount--;		
	}
	
	return 0;
}




