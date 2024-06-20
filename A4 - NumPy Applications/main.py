# Assignment-4: NumPy and its Applications
# NAME : Tuhin Mondal
# ROLL NO: 22CS10087

# Import necessary libraries
import numpy as np
import csv
import time
import cv2
import matplotlib.pyplot as plt

# --------------------------------------------------
# PROGRAM 1: Read data from CSV, find max and min
# --------------------------------------------------
print("PROGRAM 1 :")

# Read data from CSV file ('book1.csv')
array = np.genfromtxt('book1.csv', delimiter='\t', usecols=1, skip_header=1, dtype=int)
print(array)

# Find maximum and minimum elements in the array
max_element = np.max(array)
min_element = np.min(array)
print("Max element = ", max_element, "\nMin element = ", min_element)

# --------------------------------------------------
# PROGRAM 2: Sort the array
# --------------------------------------------------
print("\nPROGRAM 2 :")

# Sort the array obtained from 'book1.csv'
sorted_array = np.sort(array)
print(sorted_array)

# --------------------------------------------------
# PROGRAM 3: Reverse the sorted array
# --------------------------------------------------
print("\nPROGRAM 3 :")

# Reverse the sorted array
reversed_array = np.flip(sorted_array)
print(reversed_array)

# --------------------------------------------------
# PROGRAM 4: Calculate means of arrays from CSV files
# --------------------------------------------------
print("\nPROGRAM 4 :")

# Define CSV filenames
filenames = ['Book1.csv', 'Book2.csv', 'Book3.csv']
array_list = []

# Read data from each CSV file and calculate mean
for filename in filenames:
    array = np.genfromtxt(filename, delimiter='\t', usecols=1, skip_header=1, dtype=float)
    array_list.append(array)

means = []
for array in array_list:
    if array is not None:
        mean = np.mean(array)
        means.append(mean)
    else:
        means.append(None)
print("Means of all arrays:", means)

# --------------------------------------------------
# PROGRAM 5: Load and display an image
# --------------------------------------------------
print("\nPROGRAM 5 :")

# Load and display an image ('a.png') using OpenCV
image = cv2.imread('a.png')
X = np.array(image)
if image is not None:
    cv2.imshow('Image', image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
else:
    print("Error loading image")

# --------------------------------------------------
# PROGRAM 6: Convert image to grayscale and display
# --------------------------------------------------
print("\nPROGRAM 6 :")

# Convert the loaded image to grayscale and display
grey_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
if grey_image is not None:
    cv2.imshow('Image', grey_image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
else:
    print("Error loading image")

# --------------------------------------------------
# PROGRAM 7: Perform matrix multiplication using NumPy
# --------------------------------------------------
print("\nPROGRAM 7 :")

# Perform matrix multiplication on grayscale image using NumPy
start_time = time.time()
X = np.array(grey_image)
Y = np.transpose(X)
Z = np.dot(X, Y)

# Save the resulting image and display it
cv2.imwrite("img.png", Z)
img = cv2.imread("img.png")
end_time = time.time()
print("Time taken using Numpy =", end_time - start_time)

if img is not None:
    cv2.imshow('Image', img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
else:
    print("Error loading image")

# --------------------------------------------------
# PROGRAM 8: Perform matrix multiplication without NumPy
# --------------------------------------------------
print("\nPROGRAM 8 :")

# Define a function to perform matrix multiplication without NumPy
def matrix_multiply(A, B):
    Z = [[0 for _ in range(len(B[0]))] for _ in range(len(A))]
    for i in range(len(A)):
        for j in range(len(B[0])):
            for k in range(len(B)):
                Z[i][j] += A[i][k] * B[k][j]
    return Z

# Perform matrix multiplication without NumPy and measure time taken
image = cv2.imread('a.png')
X = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
Y = np.transpose(X)

start = time.time()
Z = matrix_multiply(X, Y)
end = time.time()

print("Time taken without NumPy:", end - start)
print(Z)

# --------------------------------------------------
# PROGRAM 9: Plot pixel intensity histogram
# --------------------------------------------------
print("\nPROGRAM 9 :")

# Compute and plot the histogram of pixel intensities
histogram = cv2.calcHist([grey_image], [0], None, [256], [0, 256])
plt.plot(histogram)
plt.title("Pixel Intensity Histogram")
plt.xlabel("Pixel Intensity")
plt.ylabel("Frequency")
plt.show()

# --------------------------------------------------
# PROGRAM 10: Draw a black rectangle on the image
# --------------------------------------------------
print("\nPROGRAM 10 :")

# Define coordinates for the rectangle
top_right = (40, 100)
bottom_left = (70, 200)

# Draw a black rectangle on the grayscale image
cv2.rectangle(grey_image, top_right, bottom_left, (0, 0, 0), -1)
cv2.imshow('Black Rectangled Image', grey_image)
cv2.waitKey(0)
cv2.destroyAllWindows()

# --------------------------------------------------
# PROGRAM 11: Binarize the image with different thresholds
# --------------------------------------------------
print("\nPROGRAM 11 :")

# Define threshold values for binarization
threshold_values = [50, 70, 100, 150]

# Binarize the grayscale image using different thresholds
binarized_images = []
for threshold_value in threshold_values:
    binarized_image = np.where(grey_image > threshold_value, 255, 0).astype(np.uint8)
    binarized_images.append(binarized_image)

# Display the binarized images
for idx, binarized_image in enumerate(binarized_images):
    cv2.imshow(f'Binarized Image (Threshold={threshold_values[idx]})', binarized_image)

cv2.waitKey(0)
cv2.destroyAllWindows()

# --------------------------------------------------
# PROGRAM 12: Apply a filter to convolute the image
# --------------------------------------------------
print("\nPROGRAM 12 :")

# Define a filter for convolution
filter_list = np.array([[-1, -1, -1], [0, 0, 0], [1, 1, 1]])

# Convolute the original image with the filter and display the result
filtered_image = cv2.filter2D(image, -1, filter_list)
cv2.imshow('Filtered convoluted  image', filtered_image)
cv2.waitKey(0)
cv2.destroyAllWindows()
