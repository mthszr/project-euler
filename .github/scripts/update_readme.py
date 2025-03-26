import os
import re
import requests
import json

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

def extract_description(file_path):
    """Extract a more precise description from solution files."""
    try:
        with open(file_path, 'r', encoding='utf-8', errors='ignore') as file:
            lines = file.readlines()
            
            # Look for Project Euler problem description in specific patterns
            
            # Pattern 1: Check for the actual problem description in cout statements 
            # (often the most precise description)
            for i, line in enumerate(lines):
                if 'cout' in line and ('?' in line or 'problem' in line.lower() or 'calculate' in line.lower()):
                    # Extract the text between quotes
                    match = re.search(r'"([^"]*)"', line)
                    if match:
                        desc = match.group(1).strip()
                        # Remove "What is", "Find the", etc. to make it more concise
                        desc = re.sub(r'^(What is|Find|Calculate|Compute|Determine)\s+', '', desc)
                        # Remove question mark at the end
                        desc = re.sub(r'\?$', '', desc.strip())
                        if len(desc) > 10:  # Ensure it's not empty or too short
                            desc = desc[:100] + ('...' if len(desc) > 100 else '')
                            return desc[0].upper() + desc[1:] if desc else desc
            
            # Pattern 2: Look for multiline comments at the top
            in_comment = False
            comment_lines = []
            
            for line in lines[:20]:  # Only check the first 20 lines
                line = line.strip()
                if '/*' in line and '*/' in line:
                    # Single line /* */ comment
                    comment = line[line.find('/*')+2:line.find('*/')]
                    if len(comment.strip()) > 10:
                        comment = comment.strip()[:100] + ('...' if len(comment.strip()) > 100 else '')
                        return comment[0].upper() + comment[1:] if comment else comment
                elif '/*' in line:
                    in_comment = True
                    comment_lines.append(line[line.find('/*')+2:].strip())
                elif '*/' in line and in_comment:
                    in_comment = False
                    comment_lines.append(line[:line.find('*/')].strip())
                    full_comment = ' '.join(comment_lines)
                    if len(full_comment) > 10:
                        full_comment = full_comment[:100] + ('...' if len(full_comment) > 100 else '')
                        return full_comment[0].upper() + full_comment[1:] if full_comment else full_comment
                elif in_comment:
                    # Inside a multiline comment
                    clean_line = line.lstrip('* ').strip()
                    if clean_line:
                        comment_lines.append(clean_line)
            
            # Pattern 3: Fall back to single line comments (existing behavior)
            for line in lines[:30]:  # Only check first 30 lines
                if '//' in line and not line.strip().startswith('//'):
                    # Skip lines that have code before the comment
                    continue
                if '//' in line:
                    description = line.strip().replace('//', '').strip()
                    if len(description) > 10:  # Ensure it's not empty or too short
                        description = description[:100] + ('...' if len(description) > 100 else '')
                        return description[0].upper() + description[1:] if description else description
            
            # Pattern 4: Look for problem descriptions in problem statements or code
            problem_keywords = ['Find', 'Calculate', 'Determine', 'Compute', 'What is']
            for i, line in enumerate(lines[:50]):  # Check first 50 lines
                for keyword in problem_keywords:
                    if keyword in line:
                        # Extract potential problem description
                        desc = line.strip()
                        if len(desc) > 15:  # Ensure it's a substantial line
                            desc = desc[:100] + ('...' if len(desc) > 100 else '')
                            return desc[0].upper() + desc[1:] if desc else desc
            
            # If no good description found
            default_desc = "Problem " + os.path.basename(file_path).replace('.cpp', '').replace('p', '')
            return default_desc[0].upper() + default_desc[1:] if default_desc else default_desc
    except:
        default_desc = "Problem " + os.path.basename(file_path).replace('.cpp', '').replace('p', '')
        return default_desc[0].upper() + default_desc[1:] if default_desc else default_desc

# Add this new function for AI-enhanced descriptions
def enhance_description_with_ai(file_path, basic_description):
    """Use OpenAI API to generate a more precise description based on code analysis."""
    try:
        # Read the file content
        with open(file_path, 'r', encoding='utf-8', errors='ignore') as file:
            code_content = file.read()
        
        # Prepare the API request
        api_key = os.getenv('OPENAI_API_KEY')  # Set this in your environment variables or GitHub secrets
        if not api_key:
            return basic_description
            
        headers = {
            'Content-Type': 'application/json',
            'Authorization': f'Bearer {api_key}'
        }
        
        # Craft the prompt
        prompt = f"""
        This is a Project Euler solution code:
        
        ```
        {code_content[:1000]}  # Limiting to first 1000 chars to avoid token limits
        ```
        
        The current extracted description is: "{basic_description}"
        
        Please provide a clear, concise one-sentence description of the mathematical problem being solved.
        Start with a capital letter and don't include phrases like "This problem asks" or "In this problem".
        Just state what needs to be calculated/found directly.
        """
        
        data = {
            'model': 'gpt-3.5-turbo',
            'messages': [
                {'role': 'system', 'content': 'You are a helpful assistant that generates concise descriptions of Project Euler problems.'},
                {'role': 'user', 'content': prompt}
            ],
            'max_tokens': 100,
            'temperature': 0.3
        }
        
        # Make the API call
        response = requests.post('https://api.openai.com/v1/chat/completions', 
                                headers=headers, 
                                data=json.dumps(data),
                                timeout=10)
        
        if response.status_code == 200:
            result = response.json()
            enhanced_description = result['choices'][0]['message']['content'].strip()
            
            # Remove quotes if they're in the response
            enhanced_description = enhanced_description.strip('"\'')
            
            # Ensure the first letter is uppercase
            if enhanced_description:
                enhanced_description = enhanced_description[0].upper() + enhanced_description[1:]
                
            return enhanced_description
        
        return basic_description
    except Exception as e:
        print(f"Error in AI description enhancement: {e}")
        return basic_description

# Modify your generate_solutions_table function to use the AI enhancement
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
        # Get a more precise description
        file_path = os.path.join(directory, filename)
        basic_description = extract_description(file_path)
        
        # Enhance with AI if API key is available
        description = enhance_description_with_ai(file_path, basic_description)
        
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