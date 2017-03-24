#include "Linux_SerailCom.h"


#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

int Linux_SerailCom::set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop)
{
    struct termios newtio,oldtio;
    if  ( tcgetattr( fd,&oldtio)  !=  0)
    {
        perror("SetupSerial 1");
        return -1;
    }
    bzero( &newtio, sizeof( newtio ) );
    newtio.c_cflag  |=  CLOCAL | CREAD;
    newtio.c_cflag &= ~CSIZE;

    switch( nBits )
    {
    case 7:
        newtio.c_cflag |= CS7;
        break;
    case 8:
        newtio.c_cflag |= CS8;
        break;
    }

    switch( nEvent )
    {
    case 'O':                     //奇校验
        newtio.c_cflag |= PARENB;
        newtio.c_cflag |= PARODD;
        break;
    case 'E':                     //偶校验
        newtio.c_cflag |= PARENB;
        newtio.c_cflag &= ~PARODD;
        break;
    case 'N':                    //无校验
        newtio.c_cflag &= ~PARENB;
        break;
    default:
        return -1;
    }

switch( nSpeed )
    {
    case 2400:
    printf("2400\n");
        cfsetispeed(&newtio, B2400);
        cfsetospeed(&newtio, B2400);
        break;
    case 4800:
    printf("4800\n");
        cfsetispeed(&newtio, B4800);
        cfsetospeed(&newtio, B4800);
        break;
    case 9600:
    printf("9600\n");
        cfsetispeed(&newtio, B9600);
        cfsetospeed(&newtio, B9600);
        break;
    case 115200:
        printf("115200\n");
        cfsetispeed(&newtio, B115200);
        cfsetospeed(&newtio, B115200);
        break;
    default:
    printf("default\n");
        cfsetispeed(&newtio, B9600);
        cfsetospeed(&newtio, B9600);
        break;
    }

    if( nStop == 1 )
    {
        newtio.c_cflag &=  ~CSTOPB;
    }
    else if ( nStop == 2 )
    {
        newtio.c_cflag |=  CSTOPB;
    }
	
	//----------------for test-------------
	/* Raw input */
    newtio.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

    /* C_IFLAG      Input options

       Constant     Description
       INPCK        Enable parity check
       IGNPAR       Ignore parity errors
       PARMRK       Mark parity errors
       ISTRIP       Strip parity bits
       IXON Enable software flow control (outgoing)
       IXOFF        Enable software flow control (incoming)
       IXANY        Allow any character to start flow again
       IGNBRK       Ignore break condition
       BRKINT       Send a SIGINT when a break condition is detected
       INLCR        Map NL to CR
       IGNCR        Ignore CR
       ICRNL        Map CR to NL
       IUCLC        Map uppercase to lowercase
       IMAXBEL      Echo BEL on input line too long
    */
    if (nEvent == 'N') {
        /* None */
        newtio.c_iflag &= ~INPCK;
    } else {
        newtio.c_iflag |= INPCK;
    }

    /* Software flow control is disabled */
    newtio.c_iflag &= ~(IXON | IXOFF | IXANY);

    /* C_OFLAG      Output options
       OPOST        Postprocess output (not set = raw output)
       ONLCR        Map NL to CR-NL

       ONCLR ant others needs OPOST to be enabled
    */

    /* Raw ouput */
    newtio.c_oflag &=~ OPOST;
	//-------------------------------------
    newtio.c_cc[VTIME]  = 1/*40*/;/* Set timeout of 4.0 seconds */
    newtio.c_cc[VMIN] = 0;
    tcflush(fd,TCIFLUSH);
    if((tcsetattr(fd,TCSANOW,&newtio))!=0)
    {
        perror("com set error");
        return -1;
    }
    printf("set done!\n");
    return 0;
}

int Linux_SerailCom::open_port(char* portName,int flag/*0阻塞 其它非阻塞*/)
{
    if(flag == 0)
    {
        fd = open(portName, O_RDWR|O_NOCTTY);//以阻塞型式打开串口
    }
    else
    {
        fd = open(portName,  O_RDWR | O_NOCTTY | O_NDELAY | O_EXCL);//以非阻塞型式打开串口
    }

    if (-1 == fd)
    {
        perror("Can't Open Serial Port");
        return(-1);
    }

    if(fcntl(fd, F_SETFL, 0)<0)
    {
        printf("fcntl failed!\n");
    }

    if(isatty(STDIN_FILENO)==0)
    {
        printf("standard input is not a terminal device\n");
    }

    return fd;
}

Linux_SerailCom::Linux_SerailCom():fd(0)
{

}

Linux_SerailCom::~Linux_SerailCom()
{
   this->Close();
}

int Linux_SerailCom::Open(char *portName,int baud,char parity,int data_bit,int stop_bit,int flag)
{

    if((fd=open_port(portName,flag/*是否阻塞*/))<0)
    {
        perror("open_port error");
        _isOpened = false;
        return -1;
    }

    if(set_opt(fd,baud,data_bit,parity,stop_bit)<0)
    {
        perror("set_opt error");
        _isOpened = false;
        return -2;
    }

     _isOpened = true;

    return 0;
}

bool Linux_SerailCom::IsOpen()
{
    return _isOpened;
}

int Linux_SerailCom::Read(char *buf, int maxBufsize)
{
    return read(fd,buf,maxBufsize);
}

int Linux_SerailCom::Write(char *buf, int maxBufsize)
{
    return write(fd,buf,maxBufsize);
}

void Linux_SerailCom::Close()
{
    close(fd);
}


