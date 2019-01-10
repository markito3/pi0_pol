#!/bin/sh
setup_gluex
export JANA_CALIB_CONTEXT="variation=mc_sim1"
hdgeant
mcsmear hdgeant.hddm
hd_root -PJANA:BATCH_MODE=1 -PPLUGINS=monitoring_hists,danarest,pi0_pol_plugin hdgeant_smeared.hddm
