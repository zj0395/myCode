#ifndef TCPDEFINES_H
#define TCPDEFINES_H

#define PORT 8888

enum MessageType{
    M_Login = 0,
    M_Register,
    M_Message,
    M_LoginSuccess,
    M_RegisterSuccess,

    //return to sender
    M_Success = 10,
    M_SendSuccess,
    M_WrongPassword,
    M_WrongUserName,
    M_UserNameExist,
    M_DestNotExist,
    M_DestNotOnLine,
    M_EmptyMsg,
};

#endif // TCPDEFINES_H
