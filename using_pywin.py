import os
import time
import win32clipboard
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler

ROOT_FOLDER = r"root" # here you can change the root folder
copied_from_root = False

def get_clipboard_files():
    win32clipboard.OpenClipboard()
    try:
        # CF_HDROP indicates files are copied to the clipboard
        if win32clipboard.IsClipboardFormatAvailable(win32clipboard.CF_HDROP):
            file_paths = win32clipboard.GetClipboardData(win32clipboard.CF_HDROP)
            return list(file_paths)  # Return the file paths as a list
        else:
            return []
    finally:
        win32clipboard.CloseClipboard()

def is_inside_root(file_path):
    if not os.path.isabs(file_path):
        return False
    try:
        return os.path.commonpath([ROOT_FOLDER, file_path]) == ROOT_FOLDER
    except ValueError:
        return False

def monitor_clipboard():
    global copied_from_root
    last_clipboard = None
    while True:
        clipboard_files = get_clipboard_files()
        if clipboard_files != last_clipboard:
            last_clipboard = clipboard_files
            if clipboard_files:
                print(f"Files copied to clipboard: {clipboard_files}")
                print("Files detected in the clipboard!")
                copied_from_root = all(is_inside_root(f) for f in clipboard_files)
                if copied_from_root:
                    print("These files are from the root folder.")
                else:
                    print("These files are not from the root folder.")
            else:
                print("No files detected in clipboard.")
        time.sleep(1)


class FileSystemHandler(FileSystemEventHandler):
    def on_created(self, event):
        global copied_from_root
        print(f"File created: {event.src_path}")
        if copied_from_root and not is_inside_root(event.src_path):
            print(f"Unauthorized file paste detected! Deleting: {event.src_path}")
            try:
                if os.path.isfile(event.src_path):
                    os.remove(event.src_path)
                elif os.path.isdir(event.src_path):
                    os.rmdir(event.src_path)
            except Exception as e:
                print(f"Error while deleting: {e}")

def monitor_file_system():
    observer = Observer()
    event_handler = FileSystemHandler()
    observer.schedule(event_handler, ROOT_FOLDER, recursive=True)
    observer.start()
    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        observer.stop()
    observer.join()

if __name__ == "__main__":
    from threading import Thread
    clipboard_thread = Thread(target=monitor_clipboard, daemon=True)
    clipboard_thread.start()
    monitor_file_system()
