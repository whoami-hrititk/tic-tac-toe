🕹️ Tic-Tac-Toe (C++ with ncurses)

This is a dynamic Tic-Tac-Toe game built in C++ using the ncurses library. The game runs in the terminal and features an interactive grid, real-time cursor control, and a clean interface—all rendered with ncurses.
🎯 Features

Interactive 3x3 grid gameplay

Built using the ncurses library for terminal-based UI

Two-player mode (local)

Keyboard navigation with arrow keys

Real-time board updates and win detection

Dynamic UI—resizes gracefully in most terminal environments

🧰 Requirements

C++ compiler (e.g. g++)

ncurses library

On Debian/Ubuntu-based systems:

    sudo apt-get install libncurses5-dev libncursesw5-dev

⚙️ Build & Run

Clone the repository:

    git clone https://github.com/whoami-hritik/tic-tac-toe.git
    cd tic-tac-toe

Compile the game:

    g++ -o tictactoe game.cpp -lncurses

Run it:

    ./tictactoe

🎮 Controls

Arrow Keys – Move the cursor

Enter or Space – Place X or O

q – Quit the game

📦 File Structure

tic-tac-toe-ncurses/
├── main.cpp          # Main game logic
├── README.md         # This file

🤝 Contributing

Pull requests and suggestions are welcome! Feel free to fork the repo and improve the game.
