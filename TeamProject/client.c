#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>

#define PORT 5050
#define MAX_BUF 100

char get_name[MAX_BUF];
static int sock;
void all_connect();//접속
void *receive(void *arg);//메세지 수신 쓰레드
void *send_message(void *arg);//메시지 전송
void error_handling(char *messasge);
void first_connect(int port){

    struct sockaddr_in serv_addr;
    if((sock=socket(AF_INET,SOCK_STREAM,0))==-1){
        error_handling("socket() error");
    }

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family =AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    serv_addr.sin_port=htons(port);

    if(connect(sock,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr))==-1){
        error_handling("connect() error");
    }
}
void all_connect(int port){

    struct sockaddr_in serv_addr;

    pthread_t tid, tid1;
    void * thread_return;

    if((sock=socket(AF_INET,SOCK_STREAM,0))==-1){
        error_handling("socket() error");
    }

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family =AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    serv_addr.sin_port=htons(port);

    if(connect(sock,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr))==-1){
        error_handling("connect() error");
    }

    pthread_create(&tid,NULL,receive,NULL);
    pthread_create(&tid1,NULL,send_message,NULL);
    pthread_join(tid1, &thread_return);
    pthread_join(tid1, &thread_return);

}

void *receive(void *arg){

        char buf[MAX_BUF];
        while(1){
                memset(buf,0,MAX_BUF);
                if(recv(sock,buf,MAX_BUF,0)==-1){
            error_handling("socket() error");
                }
                if(buf[0]!=0){
                        printf("전달 받은 카톡내용 : %s\n",buf);
			            memset(buf,0,MAX_BUF);
                        }
        }
}

void *send_message(void *arg){
        char buf[MAX_BUF];
        char sub2_buf[MAX_BUF];
        char sub_buf[MAX_BUF];
        int len;
        char optionbuf[MAX_BUF];
        char optionbuf_sub[MAX_BUF];
        memset(buf,0,MAX_BUF);
        while(1)
        {
            fgets(sub_buf, MAX_BUF,stdin);
            
               if(!strcmp(sub_buf,"clear\n"))
               {
                   system("clear");
                   printf("옵션 발동. [청소하기]\n");
               }
               else if(!strcmp(sub_buf,"ls\n"))
               {
                   system("ls -l");
                   printf("옵션 발동. [파일보기]\n");
               }
               else if(!strcmp(sub_buf,"rm\n"))
               {
                   printf("옵션 발동. [파일 삭제] 삭제할 파일 명을 입력하시오.\n");
                   fgets(optionbuf, MAX_BUF, stdin);
                   sprintf(optionbuf_sub, "rm -ri %s", optionbuf);
                   system(optionbuf_sub);
               }
               else if(!strcmp(sub_buf,"mkdir\n"))
               {
                   printf("옵션 발동. [파일 생성] 생성할 파일 명을 입력하시오.\n");
                   fgets(optionbuf, MAX_BUF, stdin);
                   sprintf(optionbuf_sub, "mkdir -p %s", optionbuf);
                   system(optionbuf_sub);
               }
               else if(!strcmp(sub_buf,"cat\n"))
               {
                   printf("옵션 발동. [파일 읽기] 읽을 파일 명을 입력하시오.\n");
                   fgets(optionbuf, MAX_BUF, stdin);
                   sprintf(optionbuf_sub, "cat %s", optionbuf);
                   system(optionbuf_sub);
               }
               else if(!strcmp(sub_buf,"sudo apt-get install\n"))
               {
                   printf("옵션 발동. [패키지 설치] 설치할 패키지 명을 입력하시오.\n");
                       fgets(optionbuf, MAX_BUF, stdin);
                   sprintf(optionbuf_sub, "sudo apt-get install %s", optionbuf);
                   system(optionbuf_sub);
               }

               memset(optionbuf_sub,0,MAX_BUF);
               memset(optionbuf,0,MAX_BUF);

               if(sub_buf[0]!='\n'){
                   strcpy(sub2_buf,get_name);
                   sprintf(buf, "%s %s", sub2_buf, sub_buf);
                   len=strlen(buf);
                   if(send(sock,buf,len,0)!=len){
                       fprintf(stderr,"send failed\n");
                       exit(1);
                   }
               }
        }
}

void Room(int get_port){
    char buf[MAX_BUF];
    int len;

    memset(buf,0,MAX_BUF);
    strcpy(buf,"연결자 :  ");
    strcat(buf,get_name);
    len=strlen(buf);
    printf("단톡방에 들어왔습니다.  %s\n",buf);
    if(send(sock,buf,len,0)!=len){
        fprintf(stderr,"send failed\n");
        exit(1);
    }
    if(get_port==5060){
        printf("\t<<<여자친구 방>>>\n");
        all_connect(5060);
    }
    else if(get_port==5070){
        printf("\t<<<소공단톡 단톡>>>\n");
        all_connect(5070);
    }
    else if(get_port==5080){
        printf("\t<<<고딩친구 단톡>>>\n");
        all_connect(5080);
    }
    else if(get_port==5090){
        printf("\t<<<중딩친구 단톡>>>\n");
        all_connect(5090);
    }
    else if(get_port==5100){
        printf("\t<<<초딩친구 단톡>>>\n");
        all_connect(5100);
    }
    else if(get_port==5110){
        printf("\t<<<학원친구 단톡>>>\n");
        all_connect(5110);
    }
    else if(get_port==5120){
        printf("\t<<<부모님 단톡>>>\n");
        all_connect(5120);
    }
    else if(get_port==5130){
        printf("\t<<<동아리 단톡>>>\n");
        all_connect(5130);
    }
    else if(get_port==5140){
        printf("\t<<<대외활동 단톡>>>\n");
        all_connect(5140);
    }
    else if(get_port==5150){
        printf("\t<<<세컨드 단톡>>>\n");
        all_connect(5150);
    }
    else printf("\t잘못 입력하셨습니다.\n");
}

int main(int argc,char *argv[]){
    int first_port;
    int port;
    if(argc!=2){
        printf("Usage : %s <name>\n", argv[0]);
        exit(1);
    }
    printf("연결 포트 번호를 입력하라(5050)\n");
    scanf("%d", &first_port);
    if(first_port!=5050)
    {
        printf("연결 포트 번호를 확인하세요.\n");
        exit(1);
    }
    strcat(get_name,"[");
    strcat(get_name,argv[1]);
    strcat(get_name,"]");
	first_connect(first_port);

    printf("방의 포트 번호를 입력하라\n");
    printf(" 1. 여자친구(5060)\n 2. 소공단톡(5070)\n 3. 고딩친구(5080)\n 4. 중딩친구(5090)\n 5. 초딩친구(5100)\n 6. 학원친구(5110)\n 7. 부모님(5120)\n 8. 동아리(5130)\n 9. 대외활동(5140)\n 10. 세컨드(5150)\n");
    printf(">>");
    scanf("%d", &port);
    if(port!=5060 && port!=5070 && port!=5080 && port!=5090 && port!=5100 && port!=5110 && port!=5120 && port!=5130 && port!=5140 && port!=5150)
    {
        printf("방의 포트 번호를 확인하세요.\n");
        exit(1);
    }
    Room(port);

    return 0;
}
void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

