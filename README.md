# WNote
## Create and manage quick notes from the Windows cmd

### Requirements
- Windows operating system

### When to use it?
When you want a quick way to save a note and easily retrieve it without using temporary txt files on the desktop or in some remote folder: with WNote everything is organized!

### How to use it?
- run the command "note -s" to setup the notes folder (it will be created in your default "My Documents" Windows folder)
- Now you can:
  - create a new note
  - view a note
  - copy a note to the clipboard
  - manage the note
- To view the command syntax, run "note" with no parameters.

### Customization
I suggest you add the program to the environment variables, to use the command from cmd quickly:
1. Type in search bar "environment..." and choose Edit the system environment variables which opens up the System Properties window
1. Click the Environment Variables... button
1. In the Environment Variables tab, double click the Path variable in the System variables section
1. Add the path to the folder containing the wnote.exe to the Path by double clicking on the empty line and paste the path.
1. Click ok and exit. Open a new cmd prompt and hit the command from any folder and it should work.
