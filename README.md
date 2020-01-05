# PPM Compressor

An arithmetic compressor that uses a Pediction by Partial Matching (PPM) method to get symbol
probabilities.

## Building and running

To build the project on Linux, use:

``` bash
$ mkdir build
$ cd build
$ cmake ..
$ make compressor
```

To compress a file, use:

```bash
$ ./compressor -c input_file_name k tree_mode
```

The first parameter *input_file_name* is self explanatory.

*k* defines the maximum size of the context to be used on the compression process, and is optional (with a default value of 2). 

*tree_mode* indicate how to create the internal tree. It can assume two values: **-list**, to force 
the use of lists or **-map**, to force the use of maps. In absence, the choice depends on the *k* 
value.

The generated output file will be labeled according to the input plus the *.xdg* extension.

To decompress, use:

```bash
$ ./compressor -d input_file_name output_file_name
```

The two parameters are self explanatory. The first one must end with *.xdg* as its extension 
and label a file that must contain a proper XDG header. The second parameter is optional, and 
defaults to the input file name without the *.xdg* extension.
