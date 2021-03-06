#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>

#define PORT_NUM 5050//포트 번호
#define BACKLOG 20//연결 요청 대기 큐의 크기
#define MAX_BUF 100//버퍼 크기
#define TRUE 1
#define FALSE 0
/*
typedef struct _Data {
    GtkWidget *window1;//frame
    GtkWidget *button1;//
    GtkWidget *entry1;// 입력
    GtkWidget *textview1;//textview
}Data;
*/
void *first_receive(void *arg);//첫번째 연결
void error_handling(char *message);//에러처리 함수

void *receive_1room(void *arg);//방 쓰레드 함수
void *receive_2room(void *arg);
void *receive_3room(void *arg);
void *receive_4room(void *arg);
void *receive_5room(void *arg);
void *receive_6room(void *arg);
void *receive_7room(void *arg);
void *receive_8room(void *arg);
void *receive_9room(void *arg);
void *receive_10room(void *arg);

void send_1room(char *msg);//받은 메세지를 보내는 함수
void send_2room(char *msg);
void send_3room(char *msg);
void send_4room(char *msg);
void send_5room(char *msg);
void send_6room(char *msg);
void send_7room(char *msg);
void send_8room(char *msg);
void send_9room(char *msg);
void send_10room(char *msg);

void setnonblockingmode(int sock);//넌블럭
void kakaotalk_Room();//방

pthread_mutex_t mutx;//뮤텍스
static int serv_clnt_sock[MAX_BUF];//서버 소켓
static int clnt_sock[10][MAX_BUF];//연결된 소켓을 저장하기 위한 배열
int clnt_serv_num=0;

int clnt_sock_num=0;//연결 요청 대기큐에서 만들어질 클라이언트 소켓
int clnt_sock_num1=0;
int clnt_sock_num2=0;
int clnt_sock_num3=0;
int clnt_sock_num4=0;
int clnt_sock_num5=0;
int clnt_sock_num6=0;
int clnt_sock_num7=0;
int clnt_sock_num8=0;
int clnt_sock_num9=0;

/*
G_MODULE_EXPORT void
quit1(GtkWidget *window,gpointer data){
    gtk_widget_destroy(window);
}
*/


void setnonblockingmode(int sock)//넌 블럭
{
    int flag=fcntl(sock, F_GETFL, 0);//소켓의 옵션을 얻음
    fcntl(sock, F_SETFL, flag|O_NONBLOCK);//소켓의 옵션을 변경
}

void *first_receive(void *arg){//접속
	char buf[MAX_BUF];
	int i;
	int check;
	while(1){
	        memset(buf,0,MAX_BUF);//버퍼 초기화
		i=0;
		while(i<=clnt_serv_num+1){
			check=recv(serv_clnt_sock[i],buf,MAX_BUF,0);//메세지 받음
			setnonblockingmode(serv_clnt_sock[i]);//넌 블럭
			if(check==-1){
				i++;
				continue;//메세지를 잘못 받으면 다음 것을 받기 위한 continue문
			}
			else if(buf[0]!=0){//버퍼가 비어있지 않으면 다음 소켓으로 감
				i++;
				}
		}
	}
}
void *receive_1room(void *arg){//첫번째 방
	
	char buf[MAX_BUF];
	int i;
    int check;
    while(1){
        memset(buf,0,MAX_BUF);//버퍼 비움
        i=0;
        while(i<=clnt_sock_num+1){
            check=recv(clnt_sock[0][i],buf,MAX_BUF,0);//클라이언트로부터 메세지를 받음
            setnonblockingmode(clnt_sock[0][i]);//넌 블럭
			if(check==-1){
				i++;
				continue;
			}
			else if(buf[0]!=0){

				send_1room(buf);
				memset(buf,0,MAX_BUF);
				i++;
				}
		}
	}
}
void *receive_2room(void *arg){//2
		
	char buf[MAX_BUF];
	int i;
    int check;
    while(1){
        memset(buf,0,MAX_BUF);
        i=0;
        while(i<=clnt_sock_num1+1){
            check=recv(clnt_sock[1][i],buf,MAX_BUF,0);
            setnonblockingmode(clnt_sock[1][i]);

			if(check==-1){
				i++;
				continue;
			}
			else if(buf[0]!=0){
				
				send_2room(buf);
				memset(buf,0,MAX_BUF);
				i++;
				}
		}
	}
}
void *receive_3room(void *arg){//3
	
	char buf[MAX_BUF];
	int i;
    int check;
    while(1){
        memset(buf,0,MAX_BUF);
        i=0;
        while(i<=clnt_sock_num2+1){
            check=recv(clnt_sock[2][i],buf,MAX_BUF,0);
            setnonblockingmode(clnt_sock[2][i]);

            if(check==-1){
                i++;
				continue;
			}
			else if(buf[0]!=0){
				
				send_3room(buf);
				memset(buf,0,MAX_BUF);
				i++;
				}
		}
	}
}
void *receive_4room(void *arg){//4

    char buf[MAX_BUF];
    int i;
    int check;
    while(1){
        memset(buf,0,MAX_BUF);
        i=0;
        while(i<=clnt_sock_num3+1){
            check=recv(clnt_sock[3][i],buf,MAX_BUF,0);
            setnonblockingmode(clnt_sock[3][i]);

            if(check==-1){
                i++;
                continue;
            }
            else if(buf[0]!=0){

                send_4room(buf);
                memset(buf,0,MAX_BUF);
                i++;
            }
        }
    }
}

