import os
import re

def count_solutions():
    """Count the number of solution files in the repository."""
    count = 0
    
    # Define directories and file extensions to look for
    solution_dirs = ["level 1", "level 2", "level 3", "bonus"]
    extensions = [".cpp", ".py", ".java", ".js"]
    
    for directory in solution_dirs:
        if os.path.exists(directory):
            for filename in os.listdir(directory):
                if any(filename.endswith(ext) for ext in extensions):
                    count += 1
    
    return count

def update_readme():
    """Update the README.md with the new problem count."""
    count = count_solutions()
    
    # Read the current README
    try:
        with open("README.md", "r") as file:
            content = file.read()
    except FileNotFoundError:
        # Create a new README if it doesn't exist
        content = "# Project Euler Solutions\n\nSolutions to Project Euler problems.\n\n"
    
    # Update or add the count
    count_pattern = r"Problems solved: \d+"
    count_replacement = f"Problems solved: {count}"
    
    if re.search(count_pattern, content):
        content = re.sub(count_pattern, count_replacement, content)
    else:
        content += f"\n## Statistics\n\n{count_replacement}\n"
    
    # Write the updated content
    with open("README.md", "w") as file:
        file.write(content)

if __name__ == "__main__":
    update_readme()