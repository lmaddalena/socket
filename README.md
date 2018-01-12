# USING SOCKET

## Come utilizzare un socket per effettuare chiamate http

La tipica modalita' di utilizzo dei socket e' la seguente:

1. Creazione socket
1. Assegnazione indirizzo
1. Apertura socket (connessione)
1. Invio richiesta
1. Attesa risposta
1. Chiusura socket

### Tipologia di richieste http

GET:

    GET /path?query_string HTTP/1.0\r\n
    \r\n

POST:

    POST /path HTTP/1.0\r\n
    Content-Type: text/plain\r\n
    Content-Length: 12\r\n
    \r\n
    query_string

### Riferimenti

* <https://stackoverflow.com/questions/22077802/simple-c-example-of-doing-an-http-post-and-consuming-the-response>
* <http://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html>
* <http://www.feelinglinux.com/articles/usosocket.jsp>
