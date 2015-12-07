#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>

#define PORT 5050//포트번호
#define MAX_BUF 100//버퍼 크기

typedef struct _Data {//GTK위젯
    GtkWidget *window1;//frame
    GtkWidget *window2;//frame
    GtkWidget *window3;//frame
    GtkWidget *button;//romm button
    GtkWidget *button1;//name
    GtkWidget *button12;//send
    GtkWidget *entry1;// 대화명
    GtkWidget *entry2;// 입력
    GtkWidget *textview1;//textview
}Data;


char get_name[MAX_BUF];//이름 저장 배열
static int sock;//소켓
void all_connect();//접속
void *receive(void *arg);//메세지 수신 쓰레드
void *option(void *arg);//메세지 옵션(시스템 함수) 쓰레드
void error_handling(char *messasge);//에러 처리 함수


G_MODULE_EXPORT void//프레임 콜백 함수
quit1(GtkWidget *window,gpointer data){
        gtk_widget_destroy(window);
}
G_MODULE_EXPORT void//프레임 콜백 함수
quit2(GtkWidget *window,gpointer data){
            gtk_widget_destroy(window);
}
G_MODULE_EXPORT void//프레임 콜백 함수
quit3(GtkWidget *window,gpointer data){
            gtk_widget_destroy(window);
}

void first_connect(int port){//첫번째 방 연결
    struct sockaddr_in serv_addr;
    if((sock=socket(AF_INET,SOCK_STREAM,0))==-1){//소켓 생성
        error_handling("socket() error");
    }

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family =AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");//연결 아이피 주소
    serv_addr.sin_port=htons(port);//연결 포트번호

    if(connect(sock,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr))==-1){
        error_handling("connect() error");
    }
}
void all_connect(int port){//방 연결 함수

    struct sockaddr_in serv_addr;

    pthread_t tid, tid1;
    void * thread_return;

    if((sock=socket(AF_INET,SOCK_STREAM,0))==-1){//소켓 생성
        error_handling("socket() error");
    }

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family =AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");//연결 아이피 주소
    serv_addr.sin_port=htons(port);//연결 포트 번호

    if(connect(sock,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr))==-1){
        error_handling("connect() error");//연결
    }

    //pthread_create(&tid,NULL,receive,NULL);
    //pthread_create(&tid1,NULL,send_message,NULL);
    //pthread_join(tid1, &thread_return);
    //pthread_join(tid1, &thread_return);
}
void *option(void *arg){//메세지 옵션 함수
    char buf[MAX_BUF];
    char sub2_buf[MAX_BUF];
    char sub_buf[MAX_BUF];
    int len;
    char optionbuf[MAX_BUF];
    char optionbuf_sub[MAX_BUF];
    memset(buf,0,MAX_BUF);
    while(1)
    {
        fgets(sub_buf, MAX_BUF,stdin);//입력 받기
//시스템 오퍼레이션 함수 사용
        if(!strcmp(sub_buf,"---clear\n"))
        {
            system("clear");
            printf("옵션 발동. [청소하기]\n");
        }
        else if(!strcmp(sub_buf,"---pwd\n"))
        {
            system("pwd");
            printf("옵션 발동. [경로출력]\n");
        }
        else if(!strcmp(sub_buf,"---df\n"))
        {
            system("df");
            printf("옵션 발동. [디스크용량]\n");
        }

        else if(!strcmp(sub_buf,"---du\n"))
        {
            system("du");
            printf("옵션 발동. [디스크사용공간]\n");
        }
        else if(!strcmp(sub_buf,"---ps\n"))
        {
            system("ps");
            printf("옵션 발동. [프로세스확인]\n");
        }
        else if(!strcmp(sub_buf,"---ls\n"))
        {
            system("ls -l");
            printf("옵션 발동. [파일보기]\n");
        }
        else if(!strcmp(sub_buf,"---ifconfig\n"))
        {
            system("ifconfig");
            printf("옵션 발동. [네트워크확인]\n");
        }
        //동적으로 시스템 오퍼레이션 사용
        else if(!strcmp(sub_buf,"---rm\n"))
        {
            printf("옵션 발동. [파일 삭제] 삭제할 파일 명을 입력하시오.\n");
            fgets(optionbuf, MAX_BUF, stdin);
            sprintf(optionbuf_sub, "rm -ri %s", optionbuf);
            system(optionbuf_sub);
        }
        else if(!strcmp(sub_buf,"---mkdir\n"))
        {
            printf("옵션 발동. [파일 생성] 생성할 파일 명을 입력하시오.\n");
            fgets(optionbuf, MAX_BUF, stdin);
            sprintf(optionbuf_sub, "mkdir -p %s", optionbuf);
            system(optionbuf_sub);
        }
        else if(!strcmp(sub_buf,"---cat\n"))
        {
            printf("옵션 발동. [파일 읽기] 읽을 파일 명을 입력하시오.\n");
                fgets(optionbuf, MAX_BUF, stdin);
            sprintf(optionbuf_sub, "cat %s", optionbuf);
            system(optionbuf_sub);
        }
        else if(!strcmp(sub_buf,"---sudo apt-get install\n"))
        {
            printf("옵션 발동. [패키지 설치] 설치할 패키지 명을 입력하시오\n");
            fgets(optionbuf, MAX_BUF, stdin);
            sprintf(optionbuf_sub, "sudo apt-get install %s", optionbuf);
            system(optionbuf_sub);
        }
    }
}




