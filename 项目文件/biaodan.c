#include<stdio.h>
#include "mysql_select.h"
#include <unistd.h>
#include<stdlib.h>
#include<string.h>
#include <fcgi_stdio.h>
int main(void)
{
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
		if(method == NULL){
			return 0;
		}
		if(strcmp(method, "get") == 0 || strcmp(method, "GET") == 0)
		{
			p   =   getenv("QUERY_STRING");     /*从环境变量QUERY_STRING>    中得到Form数据*/
			if   (p!=NULL)   {
				strncpy(InputBuffer,p,sizeof(InputBuffer));
			}
		}
		else if(strcmp(method, "post") == 0 || strcmp(method, "POST") == 0)
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

		//	printf("%s", getenv("QUERY_STRING"));

		printf("\n");
		char name[30],passwd[20];
		//post方法通过标准输入把客户端的参数传递过来，服务器端只能从标准输入获得数据
		sscanf(InputBuffer,"user=%s",name);
		sscanf(name,"%[^&]",name);//正则表达式，遇到&就结束
		char user[30];
		char password[28];
		strcpy(user,name);
//		printf("user: %s ,name %s<br> ",user,name);
		memcpy(passwd,InputBuffer+5+strlen(name),strlen(InputBuffer)-5-strlen(name));//5表示name=的长度
//		printf("%s,<br>",passwd);
		sscanf(passwd,"&passwd=%s",passwd);
		sscanf(passwd,"%[^&]",passwd);//正则表达式，遇到&就结束
//		printf("%s,<br>",passwd);
//		printf("user:%s <br>\npasswd: %s<br>\n",user,passwd);
		sql_query(user,password);
//		printf("user:%s <br>\npassword: %s<br>\n",user,password);
		if((int)strlen(user)==0||!strcmp(user,"root")||strcmp(passwd,password))
		{
			printf("<script type=text/javascript>alert(\"用户名或密码错误\");location.href=\"login.html\";</script>");
			printf("</body></html>\n");
		}
		else if((strcmp(user,name)==0)&&(strcmp(passwd,password)==0))
		{
			printf("\n");
			printf("<script type=text/javascript>alert(\"登录成功!!\");location.href="        "\"index.html\";</script>");
			printf("</body></html>\n");
		}
	}
	return 0;
}
