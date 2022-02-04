// $Id$
//
//    File: JEventProcessor_pi0_pol_plugin.h
// Created: Wed Jun 23 18:19:06 EDT 2021
// Creator:  (on Linux markdesk5.itodomain 5.12.7-300.fc34.x86_64 x86_64)
//

#ifndef _JEventProcessor_pi0_pol_plugin_
#define _JEventProcessor_pi0_pol_plugin_

#include <JANA/JEventProcessor.h>
#include <TFile.h>
#include <TH1F.h>

static TFile* file;
static TH1F* h1;

class JEventProcessor_pi0_pol_plugin:public jana::JEventProcessor{
public:
  JEventProcessor_pi0_pol_plugin();
  ~JEventProcessor_pi0_pol_plugin();
  const char* className(void){return "JEventProcessor_pi0_pol_plugin";}

private:
  jerror_t init(void); ///< Called once at program start.
  jerror_t brun(jana::JEventLoop *eventLoop, int32_t runnumber); ///< Called everytime a new run number is detected.
  jerror_t evnt(jana::JEventLoop *eventLoop, uint64_t eventnumber); ///< Called every event.
  jerror_t erun(void); ///< Called everytime run number changes, provided brun has been called.
  jerror_t fini(void); ///< Called after last event of last event source has been processed.
};

#endif // _JEventProcessor_pi0_pol_plugin_
