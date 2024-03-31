# Chiter

## Description
This is a basic implementation of a Worm that carries a Trojan within it.

The worm spreads through your file subdirectories, starting from the directory it is placed in. Once inside, a trojan downloads resources from the internet and runs it on your computer.

Currently, it is not downloading anything malicious, so it's perfectly safe to run on your computer. There is also a cleanup program to clean up after the worm.

## Usage
Run the file by exploiting an input validation vulnerability in SampleEntry, using
```
./SampleEntry "INSERT TEXT HERE";./Chiter
```

Cleanup the files downloaded using the Cleanup.py, specify the file name to clean
```
python3 Cleanup.py
```
Files to clean are "Chiter" and "not_a_trojan"
