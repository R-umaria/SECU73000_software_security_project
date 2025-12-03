#include <stdio.h>

#define PORT 8081
#define USERNAME 0x01
#define PASSWORD 0x02
#define BADUSER "\x33\x44 Error: unknown/incorrect username"
#define BADPASS "\x33\x45 Error: incorrect password"
#define READY   "\x41\x41 ready"
#define USERPATH "./users/"
#define POSTINGPATH "./postings/"	
#define LISTCOMMAND "ls ./postings/ > list.txt"
#define FILENOTAVAIL "\x33\x31 Error: requested file not available"
#define BEGINFILE "\x41\x41 BEGIN FILE: END WITH '!!!'"
#define POSTINGWROTE "\x41\x42 Success: Posting has been written"
#define LIST_POSTINGS 0x22
#define READ_POSTING 0x23
#define WRITE_POSTING 0x24
#define COMMAND 0x25
#define ADD_USER 0x26

void logData(FILE *logfile, char *format, ...);
int setupSock(FILE *logf, unsigned short port);
int writeSock(int sock, char *buf, size_t len);
int readSock(int sock, char *buf, size_t len);
void mainLoop(FILE *logf, int sock);
void handleConnection(FILE *logfile, int sock);
int userFunctions(FILE *logfile, int sock, char *user);
char *findarg(char *argbuf, char argtype);
int authenticate(FILE *logfile, char *user, char *pass);
void addUser(FILE *log, int sock, char *action);
int adminFunctions(FILE *logfile, int sock);
void command(FILE *log, int sock, char *action);
void listPostings(int sock, FILE *logfile, char *action);
void readPosting(int sock, FILE *logfile, char *action);
void writePosting(int sock, FILE *logfile, char *action);
void spawnhandler(int signumber);
