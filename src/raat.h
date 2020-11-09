#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <ctype.h>

#include <syslog.h>
#include <signal.h>
#include <sys/stat.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>

#include "uthash.h"
#include "utarray.h"

extern int errno;

typedef struct {
	int iflag;
	int hflag;
	int wflag;
	int lflag;
	int sflag;
	int bflag;
	int tflag;
	int Dflag;
	int breakUp;
	char *p_breakUp;
	int dataType;
	char *p_dataType;
	int sleepTime;
	char *p_sleepTime;
} flags;

typedef struct {
	char mac[20]; 
	int rt_table_id; 
	char ipv4[20];
	int breakup_count;
	int node_timestamp;
	int node_timestamp_tmp;
	unsigned long route_hash;
	unsigned long route_hash_tmp;
	UT_hash_handle hh1, hh2;
	UT_array *p_route_announce;
	UT_array *p_route_main;
} pull;

typedef struct {
	char batmanIf[15];
	char batmanAddr[32];
	int wanRouteExists;
	int wanPublish;
	int lanPublish;
	UT_array *p_pushRoutes;
} push;

//push functions
void checkBatIf(push *snd);
void getBatIpAddr(push *snd);
void wanRouteExists(push *snd);
void getLocalRoutes(push *snd);
void pushData(push *snd, flags *f);

//pull functions
void flushRulesRoutes(void);
void getAndSetStruct(push *snd, pull *rcv, flags *f);
void checkStatus(flags *f, pull *rcv);
void deleteRoute(pull *rcv, char **pp_route, char ip_cmd[]);
void addRoute(pull *rcv, char **pp_route, char ip_cmd[]);
void removeExpired(pull *rcv, flags *f);
unsigned long sdbm(char *str);