void *receive_5room(void *arg){//5

    char buf[MAX_BUF];
    int i;
    int check;
    while(1){
        memset(buf,0,MAX_BUF);
        i=0;
        while(i<=clnt_sock_num4+1){
            check=recv(clnt_sock[4][i],buf,MAX_BUF,0);
            setnonblockingmode(clnt_sock[4][i]);

            if(check==-1){
                i++;
                continue;
            }
            else if(buf[0]!=0){

                send_5room(buf);
                memset(buf,0,MAX_BUF);
                i++;
            }
        }
    }
}

void *receive_6room(void *arg){//6

    char buf[MAX_BUF];
    int i;
    int check;
    while(1){
        memset(buf,0,MAX_BUF);
        i=0;
        while(i<=clnt_sock_num5+1){
            check=recv(clnt_sock[5][i],buf,MAX_BUF,0);
            setnonblockingmode(clnt_sock[5][i]);
            if(check==-1){
                i++;
                continue;
            }
            else if(buf[0]!=0){

                send_6room(buf);
                memset(buf,0,MAX_BUF);
                i++;
            }
        }
    }
}

void *receive_7room(void *arg){//7

    char buf[MAX_BUF];
    int i;
    int check;
    while(1){
        memset(buf,0,MAX_BUF);
        i=0;
        while(i<=clnt_sock_num6+1){
            check=recv(clnt_sock[6][i],buf,MAX_BUF,0);
            setnonblockingmode(clnt_sock[6][i]);

            if(check==-1){
                i++;
                continue;
            }
            else if(buf[0]!=0){

                send_7room(buf);
                memset(buf,0,MAX_BUF);
                i++;
            }
        }
    }
}

void *receive_8room(void *arg){//8

    char buf[MAX_BUF];
    int i;
    int check;
    while(1){
        memset(buf,0,MAX_BUF);
        i=0;
        while(i<=clnt_sock_num7+1){
            check=recv(clnt_sock[7][i],buf,MAX_BUF,0);
            setnonblockingmode(clnt_sock[7][i]);

            if(check==-1){
                i++;
                continue;
            }
            else if(buf[0]!=0){

                send_8room(buf);
                memset(buf,0,MAX_BUF);
                i++;
            }
        }
    }
}

void *receive_9room(void *arg){//9

    char buf[MAX_BUF];
    int i;
    int check;
    while(1){
        memset(buf,0,MAX_BUF);
        i=0;
        while(i<=clnt_sock_num8+1){
            check=recv(clnt_sock[8][i],buf,MAX_BUF,0);
            setnonblockingmode(clnt_sock[8][i]);

            if(check==-1){
                i++;
                continue;
            }
            else if(buf[0]!=0){

                send_9room(buf);
                memset(buf,0,MAX_BUF);
                i++;
            }
        }
    }
}

