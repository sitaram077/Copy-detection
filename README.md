# Copy-detection

This software restricts users from copying and pasting files or content from a specific "root" folder to any location outside this folder, including external drives or cloud locations. It uses system-level hooks to monitor clipboard events and intercept file operations, ensuring that users adhere to these restrictions.

## **Features**

- **Clipboard Monitoring**: Monitors the clipboard for copied files.
- **File System Monitoring**: Watches for file transfer attempts to ensure files copied from the "root" folder are not pasted outside of it.
- **Threaded Operation**: Uses threads to run both clipboard monitoring and file system monitoring concurrently.
- **Multi-Language Implementation**: Available in both Python and C++ for flexibility.
- **Cross-Platform Design**:
  - **Python**: Designed for Windows systems but can be adapted to Linux.
  - **C++**: Primarily targeted at Windows 11 using Windows-specific APIs.

When a user copies a file from within the `root` folder, they can only paste it inside the `root` folder, including its subfolders. Copying a file from outside the `root` folder allows the file to be pasted anywhere.

---

## **Requirements**

### **Python Implementation**
- **Operating System**: Windows (Tested on Windows 11)
- **Python Version**: Python 3.6 or above
- **Python Libraries**:
  - `pywin32`
  - `watchdog`

### **C++ Implementation**
- **Operating System**: Windows 11
- **Compiler**: GCC (TDM-GCC-64) or any C++17 compatible compiler
- **Libraries**:
  - Standard C++ Libraries
  - Windows-specific APIs for clipboard and file system monitoring

---

## **Installation**

### **1. Clone the Repository**
Clone the project to your local machine:

```bash
git clone https://github.com/sitaram077/Copy-detection.git
cd Copy-detection
```

### **Running the Python Implementation**

#### **Setup**

1. Install Python dependencies:

   ```bash
   pip install pywin32 watchdog
   ```

2. Set the ROOT_FOLDER: Open the Python script (file_transfer_restriction.py) and modify the ROOT_FOLDER variable to point to the folder you want to monitor.

Example:

```python
ROOT_FOLDER = r"C:\path\to\root"
```
3. Run the Script
Run the Python script from the terminal or command prompt:

```bash
python file_transfer_restriction.py
```
#### Example Behavior
Files Copied from the Root Folder:

-Pasting inside the root folder → Allowed.
-Pasting outside the root folder → File will be deleted.
-Files Copied from Outside the Root Folder:
-Pasting anywhere, including the root folder → Allowed.

Console Output Examples:

Files copied from the root folder: plaintext
```
Files copied to clipboard: ['C:\\path\\to\\root\\file1.txt']
Files detected in the clipboard!
These files are from the root folder.
Unauthorized paste attempt: plaintext
File created: C:\path\to\unauthorized_location\file1.txt
Unauthorized file paste detected! Deleting: C:\path\to\unauthorized_location\file1.txt
```


### **Running the C++ implementation**
Run the Program
Run the compiled executable:

```bash
Copy code
./restrict_paste
```
Example Behavior
Files Copied from the Root Folder:
Pasting inside the root folder → Allowed.
Pasting outside the root folder → Blocked.
Files Copied from Outside the Root Folder:

Pasting anywhere, including the root folder → Allowed.
```
Output
Files copied from the root folder: plaintext
Clipboard event detected: File copied from root folder.
Unauthorized paste attempt: plaintext
Unauthorized file paste outside root folder detected. Action blocked.
```
Feel free to contact me for errors in execution: sitaramyeleswarapu@gmail.com
