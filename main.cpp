#include <iostream>
#include <string>
#include <windows.h>
#include <shlobj.h>
#include <vector>
#include <algorithm>
#include <thread>


const std::string ROOT_FOLDER = "C:\\Users\\sitar\\OneDrive\\Desktop\\copy_detection_software\\root"; 

bool copiedFromRoot = false;

bool isInsideRoot(const std::string& filePath) {
    return filePath.find(ROOT_FOLDER) == 0; 
}

void monitorClipboard() {
    while (true) {
        if (OpenClipboard(nullptr)) {
            HANDLE hData = GetClipboardData(CF_UNICODETEXT);
            if (hData != NULL) {
                wchar_t* pszText = static_cast<wchar_t*>(GlobalLock(hData));
                if (pszText != NULL) {
                    std::wstring filePath(pszText);
                    copiedFromRoot = isInsideRoot(std::string(filePath.begin(), filePath.end()));
                    std::cout << "Clipboard file copied: " << filePath << "\n";
                    std::cout << "Inside root folder: " << copiedFromRoot << "\n";
                    GlobalUnlock(hData);
                }
            }
            CloseClipboard();
        }
        Sleep(1000); 
    }
}

void monitorFileSystem() {
    HANDLE hDir = FindFirstChangeNotification(
        ROOT_FOLDER.c_str(),
        TRUE, 
        FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME | FILE_NOTIFY_CHANGE_ATTRIBUTES
    );

    if (hDir == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to watch directory " << ROOT_FOLDER << std::endl;
        return;
    }

    while (true) {
        DWORD dwWaitStatus = WaitForSingleObject(hDir, INFINITE);
        if (dwWaitStatus == WAIT_OBJECT_0) {
            std::cout << "File system change detected.\n";

            std::string destinationFile = "C:\\Users\\sitar\\OneDrive\\Desktop\\copy_detection_software\root\new.txt"; // Example destination file path

            if (copiedFromRoot && !isInsideRoot(destinationFile)) {
                std::cout << "Unauthorized paste operation detected! File won't be pasted outside the root folder.\n";
            }
            FindNextChangeNotification(hDir);
        }
    }
}

int main() {
    std::thread clipboardThread(monitorClipboard);

    monitorFileSystem();
    clipboardThread.join();

    return 0;
}
