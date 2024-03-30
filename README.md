<h2>Chiter</h2>

# Basic Worm containing a Trojan

The worm spreads through your file subdirectories, starting from the directory it is placed in. Once inside, a trojan downloads resources from the internet and runs it on your computer.

Run the file by exploiting an input validation vulnerability in SampleEntry, using
```
./SampleEntry "INSERT TEXT HERE";./Chiter
```

Cleanup the files downloaded using the Cleanup.py, specify the file name to clean