void *receive_10room(void *arg){//10

    char buf[MAX_BUF];
    int i;
    int check;
    while(1){
        memset(buf,0,MAX_BUF);
        i=0;
        while(i<=clnt_sock_num9+1){
            check=recv(clnt_sock[9][i],buf,MAX_BUF,0);
            setnonblockingmode(clnt_sock[9][i]);
            if(check==-1){
                i++;
                continue;
            }
            else if(buf[0]!=0){

                send_10room(buf);
                memset(buf,0,MAX_BUF);
                i++;
            }
        }
    }
}
void send_1room(char* msg){//받은 메세지를 보내는 함수

	char buf[MAX_BUF];//버퍼

	int len;
	int i=0;
	
	memset(buf,0,MAX_BUF);//버퍼 초기화
	strcpy(buf,msg);//받은 메세지를 버퍼배열에 복사
	
	len=strlen(buf);
	pthread_mutex_lock(&mutx);//동기화 시작
		for(i=0;i<clnt_sock_num;i++){
			if(send(clnt_sock[0][i],buf,len,0)!=len){//전송
				fprintf(stderr,"실패");
			}
			else{ 
			printf("%d 번째의 연결자에게 전송했습니다.\n",i+1);//터미널에 보여줌
			}
		}
    pthread_mutex_unlock(&mutx);//동기화 끝
}
void send_2room(char* msg){//2

	char buf[MAX_BUF];

	int len;
	int i=0;
	
	memset(buf,0,MAX_BUF);
	strcpy(buf,msg);
	len=strlen(buf);
    pthread_mutex_lock(&mutx);
		for(i=0;i<clnt_sock_num1;i++){
			if(send(clnt_sock[1][i],buf,len,0)!=len){
				fprintf(stderr,"실패");
			}
			else{
			printf("%d 번째의 연결자에게 전송했습니다.\n",i+1);
			}
		}
    pthread_mutex_unlock(&mutx);
}
void send_3room(char* msg){//3

	char buf[MAX_BUF];

	int len;
	int i=0;
	
	memset(buf,0,MAX_BUF);
	strcpy(buf,msg);
	len=strlen(buf);
	pthread_mutex_lock(&mutx);
		for(i=0;i<clnt_sock_num2;i++){
			if(send(clnt_sock[2][i],buf,len,0)!=len){
				fprintf(stderr,"실패");
			}
			else{
			printf("%d 번째의 연결자에게 전송했습니다.\n",i+1);
			}
		}
    pthread_mutex_unlock(&mutx);
}

void send_4room(char* msg){//4

    char buf[MAX_BUF];

    int len;
    int i=0;

    memset(buf,0,MAX_BUF);
    strcpy(buf,msg);

    len=strlen(buf);
    pthread_mutex_lock(&mutx);
    for(i=0;i<clnt_sock_num3;i++){
        if(send(clnt_sock[3][i],buf,len,0)!=len){
            fprintf(stderr,"실패");
        }
        else{
			printf("%d 번째의 연결자에게 전송했습니다.\n",i+1);
        }
    }
    pthread_mutex_unlock(&mutx);
}

void send_5room(char* msg){//5

    char buf[MAX_BUF];

    int len;
    int i=0;

    memset(buf,0,MAX_BUF);
    strcpy(buf,msg);

    len=strlen(buf);
    pthread_mutex_lock(&mutx);
    for(i=0;i<clnt_sock_num4;i++){
        if(send(clnt_sock[4][i],buf,len,0)!=len){
            fprintf(stderr,"실패");
        }
        else{
			printf("%d 번째의 연결자에게 전송했습니다.\n",i+1);
        }
    }
    pthread_mutex_unlock(&mutx);
}

void send_6room(char* msg){//6

    char buf[MAX_BUF];

    int len;
    int i=0;

    memset(buf,0,MAX_BUF);
    strcpy(buf,msg);

    len=strlen(buf);
    pthread_mutex_lock(&mutx);
    for(i=0;i<clnt_sock_num5;i++){
        if(send(clnt_sock[5][i],buf,len,0)!=len){
            fprintf(stderr,"실패");
        }
        else{
			printf("%d 번째의 연결자에게 전송했습니다.\n",i+1);
        }
    }
    pthread_mutex_unlock(&mutx);
}

