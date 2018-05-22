#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>	/* exit() warnings */
#include <string.h>	/* memset warnings */
#include <unistd.h>
#include <arpa/inet.h>


#define BUF_SIZE	1024
#define SERVER_IP	"127.0.0.1"
#define	SERVER_PORT	60000

int main(int argc, char *argv[]){
    int			sock_send;
    struct sockaddr_in	addr_send;
    char			text[80],buf[BUF_SIZE];
    int			send_len,bytes_sent;
    
    
    void getPlayerMove() { 
	// This function places the x and y coordinates from the client on the grid 
		char choice[5];
    	int x, y;
    	char* letter;
    
    	printf("Enter \"quit\" to end the game or \"play\":\n");
    	scanf("%s", choice);
    
    	if (strcmp(choice,"quit") == 0){
        	close(sock_recv);
        	//break;
    	}
    	
    	if(strcmp(choice,"play") == 0)
    	{
    		printf("Enter letter to play \n");
    		scanf("%s", letter);
			printf("Enter your x and y coordinates respectively(Example: 3 4):\n");
        	scanf("%d %d", &x, &y);	
        	makePlay(x,y,letter);
        	drawBoard();
		}
	}
        /* create socket for sending data */
    sock_send=socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock_send < 0){
        printf("socket() failed\n");
        exit(0);
    }

            /* fill the address structure for sending data */
    memset(&addr_send, 0, sizeof(addr_send));  /* zero out structure */
    addr_send.sin_family = AF_INET;  /* address family */
    addr_send.sin_addr.s_addr = inet_addr(SERVER_IP);
    addr_send.sin_port = htons((unsigned short)SERVER_PORT);

    while(1){
        printf("Send? ");
        //getPlayerMove();
        scanf("%s",text);
        if (strcmp(text,"quit") == 0)
            break;

        strcpy(buf,text);
        send_len=strlen(text);
        bytes_sent=sendto(sock_send, buf, send_len, 0,(struct sockaddr *) &addr_send, sizeof(addr_send));
        }

    close(sock_send);
}


