//PROGRAM 5: SIGNAL HANDLING FILE
//PROGRAMMED BY: NICHOLAS STEELE (NSS150130)
//CS3377.501
#include "program5.h"

//this functions removes the daemons PID file, closes the log and exits the daemon
void killDaemon(int signal_num)
{    
	removePID();
	closeLog();
	exit(signal_num);
}

//this function reconfigures 
void reconfigure(int signal_num)
{
	parseconfigfile();
}

//this function is the main signal handler
void signalHandling()
{
	signal(SIGINT, killDaemon);
	signal(SIGTERM, killDaemon);
	signal(SIGHUP, reconfigure);
}