void insert_text(gchar *text,GtkWidget *textview){//텍스트뷰에 입력 받기 하기 위한 함수

    GtkTextBuffer *tbuffer;
    GtkTextIter ei;
    tbuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));
    gtk_text_buffer_get_end_iter(tbuffer, &ei);
    gtk_text_buffer_insert(tbuffer, &ei, text, -1);
}
void *receive(void *arg){//메시지 받기 쓰레드

        char buf[MAX_BUF];
        Data *data=(Data *)arg;
        while(1){
                memset(buf,0,MAX_BUF);//버퍼 초기화
                if(recv(sock,buf,MAX_BUF,0)==-1){//메세지 받기
                    error_handling("socket() error");
                }
                if(buf[0]!=0){//버퍼가 비어있지 않다면
                    printf("전달 받은 카톡내용 : %s\n",buf);
                    insert_text(buf,(GtkWidget*)(data->textview1));//텍스트뷰로 전달
                    insert_text("\n",(GtkWidget*)(data->textview1));//텍스트뷰로 전달
                    memset(buf,0,MAX_BUF);
                }
        }
}
G_MODULE_EXPORT void
kakao_room(GtkWidget *button,Data *data){//카카오톡 방 
     char buf[MAX_BUF];
     int len;
    const char *num;

    memset(buf,0,MAX_BUF);
    strcpy(buf,"연결자 :  ");
    strcat(buf,get_name);
    len=strlen(buf);
    printf("단톡방에 들어왔습니다.  %s\n",buf);
    if(send(sock,buf,len,0)!=len){
        fprintf(stderr,"send failed\n");
        exit(1);
    }
    num=gtk_button_get_label(GTK_BUTTON(button));//레이블로 어떤 방인지 인식
//10개의 방
  if(!strcmp(num,"여자친구")){
        printf("\t<<<여자친구 방>>>\n");
        all_connect(5060);
    }
    else if(!strcmp(num,"소공친구")){
        printf("\t<<<소공단톡 단톡>>>\n");
        all_connect(5070);
    }
    else if(!strcmp(num,"고딩친구")){
        printf("\t<<<고딩친구 단톡>>>\n");
        all_connect(5080);
    }
    else if(!strcmp(num,"중딩친구")){
        printf("\t<<<중딩친구 단톡>>>\n");
        all_connect(5090);
    }
    else if(!strcmp(num,"초딩친구")){
        printf("\t<<<초딩친구 단톡>>>\n");
        all_connect(5100);
    }
    else if(!strcmp(num,"학원친구")){
        printf("\t<<<학원친구 단톡>>>\n");
        all_connect(5110);
    }

    else if(!strcmp(num,"부모님")){
        printf("\t<<<부모님 단톡>>>\n");
        all_connect(5120);
    }
    else if(!strcmp(num,"동아리")){
        printf("\t<<<동아리 단톡>>>\n");
        all_connect(5130);
    }
    else if(!strcmp(num,"대외활동")){
        printf("\t<<<대외활동 단톡>>>\n");
        all_connect(5140);
    }
    else if(!strcmp(num,"세컨드")){
        printf("\t<<<세컨드 단톡>>>\n");
        all_connect(5150);
    }

    else printf("\t잘못 입력하셨습니다.\n");

    gtk_widget_show_all(data->window3);//3번째 프레임 띄우기
}

