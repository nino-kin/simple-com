#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
 int sock;
 struct sockaddr_in addr;

 sock = socket(AF_INET, SOCK_DGRAM, 0);

 addr.sin_family = AF_INET;                     /* IP protocol family.  */
 addr.sin_port = htons(12345);                  /* Port number.         */
 addr.sin_addr.s_addr = inet_addr("127.0.0.1"); /* Internet address.    */

 char message[] = "HELLO";

 sendto(sock, message, 5, 0, (struct sockaddr *)&addr, sizeof(addr));

 close(sock);

 return 0;
}
