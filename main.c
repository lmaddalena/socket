#include "stda.h"

void error(const char*);
void pausa(void);

int main(int argc, char *argv[])
{    
    // verifico i parametri di input
    if (argc < 3) 
    { 
        puts("Parameters: <path> <querystring>"); 
        exit(EXIT_FAILURE); 
    }

	printf("Test Socket\n");
    printf("-----------\n\n");

    // host
    int port = 5000;
    char *host = "localhost";
    
    char *request_fmt = "GET /%s?%s HTTP/1.0\r\n\r\n";    
    char request[1024];             // messaggio di request;
    char response[4096];            // messaggio di response

    printf("Host: %s\nPort: %i\n\n", host, port);

    // compone la request con i parametri di input
    sprintf(request, request_fmt, argv[1], argv[2]);
    printf("Request:\n%s\n",request);


    struct hostent *server;
    struct sockaddr_in serv_addr;
    int sockfd;                     // descrittore socket
    int bytes;                      // bytes
    int sent;                       // bytes inviati
    int received;                   // bytes ricevuti
    int total;                      // bytes totali da inviare

    // crea il socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
        error("ERRORE: impossibile aprire il socket");

    // recupera l'indirizzo IP dal nome host
    server = gethostbyname(host);
    if(server == NULL)
        error("ERRORE: nome host non valido");

    // Riempie la struttura
    memset(&serv_addr, 0, sizeof(serv_addr));   // mette tutto a 0
    serv_addr.sin_family = AF_INET;             // protocolli internet
    serv_addr.sin_port = htons(port);           // porta (convertita in unsigned short int)
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr_list[0], server->h_length);
    
   // connette il socket
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("ERRORE: connessione fallita!");

    // invia la richiesta
    total = strlen(request);
    sent = 0;
    do {
        bytes = write(sockfd, request+sent,total-sent);
        if (bytes < 0)
            error("ERRORE: errore di scrittura nel socket");

        if (bytes == 0)
            break;

        sent+= bytes;
    } while (sent < total);

    // ottiene la risposta
    memset(response, 0, sizeof(response));
    total = sizeof(response) - 1;
    received = 0;
    do {
        bytes = read(sockfd, response+received, total - received);
        if (bytes < 0)
            error("ERRORE: errore durante la lettura della risposta dal socket");

        if (bytes == 0)
            break;
        received+=bytes;
    } while (received < total);

    if (received == total)
            error("ERRORE: risposta troppo grande");

    // chiude il socket
    close(sockfd);

    // processa la risposta
    printf("Response:\n%s\n",response);

    pausa();
    exit(EXIT_SUCCESS);
}

void error(const char *msg)
{ 
    perror(msg);
    pausa();    
    exit(EXIT_FAILURE);
}

void pausa()
{
    // aggiungere l'opzione -DDEBUG al compilatore
    #ifdef DEBUG
    printf("Premere [ENTER] per continuare....\n");
    getchar();
    #endif
}