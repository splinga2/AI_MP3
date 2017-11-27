import sys

example_width = 0
example_height = 0
num_classes = 0
num_examples = 0
k = 1.0

# Check for proper usage
if(len(sys.argv) != 4):
	print("USAGE: Training.py mode labels examples")
	sys.exit()

# Determine mode
if(sys.argv[1] == 'd'):
	example_width = 28
	example_height = 28
	num_classes = 10
	value_map = {}
	value_map[' '] = 0
	value_map['+'] = 1
	value_map['#'] = 1
else:
	print("Unrecognized mode: " + sys.argv[1])
	sys.exit()

# Initialize training results
class_features = [[[0.0 for i in range(example_width)] for j in range(example_height)] for c in range(num_classes)]
class_priors = [0.0 for c in range(num_classes)]
class_num_examples = [0 for c in range(num_classes)]


# Open input files
input_labels = open(sys.argv[2], 'r')
input_examples = open(sys.argv[3], 'r')

for line in input_labels:
	# Get example label
	label = int(line)

	# Add to feature set
	for j in range(example_height):
		row = input_examples.readline()
		for i in range(example_width):
			char = row[i]

			# Update feature value
			class_features[label][j][i] += value_map[char]

	# Increment number of examples
	num_examples += 1
	class_num_examples[label] += 1

# Close input files
input_examples.close()
input_labels.close()

# Normalize
for c in range(num_classes):
	for j in range(example_height):
		for i in range(example_width):
			numerator = class_features[c][j][i] + k
			denominator = class_num_examples[c] + 2*k
			class_features[c][j][i] = numerator/denominator
	class_priors[c] = class_num_examples[c] / num_examples

# Write to output file
output_name = 'TrainingResults_' + sys.argv[1] + '.txt'
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
	f.write('\n')

