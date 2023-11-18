import random

def generate_sparse_matrix(rows, cols, fill_percentage):
    num_elements = int(rows * cols * fill_percentage)
    matrix = [[0 for _ in range(cols)] for _ in range(rows)]

    for _ in range(num_elements):
        while True:
            row = random.randint(0, rows - 1)
            col = random.randint(0, cols - 1)
            if matrix[row][col] == 0:
                matrix[row][col] = random.randint(-100, 100)
                break

    return matrix

def print_matrix_in_coordinates(matrix):
    rows = len(matrix)
    cols = len(matrix[0])
    non_zero_elements = []

    for i in range(rows):
        for j in range(cols):
            if matrix[i][j] != 0:
                non_zero_elements.append((i, j, matrix[i][j]))

    print(rows, cols, len(non_zero_elements))

    for elem in non_zero_elements:
        print(elem[0] + 1, elem[1] + 1, elem[2])

matrix = generate_sparse_matrix(1000, 1000, 0.20)

print_matrix_in_coordinates(matrix)
