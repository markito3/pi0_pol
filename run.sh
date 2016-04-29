#!/bin/sh
source /group/halld/Software/build_scripts/gluex_env_jlab.sh
hdgeant
mcsmear hdgeant.hddm
hd_root -PPLUGINS=monitoring_hists,danarest,pi0_pol_plugin hdgeant_smeared.hddm
