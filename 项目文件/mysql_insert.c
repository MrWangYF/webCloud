#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "mysql.h"
                                     

//int mysql_insert(char *username/*in*/,char *password/*in*/,char *filename/*in*/,char *fileid/*in*/)
int mysql_insert(char *filename/*in*/,char *fileid/*in*/)
{
	int ret = 0;
	
	MYSQL *mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	
	char query[1024];
	
	memset(query,0,sizeof(query));
	//sprintf(query,"INSERT INTO tbl_name(username,password,timestamp,filename,fileid)"\
	//							" VALUES(%s,%s,NULL,%s,%s)"\
	//							,username,password,filename,fileid);
	sprintf(query,"INSERT INTO user(name,password)"\
								" VALUES(\"%s\",\"%s\")"\
								,filename,fileid);
	printf("query:%s",query);
	mysql = mysql_init(NULL);
	
	mysql =mysql_real_connect(mysql, "localhost", "root", "yunfei962464", "dawei", 0, NULL, 0);
	
	if (mysql == NULL) {
		ret = mysql_errno(mysql);
		printf("func mysql_real_connect() err\n");
		return ret;
	} else {
		printf(" ok......\n");
	}
	
	ret = mysql_query(mysql, query);	
	if (ret != 0) {
		printf("mysql_query() err:%d\n", ret);
		return ret;
	}
	
	mysql_close(mysql);
	
	return 0;	
}

int main(void)
{	
	//int mysql_insert(char *filename/*in*/,char *fileid/*in*/)
	char *filename = "test";
	char fileid[128] = "123456";
	int result;

	result = mysql_insert(filename/*in*/,fileid/*in*/);
	if(result != 0) {
		printf("mysql_insert error\n");
	}
	
	return result;		
}
