// client

#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include "comm_socket.h"

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

static int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

std::map<int, std::string> commands{
    {27, "EDD"},
    {'i', "FWD"},
    {'k', "BWD"},
    {' ', "STP"},
    {'j', "LFT"},
    {'l', "RGT"},
    {',', "CNT"}
};

static void send_cmd( comm_data &comm, int key )
{
    comm_send_cmd( comm, commands[key].c_str() );
    printf("send command %s\n", commands[key].c_str());
}

int main(int argc, char **argv)
{
    std::string server_ip;
    std::string client_ip;
    comm_data comm;
    
    if( argc != 3 )
    {
        fprintf( stderr, "Usage: %s <server_ip> <client_ip>\n", argv[0] );
        return 1;
    }
    else
    {
        server_ip = argv[1];
        client_ip = argv[2];
    }

    if( comm_client_init_connect( comm, server_ip, client_ip, 9876 ) )
    {
        return 1;
    }

    printf("Please input command\n");
    printf("i : FWD\n" );
    printf("k : BWD\n" );
    printf("j : LFT\n" );
    printf("l : RGT\n" );
    printf(", : CNT\n" );
    printf("SPACE : STP\n" );
    printf("ESC : EDD\n" );

    while( 1 )
    {
        usleep(100);
      
        if (kbhit()) {

            int key = getchar();
            printf("\n");

	
            if( key == 27 )
            {
                if( comm_send_cmd( comm, "EDD" ) == 4 )
                {
                    break;
                }
            }
            else
            {
                switch( key )
                {
                case 'i': 
                case 'k': 
                case ' ': 
                case 'j': 
                case 'l': 
                case ',': 
                    send_cmd(comm, key);
                    break;
	      
                default:
                    printf("unknown command\n");
                    break;
                }
            }
	
        }
    }
    
    comm_send_cmd( comm, "EDD" );
    comm_fina( comm );
    
    return 0;
}    