G_MODULE_EXPORT void
name(GtkWidget *window,Data *data){//대화명 받기 위한 시그널

    const gchar *name_entry;
    memset(get_name,0,MAX_BUF);
    name_entry=gtk_entry_get_text(GTK_ENTRY((GtkWidget*)(data->entry1)));//에디트 컨트롤의 문자를 저장
    strcat(get_name,"[");
    strcat(get_name,name_entry);
    strcat(get_name,"]");
    gtk_widget_show_all(data->window2);//2번째 프레임 띄우기
}

G_MODULE_EXPORT void
send_message(GtkButton *button,Data *data){//메세지 전송
    pthread_t tid;
    const gchar *text;
    char buf[MAX_BUF];
    int len;
    char sub2_buf[MAX_BUF];
    char sub_buf[MAX_BUF];
    char optionbuf[MAX_BUF];
    char optionbuf_sub[MAX_BUF];
    pthread_create(&tid,NULL,receive,(void*)data);//받는 쓰레드
    pthread_create(&tid,NULL,option,NULL);//메세지 옵션 시스템 함수 쓰레드
    memset(buf,0,MAX_BUF);
    text=gtk_entry_get_text(GTK_ENTRY((GtkWidget*)(data->entry2)));
    strcpy(buf,get_name);
    strcat(buf,text);
    len=strlen(buf);
    if(send(sock,buf,len,0)!=len){//서버에 전송
        fprintf(stderr,"send failed\n");
        exit(1);
    }
    gtk_entry_set_text(GTK_ENTRY((GtkWidget*)(data->entry2))," ");//보낸후 에디트 컨트롤 비움
}

int main(int argc,char *argv[]){
    all_connect(5050);//처음 연결
//GTK기본 함수
    GtkBuilder *builder;
    Data *data;
    gtk_init(&argc,&argv);
    builder=gtk_builder_new();
    gtk_builder_add_from_file(builder,"client.glade",NULL);//글레이드 연결
    data=g_slice_new(Data);
    data->window1 = GTK_WIDGET(gtk_builder_get_object(builder,"window1"));//fram
    data->window2 = GTK_WIDGET(gtk_builder_get_object(builder,"window2"));//fram
    data->window3 = GTK_WIDGET(gtk_builder_get_object(builder,"window3"));//fram
    data->button = GTK_WIDGET(gtk_builder_get_object(builder,"button2"));//room
    data->button = GTK_WIDGET(gtk_builder_get_object(builder,"button3"));//room
    data->button = GTK_WIDGET(gtk_builder_get_object(builder,"button4"));//room
    data->button = GTK_WIDGET(gtk_builder_get_object(builder,"button5"));//room
    data->button = GTK_WIDGET(gtk_builder_get_object(builder,"button6"));//room
    data->button = GTK_WIDGET(gtk_builder_get_object(builder,"button7"));//room
    data->button = GTK_WIDGET(gtk_builder_get_object(builder,"button8"));//room
    data->button = GTK_WIDGET(gtk_builder_get_object(builder,"button9"));//room
    data->button = GTK_WIDGET(gtk_builder_get_object(builder,"button10"));//room
    data->button = GTK_WIDGET(gtk_builder_get_object(builder,"button11"));//room
    data->entry1 = GTK_WIDGET(gtk_builder_get_object(builder,"entry1"));//대화명
    data->entry2 = GTK_WIDGET(gtk_builder_get_object(builder,"entry2"));//내용입
    data->textview1 = GTK_WIDGET(gtk_builder_get_object(builder,"textview1"));//
    data->button1 =GTK_WIDGET(gtk_builder_get_object(builder,"button1"));//name
    data->button12 =GTK_WIDGET(gtk_builder_get_object(builder,"button12"));//send
    gtk_builder_connect_signals(builder,data);
    g_object_unref(G_OBJECT(builder));
    gtk_widget_show_all(data->window1);
    gtk_main();
    g_slice_free(Data,data);
}
void error_handling(char *message)//에러 함수
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

