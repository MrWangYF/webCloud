#include<stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include<string.h>
int main(void)
{
	char data[40]="";
	printf("Content-type: text/html;charset=utf-8\n\n");
	//注意这里要两个换行符，这是HTML的规定
	printf("\n");
	printf("<html><head><title>用户验证</title></head>");
	printf("<body>");
	char name[30]="",passwd[20]="";
	//      data=getenv("CONTENT_LENGTH");
	printf("<p></p><p></p>\n");
	scanf("%s",data);       //post方法通过标准输入把客户端的参数传递过来，服务器端只能从标准输入获得数据
	sscanf(data,"name=%s",name);
	sscanf(name,"%[^&]",name);//正则表达式，遇到&就结束
	memcpy(passwd,data+5+strlen(name),strlen(data)-5-strlen(name));//5表示name=的长度
	sscanf(passwd,"&password=%s",passwd);
	if(strlen(name)==0||strcmp(name,"root"))
	{
		printf("<p></p><p></p>\n");
		printf("用户名为空或者错误");
		printf("</body></html>");
	}
	else
	{
		printf("<p></p><p></p>\n");
		printf("用户名为:%s\n",name);
		printf("<br>");
		printf("密码为：%s\n",passwd);
		printf("</body></html>");
	}
	return 0;
}
