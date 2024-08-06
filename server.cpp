#include<iostream>
#include <arpa/inet.h> 
#include <sys/types.h>
#include <sys/unistd.h>
#include <memory.h>
#define protocol 5000
#define ip INADDR_ANY
using std::cerr;
using std::cout;
using std::endl;
int main(int argc,char *argv[])
{
    //分配嵌套字
    int SSockfd=socket(AF_INET,SOCK_STREAM,0);
    if(SSockfd==-1){cerr<<"fail to get Sockdf";return -1;}
    
    //分配协议端口与ip
    sockaddr_in Saddr{AF_INET,htons(protocol),htonl(ip),0};

    //绑定
    if(bind(SSockfd, (sockaddr *)(&Saddr),sizeof(sockaddr_in))==-1)
    {cerr<<"fail to bind";close(SSockfd);return -1;}
    
    //监听
    cout<<"start to listen"<<endl;
    if(listen(SSockfd,128)){cerr<<"fail to listen";close(SSockfd);return -1;}
    
    while(true)
    {
        sockaddr_in Caddr;
        socklen_t len=sizeof(sockaddr_in);
        const size_t bytesize=64;
        int CSockdf=accept(SSockfd,(sockaddr *)(&Caddr),&len);
        if(CSockdf==-1){cerr<<"fail to get CSocket"<<endl;close(SSockfd);return -1;}
        else cout<<"success to established"<<endl;
        
        //打印ip与端口
        char buf[bytesize];
        memset(&buf,0,bytesize);
        cout<<"ip:"<<inet_ntop(AF_INET,&Caddr.sin_addr,buf,sizeof(buf))<<" "<<"protocol:"<<Caddr.sin_port<<endl;
        
        //接受消息
        memset(&buf,0,bytesize);

        auto rel=read(CSockdf,&buf,size_t(buf));
        if(rel==-1)
        {cerr<<"fail to accept "; close(CSockdf);close(SSockfd);return -1;}
        
        //打印消息
        cout<<"len:"<<rel<<endl<<"context:"<<buf<<endl;
        
        //回复消息
        if(write(CSockdf,&buf,bytesize)==-1)
        {cerr<<"fail to sent "; close(CSockdf);close(SSockfd);return -1;}
        
        close(CSockdf);
    }
    
  
   
    close(SSockfd);
  
    cout<<"close"<<endl;
    return 0;
}
