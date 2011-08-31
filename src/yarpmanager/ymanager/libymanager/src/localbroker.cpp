/*
 *  Yarp Modules Manager
 *  Copyright: Robotics, Brain and Cognitive Sciences - Italian Institute of Technology (IIT)
 *  Authors: Ali Paikan <ali.paikan@iit.it>
 * 
 *  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#include "localbroker.h"

#include <signal.h>

#define YARPRUN_ERROR 		-1
#define RUN_TIMEOUT 		3 //times of 100ms + running() delay = 3s
#define STOP_TIMEOUT 		10
#define KILL_TIMEOUT 		3

using namespace yarp::os;


LocalBroker::LocalBroker()
{
	bOnlyConnector = bInitialized = false;	
	//yarp.setVerbosity(-1);
}


LocalBroker::~LocalBroker()
{
}


bool LocalBroker::init(void)
{
	if(!NetworkBase::checkNetwork())
	{
		strError = "Yarp network server is not up.";
		return false;
	}
	bInitialized = true;
	bOnlyConnector = true;
	return true;
}

bool LocalBroker::init(const char* szcmd, const char* szparam,
			const char* szhost, const char* szstdio,
			const char* szworkdir )
{
	if(!NetworkBase::checkNetwork())
	{
		strError = "Yarp network server is not up.";
		return false;
	}
	
	if(!szcmd)
	{
		strError = "command is not specified.";
		return false;
	}

	if(szhost)
		strHost = szhost;
	else
		strHost = "/localhost";

	if(!exists(strHost.c_str())) // we need to run yarprun as a local server
	{
		/**
		 *  Only on POSIX
		 */ 
		pid_t child_pid;
		child_pid = fork();
		if (child_pid == 0)
		{
			/**
			 *  Now execute PROGRAM, searching for it in the path.
			 */
			execlp("yarprun", "--server", strHost.c_str(), NULL);

			/**
			 *  The execvp function returns only if an error occurs.
			 */
			strError = "An error occurred while running yarprun as a server.";
			return false;
		}
		else
		{
			int w = 0;
			while((w++ < STOP_TIMEOUT) && !exists(strHost.c_str()))
				Time::delay(0.1); 
			if(!exists(szhost))
			{
				strError = strHost;
				strError += " does not exist. Cannot initialize yarprun.";
				return false;
			}		
		}
	}
	
	strCmd = szcmd;	
	if(szparam)
		strParam = szparam;
	if(szworkdir)
		strWorkdir = szworkdir;
	if(szstdio)
		strStdio = szstdio;

	strTag = strHost + strCmd + strParam;
	
	bInitialized = true;			
	return true;
}


bool LocalBroker::run()
{	
	if(!bInitialized) return false;
	if(bOnlyConnector) return false;
	
	strError.clear();
	int ret = requestServer(runProperty());
	if( ret == -1)
	{
		strError = "cannot ask ";
		strError += strHost;
		strError += " to run ";
		strError += strCmd;
		return false;
	}
	
	int w = 0;
	while(w++ < RUN_TIMEOUT)
	{
		if(running())
			return true;
		Time::delay(0.1); 
	}

	strError = "cannot run ";
	strError += strCmd;
	strError += " on ";
	strError += strHost;	
	return false;
}

bool LocalBroker::stop()
{
	if(!bInitialized) return true;
	if(bOnlyConnector) return false;
	
	strError.clear();
	yarp::os::Bottle msg,grp,response;
	
	grp.clear();
	grp.addString("on");
	grp.addString(strHost.c_str());
	msg.addList()=grp;
	grp.clear();
	grp.addString("sigterm");
	grp.addString(strTag.c_str());
	msg.addList()=grp;
    response=SendMsg(msg, strHost.c_str());
	int ret = response.get(0).asString()=="sigterm OK"?0:YARPRUN_ERROR;
	
	if( ret == -1)
	{
		strError = "cannot ask ";
		strError += strHost;
		strError += " to stop ";
		strError += strCmd;
		return false;
	}
	
	int w = 0;
	while(w++ < STOP_TIMEOUT)
	{
		if(!running())
			return true;
		Time::delay(0.1); 
	}

	strError = "Timeout! cannot stop ";
	strError += strCmd;
	strError += " on ";
	strError += strHost;
	return false;
}

bool LocalBroker::kill()
{
	if(!bInitialized) return true;
	if(bOnlyConnector) return false;
	
	strError.clear();
	
	yarp::os::Bottle msg,grp,response;	
	grp.clear();
	grp.addString("on");
	grp.addString(strHost.c_str());
	msg.addList() = grp;
	grp.clear();
	grp.addString("kill");
	grp.addString(strTag.c_str());
	grp.addInt(SIGKILL);
	msg.addList() = grp;
    response = SendMsg(msg, strHost.c_str());
	int ret = response.get(0).asString()=="kill OK"?0:YARPRUN_ERROR;
	if( ret == -1)
	{
		strError = "cannot ask ";
		strError += strHost;
		strError += " to kill ";
		strError += strCmd;
		return false;
	}
	
	int w = 0;
	while(w++ < KILL_TIMEOUT)
	{
		if(!running())
			return true;
		Time::delay(0.1); 
	}

	strError = "cannot kill ";
	strError += strCmd;
	strError += " on ";
	strError += strHost;
	return false;	
}


