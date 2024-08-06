#include<iostream>
#include <arpa/inet.h> 
#include <sys/types.h>
#include <sys/unistd.h>
#include <string.h>
#define protocol 5000
#define ip "192.168.0.105"

using std::cerr;
using std::cout;
using std::endl;
int main(int argc,char *argv[])
{
    if(argc==1){cerr<<"输入信息"<<endl;return -1;}
    
    //建立嵌套字
    int Sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(Sockfd<0){cerr<<"fail to get Sockdf";return -1;}
    
    //协议端口与地址
    sockaddr_in addr ;
    memset(&addr,0,sizeof(addr));
    addr.sin_family=AF_INET;
    inet_pton(AF_INET,ip,&addr.sin_addr);
    addr.sin_port=htons(protocol);
   
    //请求连接
    cout<<"start to connect"<<endl;
    if(connect(Sockfd,(sockaddr *)&addr,sizeof(sockaddr_in))==-1)
    {cerr<<"fail to connect"<<endl;close(Sockfd);return -1;}else{cout<<"success to connect"<<endl;}

    //发送消息
    if(write(Sockfd,argv[1],strlen(argv[1]))==-1){cerr<<"fail to sent"<<endl;close(Sockfd);return-1;}
    cout<<"sent:"<<argv[1]<<endl;
    //接受消息
    char buf[64];
    memset(&buf,0,64);
    if(read(Sockfd,buf,63)==-1){cerr<<"fail to reseiver"<<endl;close(Sockfd);return-1;}
    cout<<"receive:"<<buf<<endl;
   
    //断开连接
    close(Sockfd);
    cout<<"close"<<endl;
    return 0;
}