//PROGRAM5-PARSECOMMANDLINE FILE
//PROGRAMED BY:NICHOLAS STEELE (NSS150130)
//CS3377.501
#include "program5.h"
//TCLAP FILES
#include <tclap/SwitchArg.h>
#include <tclap/ValueArg.h>
#include <tclap/UnlabeledValueArg.h>
#include <tclap/CmdLine.h>

//parses command line and adds respective values to a map containing flags for arguments and strings for file names
void parsecmdline(int argc, char* argv[])
{
  
  try{
    //TCLAP object declarations
    TCLAP::CmdLine cmd("CS3376.502 Program 5", ' ', "1.0"); 
    TCLAP::UnlabeledValueArg<string> confFile("conffile", "The name of the configuration file. Defaults to cs3377dirmond.conf", false, "cs3377dirmond.conf", "config filename");
    TCLAP::SwitchArg dFlag("d", "deaemon", "Run in deaemon mode (forks to run as a daemon).", cmd, false);

    //add flag and value arguments to the commandline object
    cmd.add(confFile);

    //read the inputted command line arguments entered into the program
    cmd.parse(argc, argv);

    //check if the user wants to run program in daemon mode
    if(dFlag.getValue())
	    myMap[DMODE] = "true";
    else
	    myMap[DMODE] = "false";

    //save the user inputted config file to the input file name string variable in the map
    myMap[CONF] = confFile.getValue();
  }

    //if the user enters invalid arguments into the command line, report the error and exit the program 
  catch(TCLAP::ArgException &e){
      cerr << "error: " << e.error() << " for arg " << e.argId() << endl;
      exit(0);
  }    
}
