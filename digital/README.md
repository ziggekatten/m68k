## Memory map and glue logic
I use Digital () to do alot of digital circuit designs, and it also have the very conveniant feature of generating circuits from truth tables, and then create .JED files for the GAL's that I'm using (GAL22v10D from Lattice).

| File       | Description                                                                          |
|------------|--------------------------------------------------------------------------------------|
| address_decoder_gal.tru   | Truth table for address decoding  |
| memorydecoding.dig        | This is an design based on multiplexers (74LS138) instead of an GAL   |