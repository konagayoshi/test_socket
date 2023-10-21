// server

#include <unistd.h>
#include <string>
#include <vector>
#include <deque>
#include "comm_socket.h"

int main(int argc, char **argv)
{
    comm_data comm;
    std::string client_addr;
    std::vector<std::string> commands = { "EDD", "FWD", "BWD", "STP", "LFT", "RGT", "CNT" };
    int end_loop = 0;
	    
    if( comm_server_init_wait( comm, client_addr ) )
    {
        fprintf( stderr, "Failed to initialize communication\n" );
        return 1;
    }

    data_sender_data dsender;
    if( data_sender_init( dsender, client_addr ) )
    {
        fprintf( stderr, "Error initializing data_sender\n" );
        comm_fina( comm );
        return 1;
    }

    while( 1 )
    {
        usleep(100);
	
        int command = comm_check_cmds( comm, commands );
        if( command >= 0 )
        {


            switch( command )
            {
	    case 0:
                end_loop = 1;
	        printf("end loop\n");
                break;
	    
	    case 1:
	    case 2:
	    case 3:
	    case 4:
	    case 5:
	    case 6:
                printf("receive command %s\n", commands[command].c_str());
                break;
	    default:
                printf("unknown command\n");
                break;
            }
        }

	if(end_loop)
            break;
    }

    if( data_sender_fina( dsender ) )
    {
        fprintf( stderr, "Error finalizing data_sender\n" );
    }
    comm_fina( comm );
    
    return 0;
}    
