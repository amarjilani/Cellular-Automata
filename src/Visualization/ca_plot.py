# Cellular Automata Visualization Script 

import matplotlib.pyplot as plt 
from matplotlib.colors import ListedColormap
import argparse
import os
import ast
import imageio.v2 as imageio
import re

def generate_plots(csv_file, output_dir, colors, plot_width, plot_height):
    """
    Visualization for CellularAutomata CSV output 

    Params
    ------
    csv_file : string
        Path to CSV file containing CA output data

    output_dir : string
        Path to directory to save plot images

    """

    # handle optional arguments 
    min_value = None
    max_value = None
    if plot_width:
        w = plot_width
    else:
        w = 10

    if plot_height:
        h = plot_height
    else:
        h = 10

    if colors:
        try:
            color_dict = ast.literal_eval(colors)
        except:
            raise ValueError("Invalid format for colors. Please provide a dictionary with format {state:color}")
        color_list = [color_dict[i] for i in sorted(color_dict.keys())]
        cmap = ListedColormap(color_list)

        # ensures that colors are correct, even if a state doesn't occur in the data! 
        min_value = min(color_dict.keys())
        max_value = max(color_dict.keys())
    else:
        cmap = "viridis"

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
        else:
            grid = [list(map(int, row.split(','))) for row in rows]
            parsed_data.append(grid)

    if not min_value and not max_value:
        # get min/max values for color scale, keeps it consistent throughout all timesteps 
        flat_list = [item for sublist1 in parsed_data for sublist2 in sublist1 for item in sublist2]

        min_value = min(flat_list)
        max_value = max(flat_list)

    # plot each timestep and save to directory 
    for i, grid in enumerate(parsed_data):
        plt.figure(figsize=(w, h))
        plt.pcolormesh(grid, cmap=cmap, vmin=min_value, vmax=max_value)
        plt.title(f'Timestep {i + 1} - Dimensions: {dimensions[0]}x{dimensions[1]}')
        plt.colorbar(label='Cell State')

        plt.xlim(0, dimensions[0])  
        plt.ylim(0, dimensions[1])     

        plt.savefig(os.path.join(output_dir, f'timestep_{i}.png'))
        plt.close()

def extract_number(filename):
    """
    Regex function to extract the number from the filename for proper sorting 
    """
    numbers = re.findall(r'\d+', filename)
    return int(numbers[0])

def create_gif(dir):
    """
    Creates a gif from the images located in the passed directory 
    """
    # get filenames 
    files = [f for f in os.listdir(dir) if os.path.isfile(os.path.join(dir, f))]

    # sort files by timestep number 
    files = sorted(files, key=extract_number)
    images = []
    for file in files:
        file_path = os.path.join(dir, file)
        images.append(imageio.imread(file_path))

    # save gif 
    imageio.mimsave("output.gif", images, duration=0.5, loop=0)



if __name__ == "__main__":
    # parse command line arguments 
    parser = argparse.ArgumentParser(description='Generate plots from a CSV file.')
    parser.add_argument('csv_file', type=str, help='Path to the input CSV file.')
    parser.add_argument('output_dir', type=str, help='Directory to save the output plots.')
    parser.add_argument('--colors', type=str, help='Colors for the plot.', default=None)
    parser.add_argument('--width', type=int, help='Width of the plot in pixels.', default=None)
    parser.add_argument('--height', type=int, help='Height of the plot in pixels.', default=None)
    parser.add_argument('--gif', type=bool, help="Set whether to create gif from plots. ", default=None)

    args = parser.parse_args()
    
    generate_plots(args.csv_file, args.output_dir, args.colors, args.width, args.height)

    if args.gif:
        create_gif(args.output_dir)
