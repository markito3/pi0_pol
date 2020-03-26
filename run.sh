#!/bin/bash
source /group/halld/Software/build_scripts/gluex_env_jlab.sh
export JANA_CALIB_CONTEXT="variation=mc_sim1"
echo "Running hdgeant4 ..."
rm -fv run.mac
cat > run.mac <<EOF
/run/beamOn 10000
EOF
command="hdgeant4 run.mac"
echo command = $command
$command
mcsmear hdgeant.hddm
hd_root -PJANA:BATCH_MODE=1 -PPLUGINS=monitoring_hists,danarest,pi0_pol_plugin hdgeant_smeared.hddm
