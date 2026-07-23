import subprocess
import json
import os

out = subprocess.check_output(["make", "--always-make", "--dry-run"]).decode("utf-8")
cwd = os.getcwd()

compile_commands = []
for line in out.splitlines():
    if "cc " in line and "-c" in line:
        parts = line.split()
        try:
            c_index = parts.index("-c")
            file_path = parts[c_index + 1]
            abs_file_path = os.path.abspath(file_path)
            # Replace cc with /usr/bin/gcc to ensure clangd finds system headers
            line = line.replace("cc ", "/usr/bin/gcc ")
            compile_commands.append({
                "directory": cwd,
                "command": line,
                "file": abs_file_path
            })
        except ValueError:
            pass

with open("compile_commands.json", "w") as f:
    json.dump(compile_commands, f, indent=4)
