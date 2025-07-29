# 🔄📦🕵️‍♂️ VersionSync Tracker

## Project Overview

The VersionSync Tracker project aims to establish a file format for a new application. This format will incorporate metadata including a version number and the last modification date, in addition to the file's content.

### Binary File Format

The binary file format consists of:

- Magic word `0x1001CAFE` (int, 4 bytes)
- Version number as an unsigned long integer (8 bytes)
- Timestamp of the last modification (struct timespec, 16 bytes)
- Arbitrary size valuable data

### 📈 Version Increment Process

To increment the version number:

1. Open the file.
2. Verify the magic word. Exit with an error if it does not match to prevent corruption of a file in another format.
3. Read the current version, increment it, and write the new version to the file.
4. Record a timestamp obtained with `clock_gettime()`.
5. Close the file.
6. Important: Do not erase the following data, as it is the file's useful content.
7. If the file does not exist, create it with version zero and the current time.

### `Bumpvers` Utility

This function is used in the `bumpvers` utility to increment the version in the specified file. The program accepts a single argument, the name of the file. To execute the program and verify the file content, use the following command:

```bash
./bumpvers fichier.bin
```


## 🚀 How to Run

### Prerequisites
1. **Environment Setup**:
   - Ensure you are on a Linux-based system as the project uses `clock_gettime()` and other POSIX-compliant features.

2. **Required Tools**:
   - Install GCC for compilation if not already installed:
     ```bash
     sudo apt-get install gcc
     ```
   - Install CMake for project build management:
     ```bash
     sudo apt-get install cmake
     ```

---

### Compilation Instructions

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/your-repo/version-sync-tracker.git
   cd version-sync-tracker
Generate the Build Files:

Use cmake to create the build files:
```bash
cmake .
```
Build the Project:

Compile the project using make:
```bash
make
```
Running the Program
Run the bumpvers Utility:

To increment the version number of a binary file, execute:
```bash
./bumpvers fichier.bin
```
Replace fichier.bin with the desired file name.
Verify File Content:

After running bumpvers, check the binary file to ensure the version is updated while preserving its content.
Folder Structure
cmake/: CMake configuration files for project build setup.
src/: Contains the source code for the project, including the bumpvers utility implementation.
test/: Directory for test scripts and related files.
CMakeLists.txt: Build configuration file for CMake.
config.h.in: Header file template used in the project.
env.sh.in: Environment setup file template for additional configurations.
Notes
If the binary file does not exist, the bumpvers utility will create it with version 0 and the current timestamp.
Ensure the magic word 0x1001CAFE matches the expected format. If it does not, the program will terminate to avoid corrupting unrelated files.
Use make clean to remove build artifacts if needed:
```bash
make clean
```
The project automatically tracks and updates the modification timestamp using clock_gettime().
