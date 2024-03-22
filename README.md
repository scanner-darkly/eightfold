# eightfold

A collection of modules centered around the concept of generating and processing eight voices.

## orca's heart v2

<img src="https://github.com/scanner-darkly/eightfold-docs/blob/main/images/orcas_heart_v2_panel.jpg?raw=true" alt="orca's heart v2 panel" width="450" height="380" />

[Full Manual](https://github.com/scanner-darkly/eightfold/wiki/Orca's-Heart-v2)

An eight-voice algorithmic sequence generator, the new version of [orca's heart](https://github.com/scanner-darkly/vcv-collection-one?tab=readme-ov-file#orcas-heart).
This module generates sequences using an algorithm - instead of programming a sequence, you select the scale notes and control the algorithm parameters. You can use
it to sequence up to 8 voices and produce 8 modulation CVs and gates that can be used to modulate Orca's Heart itself or other modules in your patch.

### quick start

For the most basic use:

- connect `VOICES` CV outputs to 1V/Oct (pitch) oscillator inputs
- connect `VOICES` gate outputs to the envelopes that are used to control the VCAs the oscillators are going through
- select scale notes - the white LED shows the currently selected scale
- adjust sequencer speed with the `SPEED` knob
- use the knobs to change algorithm parameters to modify the sequence
- use `MODULATION` outputs to modulate voice parameters (oscillator waveform / filter cutoff / etc)

<img src="https://github.com/scanner-darkly/eightfold-docs/blob/main/images/patch_easy_start.jpg?raw=true" alt="quick start patch" width="491" height="237" />

### knob functions

| Knob | Function |
| ---: | :------- |       
|`SPEED`|the internal clock speed (BPM)|
|`LENGTH`|the length of the sequence (steps)|
|`TRANS`|transposition (1V/Oct)|
|`GATE L`|voice gate length (sec)|
|`VOICES`|number of voices|
|`SPREAD`|spread voices across a step|
|`ALGO X`|algorithm X parameter|
|`ALGO Y`|algorithm Y parameter|
|`SHIFT`|algorithm shift parameter|
|`SPACE`|add more "space" to sequence|
|`ROTATE`|rotate sequences for different voices|
|`XMOD`|add internal cross modulation|

See below for more details on what each function does.

### scale section

The top section with the red inputs / buttons / knobs is the scale section. This is where you select the notes that will be used in a generated sequence.
There are two scales available, and you can switch between them manually or by sending a trigger to `Toggle Scales A/B` input (next to `A` and `B` labels).
The manual switch can also select both scales at once, giving you a two octave range (scale B is transposed an octave up in this case).

There are 16 pentatonic scale presets available which can be selected with a knob or a control voltage. The linked button enables or disables presets - make sure
to disable them to prevent overwriting the notes that are currently selected. The presets cannot be overwritten - if you select a preset and change any notes,
those changes will not be stored in the preset.

Each scale can be transposed an octave up with a button or a gate sent to the corresponding input.

### clocking

The module has an internal clock which you can control with the `SPEED` knob (the value is BPM). This clock is sent to the `Clock` output. The internal clock is
disabled if something is connected to the `Clock` input - send a trigger here to sync Orca's Heart to another module.

### outputs

There are two main groups of outputs (in addition to the `Clock` and `Reset` outputs):

- `VOICES` - 8 CV and gate outputs for the 8 generated sequences
- `MODULATION` - 4 modulation CV and gate outputs for additional modulation

Modulation CVs (which produce voltage in the 0..+10V range) are stepped CVs that are also generated by the algorithm and will be affected by the algorithm
parameters.

The blue colour denotes polyphonic outputs - if you use Orca's Heart with a polyphonic module such as [Plaits](https://library.vcvrack.com/AudibleInstruments/Plaits),
you can use a single cable for all 8 voices by connecting to CV/gate output 1. The polyphonic modulation outputs also produce 8 CVs/gates, if you need to use
modulation CV/gate 5-8 with a non polyphonic module, connect output 1 to a [Split](https://library.vcvrack.com/Fundamental/Split) module.

[Lines module](#lines) can help with visualizing the polyphonic outputs.   

## formation

<img src="https://github.com/scanner-darkly/eightfold-docs/blob/main/images/formation_panel.jpg?raw=true" alt="formation panel" width="104" height="380" />

A mono to polyphonic voltage converter - take single voltage and convert it into a swarm of eight voltages.

## lines

<img src="https://github.com/scanner-darkly/eightfold-docs/blob/main/images/lines_panel.jpg?raw=true" alt="lines panel" width="29" height="380" />

A simple poly voltage visualizer. Visualize a single or up to 16 multiple voltages. Supports vertical or horizontal mode and different voltage ranges.
