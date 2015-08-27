// $Id$
//
//    File: JEventProcessor_pi0_pol_plugin.cc
// Created: Thu Aug 27 15:53:07 EDT 2015
// Creator: marki (on Linux ifarm1401 2.6.32-431.el6.x86_64 x86_64)
//

#include "JEventProcessor_pi0_pol_plugin.h"
using namespace jana;


// Routine used to create our JEventProcessor
#include <JANA/JApplication.h>
#include <JANA/JFactory.h>
extern "C"{
void InitPlugin(JApplication *app){
	InitJANAPlugin(app);
	app->AddProcessor(new JEventProcessor_pi0_pol_plugin());
}
} // "C"


//------------------
// JEventProcessor_pi0_pol_plugin (Constructor)
//------------------
JEventProcessor_pi0_pol_plugin::JEventProcessor_pi0_pol_plugin()
{

}

//------------------
// ~JEventProcessor_pi0_pol_plugin (Destructor)
//------------------
JEventProcessor_pi0_pol_plugin::~JEventProcessor_pi0_pol_plugin()
{

}

//------------------
// init
//------------------
jerror_t JEventProcessor_pi0_pol_plugin::init(void)
{
	// This is called once at program startup. If you are creating
	// and filling historgrams in this plugin, you should lock the
	// ROOT mutex like this:
	//
	// japp->RootWriteLock();
	//  ... fill historgrams or trees ...
	// japp->RootUnLock();
	//

	return NOERROR;
}

//------------------
// brun
//------------------
jerror_t JEventProcessor_pi0_pol_plugin::brun(JEventLoop *eventLoop, int runnumber)
{
	// This is called whenever the run number changes
	return NOERROR;
}

//------------------
// evnt
//------------------
jerror_t JEventProcessor_pi0_pol_plugin::evnt(JEventLoop *loop, int eventnumber)
{
	// This is called for every event. Use of common resources like writing
	// to a file or filling a histogram should be mutex protected. Using
	// loop->Get(...) to get reconstructed objects (and thereby activating the
	// reconstruction algorithm) should be done outside of any mutex lock
	// since multiple threads may call this method at the same time.
	// Here's an example:
	//
	// vector<const MyDataClass*> mydataclasses;
	// loop->Get(mydataclasses);
	//
	// japp->RootWriteLock();
	//  ... fill historgrams or trees ...
	// japp->RootUnLock();


	return NOERROR;
}

//------------------
// erun
//------------------
jerror_t JEventProcessor_pi0_pol_plugin::erun(void)
{
	// This is called whenever the run number changes, before it is
	// changed to give you a chance to clean up before processing
	// events from the next run number.
	return NOERROR;
}

//------------------
// fini
//------------------
jerror_t JEventProcessor_pi0_pol_plugin::fini(void)
{
	// Called before program exit after event processing is finished.
	return NOERROR;
}

