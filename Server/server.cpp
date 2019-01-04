//winsock实现部分代码
// Created by longx on 2018/12/2.
//

#include "server.h"
#include <iostream>
#include <conio.h>
#include <fstream>
#include <time.h>
#include <exception>
using  std::ofstream;
using  std::cout;
using  std::endl;
using  std::cerr;

//浏览器连接线程
DWORD WINAPI BrowserThread(LPVOID lpParameter);
//客户端连接线程
DWORD WINAPI CreateClientThread(LPVOID lpParameter);
//写入文件
bool WirteFile(char* buf);
CRITICAL_SECTION file_thread;//线程锁

Server::Server() {
    cout << "++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "+       Begin starting server...           +" << endl;
    //设置winsock版本
    winsock_ver = MAKEWORD(2,2);
    //设置IP地址长度
    addr_len = sizeof(SOCKADDR_IN);
    //设置为IPV4协议
    addr_srv.sin_family = AF_INET;
    //设置监听端口
    addr_srv.sin_port = ::htons(SERVER_PORT);
    //设置为所有IP地址段都可连接
    addr_srv.sin_addr.S_un.S_addr = INADDR_ANY;


    //启动
    ret_val = ::WSAStartup(winsock_ver,&wsa_data);
    if(ret_val != 0)
    {
        cerr << ">> Start WSA failed with erorr code: " << ::WSAGetLastError() << " <<" << endl;
        ::getch();
        exit(1);
    }
    cout << "+       WSA start success...               +" << endl;
    //
    sock_srv = ::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(sock_srv == INVALID_SOCKET)
    {
        cerr << ">> Start socket failed with erorr code: " << ::WSAGetLastError() << " <<" << endl;
        ::WSACleanup();
        ::getch();
        exit(1);
    }
    cout << "+       Create socket success...           +" << endl;
    //绑定监听端口
    ret_val = ::bind(sock_srv,(SOCKADDR*)&addr_srv,addr_len);
    if(ret_val != 0)
    {
        cerr << ">> Bind the port failed with erorr code: " << ::WSAGetLastError() << " <<" << endl;
        ::WSACleanup();
        ::getch();
        exit(1);
    }
    cout << "+       Bind the socket success...         +" << endl;
    //服务端开始监听
    ret_val = ::listen(sock_srv,SOMAXCONN);
    if(ret_val == SOCKET_ERROR)
    {
        cerr << ">> Server listening failed with erorr code: " << ::WSAGetLastError() << " <<" << endl;
        ::WSACleanup();
        ::getch();
        exit(1);
    }
    cout << "+       Server socket starts listening...  +" << endl;

    //
    cout << "+       Start server success...            +" << endl;
    cout << "++++++++++++++++++++++++++++++++++++++++++++" << endl;

}

Server::~Server() {
    //关闭套接字
    ::closesocket(sock_srv);
    ::closesocket(sock_clt);
    //关闭WSA
    ::WSACleanup();
    cout << "##       Stop server success...           ##" << endl;
}



void Server::WaitForClient() {
    cout << "[Start]:Waiting for connecting... " << endl;
    char buf_msg[MSG_BUF_SIZE];
    int ret_val = 0;
    int send_result = 0;
    ConnectType connectType = None;
    while (true)
    {
        sock_clt = accept(sock_srv,(SOCKADDR*)&addr_clt,&addr_len);
        if(sock_clt == INVALID_SOCKET)
        {
            cerr << "[Error]:Accept client failed with error code:" << ::WSAGetLastError() << endl;
            ::WSACleanup();
            ::getch();
            exit(1);
        }

        //判断连接类型
        memset(buf_msg,0,MSG_BUF_SIZE);
        ret_val = ::recv(sock_clt,buf_msg,MSG_BUF_SIZE,0);
        if(ret_val > 0)
        {
            if(strcmp(buf_msg,"ATM Requests a connection") == 0)
            {
                cout  << "[Note]:A new client Requests a connection from <IP: " << ::inet_ntoa(addr_clt.sin_addr) << " >" << " && "
                      << "<Port: " << ::ntohs(addr_clt.sin_port) << ">" << endl;
                send_result = ::send(sock_clt,"200", MSG_BUF_SIZE,0);
                if(send_result == SOCKET_ERROR)
                {
                    cerr << "[Error]:Send message to client failed with error code:"
                         << ::WSAGetLastError() << endl;
                    ::closesocket(sock_clt);
                    continue;
                }
                connectType = Client;
            } else if(strstr(buf_msg, "GET") != NULL)
            {
                cout  << "[Note]:A new Browser Requests a connection from <IP: " << ::inet_ntoa(addr_clt.sin_addr) << " >" << " && "
                      << "<Port: " << ::ntohs(addr_clt.sin_port) << ">" << endl;
                send_result = ::send(sock_clt,"200", MSG_BUF_SIZE,0);
                if(send_result == SOCKET_ERROR)
                {
                    cerr << "[Error]:Send message to client failed with error code:"
                         << ::WSAGetLastError() << endl;
                    CloseConnect(sock_clt);
                    continue;
                }
                connectType = Browser;
            } else
            {
                connectType = None;
            }
        } else if(ret_val == 0)
        {
            CloseConnect(sock_clt);
            continue;
        }
        cout << "[Note]:Begin create thread connection for socket <" << sock_clt << ">" << endl;
        //创建对应的进程
        SwitchThreaad(connectType);
        if(h_thread == NULL)
        {
            cerr << "[Error]:Create thread failed with error code:" << ::WSAGetLastError() << endl;
            ::WSACleanup();
            continue;
        }
        cout << "[Note]:The connect thread has created.< id = " << h_thread << ",socket = " << sock_clt << " >" << endl;
        ::CloseHandle(h_thread);
    }
}
//关闭套接字连接
bool Server::CloseConnect(SOCKET socketfd)
{
    int ret_num;
    cout << "[Note]:Closing socket < " << socketfd << " >..." << endl;
    ret_num = ::shutdown(socketfd,SD_SEND);
    if(ret_num == SOCKET_ERROR)
    {
        cerr << "[Error]:Close Client socket failed with error code: "
             << WSAGetLastError() << endl;
        ::closesocket(socketfd);
        return false;
    }
    return true;
}
void Server::SwitchThreaad(ConnectType &connection) {
    switch (connection)
    {
        case None:
            h_thread == NULL;
            break;
        case Browser:
            h_thread = ::CreateThread(nullptr,0,BrowserThread,(LPVOID)sock_clt,0, nullptr);
            break;
        case Client:
            h_thread = ::CreateThread(nullptr,0,CreateClientThread,(LPVOID)sock_clt,0, nullptr);
            break;
    }
}

