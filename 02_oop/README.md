# C++, OOP, STL

The following approaches are required:
- C++;
- STL;
- Usage of additional libraries or 3rd party code is prohibited;
- For UI might be used winAPI, Qt etc;
- The application should be written with using OOP;
- Application should be cross-compile, e.g. should be compilable on Linux OS (Ubuntu 20.04) and Windows OS (Windows 10) without any code modifications.

----

# Task 2. Sub-Task 9. 2048 Game Application
## Implement 2048 game application.
Application should:
- Show main menu and controls to start a game
- Implement game logic
- Ability to undo the step
- Smooth animation
- Calculate and display user score
- Non-blocking UI – it should not freeze while using the app
- Documentation: requirements specification, software design documentation (application modules description, class diagram, sequence diagram).

----

## The folder Doc

 * **[WBS](Doc/WBS.md)** WBS File
 * **[Use Case Diagram](Doc/UseCaseDiagram.jpg)** Use Diagram File
 * **[Game Sequence diagrams](Doc/GameSequencediagrams.png)** Sequence Diagrams File
 * **[Class Diagram](Doc/ClassDiagram.png)** Class Diagram File
 
 ## The folder Src
 
* **[CMakeLists](Src/CMakeLists.txt)** File for the create Project
* **[main.cpp](Src/main.cpp)** File the Project
* **[mainwindow.h](Src/mainwindow.h)** File the Project
* **[mainwindow.cpp](Src/mainwindow.cpp)** File the Project
* **[mainwindow.ui](Src/mainwindow.ui)** File the Project

----

Assembly is performed by standard means CMake in the QtCreator 4.15.0
