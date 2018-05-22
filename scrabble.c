#include <stdio.h>
#include <sys/types.h>	/* system type defintions */
#include <sys/socket.h>	/* network system functions */
#include <netinet/in.h>	/* protocol & struct definitions */
#include <stdlib.h>	/* exit() warnings */
#include <string.h>	/* memset warnings */
#include <arpa/inet.h>
#include <unistd.h>

#include <ctype.h>
#include <time.h>

#define BUF_SIZE	1024
#define LISTEN_PORT	60000

/*
* Rushane Barnes, 620097883
* Matthew Patterson, 620095960
* Cassandrae Campbell, 620320101
*/

typedef enum { false, true } bool; // custom boolean type

int main(int argc, char *argv[]){
    int	sock_recv;
    struct sockaddr_in	my_addr;
    int			i;
    fd_set	readfds,active_fd_set,read_fd_set;
    struct timeval		timeout={0,0};
    int			incoming_len;
    struct sockaddr_in	remote_addr;
    int			recv_msg_size;
    char			buf[BUF_SIZE];
    int			select_ret;
    
    // For manipulation of words.txt file
	char line[1024] ;
    FILE* fp = fopen("words.txt", "r") ;
    char checkWord[200]; 
    char * takeWord;
    
	// For searching in all 8 direction
    int x[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int y[] = { -1, 0, 1, -1, 1, -1, 0, 1 };  
    int k,j;
	int const NUM_RANGE=8;
	
    //global declaration structure grid
	char * grid[NUM_RANGE][NUM_RANGE];

    void getNewBoard(){
        //creates a brand new blank board. Returns a pointer to the array 
        for (j = 0; j < NUM_RANGE; j++){
            for (k = 0; k < NUM_RANGE; k++)
            {
                grid[k][j]="   ";
            }//Endfor
        }//Endfor
        return;
    }//EndFunction getNewBoard

	void drawBoard(){
    //This function prints out the board that was passed. Returns void
    char * const NLINE = "    1    2    3    4    5    6    7    8";
    char * const HLINE = "  +----+----+----+----+----+----+----+----+";
    char * const VLINE = "  |    |    |    |    |    |    |    |    |";

    printf("%s\n",NLINE);
    printf("%s\n",HLINE);
    for (j = 0; j < NUM_RANGE; j++)
    {  
        printf("%s\n",VLINE);
        printf("%d ",j+1);
        for (k = 0; k < NUM_RANGE; k++)
        {  if(strcmp(grid[k][j],"   ")==0){
                printf("| %s",grid[k][j]);
            }else{
                printf("| %s  ",grid[k][j]);
            }
        }
        printf("%s","|");
        printf("\n");
        printf("%s\n",VLINE);
        printf("%s\n",HLINE);
    }
    return;
	}//EndFunction drawBoard

   
	void makePlay(int x, int y, char* c){
   //Arrays are zero indexed but our grid starts at index 1
   		grid[x-1][y-1]=c;
   		return;
	}
	
	int calculateScore(char * word) { // calculate the score for a word
	 	int score = 0;
	 	int i,j, len;
	 	/*'A': 1, 'B': 3, 'C': 3, 'D': 2, 'E': 1, 'F': 4, 'G': 2, 'H': 4, 'I': 1, 'J': 8, 'K': 5, 'L': 1, 'M': 3, 'N': 1, 'O': 1, 'P': 3,
'Q': 10, 'R': 1, 'S': 1, 'T': 1, 'U': 1, 'V': 4, 'W': 4, 'X': 8, 'Y': 4, 'Z': 10 */
	 	len = strlen(word);
	 	for(i=0;i<len;i++) {
	 		switch(word[i])
	 		{
	 		   case 'A': score += 1;
            			 break;
        	   case 'B': score += 3;
                          break;
        	   case 'C': score += 3;
            			  break;
               case 'D': score += 2;
                          break;
               case 'E': score += 1;
                          break;
               case 'F': score += 4;
                         break;
               case 'G': score += 2;
                         break;
               case 'H': score += 4;
                         break;
               case 'I': score += 1;
                         break;
               case 'J': score += 8;
                         break;
               case 'K': score += 1;
                         break;
               case 'L': score += 5;
                         break;
               case 'M': score += 3;
                         break;
               case 'N': score += 1;
                         break;
               case 'O': score += 1;
                         break;
               case 'P': score += 3;
                         break;
               case 'Q': score += 10;
                         break;
               case 'R': score += 1;
                         break;
                case 'S': score += 1;
                         break;
                case 'T': score += 1;
                         break;
                case 'U': score += 1;
                         break;
                case 'V': score += 4;
                         break;
                case 'W': score += 4;
                         break;
                case 'X': score += 8;
                         break;
                case 'Y': score += 4;
                         break;
                case 'Z': score += 10;
                		  break;
               default:
                      printf("error, enter a letter\n");
                      break;  	
			} // end switch
		 } //end for
		 return score;
	} // end calculateScore function 
	
	  bool searchGrid(char * grid[NUM_RANGE][NUM_RANGE], int row, int col, char * word)
    {
    // If first character of word doesn't match with
    // given starting point in grid.
         if (*grid[row][col] != word[0])
              return false;
 
    	 int len = strlen(word);
    	 int dir;
 
         // Search word in all 8 directions starting from (row,col)
    	for (dir = 0; dir < 8; dir++)
    	{
        // Initialize starting point for current direction
        	int k, rd = row + x[dir], cd = col + y[dir];
 
        // First character is already checked, match remaining
        // characters
        	for (k = 1; k < len; k++)
        	{
            	// If out of bound break
            	if (rd >= NUM_RANGE || rd < 0 || cd >= NUM_RANGE || cd < 0)
                	break;
 
            	// If not matched,  break
            	if (*grid[rd][cd] != word[k])
                	break;
 
            //  Moving in particular direction
            	rd += x[dir], cd += y[dir];
        	}
 
        	// If all character matched, then value of must
        	// be equal to length of word
        	if (k == len)
            	return true;
    	} // end for
        return false;
    } // end function
	
	 int wordSearch(char * grid[NUM_RANGE][NUM_RANGE], char * word) //  searches for word in the grid
    {
    // Consider every point as starting point and search
    // given word
       int row,col;
       int ans;
       //char ;
       for (row = 0; row < NUM_RANGE; row++)
           for (col = 0; col < NUM_RANGE; col++)
                if (searchGrid(grid, row, col, word))
                    //printf("Word %s found at %d, %d\n",word,row+1,col+1);
                    ans = calculateScore(word);
                    //strcpy(takeWord, word);
                    //return word;
        return ans;
    } // end function
	
	void getScore() // gets score of player if word on the grid is valid
	{
		int b = 0;
	    while(fscanf(fp, "%s", checkWord) != EOF)
        {
    	   if(strlen(checkWord)>=4) { // checking if length of word in dictionary is greater than or equal to 4
    		   b = wordSearch(grid, checkWord); // checks if what is in the dictionary is on the grid
		    }
       } 
       printf("Player Score: %d\n",b); 
	}
		
	
	
	
	
	int isOnBoard(int x, int y){ // checks if x and y coordinates are on the board
    	int i,k;
    
    	for(i=0; i<NUM_RANGE;i++){
        	for(k=0; k<NUM_RANGE;k++){
            	if(x==i && y==k){
                	return 1;
            	}	
			else{
                	return 0;
            	}
        	}
    	}
    } 
    
    void startBoard(){ /*  randomly position 10 letters on the board. */
	    //srand(time(NULL));
	    
        makePlay(rand() % 8 + 1,rand() % 8 + 1,"A"); // 1 
		makePlay(rand() % 8 + 1,rand() % 8 + 1,"R"); // 2
		makePlay(rand() % 8 + 1,rand() % 8 + 1,"D"); // 3
		makePlay(rand() % 8 + 1,rand() % 8 + 1,"E"); // 4
		makePlay(rand() % 8 + 1,rand() % 8 + 1,"G"); // 5
		makePlay(rand() % 8 + 1,rand() % 8 + 1,"T"); // 6
		makePlay(rand() % 8 + 1,rand() % 8 + 1,"E"); // 7
		makePlay(rand() % 8 + 1,rand() % 8 + 1,"N"); // 8
		makePlay(rand() % 8 + 1,rand() % 8 + 1,"O"); // 9
		makePlay(rand() % 8 + 1,rand() % 8 + 1,"Z"); // 10	
    }
    
  
     
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
			printf("Enter x and y coordinates respectively(Eg. 3 4 - 3 represent column, 4 represents row):\n");
        	scanf("%d%d", &x, &y);	
        	makePlay(x,y,letter);
        	drawBoard();
        	getScore();
		}
	}

	
	
	getNewBoard();
    //Displaying empty board
    printf("\n%s\n\n","Printing Scrabble Board....");
    //drawBoard();
    //making two plays
    startBoard();
    drawBoard();
    printf("/****Rules******/\n");
    printf("Client side enters \"play\"\n");
    printf("On the server side, client enters letter and xy coordinates\n");
    //printf("/***************/");
    
	//wordSearch(grid, "td");
    //printf("\n%s\n\n","RePrinting board after plays....");
    //redrawing the board with plays shown
    //drawBoard();


            /* create socket for receiving */
    sock_recv=socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock_recv < 0){
        printf("socket() failed\n");
        exit(0);
    }
        /* make local address structure */
    memset(&my_addr, 0, sizeof (my_addr));	/* zero out structure */
    my_addr.sin_family = AF_INET;	/* address family */
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);  /* current machine IP */
    my_addr.sin_port = htons((unsigned short)LISTEN_PORT);
        /* bind socket to the local address */
    i=bind(sock_recv, (struct sockaddr *) &my_addr, sizeof (my_addr));
    if (i < 0){
        printf("bind() failed\n");
        exit(0);
    }
       FD_ZERO(&readfds);		/* zero out socket set */
       FD_SET(sock_recv,&readfds);	/* add socket to listen to */
        /* listen ... */
    while (1){
        read_fd_set = active_fd_set;
        select_ret=select(sock_recv+1,&readfds,NULL,NULL,NULL);
        /*select_ret=select(sock_recv+1,&readfds,NULL,NULL,&timeout);*/
        if (select_ret > 0){		/* anything arrive on any socket? */
            /*puts("I received something");*/
            incoming_len=sizeof(remote_addr);	/* who sent to us? */
            recv_msg_size=recvfrom(sock_recv,buf,BUF_SIZE,0,(struct sockaddr *)&remote_addr,&incoming_len);
           /*puts("After receiving...");*/
            if (recv_msg_size > 0){	/* what was sent? */
                buf[recv_msg_size]='\0';
              /*puts("After receiving2...");*/
              char bob[20] = "Player";
                //printf("From %s received: %s\n",inet_ntoa(remote_addr.sin_addr),buf);
                printf("From %s received: %s\n",bob,buf);
                /*printf("From  received:%s \n",buf);*/
                 /*puts("After receiving3...");*/
             }
            }
        if (strcmp(buf,"play") == 0)
             getPlayerMove();
        
        if (strcmp(buf,"quit") == 0)
            break;

    }

    close(sock_recv);
}
