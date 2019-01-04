#ifndef SERVER_H
#define SERVER_H

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 	// 解决冲突的关键
#endif
#include <windows.h>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <wininet.h>

//端口
#define SERVER_PORT 5000

//消息长度
#define MSG_BUF_SIZE 1024

enum ConnectType
{
    None,Browser,Client
};

class Server{
public:
    Server();
    ~Server();
    //不生成默认的拷贝函数
    Server(const Server&) = delete;
    //不生成“=”运算符重载函数
    Server& operator=(const Server&) = delete;
    //等待客户端连接
    void WaitForClient();

protected:
    /**win套接字版本*/
    WORD winsock_ver;
    /**wsa数据*/
    WSADATA wsa_data;
    /**服务器套接字*/
    SOCKET sock_srv;
    /**客户端套接字*/
    SOCKET sock_clt;
    /**服务端线程句柄*/
    HANDLE h_thread;
    /**服务端地址*/
    SOCKADDR_IN addr_srv;
    /**客户端地址*/
    SOCKADDR_IN addr_clt;

    /***/
    int ret_val;
    /**网络地址长度*/
    int addr_len;
    //根据连接类型创建对应的线程
    void SwitchThreaad(ConnectType&);
    //关闭套接字连接
    bool CloseConnect(SOCKET);

};


#endif