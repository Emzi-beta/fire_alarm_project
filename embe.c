#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <wiringPi.h>
#define FLAME 5
#define FLAME2 11
#define FLAME3 25
#define FLAME4 31
#define BUZZERPOWER 24
#define BUZZERPOWER2 27
#define BUZZERPOWER3 28
#define BUZZERPOWER4 29
#define BUF_SIZE 1024

unsigned char flameFlag =  0;
unsigned char flameFlag2 = 0;
unsigned char flameFlag3 = 0;
unsigned char flameFlag4 = 0;

void myInterrupt(void){
    flameFlag = 1;
}
void myInterrupt2(void){
    flameFlag2 = 1;
}
void myInterrupt3(void){
    flameFlag3 = 1;
}
void myInterrupt4(void){
    flameFlag4 = 1;
}

void error_handling(char *message);

int main(int argc, char *argv[]) {
    int sock;
    char message[BUF_SIZE];
    int str_len, recv_len, recv_cnt;
    struct sockaddr_in serv_adr;

    if (argc != 3) {
        printf("Usage : %s <IP> <port> \n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        error_handling("socket() error");

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) == -1)
        error_handling("connect() error!");
    else
        puts("Connected...");

    if (wiringPiSetup() < 0)
        return 1;

    if (wiringPiISR(FLAME, INT_EDGE_FALLING, &myInterrupt) < 0) {
        printf("Unable to setup ISR\n");
        return 1;
    }
    if (wiringPiISR(FLAME2, INT_EDGE_FALLING, &myInterrupt2) < 0) {
        printf("Unable to setup  ISR\n");
        return 1;
    }
    if (wiringPiISR(FLAME3, INT_EDGE_FALLING, &myInterrupt3) < 0) {
        printf("Unable to setup ISR\n");
        return 1;
    }
    if (wiringPiISR(FLAME4, INT_EDGE_FALLING, &myInterrupt4) < 0) {
        printf("Unable to setup ISR\n");
        return 1;
    }
    //buzzer1
    pinMode(BUZZERPOWER, OUTPUT);
    digitalWrite(BUZZERPOWER, 1);
    softToneCreate(BUZZERPOWER);
    //buzzer2
    pinMode(BUZZERPOWER2, OUTPUT);
    digitalWrite(BUZZERPOWER2, 1);
    softToneCreate(BUZZERPOWER2);
    //buzzer3
    pinMode(BUZZERPOWER3, OUTPUT);
    digitalWrite(BUZZERPOWER3, 1);
    softToneCreate(BUZZERPOWER3);
    //buzzer4
    pinMode(BUZZERPOWER4, OUTPUT);
    digitalWrite(BUZZERPOWER4, 1);
    softToneCreate(BUZZERPOWER4);
    while (1) {
        //첫번째 감지
        if (flameFlag1 == 1) {
            strcpy(message,"1");
            write(sock, message, strlen(message));
            printf("detect flame \n");
            //각 데시벨이 다르게 출력되는지 확인용입니다.
            softToneWrite(BUZZERPOWER, 1100);
            softToneWrite(BUZZERPOWER2, 0);
            softToneWrite(BUZZERPOWER3, 0);
            softToneWrite(BUZZERPOWER4, 0);
            delay(800);
            softToneWrite(BUZZERPOWER, 0);
            softToneWrite(BUZZERPOWER2, 1000);
            softToneWrite(BUZZERPOWER3, 0);
            softToneWrite(BUZZERPOWER4, 0);
            delay(800);
            softToneWrite(BUZZERPOWER, 0);
            softToneWrite(BUZZERPOWER2, 0);
            softToneWrite(BUZZERPOWER3, 900);
            softToneWrite(BUZZERPOWER4, 0);
            delay(800);
            softToneWrite(BUZZERPOWER, 0);
            softToneWrite(BUZZERPOWER2, 0);
            softToneWrite(BUZZERPOWER3, 0);
            softToneWrite(BUZZERPOWER4, 800);
            delay(800);

            //다 꺼짐
            softToneWrite(BUZZERPOWER, 0);
            softToneWrite(BUZZERPOWER2, 0);
            softToneWrite(BUZZERPOWER3, 0);
            softToneWrite(BUZZERPOWER4, 00);
            delay(1000);

            //전체 출력
            softToneWrite(BUZZERPOWER, 1100);
            softToneWrite(BUZZERPOWER2,1000);
            softToneWrite(BUZZERPOWER3,900);
            softToneWrite(BUZZERPOWER4,800);
            flameFlag = 0;
        }
        //두번째 감지
        if (flameFlag2 == 1) {
            strcpy(message,"2");
            write(sock, message, strlen(message));
            printf("detect flame2 \n");
            //각 데시벨이 다르게 출력되는지 확인용입니다.
            softToneWrite(BUZZERPOWER, 1000);
            softToneWrite(BUZZERPOWER2, 0);
            softToneWrite(BUZZERPOWER3, 0);
            softToneWrite(BUZZERPOWER4, 0);
            delay(800);
            softToneWrite(BUZZERPOWER, 0);
            softToneWrite(BUZZERPOWER2, 1100);
            softToneWrite(BUZZERPOWER3, 0);
            softToneWrite(BUZZERPOWER4, 0);
            delay(800);
            softToneWrite(BUZZERPOWER, 0);
            softToneWrite(BUZZERPOWER2, 0);
            softToneWrite(BUZZERPOWER3, 1000);
            softToneWrite(BUZZERPOWER4, 0);
            delay(800);
            softToneWrite(BUZZERPOWER, 0);
            softToneWrite(BUZZERPOWER2, 0);
            softToneWrite(BUZZERPOWER3, 0);
            softToneWrite(BUZZERPOWER4, 900);
            delay(800);

            //다 꺼짐
            softToneWrite(BUZZERPOWER, 0);
            softToneWrite(BUZZERPOWER2, 0);
            softToneWrite(BUZZERPOWER3, 0);
            softToneWrite(BUZZERPOWER4, 00);
            delay(1000);

            //전체 출력
            softToneWrite(BUZZERPOWER, 1000);
            softToneWrite(BUZZERPOWER2,1100);
            softToneWrite(BUZZERPOWER3,1000);
            softToneWrite(BUZZERPOWER4,900);
            flameFlag = 0;
        }

        if (flameFlag3 == 1) {
            strcpy(message,"3");
            write(sock, message, strlen(message));
            printf("detect flame3 \n");
            //각 데시벨이 다르게 출력되는지 확인용입니다.
            softToneWrite(BUZZERPOWER, 900);
            softToneWrite(BUZZERPOWER2, 0);
            softToneWrite(BUZZERPOWER3, 0);
            softToneWrite(BUZZERPOWER4, 0);
            delay(800);
            softToneWrite(BUZZERPOWER, 0);
            softToneWrite(BUZZERPOWER2, 1000);
            softToneWrite(BUZZERPOWER3, 0);
            softToneWrite(BUZZERPOWER4, 0);
            delay(800);
            softToneWrite(BUZZERPOWER, 0);
            softToneWrite(BUZZERPOWER2, 0);
            softToneWrite(BUZZERPOWER3, 1100);
            softToneWrite(BUZZERPOWER4, 0);
            delay(800);
            softToneWrite(BUZZERPOWER, 0);
            softToneWrite(BUZZERPOWER2, 0);
            softToneWrite(BUZZERPOWER3, 0);
            softToneWrite(BUZZERPOWER4, 1000);
            delay(800);

            //다 꺼짐
            softToneWrite(BUZZERPOWER, 0);
            softToneWrite(BUZZERPOWER2, 0);
            softToneWrite(BUZZERPOWER3, 0);
            softToneWrite(BUZZERPOWER4, 00);
            delay(1000);

            //전체 출력
            softToneWrite(BUZZERPOWER, 900);
            softToneWrite(BUZZERPOWER2,1000);
            softToneWrite(BUZZERPOWER3,1100);
            softToneWrite(BUZZERPOWER4,1000);
            flameFlag = 0;
        }
        if (flameFlag4 == 1) {
            strcpy(message,"4");
            write(sock, message, strlen(message));
            printf("detect flame4 \n");
            //각 데시벨이 다르게 출력되는지 확인용입니다.
            softToneWrite(BUZZERPOWER, 800);
            softToneWrite(BUZZERPOWER2, 0);
            softToneWrite(BUZZERPOWER3, 0);
            softToneWrite(BUZZERPOWER4, 0);
            delay(800);
            softToneWrite(BUZZERPOWER, 0);
            softToneWrite(BUZZERPOWER2, 900);
            softToneWrite(BUZZERPOWER3, 0);
            softToneWrite(BUZZERPOWER4, 0);
            delay(800);
            softToneWrite(BUZZERPOWER, 0);
            softToneWrite(BUZZERPOWER2, 0);
            softToneWrite(BUZZERPOWER3, 1000);
            softToneWrite(BUZZERPOWER4, 0);
            delay(800);
            softToneWrite(BUZZERPOWER, 0);
            softToneWrite(BUZZERPOWER2, 0);
            softToneWrite(BUZZERPOWER3, 0);
            softToneWrite(BUZZERPOWER4, 1100);
            delay(800);

            //다 꺼짐
            softToneWrite(BUZZERPOWER, 0);
            softToneWrite(BUZZERPOWER2, 0);
            softToneWrite(BUZZERPOWER3, 0);
            softToneWrite(BUZZERPOWER4, 00);
            delay(1000);

            //전체 출력
            softToneWrite(BUZZERPOWER, 800);
            softToneWrite(BUZZERPOWER2,900);
            softToneWrite(BUZZERPOWER3,1000);
            softToneWrite(BUZZERPOWER4,1100);
            flameFlag = 0;
        }






        delay(1000);
        digitalWrite(BUZZERPOWER, 0);
        digitalWrite(BUZZERPOWER2, 0);
        digitalWrite(BUZZERPOWER3, 0);
        digitalWrite(BUZZERPOWER4, 0);
    }



    close(sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}



}