bool LocalBroker::running(void)
{
	if(!bInitialized) return false;
	if(bOnlyConnector) return false;
	
	strError.clear();
	yarp::os::Bottle msg,grp,response;
	
	grp.clear();
	grp.addString("on");
	grp.addString(strHost.c_str());
	msg.addList()=grp;

	grp.clear();
	grp.addString("isrunning");
	grp.addString(strTag.c_str());
	msg.addList()=grp;
	
    response = SendMsg(msg, strHost.c_str());	
	if (!response.size()) 
		return false;
	return response.get(0).asString()=="running";
}


Property& LocalBroker::runProperty(void)
{
	command.clear();
	string cmd = strCmd + string(" ") + strParam;
	command.put("cmd", cmd.c_str());
	command.put("on", strHost.c_str());
	command.put("as", strTag.c_str());
	if(!strWorkdir.empty())
		command.put("workdir", strWorkdir.c_str());
	if(!strStdio.empty())
		command.put("stdio", strStdio.c_str());
	return command;
}


/**
 *  connecttion broker
 */ 
bool LocalBroker::connect(const char* from, const char* to, 
			const char* carrier)
{
	
	if(!from)
	{
		strError = "no source port is introduced.";
		return false;
	}

	if(!to)
	{
		strError = "no destination port is introduced.";
		return false;
	}

	if(!exists(from))
	{
		strError = from;
		strError += " does not exist.";
		return false;
	}

	if(!exists(to))
	{
		strError = to;
		strError += " does not exist.";
		return false;
	}
		
	if(connected(from, to))
		return true;
		
	if(!NetworkBase::connect(from, to, carrier))
	{
		strError = "cannot connect ";
		strError +=from;
		strError += " to " + string(to);
		return false;
	}
	return true;
}

bool LocalBroker::disconnect(const char* from, const char* to)
{
	
	if(!from)
	{
		strError = "no source port is introduced.";
		return false;
	}

	if(!to)
	{
		strError = "no destination port is introduced.";
		return false;
	}

	if(!exists(from))
	{
		strError = from;
		strError += " does not exist.";
		return false;
	}

	if(!exists(to))
	{
		strError = to;
		strError += " does not exist.";
		return false;
	}
	
	if(!connected(from, to))
		return true;

	if( !NetworkBase::disconnect(from, to))
	{
		strError = "cannot disconnect ";
		strError +=from;
		strError += " from " + string(to);		
		return false;
	}
	return true;
	
}

bool LocalBroker::exists(const char* port)
{
	return NetworkBase::exists(port);
}

bool LocalBroker::connected(const char* from, const char* to)
{
	return NetworkBase::isConnected(from, to);
}


const char* LocalBroker::error(void)
{
	return strError.c_str();
}


/**
 * 
 *  mimicing yarprun
 */ 
Bottle LocalBroker::SendMsg(Bottle& msg,ConstString target)
{
	Port port;
    port.open("...");
    for (int i=0; i<20; ++i)
	{
	    if (NetworkBase::connect(port.getName().c_str(),target.c_str())) break;
	    Time::delay(1.0);
	}
	Bottle response;
    port.write(msg,response);
    NetworkBase::disconnect(port.getName().c_str(),target.c_str());
    port.close();
	return response;
}


int LocalBroker::requestServer(Property& config)
{
	yarp::os::Bottle msg;

	// USE A YARP RUN SERVER TO MANAGE STDIO
	//
	// client -> stdio server -> cmd server
	//
	if (config.check("cmd") && config.check("stdio"))
	{
		if (config.find("stdio")=="") {return YARPRUN_ERROR; }
		if (config.find("cmd")=="")   {return YARPRUN_ERROR; }
		if (!config.check("as") || config.find("as")=="") { return YARPRUN_ERROR; }
		if (!config.check("on") || config.find("on")=="") { return YARPRUN_ERROR; }

		msg.addList()=config.findGroup("stdio");
		msg.addList()=config.findGroup("cmd");
		msg.addList()=config.findGroup("as");
		msg.addList()=config.findGroup("on");
		
		if (config.check("workdir")) msg.addList()=config.findGroup("workdir");
		if (config.check("geometry")) msg.addList()=config.findGroup("geometry");
		if (config.check("hold")) msg.addList()=config.findGroup("hold");

		Bottle response=SendMsg(msg,config.find("stdio").asString());
		if (!response.size()) return YARPRUN_ERROR;
		return response.get(0).asInt()>0?1:0;
	}
	
	// DON'T USE A RUN SERVER TO MANAGE STDIO
	//
	// client -> cmd server
	//
	if (config.check("cmd"))
	{                
		if (config.find("cmd").asString()=="")   { return YARPRUN_ERROR; }
		if (!config.check("as") || config.find("as").asString()=="") {return YARPRUN_ERROR; }
		if (!config.check("on") || config.find("on").asString()=="") {return YARPRUN_ERROR; }

		msg.addList()=config.findGroup("cmd");
		msg.addList()=config.findGroup("as");

		if (config.check("workdir")) msg.addList()=config.findGroup("workdir");

		Bottle response=SendMsg(msg,config.find("on").asString());
		if (!response.size()) return YARPRUN_ERROR;
		return response.get(0).asInt()>0?1:0;
	}
	return 0;
}

