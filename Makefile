all: hd_root.root

hdgeant.hddm:
	rm -fv run.mac ; \
	echo /run/beamOn 10000 > run.mac ; \
	hdgeant4 run.mac

hdgeant_smeared.hddm: hdgeant.hddm
	mcsmear hdgeant.hddm

hd_root.root: hdgeant_smeared.hddm
	hd_root -PJANA:BATCH_MODE=1 -PPLUGINS=monitoring_hists,danarest,pi0_pol_plugin hdgeant_smeared.hddm

clean:
	$(RM) hdgeant.hddm hdgeant_smeared.hddm hd_root.root
