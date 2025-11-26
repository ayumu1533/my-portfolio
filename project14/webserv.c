#include <stdio.h>  // printf, perror, FILE, fdopen, fgetsで使用
#include <arpa/inet.h> //sockaddr_in,inetz_addr,htonsで使用
#include <string.h> //memsetで使用
#include <unistd.h> // read, close, sleep に使用
#include <sys/socket.h>//socket,connectで使用
#include <netinet/in.h> //sockaddr_inで使用
#include <stdlib.h> //exitで使用
#include <errno.h> // perroeで使用


int main(){

struct sockaddr_in serv_addr;
int sockfd,new_sockfd;
char buff[1024];

// ソケットを作る
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
	perror("socket");
	exit(1);
}

//socketオプション
	int flag = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(int)) ==-1) {
	perror("setsockopt");
	exit(1);
	}
	printf("1\n");
	// アドレスを作る
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);//自分自身
	serv_addr.sin_port = htons(80);//ポート番号

	// ソケットにアドレスを割り当てる
	if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        perror("bind");
        close(sockfd);
        exit(1);
    	}
	printf("2\n");
	// コネクション要求を待ち始めるよう指示
	if (listen(sockfd, 5) ==-1) {
        perror("listen");
        close(sockfd);
        exit(1);
   	}
	//クライアントを次々に受け付ける
	while(1){
	// 要求があったらそれを受け付ける (なければ待つ)
 	if ((new_sockfd = accept(sockfd, NULL, NULL)) == -1) {
        perror("accept");
        close(sockfd);
        exit(1);
    	}
	printf("3\n");
	// クライアントからデータを受け取る
	FILE *istream = fdopen(new_sockfd, "r+");
    	if (istream == NULL) {
      perror("fdopen");
      close(new_sockfd);
      close(sockfd);
   	exit(1);
     	}
    	printf("4\n");
      	// バッファリングを無効化：即時送信
    	setvbuf(istream, NULL, _IONBF, 0);
	
	int mode,len;
    	// データの読み取りと表示
    	//printf("クライアントからのデータ:\n");
    	while (1) {
        if (fgets(buff, sizeof(buff), istream) == 0) break;
        printf("%s", buff);
        if (strncmp(buff, "GET", 3) == 0) {
        	printf("5\n");
        	mode = 1;
          }
        if (strncmp(buff, "POST", 4) == 0) {
            printf("6\n");
            mode = 2;
          }
        if (strncmp(buff, "Content-Length:", 15) == 0) {
          	printf("7\n");
          	sscanf(buff,"Content-Length: %d",&len);
          }
        if(strcmp(buff,"\r\n")==0){
        	printf("8\n");
        	break;
          }
    }
    if(mode == 1) {
	    printf("9\n");
	    fprintf(istream, "HTTP/1.1 200 OK\r\n");
	    fprintf(istream, "Content-Type: text/html\r\n");
	    fprintf(istream, "\r\n");
	    fprintf(istream, "<form action='/post.html' method='post'>");
	    fprintf(istream, "address <input type='text' name='addr'>");
	    fprintf(istream, "<input type='submit' value='send'>");
	    fprintf(istream, "</form>");
     }
    if(mode == 2) {
	    printf("10\n");
	    fgets(buff,len+1, istream);
	    printf("11\n");
	    fprintf(istream, "HTTP/1.1 200 OK\r\n");
	    fprintf(istream, "\r\n");
	    fprintf(istream, "\"OK\"\r\n");
	    
     }
    
//ソケットを終了する
fclose(istream);

}
close(sockfd);

return 0;
}

