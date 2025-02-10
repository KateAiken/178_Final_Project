# 178_Final_Project
Team Name – The Enigma

Project Title – Morse code sender/receiver

Project Style – Hardware/Arduino Based

Project Reason
It involves a lot of hardware components to give us experience and practice using many components in the kit. It allows us to explore several data structures including queues and further our knowledge of the combination of more complicated data structures with hardware. 

Course Topics
-	Queues/Linked Lists – to store each the morse code form of each letter entered
-	Multi-dimensional Arrays – to store translations
-	Other structures and algorithms learned throughout the course

Preliminary Design
Start
-	Write morse code into screen using buttons which gets sent to the other Arduino and printed in morse code and text to the other screen 
	- Enter dots and dashes using buttons on screen (Buttons for dash, dot, end of a letter and space)
    - Display the . and – when they are typed and the letters after the end of the letter is entered
    - Scroll across screen as typing (top separate from bottom so both are visible)
  - Translate dots and dashes to number values (ACSII)
  - Linked listed containing 4 int values to store numbers associating with dot/dash
    - Store int values in linked list in a queue to send to the other Arduino 
    - Ignore the end of letter input to make translation to a word easier
  - All values empty for spaces/separating words
  - 2D Array to hold translation of each combination
    - Static array to reference for translation
    - Stores 4 ints to indicate the morse code and one to store the letter Ex.
  - Error checking for incorrect or invalid codes
    - If a morse code doesn’t exist inform the user and restart from the last full letter or full word depending on code capabilities
    - Translate using number to get character
    -	When list is received translate to numbers and print both morse code and text to the screen 
Goal: The Arduinos can be run completely disconnected form a laptop only plugged in to a power source, no interaction with the serial monitor etc. (Serial monitor wil be used for testing and trouble shooting)

45(Decimal):  - (ASCII)
46(Decimal): . (ASCII) 

Advances
-	An option to enter text that gets translated to morse code
  - Option to enter text or morse code 
	- Use a scroll to move up and down through a list of letters, like the number scrolling from lab 1_3
-	Light to flash the morse code on both Arduinos
  - Use numbers (Decimal translation) to indicate how many times and the length of the light flash and a longer pause for spaces
-	Buzzer to audibly output morse code 
  - Use numbers (Decimal translation) to indicate how many times and the length of the buzz and a longer pause for spaces
-	3D print case for Arduino, screen, buzzer and light
  - Design a case to enclose set up in SolidWorks and print for at least two Arduinos
-	Network for Arduinos – morse code sends/receives to multiple Arduinos
  - Connect multiple Arduinos and send the morse code to all of them and receive from any
-	Ability to select which Arduino you are sending to
  - Option to select which Arduino you are sending to, select one or all




# Git
https://www.w3schools.com/git/default.asp?remote=github

Keyboard Shortcuts 
SHIFT + G —> Jump to the end 
q —> exit the view

Connect Folder To Terminal
mkdir myproject          (Creates new folder named “my project”)
cd myproject                (Changes current working directory to “myproject”)
Navigate to folder /Users/kateaiken/Desktop/Code/myproject
*Project name cant have spaces

Initialize Git
git init

GitHub
1. Choose working directory and initialize git (in terminal)
2. Create repository (in git if not already existing)
3. Copy Link and paste in terminal —> git remote add origin link or git remote set-url origin
4. If you have files existing in folder run —> git push --set-upstream origin master
5. If you have files existing in GitHub —> git pull origin main --allow-unrelated-histories
Check links are correct —> git remote -v
Remove origin link —> git remote remove origin

Status
git status
*Tracked - files that Git knows about and are added to the repository
*Untracked - files that are in your working directory, but not added to the repository
git status --short      (Use short for a compact indication of changes by indication of flags)
Short Flags
* ?? - Untracked files
* A - Files added to stage
* M - Modified files
* D - Deleted files

Staging
Staged files are files that are ready to be committed to the repository you are working on.
Add files to staging environment when a milestone is hit or part of the work is finished.
git add filename.type      (Add file to staging environment/stage it)
git add --all  or git add -A          (Stages all changed files (new, modified, deleted))

Commit
git commit -m “Explanation of commit/message” 
*-m includes a message to indicate what has changed
*-a automatically stage every changed, already tracked file (Use when you get the M short flag as proof the correct files were modified)

git log     (Show commit history)

Branches
git branch branch-name  (Creates new branch)
git branch     (Shows all branches with a * indicating the current branch)
git checkout branch-name    (Switches workspace to branch-name)
*Using -b with checkout creates a new branch and moves to the new one
*Changing branches, ls will show different files is they were changed in the branch 

Emergency Branch
git checkout -b emergency-fix  (Using an emergency branch to fix master without effecting other branches)
git merge emergency-fix   (Merge emergency-fix with current branch)
git branch -d emergency-fix   (Delete emergency-fix)

Merge Conflict
git merge branch-name     (Merge branch-name with current branch)
*Merge conflict error message indicates conflicted versions - Fix conflict
git add filename.type (Stage file)
git commit -m "merged with branch-name after fixing conflicts"   (Commit changes)
git branch -d branch-name  (Delete branch)


Other
git --version        (Version of git)
git config --global user.name “username”     (Change username globally)
git config --global user.email “email.”       (Change email globally)
ls        (Shows list of files in directory)

Help
git command -help    (See all the available options for the specific command)
git help --all    (See all possible commands)
$ git help --all   (Warningng: Outputs a lot of text)


