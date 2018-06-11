# PPM Compressor

An arithmetic compressor that uses a Prediction by Partial Matching (PPM) method to get symbol
probabilities.

## Using the project

To build the project, type on terminal:

`$ make`

To compress some file, type:

`$ ./compressor -c input_file_name k tree_mode`

The first parameter "input_file_name" is self explanatory. "k" defines the maximum size of 
the context to be used on the compression process, and is optional (with a default value of 2). 
The generated output file will be labeled according to the input plus the ".xdg" extension.
"tree_mode" indicate how to create the internal tree. It can assume two values: -list, to force 
the use of lists or -map, to force the use of maps. In absence, the choice depends on the k 
value.

To decompress, type:

`$ ./compressor -d input_file_name output_file_name`

The two parameters are self explanatory. The first one must end with ".xdg" as its extension 
and label a file that must contain a proper XDG header. The second parameter is optional, and 
defaults to the input file name minus the ".xdg" extension. "tree_mode" indicate how to create 
the internal tree. It can assume two values: -list, to force the use of lists or -map, to force 
the use of maps. In absence, the choice depends on the k value.
