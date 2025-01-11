import numpy as np
import pandas as pd

def project_3d_to_2d(input_file, output_file):
    # Read the 3D dataset
    with open(input_file, 'r') as file:
        # Read the first line to get the number of points
        num_points = int(file.readline().strip())
        # Read the rest of the data
        data = pd.read_csv(file, delim_whitespace=True, header=None)
        data.columns = ['x', 'y', 'z']

    # Randomly project 3D points to 2D
    np.random.seed(42)  # For reproducibility
    projection_matrix = np.random.rand(2, 3)  # Random 2x3 projection matrix

    # Normalize the projection matrix to maintain the scale
    projection_matrix /= np.linalg.norm(projection_matrix, axis=1)[:, np.newaxis]

    # Project the points
    data_2d = data[['x', 'y', 'z']].values @ projection_matrix.T

    # Create a DataFrame for the 2D data
    data_2d_df = pd.DataFrame(data_2d, columns=['x', 'y'])

    # Save the 2D dataset
    with open(output_file, 'w') as file:
        # Write the number of points
        file.write(f"{num_points}\n")
        # Write the 2D points
        data_2d_df.to_csv(file, sep=' ', index=False, header=False)

    print(f"2D dataset saved to {output_file}")

# Example usage
input_file = 'dataset-1000000.txt'
output_file = '2d-dataset-1000000.txt'
project_3d_to_2d(input_file, output_file)