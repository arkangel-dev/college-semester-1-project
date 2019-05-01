import json
import math

# read the json file and put the output into a dictionary
f = open("irisdata.json" , "r")
file_json = f.read()
iris_data = json.loads(file_json)

# initiate the variables...
petal_length = []
petal_width = []
sepal_length = []
sepal_width = []

# parse out the data...
for x in iris_data["iris_data"]:
    petal_length.append(x[0])
    petal_width.append(x[1])
    sepal_length.append(x[2])
    sepal_width.append(x[3])

species_data = []
for x in iris_data["species_data"]:
    species_data.append(x)

# temporary input here...
sepal_length_in = 2.3
sepal_width_in = 7.8
petal_length_in = 1.4
petal_width_in = 2

euclidian_dist_set = []
for x in iris_data["iris_data"]:
    result = 0
    result = math.sqrt(  math.pow((x[2] - petal_length_in), 2) + math.pow((x[3] - petal_width_in), 2))  
    euclidian_dist_set.append(result)

min_euclidian_dist = min(euclidian_dist_set)
min_index = euclidian_dist_set.index(min_euclidian_dist)
best_matching_species = species_data[min_index]
print(best_matching_species)