void send_7room(char* msg){//7

    char buf[MAX_BUF];

    int len;
    int i=0;

    memset(buf,0,MAX_BUF);
    strcpy(buf,msg);

    len=strlen(buf);
    pthread_mutex_lock(&mutx);
    for(i=0;i<clnt_sock_num6;i++){
        if(send(clnt_sock[6][i],buf,len,0)!=len){
            fprintf(stderr,"실패");
        }
        else{
			printf("%d 번째의 연결자에게 전송했습니다.\n",i+1);
        }
    }
    pthread_mutex_unlock(&mutx);
}

void send_8room(char* msg){//8

    char buf[MAX_BUF];

    int len;
    int i=0;

    memset(buf,0,MAX_BUF);
    strcpy(buf,msg);

    len=strlen(buf);
    pthread_mutex_lock(&mutx);
    for(i=0;i<clnt_sock_num7;i++){
        if(send(clnt_sock[7][i],buf,len,0)!=len){
            fprintf(stderr,"실패");
        }
        else{
			printf("%d 번째의 연결자에게 전송했습니다.\n",i+1);
        }
    }
    pthread_mutex_unlock(&mutx);
}

void send_9room(char* msg){//9

    char buf[MAX_BUF];

    int len;
    int i=0;

    memset(buf,0,MAX_BUF);
    strcpy(buf,msg);

    len=strlen(buf);
    pthread_mutex_lock(&mutx);
    for(i=0;i<clnt_sock_num8;i++){
        if(send(clnt_sock[8][i],buf,len,0)!=len){
            fprintf(stderr,"실패");
        }
        else{
			printf("%d 번째의 연결자에게 전송했습니다.\n",i+1);
        }
    }
    pthread_mutex_unlock(&mutx);
}

