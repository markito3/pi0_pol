#!/bin/sh
source /group/halld/Software/build_scripts/gluex_env_jlab.sh
export JANA_CALIB_CONTEXT="variation=mc_sim1"
hdgeant
mcsmear hdgeant.hddm
hd_root -PJANA:BATCH_MODE=1 -PPLUGINS=monitoring_hists,danarest,pi0_pol_plugin hdgeant_smeared.hddm
