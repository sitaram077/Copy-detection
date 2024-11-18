# Copy-detection

This software restricts users from copying and pasting files or content from a specific "root" folder to any location outside this folder, including external drives or cloud locations. It uses system-level hooks to monitor clipboard events and intercept file operations, ensuring that users adhere to these restrictions.

## Features

- **Clipboard Monitoring**: Monitors the clipboard for copied files.
- **File System Monitoring**: Watches for file transfer attempts to ensure files copied from the "root" folder are not pasted outside of it.
- **Threaded Operation**: Uses threads to run both clipboard monitoring and file system monitoring concurrently.
- **Cross-Platform**: Designed for use on Windows, but can be adapted for Linux.


When a user copies a file from within the `root` folder, they can only paste it inside the `root` folder, including its subfolders. Copying a file from outside the `root` folder allows the file to be pasted anywhere.

## Requirements

- **Operating System**: Windows (Targeted for Windows 11)
- **Compiler**: GCC (TDM-GCC-64) or any other C++17 compatible compiler.
- **Libraries**: 
  - Standard C++ Libraries
  - Windows-specific API for clipboard and file system monitoring.

## Installation

1. **Clone the Repository**:
   Clone the project to your local machine.

   ```bash
   git clone https://github.com/sitaram077/Copy-detection.git
   cd Copy-detection

## Usage
   Running the Program
   Run the compiled executable:

 ```bash
    ./restrict_paste


