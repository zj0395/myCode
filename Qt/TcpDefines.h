#ifndef TCPDEFINES_H
#define TCPDEFINES_H

#define PORT 8888

//套接字传送的消息的格式：
//为方便表示，    下面均用 '-' 表示 换行符 '\n'
//登录及注册：    "MessageType-Name-PassWord"
//登录及注册成功： "MessageType-UserName"
//用户发送的消息： "MessageType-FromUserName-DestUserName-Message"
//消息发送成功：   "MessageType- "
//更新用户列表：   "MessageType-用户信息-用户信息-用户信息-..."，用户信息的格式为 "0UserName" 或 "1UserName" 来区分在线状态

enum MessageType{

    //send to server
    M_Login = 0,
    M_Register,
    M_Logout,


    //send to user
    M_SendSuccess = 20,
    M_LoginSuccess,
    M_RegisterSuccess,
    M_WrongPassword,
    M_WrongUserName,
    M_UserNameExist,
    M_DestNotExist,
    M_DestNotOnLine,


    //double sended
    M_Message = 40,
    M_UpdateUserList,


    //only use in private
    M_SqlInsertWrong = 60,

};

#endif // TCPDEFINES_H
