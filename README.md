# Chat Application in C (Chess & Chat) 

# Summary #
This chat program was written in C by myself and 5 other teammates. Our objective was to put to use some of the technologies we had learned from our courses (Data Structures & Algorithms, GUI, etc.) and develop a program from scratch to familiarize ourselves with the Software Development Life Cycle. 

There are two different "projects" that make up this program. The first part is the Chess game (just the src code for the game is on the "main" branch), where we created a GUI to host the game environment (chess board, chess pieces), engineered the Data Strucures to hold the data (using arrays, Doubly Linked Lists, Trees primarily), and created an opponent client with three distinct levels using the Minimax algorithm. The second part is the Chat functionality. We used most of the same Data Structures for accomplishing this task, however the "task" itself was divided into two sub-tasks: building client side and server side. These two sides were connected via socket programming. 

Please reference the software specifications for more indepth analysis on how the program worked!

# Technologies Used #
Please reference the software specification for more details on the technologies that were used in this project. However, here is a quick list of everything we used: Arrays, Doubly Linked Lists, Trees, Queueing, GUI, Socket Programming (some others listed in the software specification but the aforementioned were the primary technologies used in this project). 

# Files #
These descriptions are taken from the software specification. ClientSide and ServerSide are on the "master" branch, while the Chess files are on the "main" branch.

CLIENT SIDE:
1. Client.c
This file contains functions and other communications elements for the client side that allow it to recieve, process, and send data.

2. GUI_LC.c
This file contains the GUI functions for the chat windows, chess board and all of the functions to handle signals from the user input.

3. ClientList.c
This file contains the functions to perform the needed tasks on the client data structures.

4. ClientLog.c
This file contains the functions to save the client data in a text file when client is shut down.

5. Main.c
This file "runs" the modules from the client/server side.


SERVER SIDE:
1. ServerFunctions.c
This file contains the functions that handle user requests from the server.

2. ServerList.c
This file contains the functions for the server data structures, creating lists and accounts.

3. ServerLog.c
This file contains the functions on server-side to save the client data in a text file when client is shut down.

4. Server.c
This file contains the main function for the server program and calls the other functions needed for server operation.


CHESS FILES:
Please check out the "main" branch for these files!

1. ChessIO.c
This file contains the functions to print the ASCII menus of the user input. 

2. Board.c
This file contains the functions that will perform all of the tasks related to the chess board. 

3. Moves.c
This file contains the functions that pertain to the rules of chess. The function here can be called to check for valid moves and generate moves for the current board.

4. ChessTree.c
This file contains the functions to perform the needed tasks on the double linked list MLIST (MovesList).

5. MovesList.c
This file contains the functions to perform the needed tasks on the chess board tree TNODE (TreeNode).

6. GameLog.c
This file contains the functions that will allow for a moves log to be saved at the end of the game. 

7. AI.c
This file contains the functions that will generate the moves for the computer turn in the game. 

8. Main.c
This module contains the main function and the game play loops for each of the game play modes.
