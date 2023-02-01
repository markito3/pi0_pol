// $Id$
//
//    File: JEventProcessor_pi0_pol_plugin.cc
// Created: Wed Jun 23 18:19:06 EDT 2021
// Creator:  (on Linux markdesk5.itodomain 5.12.7-300.fc34.x86_64 x86_64)
//

#include "JEventProcessor_pi0_pol_plugin.h"
using namespace std;
using namespace jana;

// Routine used to create our JEventProcessor
#include <JANA/JApplication.h>
#include <JANA/JFactory.h>
#include <PID/DNeutralParticle.h>
#include "TMath.h"
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
  cout << "in the constructor" << endl;
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
  // This is called once at program startup. 
  Int_t bins = 20;
  Double_t xlow = -0.5, xhigh = 19.5;
  file = new TFile("p0p.root", "RECREATE");
  h1 = new TH1F("Nnc", "Neutral Particle Multiplicity", bins, xlow, xhigh);
  bins = 50; xlow = 0; xhigh = 10.0;
  h2 = new TH1F("neutral particle energy", "neutral particle energy", bins, xlow, xhigh);
  h3 = new TH1F("two-photon mass", "two-photon mass", bins = 50, xlow = 0.0, xhigh = 1.0);
  return NOERROR;
}

//------------------
// brun
//------------------
jerror_t JEventProcessor_pi0_pol_plugin::brun(JEventLoop *eventLoop, int32_t runnumber)
{
	// This is called whenever the run number changes
	return NOERROR;
}

//------------------
// evnt
//------------------
jerror_t JEventProcessor_pi0_pol_plugin::evnt(JEventLoop *loop, uint64_t eventnumber)
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
  // japp->RootFillLock(this);
  //  ... fill historgrams or trees ...
  // japp->RootFillUnLock(this);

  cout << "evnt called" << endl;
  vector<const DNeutralParticle*>neutrals;
  loop->Get(neutrals);
  double E;
  DLorentzVector gam1, gam2;
  Double_t twoGammaMass;
  unsigned int nneut = neutrals.size();
  cout << "nneut = " << nneut << endl;
  for (unsigned int i=0;i<nneut;i++){
    gam1=neutrals[i]->Get_Hypothesis(Gamma)->lorentzMomentum();
    E = gam1.E();
    cout << "i = " << i << " E = " << E << endl;
    h2->Fill(E);
    for (unsigned int j = i + 1; j < nneut; j++) {
      cout << "i = " << i << " j = " << j << endl;
      gam2=neutrals[j]->Get_Hypothesis(Gamma)->lorentzMomentum();
      twoGammaMass = gam1*gam2;
      cout <<"twoGammaMass = " << twoGammaMass << endl;
      h3->Fill(TMath::Sqrt(twoGammaMass));
    }
  }
  double di = (double)neutrals.size();
  h1->Fill(di);
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
  gDirectory->ls();
  file->Write();
  return NOERROR;
}

