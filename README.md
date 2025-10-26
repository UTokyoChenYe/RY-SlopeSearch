# RY-SlopeSearch
## Introduction
Here is the offical source code of RY-SlopeSearch, which is an slope-based alignment-free algorithms for fast DNA seqs comparision.

## Getting Start
### Requirements
- GCC 12.3.0 or higher
- CMake: Version 3.20 or higher
- third party
  - SeqAn3 Library
  - range-v3 Library: Needed as a dependency for SeqAn3
  - yaml-cpp Library: Used for YAML configuration parsing
  - OpenMP: Optional, but if enabled, it requires a compatible OpenMP installation for parallel processing support

### Installing
```shell
git clone git@github.com:UTokyoChenYe/RY-SlopeSearch.git
cd RY-SlopeSearch
mkdir build
cmake .. //Using GCC >= 12.3.0
make
```
### How to use
If you have already been in build folder, run `./RY-SlopeSearch --config {the path to your config}`.

The parameters of configs

| Parameter                     | Description                                                                          |
|-------------------------------|--------------------------------------------------------------------------------------|
| `dataset.datasets_directory`  | Specifies the directory path for the sequence data to be used.                       |
| `parameters.using_one_to_one_matching` | Enables the one-to-one matching algorithm if set to true.                |
| `parameters.using_background_matches`  | Enables background matches if set to true.                               |
| `parameters.use_openmp`       | Enables multi-threaded computation with OpenMP if supported in your environment.     |
| `sampling_method`             | Specifies the name of the sampling algorithm to use.                                  |
| `draw_F_k_function`           | If true, the F_k function graph will be generated.                                   |
| `draw_k_max`                  | The upper limit for k value in the graph, effective only if draw_F_k_function is true.|
| `output_directory`            | Specifies the path where the output files will be saved.                             |
- `fasta` files should be collected under `dataset.datasets_directory`
- each `fasta` file has one genome
- out:
  - a time stamp folder will be created under `output_directory`, your results are in there
  - results includes:
    - config you used
    - runtime log
    - `.phy` distance matrix
    - performance log
      - thread info
      - time of matrix computation

### Other tool
| Methods                     | Description                                                                          |
|-------------------------------|--------------------------------------------------------------------------------------|
| `./scripts/plot.sh`  | draw $F(k)$.                       |

