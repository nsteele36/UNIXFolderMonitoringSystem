//PROGRAM5- INOTIFY FUNCTIONS
//PROGRAMMED BY: NICHOLAS STEELE (NSS150130)
//CS3377.501
#include "program5.h"

//starts inotify
void inotifyStart()
{
    //declare variables
    size_t buffsize = sizeof(struct inotify_event) + PATH_MAX + 1;
    struct inotify_event *event = (struct inotify_event *) malloc(buffsize);
    int length, watchDir;
    int fileDesc= inotify_init();
    int acc = 0;
    
    //if file descriptor returns error print it
    if(fileDesc < 0)
    {    
        cerr << "INOTIFY ERROR: FILE DESCRIPTOR ERROR" << endl;
        return; 
    }

    //start watching the user inputted directory and begin reading
    watchDir = inotify_add_watch(fileDesc, myMap[W_DIR].c_str(), IN_MODIFY | IN_CREATE | IN_DELETE); 
    length = read(fileDesc, event, buffsize);
   
    //if there is an error reading then print and error and exit
    if(length < 0)
    {
        cerr << "INOTIFY ERROR: READ ERROR" << endl;
        return;
    }

    //this function is run every time an event happens
    while(acc < length)
    {
    	//while the event has a length
        if(event->len)
        {
	    //if an object is created in the watch directory, log it
            if(event->mask & IN_CREATE)
            {
                logCreation(event);
            }
	    //if an object is deleted in the watch directory, log it
            if(event->mask & IN_DELETE)
            {
                logDeleted(event);
            }
	    //if an object is modified in the watch directory, log it
            if(event->mask & IN_MODIFY)
            {
                logModified(event);
            }
        }
        acc += sizeof(struct inotify_event) + event->len; 
    }

    //close inotify, the file discriptor, deallocate the point memory, and exit
    inotify_rm_watch(fileDesc, watchDir);
    close(fileDesc);
    free(event);
    return;
}

