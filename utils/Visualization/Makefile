# generate visualizations for CA data 
plot: ca_plot.py test.csv
	python ca_plot.py test.csv testdir

plot_gif: ca_plot.py test.csv
	python ca_plot.py test.csv testdir --gif True

plot_traffic: ca_plot.py test_traffic.csv
	python ca_plot.py test_traffic.csv traffic --colors "{0:'grey',1:'red',2:'green',3:'yellow'}" --width 5 --height 15

plot_traffic_gif: ca_plot.py test_traffic.csv
	python ca_plot.py test_traffic.csv traffic --colors "{0:'grey',1:'red',2:'green',3:'yellow'}" --width 5 --height 15 --gif True

plot_forest_fire_gif: ca_plot.py test_forest_fire.csv
	python ca_plot.py test_forest_fire.csv forest --colors "{0:'darkgreen', 1:'orange',2:'brown'}" --gif True