#include <string.h>

#include "Serializable.h"
#include "Socket.h"

Socket::Socket(const char * address, const char * port):sd(-1)
{
    //Construir un socket de tipo AF_INET y SOCK_DGRAM usando getaddrinfo.
    struct addrinfo hints;
    struct addrinfo* res;

    memset((void*) &hints, 0, sizeof(hints));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    int rc = getaddrinfo(address, port, &hints, &res);
    if(rc < 0)
        std::cout << "Error de conexion\n";
    
    //Con el resultado inicializar los miembros sd, sa y sa_len de la clase
    sa = *res->ai_addr;
    sa_len = res->ai_addrlen;

    sd = socket(res->ai_family, res->ai_socktype, 0);
    if(sd < 0)
        std::cout << "Error en creación de socket\n";
    
    freeaddrinfo(res);
}

int Socket::recv(Serializable &obj, Socket * &sock)
{
    struct sockaddr sa;
    socklen_t sa_len = sizeof(struct sockaddr);

    char buffer[MAX_MESSAGE_SIZE];

    ssize_t bytes = ::recvfrom(sd, buffer, MAX_MESSAGE_SIZE, MSG_DONTWAIT, &sa, &sa_len);

    if ( bytes <= 0 )
    {
        return -1;
    }

    if ( sock != 0 )
    {
        sock = new Socket(&sa, sa_len);
    }

    obj.from_bin(buffer);

    return 0;
}

int Socket::send(Serializable& obj, const Socket& sock)
{
    //Serializar el objeto
    obj.to_bin();
    //Enviar el objeto binario a sock usando el socket sd
    int data = sendto(sd, (void*)obj.data(), obj.size(), 0, (struct sockaddr*)&sock.sa, sock.sa_len);

    if(data <= 0)
        return -1;
    return 0;
}

bool operator== (const Socket &s1, const Socket &s2)
{
    //Comparar los campos sin_family, sin_addr.s_addr y sin_port
    //de la estructura sockaddr_in de los Sockets s1 y s2
    //Retornar false si alguno difiere
    sockaddr_in* sockA = (sockaddr_in*) &s1.sa;
    sockaddr_in* sockB = (sockaddr_in*) &s2.sa;

    return (sockA->sin_family == sockB->sin_family 
           && sockA->sin_port == sockB->sin_port 
           && sockA->sin_addr.s_addr == sockB->sin_addr.s_addr);
};

std::ostream& operator<<(std::ostream& os, const Socket& s)
{
    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];

    getnameinfo((struct sockaddr *) &(s.sa), s.sa_len, host, NI_MAXHOST, serv,
                NI_MAXSERV, NI_NUMERICHOST);

    os << host << ":" << serv;

    return os;
};