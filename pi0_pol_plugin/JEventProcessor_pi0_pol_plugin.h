// $Id$
//
//    File: JEventProcessor_pi0_pol_plugin.h
// Created: Thu Aug 27 15:53:07 EDT 2015
// Creator: marki (on Linux ifarm1401 2.6.32-431.el6.x86_64 x86_64)
//

#ifndef _JEventProcessor_pi0_pol_plugin_
#define _JEventProcessor_pi0_pol_plugin_

#include <JANA/JEventProcessor.h>

class JEventProcessor_pi0_pol_plugin:public jana::JEventProcessor{
	public:
		JEventProcessor_pi0_pol_plugin();
		~JEventProcessor_pi0_pol_plugin();
		const char* className(void){return "JEventProcessor_pi0_pol_plugin";}

	private:
		jerror_t init(void);						///< Called once at program start.
		jerror_t brun(jana::JEventLoop *eventLoop, int runnumber);	///< Called everytime a new run number is detected.
		jerror_t evnt(jana::JEventLoop *eventLoop, int eventnumber);	///< Called every event.
		jerror_t erun(void);						///< Called everytime run number changes, provided brun has been called.
		jerror_t fini(void);						///< Called after last event of last event source has been processed.
};

#endif // _JEventProcessor_pi0_pol_plugin_

