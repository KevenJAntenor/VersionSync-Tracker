# VersionSync Tracker

## Project Overview

The VersionSync Tracker project aims to establish a file format for a new application. This format will incorporate metadata including a version number and the last modification date, in addition to the file's content.

### Binary File Format

The binary file format consists of:

- Magic word `0x1001CAFE` (int, 4 bytes)
- Version number as an unsigned long integer (8 bytes)
- Timestamp of the last modification (struct timespec, 16 bytes)
- Arbitrary size valuable data

### Version Increment Process

To increment the version number:

1. Open the file.
2. Verify the magic word. Exit with an error if it does not match to prevent corruption of a file in another format.
3. Read the current version, increment it, and write the new version to the file.
4. Record a timestamp obtained with `clock_gettime()`.
5. Close the file.
6. Important: Do not erase the following data, as it is the file's useful content.
7. If the file does not exist, create it with version zero and the current time.

### `bumpvers` Utility

This function is used in the `bumpvers` utility to increment the version in the specified file. The program accepts a single argument, the name of the file. To execute the program and verify the file content, use the following command:

```bash
./bumpvers fichier.bin
