#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "mysql.h"
#include <fcgi_stdio.h>                     

int mysql_insert(char *username/*in*/,char *password/*in*/,char *email/*in*/)
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
	sprintf(query,"INSERT INTO usertable(username,password,email)"
			" VALUES(\"%s\",\"%s\",\"%s\")"
			,username,password,email);
//	printf("query:%s",query);
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
	//int mysql_ipnsert(char *filename/*in*/,char *fileid/*in*/)


	int result;
	char InputBuffer[4096];
	char *method;//METHOD 属性值
	char *p;
	int x;
	int i,ContentLength/*数据长度*/;
	setvbuf(stdin,NULL,_IONBF,0);//关闭stdin的缓冲
	while(FCGI_Accept() >= 0)
	{
		printf("Content-type: text/html;charset=utf-8\n\n");
		//注意这里要两个换行符，这是HTML的规定
		printf("\n");
		printf("<html><head><title>用户验证</title></head>");
		printf("<body>");
		printf("\n");
		method = getenv("REQUEST_METHOD");
		printf("method:%s",method);
		printf("<br>");
		if(method == NULL){
			return 0;
		}
		if(strcmp(method, "get") == 0 || strcmp(method, "GET")     == 0)
		{
			p   =   getenv("QUERY_STRING");     /*从环境变量QU    ERY_STRING>    中得到Form数据*/
			if   (p!=NULL)   {
				strncpy(InputBuffer,p,sizeof(InputBuffer));
			}
		}
		else if(strcmp(method, "post") == 0 || strcmp(method,     "POST") == 0)
		{
			p=getenv("CONTENT_LENGTH");
			if(p!=NULL){
				ContentLength = atoi(p);
			} else {
				ContentLength = 0;
			}
			if(ContentLength > sizeof(InputBuffer)-1){
				ContentLength = sizeof(InputBuffer)-1;
			}
			i = 0;
			while(i<ContentLength)
			{
				x = fgetc(stdin);
				if(x==EOF)
					break;
				InputBuffer[i++] = x;
			}
			InputBuffer[ContentLength]   = '\0';
			//ContentLength   =   i;
		}
		else{
			return 0;
		}
		//  printf("%s", getenv("QUERY_STRING"));
		printf("\n");
//		printf("buf:%s",InputBuffer);
//		printf("<br>");
		char name[128],passwd[128],passwd2[128];
		//post方法通过标准输入把客户端的参数传递过来，服务器端只能从标准输入获得数据
		sscanf(InputBuffer,"user=%s",name);
		sscanf(name,"%[^&]",name);//正则表达式，遇到&就结束
		char user[30];
		char password[28];
		char password2[28];
		char email[1024];
		strcpy(user,name);
//		printf("user: %s\n",user);
//		printf("<br>");
		memcpy(passwd,InputBuffer+5+strlen(name),strlen(InputBuffer)-5-strlen(name));//5表示name=的长度
//		printf("passwd: %s\n<br>",passwd);
		sscanf(passwd,"&passwd=%s",passwd);
		sscanf(passwd,"%[^&]",passwd);//正则表达式，遇到&就结束
		strcpy(password,passwd);
//		printf("password: %s\n",password);
//		printf("<br>");
//		printf("passwd: %s\n<br>",passwd);
		memcpy(passwd2,InputBuffer+8+5+strlen(name)+strlen(passwd),strlen(InputBuffer)-8-5-strlen(name)-strlen(passwd));//8表示&passwd=的长度
//		printf("passwd2: %s\n<br>",passwd2);
		sscanf(passwd2,"&passwd2=%s",passwd2);
//		printf("passwd2:%s \n<br>",passwd2);
		sscanf(passwd2,"%[^&]",passwd2);//正则表达式，遇到&就结束
		strcpy(password2,passwd2);
//		printf("password2: %s\n",password2);
//		printf("<br>");
//		printf("passwd2: %s\n<br>",passwd2);
		memcpy(email,InputBuffer+5+8+9+strlen(name)+strlen(passwd)+strlen(passwd2),strlen(InputBuffer)-8-5-9-strlen(name)-strlen(passwd)-strlen(passwd2));//9表示&passwd2=的长度
//		printf("email: %s\n<br>",email);

		sscanf(email,"&email=%s",email);
		sscanf(email,"%[^&]",email);//正则表达式，遇到&就结束
//		printf(" email:%s\n",email);
//		printf("<br>");
//		printf("email: %s\n<br>",email);

		result = mysql_insert(user/*in*/,password/*in*/,email/*in*/);
		if(result != 0) {
			printf("mysql_insert error\n");
		}
		printf("<script type=text/javascript>alert(\"注册成功!!\");location.href="    "\"login.html\";</script>");
		printf("</body></html>");

		return result;		
	}
	return 0;
}