void send_10room(char* msg){//10

    char buf[MAX_BUF];

    int len;
    int i=0;

    memset(buf,0,MAX_BUF);
    strcpy(buf,msg);

    len=strlen(buf);
    pthread_mutex_lock(&mutx);
    for(i=0;i<clnt_sock_num9;i++){
        if(send(clnt_sock[9][i],buf,len,0)!=len){
            fprintf(stderr,"실패");
        }
        else{
			printf("%d 번째의 연결자에게 전송했습니다.\n",i+1);
        }
    }
    pthread_mutex_unlock(&mutx);
}
void kakaotalk_Room(){//카카오톡방
    int option;
    socklen_t optlen;
    int serv_sock[10];//서버 소켓

	int status=-1;//쓰레드
	int status1=-1;
	int status2=-1;
	int status3=-1;
	int status4=-1;
	int status5=-1;
	int status6=-1;
	int status7=-1;
	int status8=-1;
	int status9=-1;

	int i=0;
    int count=0;
	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	char buf[MAX_BUF];
	int clnt_adr_sz;

	pthread_t tid;
	pthread_t tid1;
	pthread_t tid2;
	pthread_t tid3;
	pthread_t tid4;
	pthread_t tid5;
	pthread_t tid6;
	pthread_t tid7;
    pthread_t tid8;
    pthread_t tid9;

    optlen=sizeof(option);
    option=TRUE;//옵션 변경

    for(count=0;count<=10;count++){	
        if((serv_sock[count]=socket(AF_INET,SOCK_STREAM,0))==-1){
            error_handling("socket() error");
        }
        setsockopt(serv_sock[count],SOL_SOCKET,SO_REUSEADDR,(void*)&option, optlen);
        //타임 웨이트room
        memset(&serv_addr,0,sizeof(serv_addr));
        serv_addr.sin_family=AF_INET;
        serv_addr.sin_port=htons(PORT_NUM+(count+1)*10);//소켓 포트번호 설정
        serv_addr.sin_addr.s_addr=INADDR_ANY;//자신의 아이피 주소로 초기화

	if(bind(serv_sock[count],(struct sockaddr *)&serv_addr, sizeof(struct sockaddr))==-1){	
        error_handling("bind() error");//저장된 주소로 설정
			}
	

	if(listen(serv_sock[count],BACKLOG)==-1){//연결 대기 요청 큐를 만들어 대기함
        error_handling("listen() error");
			
	}}

	
	while(1){
		int clnt_sock1;
		int clnt_sock2;
		int clnt_sock3;
		int clnt_sock4;
		int clnt_sock5;
		int clnt_sock6;
		int clnt_sock7;
        int clnt_sock8;
        int clnt_sock9;
        int clnt_sock10;
        clnt_adr_sz= sizeof(struct sockaddr_in);

       
		setnonblockingmode(serv_sock[0]);//넌블럭
		setnonblockingmode(serv_sock[1]);
		setnonblockingmode(serv_sock[2]);
		setnonblockingmode(serv_sock[3]);
		setnonblockingmode(serv_sock[4]);
		setnonblockingmode(serv_sock[5]);
		setnonblockingmode(serv_sock[6]);
		setnonblockingmode(serv_sock[7]);
		setnonblockingmode(serv_sock[8]);
		setnonblockingmode(serv_sock[9]);
        


		clnt_sock1=accept(serv_sock[0],(struct sockaddr*)&clnt_addr,&clnt_adr_sz);
		clnt_sock2=accept(serv_sock[1],(struct sockaddr*)&clnt_addr,&clnt_adr_sz);
		clnt_sock3=accept(serv_sock[2],(struct sockaddr*)&clnt_addr,&clnt_adr_sz);
		clnt_sock4=accept(serv_sock[3],(struct sockaddr*)&clnt_addr,&clnt_adr_sz);
		clnt_sock5=accept(serv_sock[4],(struct sockaddr*)&clnt_addr,&clnt_adr_sz);
		clnt_sock6=accept(serv_sock[5],(struct sockaddr*)&clnt_addr,&clnt_adr_sz);
		clnt_sock7=accept(serv_sock[6],(struct sockaddr*)&clnt_addr,&clnt_adr_sz);
		clnt_sock8=accept(serv_sock[7],(struct sockaddr*)&clnt_addr,&clnt_adr_sz);
		clnt_sock9=accept(serv_sock[8],(struct sockaddr*)&clnt_addr,&clnt_adr_sz);
		clnt_sock10=accept(serv_sock[9],(struct sockaddr*)&clnt_addr,&clnt_adr_sz);
		
        if(status!=0){//쓰레드
			status=pthread_create(&tid,NULL,receive_1room,NULL);
		}
        pthread_detach(tid);

		if(status1!=0){
			status1=pthread_create(&tid1,NULL,receive_2room,NULL);
		}
        pthread_detach(tid1);

		if(status2!=0){
			status2=pthread_create(&tid2,NULL,receive_3room,NULL);
		}
        pthread_detach(tid2);

        if(status3!=0){
            status3=pthread_create(&tid3,NULL,receive_4room,NULL);
        }
        pthread_detach(tid3);


        if(status4!=0){
            status4=pthread_create(&tid4,NULL,receive_5room,NULL);
        }
        pthread_detach(tid4);


        if(status5!=0){
            status5=pthread_create(&tid5,NULL,receive_6room,NULL);
        }
        pthread_detach(tid5);

        if(status6!=0){
            status6=pthread_create(&tid6,NULL,receive_7room,NULL);
        }
        pthread_detach(tid6);

        if(status7!=0){
            status7=pthread_create(&tid7,NULL,receive_8room,NULL);
        }
        pthread_detach(tid7);

        if(status8!=0){
            status8=pthread_create(&tid8,NULL,receive_9room,NULL);
        }
        pthread_detach(tid8);

        if(status9!=0){
            status9=pthread_create(&tid9,NULL,receive_10room,NULL);
        }
        pthread_detach(tid9);
        
        if(clnt_sock1!=-1){
                    pthread_mutex_lock(&mutx);//동기화 시작
			clnt_sock[0][clnt_sock_num]=clnt_sock1;//새로 만든 클라이언트 소켓을 새로운 배열에 저장
                    pthread_mutex_unlock(&mutx);//동기화 끝
 	     		clnt_sock_num=clnt_sock_num+1;//그 다음 소켓을 저장하기 위함
		}
		if(clnt_sock2!=-1){
			                      
                    pthread_mutex_lock(&mutx);
			clnt_sock[1][clnt_sock_num1]=clnt_sock2;
                    pthread_mutex_unlock(&mutx);
			clnt_sock_num1=clnt_sock_num1+1;
			}
		if(clnt_sock3!=-1){
			        
                    pthread_mutex_lock(&mutx);
			clnt_sock[2][clnt_sock_num2]=clnt_sock3;
                    pthread_mutex_unlock(&mutx);
			clnt_sock_num2=clnt_sock_num2+1;

			}

        if(clnt_sock4!=-1){
            pthread_mutex_lock(&mutx);
            clnt_sock[3][clnt_sock_num3]=clnt_sock4;
            pthread_mutex_unlock(&mutx);
            clnt_sock_num3=clnt_sock_num3+1;
        }

        if(clnt_sock5!=-1){
            pthread_mutex_lock(&mutx);
            clnt_sock[4][clnt_sock_num4]=clnt_sock5;
            pthread_mutex_unlock(&mutx);
            clnt_sock_num4=clnt_sock_num4+1;
        }

        if(clnt_sock6!=-1){
            pthread_mutex_lock(&mutx);
            clnt_sock[5][clnt_sock_num5]=clnt_sock6;
            pthread_mutex_unlock(&mutx);
            clnt_sock_num5=clnt_sock_num5+1;
        }


        if(clnt_sock7!=-1){
            pthread_mutex_lock(&mutx);
            clnt_sock[6][clnt_sock_num6]=clnt_sock7;
            pthread_mutex_unlock(&mutx);
            clnt_sock_num6=clnt_sock_num6+1;
        }


        if(clnt_sock8!=-1){
            pthread_mutex_lock(&mutx);
            clnt_sock[7][clnt_sock_num7]=clnt_sock8;
            pthread_mutex_unlock(&mutx);
            clnt_sock_num7=clnt_sock_num7+1;
        }


        if(clnt_sock9!=-1){
            pthread_mutex_lock(&mutx);
            clnt_sock[8][clnt_sock_num8]=clnt_sock9;
            pthread_mutex_unlock(&mutx);
            clnt_sock_num8=clnt_sock_num8+1;
        }


        if(clnt_sock10!=-1){
            pthread_mutex_lock(&mutx);
            clnt_sock[9][clnt_sock_num9]=clnt_sock10;
            pthread_mutex_unlock(&mutx);
            clnt_sock_num9=clnt_sock_num9+1;
        }
        	}

}
int main(int argc, char *argv[]){
/*
    GtkBuilder *builder;
    Data *data;
    gtk_init(&argc,&argv);
    builder=gtk_builder_new();
    gtk_builder_add_from_file(builder,"server.glade",NULL);
    data=g_slice_new(Data);
    data->window1 = GTK_WIDGET(gtk_builder_get_object(builder,"window1"));//fram
    data->button1 = GTK_WIDGET(gtk_builder_get_object(builder,"button1"));//
    data->entry1 = GTK_WIDGET(gtk_builder_get_object(builder,"entry1"));//대화명
    data->textview1 = GTK_WIDGET(gtk_builder_get_object(builder,"textview1"));//내용
    gtk_builder_connect_signals(builder,data);
    g_object_unref(G_OBJECT(builder));
    gtk_widget_show_all(data->window1);
    gtk_main();
    g_slice_free(Data,data);
*/

	int serv_sock;
	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	char buf[MAX_BUF];
    int status=-1;
	int clnt_adr_sz;
    int option;
    socklen_t optlen;
	pthread_t tid;
    pthread_mutex_init(&mutx,NULL);

	if((serv_sock=socket(AF_INET,SOCK_STREAM,0))==-1){
        error_handling("socket() error");
	}
    optlen=sizeof(option);
    option=TRUE;
    setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, (void*)&option, optlen);
    //타임 웨이트 first 강건성 처리
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(PORT_NUM);
	serv_addr.sin_addr.s_addr=INADDR_ANY;
    
	if(bind(serv_sock,(struct sockaddr *)&serv_addr, sizeof(struct sockaddr))==-1){	
        error_handling("bind() error");
			}

	

	if(listen(serv_sock,BACKLOG)==-1){
        error_handling("listen() error");
	}
	kakaotalk_Room();//카카오톡 방 생성

	while(1){
		clnt_adr_sz= sizeof(struct sockaddr_in);
		if((serv_clnt_sock[clnt_serv_num]=accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_adr_sz))==-1){
				perror("accept");
				continue; }
                else{
	
 	     		clnt_serv_num=clnt_serv_num+1;
			if(status!=0)
				status = pthread_create(&tid,NULL,first_receive,serv_clnt_sock);//쓰레드 생성
        pthread_detach(tid);

		}

	}
    return 0;
}

void error_handling(char *message)//에러처리 함수
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
