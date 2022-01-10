# GUI Git client

Design and implement GUI Git client application.
The following approaches are required:
- C++;
- STL;
- Usage of additional libraries or 3rd party code is prohibited;
- For UI might be used Qt;
- Use MVC design pattern in your application;
- The application should be written using OOP.

==========================================================
// Instruction for application gitgui

1. Start Window
	- Move to the repository direcotry
		- Load repository if last exist and set work direcotry at the root path of git repository
		- If in select direcotry now repository application throw window error and still works untill 
			user select existing direcotry whith repository or exit application.
	- Clone new repository
		- this submenu don't show any widgets error. In error case application keep working
		- If Directory field is empty:
			- get name direcotry of repository from last name of URL
		- If Directory write handle (relative). Directory create in folder where application runs.
			If select absolute path, working direcotry will be in select direcotry.
		- Application check if folder exist.
		- When Clone is success gitgui opens working repository that has been cloned
			
2. View window. Make only checkout! Don't makes any changes!
	- Double click on commit or branch show changes in select commit/branch
	- Right click on mouse button open context menu for make checkout for commit/branch respectively
	- Commits tree has two main branch:
		- "All" - show all commits in hierarchy from new to old commits 
		- "Tree" represent like a tree structure (in theory :) )
	- Current branch and current commit show below whith corresponding names: "Branch:" "Commit:"
	- "Enter find text changes" field find all commits where some text was changed. Text write in field next to button 
		Find Commits.
	- "Find Commits" button run procedure for find list commits that show in pullup widget. When you select commits from this
		list on text panel whill show commit changes whith first occure line whith text that you whanted to find

3. Edit window. Makes commit and add/remove file form/to index range.
	- Dobleclicked on filename in indexed/notindexed list widget add or restore to index range.
	- "Index ALL" push all files to index
	- "Restore" pull all files from index to untracked or notindex.
	- Text Field "Show status" only shows status of make commit.
	- Commit is created with signed.
	- Commit dosn't creat in case:
		- no indexing files
		- no msg in field "Field for Commit MSG"
		- in other case commit will be create!
	- "Clear" button only clears "Show status" and "Field for Commit MSG" box
		
 ... - PUSH and PULL not implemented
