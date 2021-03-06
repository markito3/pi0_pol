// $Id$
//
//    File: JEventProcessor_pi0_pol_plugin.cc
// Created: Thu Aug 27 15:53:07 EDT 2015
// Creator: marki (on Linux ifarm1401 2.6.32-431.el6.x86_64 x86_64)
//

#include "JEventProcessor_pi0_pol_plugin.h"
using namespace std;
using namespace jana;


// Routine used to create our JEventProcessor
#include <JANA/JApplication.h>
#include <JANA/JFactory.h>
#include <PID/DNeutralParticle.h>
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

  cout << "init called" << endl;

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

  cout << "evnt called" << endl;

  vector<const DNeutralParticle*>neutrals;
  loop->Get(neutrals);
  for (unsigned int i=0;i<neutrals.size();i++){
    DLorentzVector gam1=neutrals[i]->Get_Hypothesis(Gamma)->lorentzMomentum();
    cout << i << endl;
  }
  
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

  cout << "fini called" << endl;

  return NOERROR;
}

