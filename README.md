pico-embedded-projects/
├── .gitignore
├── README.md
├── projects/
│   ├── 01_blink/
│   │   ├── blink.c
│   │   ├── CMakeLists.txt
│   │   └── README.md
│   ├── 02_button_input/
│   │   ├── button.c
│   │   ├── CMakeLists.txt
│   │   └── README.md
│   └── 03_pwm_led/
│       ├── pwm_led.c
│       ├── CMakeLists.txt
│       └── README.md
└── scripts/
    └── upload_pico.sh

GIT PUSH: git push -u origin main 
# Git Daily Workflow Guide

Quick reference for daily Git operations in your Pico projects.

---

## 📋 Daily Development Workflow

### 1. Start Your Work Session

```bash
# Navigate to project directory
cd ~/pico

# Pull latest changes (if working from multiple locations)
git pull

# Check current status
git status
```

### 2. During Development

```bash
# Check what files changed
git status

# View specific changes in files
git diff

# View changes in a specific file
git diff projects/01_blink/blink.c
```

### 3. After Completing a Feature/Fix

```bash
# Check what you changed
git status

# Add specific files
git add projects/01_blink/blink.c
git add projects/01_blink/CMakeLists.txt

# OR add all changes in projects folder
git add projects/

# OR add everything (respects .gitignore)
git add .

# Commit with descriptive message
git commit -m "Add PWM control for LED brightness"

# Push to GitHub
git push
```

---

## 🚀 Common Commands Quick Reference

### Checking Status

```bash
git status              # See what files changed
git log --oneline       # View commit history
git diff                # See changes not yet staged
git diff --staged       # See changes that are staged
```

### Adding and Committing

```bash
git add <filename>      # Stage specific file
git add .               # Stage all changes
git commit -m "message" # Commit with message
git push                # Push to GitHub
```

### Undoing Changes

```bash
# Undo changes to a file (before staging)
git checkout -- <filename>

# Unstage a file (keep changes)
git reset HEAD <filename>

# Undo last commit (keep changes)
git reset --soft HEAD~1

# Undo last commit (discard changes) ⚠️ CAREFUL!
git reset --hard HEAD~1
```

---

## 📦 Working with New Projects

### Creating a New Project

```bash
# Create project folder
cd ~/pico/projects
mkdir 03_new_project
cd 03_new_project

# Create your files
nano main.c
nano CMakeLists.txt
nano README.md

# Build and test
mkdir build && cd build
cmake ..
make

# Upload to Pico
~/pico/upload_pico.sh project_name.uf2

# If everything works, commit to Git
cd ~/pico
git add projects/03_new_project/
git commit -m "Add new_project: description of what it does"
git push
```

### Updating Existing Project

```bash
# Navigate to project
cd ~/pico/projects/01_blink

# Edit code
nano blink.c

# Build and test
cd build
make
~/pico/upload_pico.sh blink.uf2

# Test on hardware...

# If it works, commit
cd ~/pico
git add projects/01_blink/blink.c
git commit -m "Fix: Improved LED timing logic"
git push
```

---

## 🔄 Complete Daily Workflow Example

```bash
# 1. Start work
cd ~/pico
git pull

# 2. Work on your project
cd projects/02_uart
nano uart.c

# 3. Build and test
cd build
cmake ..
make
~/pico/upload_pico.sh uart.uf2

# 4. Test on Pico...
# 5. If it works, commit

cd ~/pico
git status                                    # Check changes
git add projects/02_uart/uart.c              # Stage file
git commit -m "Add error handling for UART"  # Commit
git push                                     # Push to GitHub
```

---

## ✅ Good Commit Message Examples

```bash
git commit -m "Add button debouncing logic"
git commit -m "Fix I2C communication timing issue"
git commit -m "Improve ADC sampling rate"
git commit -m "Add README for PWM servo project"
git commit -m "Refactor GPIO initialization code"
git commit -m "Update CMakeLists for multi-core support"
```

## ❌ Bad Commit Message Examples (Avoid These!)

```bash
git commit -m "update"
git commit -m "fixed stuff"
git commit -m "changes"
git commit -m "asdf"
git commit -m "final version"
```

---

## 🌿 Working with Branches (Optional - For Experiments)

```bash
# Create a new branch for experiments
git checkout -b experimental-feature

# Work on your code...
# Build and test...

# Commit changes
git add .
git commit -m "Experimental: Testing new approach"

# If experiment worked, merge back to main
git checkout main
git merge experimental-feature
git push

# If experiment failed, just switch back to main
git checkout main
# Your main branch is unchanged!

# Delete failed experiment branch
git branch -d experimental-feature
```

---

## 🛠️ Helper Scripts

### Quick Commit Script

Create `~/pico/quick_commit.sh`:

```bash
#!/bin/bash
if [ -z "$1" ]; then
    echo "Usage: ./quick_commit.sh 'commit message'"
    exit 1
fi

git add projects/ README.md upload_pico.sh
git commit -m "$1"
git push
echo "✓ Committed and pushed!"
```

```bash
chmod +x ~/pico/quick_commit.sh

# Usage:
./quick_commit.sh "Add button LED control project"
```

---

## 📊 Checking Your Work

```bash
# View commit history with graph
git log --oneline --graph --all

# View last 5 commits
git log --oneline -5

# See what changed in last commit
git show

# See files in repository
git ls-files

# Check remote repository
git remote -v
```

---

## 🚨 Emergency Commands (Use Carefully!)

```bash
# Discard ALL local changes (can't be undone!)
git reset --hard HEAD

# Undo last commit but keep files
git reset --soft HEAD~1

# Force push (only if you're sure!)
git push --force

# Remove file from Git but keep locally
git rm --cached filename
```

---

## 💡 Pro Tips

1. **Commit often** - Small, frequent commits are better than large ones
2. **Test before committing** - Always build and test before `git commit`
3. **Write clear messages** - Future you will thank present you
4. **Pull before push** - Always `git pull` if working from multiple machines
5. **Never commit secrets** - Tokens, passwords go in .gitignore
6. **Build folders stay local** - Never commit `build/` folders

---

## 🔍 When Things Go Wrong

### "I committed the wrong file!"

```bash
# If you haven't pushed yet
git reset --soft HEAD~1
# Fix your files
git add <correct files>
git commit -m "Correct commit message"
```

### "I need to edit the last commit message"

```bash
git commit --amend -m "New commit message"
# If already pushed
git push --force
```

### "I accidentally committed a secret/token"

```bash
# Remove last commit
git reset --hard HEAD~1

# Delete the secret file
rm secret_file.txt

# Add to .gitignore
echo "secret_file.txt" >> .gitignore

# Commit again without the secret
git add .
git commit -m "Your changes (without secrets)"
git push --force

# IMPORTANT: Revoke the exposed secret immediately!
```

---

## 📚 Most Used Commands Summary

```bash
# Daily essentials
git status          # What changed?
git add .           # Stage everything
git commit -m ""    # Commit with message
git push            # Upload to GitHub
git pull            # Download from GitHub

# Viewing
git log --oneline   # History
git diff            # What changed in files

# Undoing
git checkout -- file    # Discard changes
git reset HEAD~1        # Undo last commit
```

---

## 🎯 Your Typical Work Session

```bash
cd ~/pico                              # 1. Go to projects
git pull                               # 2. Get latest
# ... code, build, test ...            # 3. Work on code
git status                             # 4. Check changes
git add .                              # 5. Stage changes
git commit -m "Descriptive message"    # 6. Commit
git push                               # 7. Push to GitHub
```

