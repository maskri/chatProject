#include <stdio.h>

#include <winsock2.h>


int main(){


    int SocketId;
    struct hostent *ServerInfoPt;
    struct sockaddr_in SockAdrDef;
    int Data, Result;
    int OpRes;
    int ServerPort = 1337;
    char * ServerName = "19.168.30.56";
    SocketId = socket(AF_INET, SOCK_STREAM, 0); // Socket creation
    SockAdrDef.sin_family = AF_INET; // Socket connection
    SockAdrDef.sin_port = htons(ServerPort);
    ServerInfoPt = gethostbyname(ServerName);
    memcpy(&SockAdrDef.sin_addr.s_addr, ServerInfoPt->h_addr, ServerInfoPt->h_length);
    OpRes = connect(SocketId, (struct sockaddr *) &SockAdrDef, sizeof(struct sockaddr_in));
    if (OpRes == -1) {
        fprintf(stderr,"Socket connexion has failed!\n");
        exit(1);
    }
    Data = (int) (rand() % 10000); // Dialog with server
    send(SocketId,(char *) &Data, sizeof(int), 0);
    recv(SocketId,(char *) &Result, sizeof(int), 0);
    close(SocketId);
    return 0;
}
