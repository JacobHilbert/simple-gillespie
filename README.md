# simple-gillespie
Gillespie algorithm implementing the ARN-Protein model for multiple cells. 

<img src="examples/graph.png" width="500">

The code calculates the evolution of several cells and averages its values every so often. The results are then stored in a `.dat` file per variable.

### To run:

```bash
make
```

## Customization

The constants of the model are defined on the [setup file](setup.cpp) as:

| name 	| meaning | default value |
| --- | --- | --- |
| tmax | run until time reaches this value | 150 |
| `dt` | Saves averages every `dt` time units | 2 |
| `cr` | average ARN creations per time unit | 1 | 
| `dr` | average ARN destructions per time unit per ARN units | 0.2 |
| `cp` | average protein creations per time unit per ARN unit | 50 |
| `dp` | average protein destructions per time unit per protein unit | 0.03333 |
| `n_cells` | Number of cells to simulate | 1000 |

"Units" are completely arbitrary.

Although this model is fairly simple, one could implement more varaibles and different equations on the `gillespie::step` and `gillespie::delta` functions of `setup.cpp`.

## How it works

