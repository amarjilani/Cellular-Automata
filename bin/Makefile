DATA_DIR = ../src/Visualization

TESTS = test_cell test_none_boundary test_periodic_boundary test_simple test_traffic test_walled_boundary

# runs csv test and moves file to visualization folder 
run_test_csv: test_csv
	./test_csv
	mv test.csv ${DATA_DIR}

run_all: $(TESTS)
	./test_cell
	./test_none_boundary
	./test_periodic_boundary
	./test_simple
	./test_traffic
	./test_walled_boundary



