import matplotlib.pyplot as plt 
import sys
import os 


def generate_plots(csv_file, output_dir):
    """
    Visualization for CellularAutomata CSV output 

    Params
    ------
    csv_file : string
        Path to CSV file containing CA output data

    output_dir : string
        Path to directory to save plot images

    """
    # create output directory if it doesn't already exist 
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    # read in data from CSV
    with open(csv_file, 'r') as file:
        data = file.read()

    # separate the time steps
    timesteps = data.strip().split('\n\n')
    parsed_data = []
    dimensions = None
    
    # process the data 
    for timestep in timesteps:
        rows = timestep.split('\n')
        if not dimensions:
            dimensions = list(map(int, rows[0].split(',')))  
        grid = [list(map(int, row.split(','))) for row in rows[1:]]
        parsed_data.append(grid)

    # plot each timestep and save to directory 
    for i, grid in enumerate(parsed_data):
        plt.figure(figsize=(8, 6))
        plt.pcolor(grid, cmap='viridis', edgecolors='k', linewidths=2, vmin=0, vmax=100)
        plt.title(f'Timestep {i + 1} - Dimensions: {dimensions[0]}x{dimensions[1]}')
        plt.colorbar(label='Cell State')
        plt.savefig(os.path.join(output_dir, f'timestep_{i}.png'))

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python ca_plot.py filename.csv output_dir")
        sys.exit(1)

    csv_file = sys.argv[1]
    output_dir = sys.argv[2]
    generate_plots(csv_file, output_dir)
