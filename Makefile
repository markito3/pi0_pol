ifndef NEVENTS
    NEVENTS=10000
endif

all: env_check hd_root.root

env_check:
	@echo PI0_POL = $(PI0_POL)
	@if [ -z $(PI0_POL) ]; then echo PI0_POL undefined; exit 1; fi
	@if [ ! -d $(PI0_POL) ]; then echo directory PI0_POL does not exist; exit 2; fi

control.in: $(PI0_POL)/control.in
	cp -pv $< .

hdgeant.hddm: control.in
	rm -fv run.mac
	echo /run/beamOn $(NEVENTS) > run.mac
	hdgeant4 run.mac

hdgeant_smeared.hddm: hdgeant.hddm
	mcsmear hdgeant.hddm

hd_root.root: hdgeant_smeared.hddm
	hd_root -PJANA:BATCH_MODE=1 -PPLUGINS=monitoring_hists,danarest,pi0_pol_plugin hdgeant_smeared.hddm

clean:
	$(RM) hdgeant.hddm hdgeant_smeared.hddm hd_root.root
