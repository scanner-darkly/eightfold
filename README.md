# eightfold

A collection of modules centered around the concept of generating and processing eight voices.

## orca's heart v2

<img src="https://github.com/scanner-darkly/eightfold-docs/blob/main/images/orcas_heart_v2_panel.jpg?raw=true" alt="orca's heart v2 panel" width="450" height="380" />

[Full Manual](https://github.com/scanner-darkly/eightfold/wiki/Orca's-Heart-v2)

An eight-voice algorithmic sequence generator, the new version of [orca's heart](https://github.com/scanner-darkly/vcv-collection-one?tab=readme-ov-file#orcas-heart).

This module generates sequences using an algorithm - instead of programming a sequence, you select the scale notes and control the algorithm parameters.
For the most basic use, connect `VOICES` CV outputs to 1V/Oct (pitch) oscillator inputs and gate outputs to a gate/trigger input on the oscillator (if it has one)
or an envelope used to control a VCA the oscillator is going through. Select scale notes and play with the knobs.

### scale section

The top section with red inputs / buttons / knobs is the scale section. This is where you select the notes that will be used in a generated sequence.
There are two scales available, and you can switch between them manually or by sending a trigger to "Toggle Scales" input.

## formation

<img src="https://github.com/scanner-darkly/eightfold-docs/blob/main/images/formation_panel.jpg?raw=true" alt="formation panel" width="104" height="380" />

A mono to polyphonic voltage converter - take single voltage and convert it into a swarm of eight voltages.

## lines

<img src="https://github.com/scanner-darkly/eightfold-docs/blob/main/images/lines_panel.jpg?raw=true" alt="lines panel" width="29" height="380" />

A simple poly voltage visualizer. Visualize a single or up to 16 multiple voltages. Supports vertical or horizontal mode and different voltage ranges.
