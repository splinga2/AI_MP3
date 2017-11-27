import sys
import math

example_width = 0
example_height = 0
num_classes = 0
num_examples = 0
k = 0.1

# Check for proper usage
if(len(sys.argv) != 5):
	print("USAGE: Part1.py training_labels training_examples test_labels test_examples")
	sys.exit()

example_width = 28
example_height = 28
num_classes = 10
value_map = {}
value_map[' '] = 0
value_map['+'] = 1
value_map['#'] = 1

# Initialize training results
class_features = [[[0.0 for i in range(example_width)] for j in range(example_height)] for c in range(num_classes)]
class_priors = [0.0 for c in range(num_classes)]
class_num_examples = [0 for c in range(num_classes)]


# Open training files
training_labels = open(sys.argv[1], 'r')
training_examples = open(sys.argv[2], 'r')

for line in training_labels:
	# Get example label
	label = int(line)

	# Add to feature set
	for j in range(example_height):
		row = training_examples.readline()
		for i in range(example_width):
			char = row[i]

			# Update feature value
			class_features[label][j][i] += value_map[char]

	# Increment number of examples
	num_examples += 1
	class_num_examples[label] += 1

# Close training files
training_examples.close()
training_labels.close()

# Normalize
for c in range(num_classes):
	for j in range(example_height):
		for i in range(example_width):
			numerator = class_features[c][j][i] + k
			denominator = class_num_examples[c] + 2*k
			class_features[c][j][i] = numerator/denominator
	class_priors[c] = class_num_examples[c] / num_examples

# Open test files
test_labels = open(sys.argv[3], 'r')
test_examples = open(sys.argv[4], 'r')

true_labels = []
guess_labels = []
total_correct = 0
num_test_examples = 0
test_class_num_examples = [0]*num_classes
class_max_probabilities = [(0,-float("inf"))]*num_classes
class_min_probabilities = [(0,float("inf"))]*num_classes
classification_rate = [0]*num_classes

features = [[' ' for i in range(example_width)] for j in range(example_height)]

# MAP classification
for number, line in enumerate(test_labels):

	# Get actual class
	true_class = int(line)

	# Update number of examples
	test_class_num_examples[true_class] += 1
	num_test_examples += 1
	true_labels.append(true_class)

	# Variables for determining label
	best_class = -1
	highest_class_prob = -float("inf")

	# Get features
	for j in range(example_height):
		row = test_examples.readline()
		for i in range(example_width):
			features[j][i] = row[i]

	# Calculate probability for each class
	for c in range(num_classes):
		probability = math.log(class_priors[c], 10)

		# Evaluate features
		for j in range(example_height):
			for i in range(example_width):
				char = features[j][i]

				if(value_map[char]):
					probability += math.log(class_features[c][j][i], 10)
				else:
					probability += math.log(1 - class_features[c][j][i], 10)

		# Check if max or min probability for this class
		if(c == true_class):
			if(probability > class_max_probabilities[c][1]):
				class_max_probabilities[c] = (number, probability)
			if(probability < class_min_probabilities[c][1]):
				class_min_probabilities[c] = (number, probability)

		# Update most likely classification
		if(probability > highest_class_prob):
			highest_class_prob = probability
			best_class = c

	# Add label
	guess_labels.append(best_class)

	if(best_class == true_class):
		classification_rate[true_class] += 1
		total_correct += 1

# Close test files
test_examples.close()
test_labels.close()

# Normalize classification rates
for c in range(num_classes):
	print("Class " + str(c) + ":")
	print(str(classification_rate[c]) + " correct out of " + str(test_class_num_examples[c]) + "; " + str(100 * classification_rate[c] / test_class_num_examples[c]) + " %\n")
	classification_rate[c] /= test_class_num_examples[c]

print("\nTotal correct: ")
print(str(total_correct) + " out of " + str(num_test_examples) + "; " + str(100 * total_correct / num_test_examples) + " %")



# Write to output file
'''output_name = 'TrainingResults_' + sys.argv[1] + '.txt'
with open(output_name, 'w') as f:
	# Write features
	for c in range(num_classes):
		for j in range(example_height):
			f.write(' '.join(map(str, class_features[c][j])))
		f.write('\n')

	# Write priors
	f.write(' '.join(map(str, class_priors)))
	f.write('\n')

	# Write number of class examples
	f.write(' '.join(map(str, class_num_examples)))
	f.write('\n')

	# Write k
	f.write(str(k))
	f.write('\n')'''

