#ifndef LINUX_SERAILCOM_H
#define LINUX_SERAILCOM_H


class Linux_SerailCom
{
public:
    Linux_SerailCom();
    ~Linux_SerailCom();

    int Open(char *portName, int baud, char parity, int data_bit, int stop_bit, int flag=0/*0阻塞 其它非阻塞*/);
    void Close();
    int Read(char* buf,int maxBufsize);
    int Write(char* buf,int maxBufsize);
    bool IsOpen();

private:
    int fd;
    bool _isOpened;

    int set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop);
    int open_port(char* portName, int flag=0/*0阻塞 其它非阻塞*/);


};

#endif // LINUX_SERAILCOM_H
