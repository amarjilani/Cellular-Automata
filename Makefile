.PHONY: environment remove-env
ENVIRONMENT=CAlib
RANGEN_DIR = utils/Rangen
TEST_DIR = tests/
EX_APP_DIR = examples/application
EX_BIN_DIR = examples/bin 


# Environment needed for visualization
environment: remove-env
	conda env create -f environment.yaml

# Remove environment 
remove-env:
	conda remove --name ${ENVIRONMENT} --all --yes

all:
	cd ${RANGEN_DIR}; make all;
	cd ${TEST_DIR}; make all;
	cd ${EX_APP_DIR}; make all; 
	cd ${EX_BIN_DIR}; make all; 

cleanall:
	cd ${RANGEN_DIR}; make cleanall; 
	cd ${TEST_DIR}; make cleanall;
	cd ${EX_APP_DIR}; make cleanall;
	cd ${EX_BIN_DIR}; make cleanall;
