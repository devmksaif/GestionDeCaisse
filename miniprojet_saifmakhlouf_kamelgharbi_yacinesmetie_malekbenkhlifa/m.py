import os

def list_files_and_directories():
    # Get the current working directory
    current_dir = os.getcwd()

    # List all files and directories in the current directory
    for item in os.listdir(current_dir):
        item_path = os.path.join(current_dir, item)
        if os.path.isdir(item_path):
            print(f"Directory: {item}")
        elif os.path.isfile(item_path):
            print(f"File: {item}")

if __name__ == "__main__":
    list_files_and_directories()
