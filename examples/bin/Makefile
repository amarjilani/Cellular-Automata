# Chem 274B: Software Engineering Fundamentals for
#            Molecular Sciences
#
# Creator:  Patrick Neal, Cameron Hu, Aamar Jilani
#
# Directory Path> 274B-Final/tests

VIS_DIR = ../../utils/Visualization/

###################################################################################

ALLPLOTS = traffic_simulation_plot compare_flat_rates_plot

###################################################################################

traffic_simulation_plot:
	echo "10" > input.txt
	echo "100" >> input.txt
	echo "0.01" >> input.txt
	echo "traffic_simulation.csv" >> input.txt
	echo "100" >> input.txt
	./traffic_simulation < input.txt
	python $(VIS_DIR)/ca_plot.py traffic_simulation.csv traffic_simulation_images  --gif True --height 5 --width 15 --colors "{0:'grey',1:'red',2:'green',3:'yellow'}"
	mv output.gif traffic_simulation.gif

compare_flat_rates_plot:
	./compare_flat_rates > velocities.txt
	python $(VIS_DIR)/ca_plot.py compare_flat_rates.csv compare_flat_rates_images --gif True --height 5 --width 15 --colors "{0:'grey',1:'red',2:'green',3:'yellow'}"
	mv output.gif compare_flat_rates.gif
	python average_velocities.py -f velocities.txt

make all: $(ALLPLOTS)

cleanall:
	rm -f input.txt
	rm -f velocities.txt
	rm -f *.gif
	rm -fr *images/
	rm -f *.csv
