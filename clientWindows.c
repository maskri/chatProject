#ifdef WIN32 /* si vous êtes sous Windows */

#include <winsock2.h>


#elif defined (linux) /* si vous êtes sous Linux */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#else /* sinon vous êtes sur une plateforme non supportée */

#error not defined for this platform

#endif
#include <stdio.h>
static void init(void)
{
#ifdef WIN32
    WSADATA wsa;
    int err = WSAStartup(MAKEWORD(2, 2), &wsa);
    if(err < 0)
    {
        puts("WSAStartup failed !");
        exit(EXIT_FAILURE);
    }
#endif
}

static void end(void)
{
#ifdef WIN32
    WSACleanup();
#endif
}

int main(){
init();

    int SocketId;
    struct hostent *ServerInfoPt;
    struct sockaddr_in SockAdrDef;
    char Data[100], Result[100];
    int OpRes;
    int ServerPort = 1337;
    char * ServerName = "192.168.30.61";
    SocketId = socket(AF_INET, SOCK_STREAM, 0); // Socket creation
    printf ("socketId : %i \n", SocketId);
    if( SocketId == -1){

        printf("erreur socketId = a -1");

        return 0;
    }
    SockAdrDef.sin_family = AF_INET; // Socket connection

    SockAdrDef.sin_port = htons(ServerPort);

    ServerInfoPt = gethostbyname(ServerName);

    memcpy(&SockAdrDef.sin_addr.s_addr, ServerInfoPt->h_addr, ServerInfoPt->h_length);

    OpRes = connect(SocketId, (struct sockaddr *) &SockAdrDef, sizeof(struct sockaddr_in));

    if (OpRes == -1) {
        printf("Socket connexion has failed!\n");
        exit(1);
    }
    printf("Moi : ");

    scanf("%s",&Data); // Dialog with server
    printf("data : %s \n",Data);
    send(SocketId, Data, sizeof(char)*100, 0);

    recv(SocketId, Result, sizeof(char)*100, 0);
    printf("\nResultat : %s \n",Result );
    close(SocketId);
    end();
    return 0;
}

