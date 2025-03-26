import os
import re

def count_solutions():
    """Count the number of solution files in the repository."""
    count = 0
    
    # Define file extensions to look for
    extensions = [".cpp", ".py", ".java", ".js", ".c", ".go"]
    
    # Find all directories in the root
    all_dirs = [d for d in os.listdir() if os.path.isdir(d)]
    
    # Filter for level directories and the bonus directory
    solution_dirs = []
    level_pattern = re.compile(r"level\s*\d+", re.IGNORECASE)
    
    for directory in all_dirs:
        if level_pattern.match(directory) or directory.lower() == "bonus":
            solution_dirs.append(directory)
    
    # Count files with matching extensions in each directory
    for directory in solution_dirs:
        if os.path.exists(directory):
            for filename in os.listdir(directory):
                if any(filename.endswith(ext) for ext in extensions):
                    count += 1
    
    return count, solution_dirs

def create_progress_bar(count, max_problems=800):
    """Create a visual progress bar for the README."""
    percentage = min(100, round(count / max_problems * 100))
    filled = int(percentage / 5)  # 20 bar segments
    bar = '█' * filled + '░' * (20 - filled)
    return f"![Progress]({percentage}% completed)\n\n```\n{bar} {percentage}%\n```"

def generate_solutions_table(solution_dirs):
    """Generate a table of solved problems with links."""
    table = "| Problem | Level | Solution | Description |\n|---------|-------|----------|-------------|\n"
    
    # Define file extensions to look for
    extensions = [".cpp", ".py", ".java", ".js", ".c", ".go"]
    
    # Get all solution files sorted by problem number
    solutions = []
    for directory in solution_dirs:
        if os.path.exists(directory):
            for filename in os.listdir(directory):
                if any(filename.endswith(ext) for ext in extensions):
                    match = re.search(r'p0*(\d+)', filename.lower())
                    if match:
                        problem_num = int(match.group(1))
                        solutions.append((problem_num, directory, filename))
    
    # Sort by problem number
    solutions.sort()
    
    # Build table rows
    for num, directory, filename in solutions:
        # Extract short description (first line of code comment if available)
        description = ""
        try:
            file_path = os.path.join(directory, filename)
            with open(file_path, 'r') as file:
                lines = file.readlines()
                for line in lines:
                    if '//' in line and not line.strip().startswith('//'):
                        # Skip lines that have code before the comment
                        continue
                    if '//' in line:
                        description = line.strip().replace('//', '').strip()
                        break
        except:
            pass
        
        table += f"| [{num}](https://projecteuler.net/problem={num}) | {directory} | [{filename}]({directory}/{filename}) | {description} |\n"
    
    return table

def update_readme():
    """Update the README.md with the new problem count."""
    count, solution_dirs = count_solutions()
    
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
    
    # Add progress bar
    progress_bar = create_progress_bar(count)
    content += f"\n## Progress\n\n{progress_bar}\n"
    
    # Add solutions table
    solutions_table = generate_solutions_table(solution_dirs)
    content += f"\n## Solutions\n\n{solutions_table}\n"
    
    # Write the updated content
    with open("README.md", "w") as file:
        file.write(content)

if __name__ == "__main__":
    update_readme()