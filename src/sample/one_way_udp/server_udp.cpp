#include <stdio.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
 int sock;
 struct sockaddr_in addr;

 char buf[2048];

 sock = socket(AF_INET, SOCK_DGRAM, 0);

 addr.sin_family = AF_INET;         /* IP protocol family.  */
 addr.sin_port = htons(12345);      /* Port number.         */
 addr.sin_addr.s_addr = INADDR_ANY; /* Internet address.    */

 bind(sock, (struct sockaddr *)&addr, sizeof(addr));

 memset(buf, 0, sizeof(buf));
 recv(sock, buf, sizeof(buf), 0);

 printf("%s\n", buf);

 close(sock);

 return 0;
}
