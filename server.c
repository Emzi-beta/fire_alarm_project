#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>

#define BUF_SIZE 100
void error_handling(char *buf);

int main(int argc, char *argv[]) {
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    struct timeval timeout;
    fd_set reads, cpy_reads;
    char message1[BUF_SIZE];


    socklen_t adr_sz;
    int fd_max, str_len,str_len3,str_len2, fd_num, i;
    char buf[BUF_SIZE];
    char buf2[BUF_SIZE];
    if (argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }


    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");
    if (listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    FD_ZERO(&reads);
    FD_SET(serv_sock, &reads);
    fd_max = serv_sock;

    while (1) {
        cpy_reads = reads;
        timeout.tv_sec = 5;
        timeout.tv_usec = 5000;

        if ((fd_num = select(fd_max + 1, &cpy_reads, 0, 0, &timeout)) == -1){
            break;
            printf("dsadas");}
        if (fd_num == 0)
            continue;

        for (i = 0; i < fd_max+1; i++) {
            if (FD_ISSET(i, &cpy_reads)) {

                if (i == serv_sock) // connection request !
                {
                    adr_sz = sizeof(clnt_adr);
                    clnt_sock =
                            accept(serv_sock, (struct sockaddr *) &clnt_adr, &adr_sz);

                    FD_SET(clnt_sock, &reads);
                    if (fd_max < clnt_sock)
                        fd_max = clnt_sock;
                    printf("connected client: %d \n", i);

                }
                else // read message !
                {
                    if (i == 4){
                        str_len3 = read(i, message1, BUF_SIZE);
                        if (strcmp(message1,"1")){
                            str_len = read(i+1, buf, BUF_SIZE); //이상하게 안받아지면 에러가 나네요ㅠㅠ
                            str_len2 = read(i+2, buf2, BUF_SIZE);
                            write(i+1, (char*)message1, str_len);
                            strcpy(message1,"5");
                            write(i+2, (char*)message1, str_len2);
                        }
                        else if (strcmp(message1,"2")){
                            str_len = read(i+1, buf, BUF_SIZE); //이상하게 안받아지면 에러가 나네요ㅠㅠ
                            str_len2 = read(i+2, buf2, BUF_SIZE);
                            write(i+1, (char*)message1, str_len);
                            strcpy(message1,"6");
                            write(i+2, (char*)message1, str_len2);
                        }
                        else if (strcmp(message1,"3")){
                            str_len = read(i+1, buf, BUF_SIZE); //이상하게 안받아지면 에러가 나네요ㅠㅠ
                            str_len2 = read(i+2, buf2, BUF_SIZE);
                            write(i+1, (char*)message1, str_len);
                            strcpy(message1,"7");
                            write(i+2, (char*)message1, str_len2);
                        }
                        else if (strcmp(message1,"4")){
                            str_len = read(i+1, buf, BUF_SIZE); //이상하게 안받아지면 에러가 나네요ㅠㅠ
                            str_len2 = read(i+2, buf2, BUF_SIZE);
                            write(i+1, (char*)message1, str_len);
                            strcpy(message1,"8");
                            write(i+2, (char*)message1, str_len2);
                        }
                    }
                }
            }
        }
    }
    close(serv_sock);
    return 0;

}

void error_handling(char *buf)
{
    fputs(buf, stderr);
    fputc('\n', stderr);
    exit(1);
}