DWORD WINAPI BrowserThread(LPVOID lpParameter)
{
    SOCKET sock_clt = (SOCKET)lpParameter;
    char buf_msg[MSG_BUF_SIZE] = {'\0'};
    int ret_val = 0;
    //制作头信息
    strcat(buf_msg,"HTTP/1.1 200 OK\r\n");
    strcat(buf_msg,"Content-Type: text/html\r\n");
    strcat(buf_msg,"\r\n");
    strcat(buf_msg,"12321");

    ret_val = ::send(sock_clt,buf_msg,strlen(buf_msg),0);
    if(ret_val <= 0)
    {
        cerr << "[Error]:Send html to Browser failed with error code: "
             << WSAGetLastError() << endl;
        ::closesocket(sock_clt);
        return 1;
    }
    ::closesocket(sock_clt);
    ret_val = ::shutdown(sock_clt,SD_SEND);
    if(ret_val == SOCKET_ERROR)
    {
        cerr << "[Error]:Close Client socket failed with error code: "
             << WSAGetLastError() << endl;
        ::closesocket(sock_clt);
        return 1;
    }
    return 0;
}

DWORD WINAPI CreateClientThread(LPVOID lpParameter)
{
    SOCKET sock_clt = (SOCKET)lpParameter;
    char buf_msg[MSG_BUF_SIZE];
    int ret_val = 0;
    do
    {
        memset(buf_msg,0,MSG_BUF_SIZE);
        ret_val = ::recv(sock_clt,buf_msg,MSG_BUF_SIZE,0);
        if(ret_val > 0)
        {
            if(strcmp(buf_msg,"close") == 0)
             {
                cout << "[Note]:The client< " << sock_clt << " >Request to close connection" << endl;
                break;
            }
            cout << "[MSG]:Message Received: { " << buf_msg << " }" << endl;
            //EnterCriticalSection(&file_thread);//上锁
            WirteFile(buf_msg);
            //LeaveCriticalSection(&file_thread);//解锁
        }
        else if(ret_val == 0)
        {
            cout << "[Note]:Closing socket < " << sock_clt << " >..." << endl;

        }
        else
        {
            cerr << "[Error]:Receive message from client failed with error code: "
                 << WSAGetLastError() << endl;
            ::closesocket(sock_clt);
            cout << "[Note]:Closing socket < " << sock_clt << " >..." << endl;
            return 1;
        }
    }while (ret_val > 0);
    ret_val = ::shutdown(sock_clt,SD_SEND);
    if(ret_val == SOCKET_ERROR)
    {
        cerr << "[Error]:Close Client socket failed with error code: "
             << WSAGetLastError() << endl;
        ::closesocket(sock_clt);
        return 1;
    }
    return 0;
}
bool WirteFile(char* buf)
{
    char fileName[64];
    char *time_str;
    time_t time_now = time(0);
    ofstream file;
    time_str =  ctime(&time_now);
    sprintf(fileName, "report.txt");
    try
    {
        file.open(fileName,std::ios::app);

    }
    catch (std::exception)
    {
        return false;
    }
    file << "+------------------------------------------BEGIN---------------------------------------------------+" << endl;
    file <<  time_str << "\n" << buf << endl;
    file << "+-------------------------------------------END----------------------------------------------------+" << endl;
    file.close();
    return true;
}