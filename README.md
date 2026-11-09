# RGB Color Comparison Tool

## Description

This program lets the user enter a palette of colors as comma-separated RGB values (each channel can be an integer or decimal from 0 to 255). After the palette is entered, the program compares every unique pair using a red-green color-vision model and reports each pair's distinguishability as High Risk, Caution, or Safe.

At least two colors are required. Press Enter on an empty line to finish entering the palette.

## Developer

Owen Dawson

## Example

To compile the program use the command:

```bash
g++ main.cpp -o main
```

to run the program use the command:

```bash
./main
```

Here is an example of the program running:

```text
All color channel values can be integers or decimals, entered in comma separated formatting (e.g. 255.0, 128.5, 0).
Press 'Enter' on an empty line to finish the palette.

Enter Color 1 as r, g, b:
255, 0, 0
Enter Color 2 as r, g, b:
0, 255, 0
Enter Color 3 as r, g, b:

Compared (2) colors.

High Risk (1)
  Color 1 vs Color 2 (0%)
```
