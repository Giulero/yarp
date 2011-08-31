// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 *  Yarp Modules Manager
 *  Copyright: Robotics, Brain and Cognitive Sciences - Italian Institute of Technology (IIT)
 *  Authors: Ali Paikan <ali.paikan@iit.it>
 * 
 *  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef __APPLOADER__
#define __APPLOADER__

#include "ymm-types.h" 
#include "application.h"

//namespace ymm {

/**
 * Abstract Class AppLoader  
 */
class AppLoader {

public: 
	AppLoader(void) {}
	~AppLoader() {}
	virtual bool init(void) = 0; 
	virtual void fini(void) = 0;
	virtual Application* getNextApplication(void) = 0;
	
protected:

private:

};
 
//}

#endif //__APPLOADER__
