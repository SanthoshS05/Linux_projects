---

# Tic Tac Toe — Socket Programming (C)

A console-based **Tic Tac Toe** game implemented in **C** using **TCP sockets**.  
This project supports **three play modes**:
1. **Server Mode** – host a network game.  
2. **Client Mode** – connect to a remote server and play over the network.  
3. **Local Mode** – play a two-player game on the same terminal.  

## 🧠 Overview

This project demonstrates **socket-based client–server communication** through a simple and interactive **Tic Tac Toe** game.  
It helps understand how to:
- Create TCP sockets using the **`socket()`**, **`bind()`**, **`listen()`**, and **`accept()`** functions.
- Establish connections using **`connect()`**.
- Send and receive game data using **`send()`** and **`recv()`**.
- Manage game logic and synchronization between two networked players.

## Setup and Installation
### Prerequisites
Make sure GCC and Make are installed:
```bash
sudo apt update
sudo apt install gcc make
```

1. **Clone the repository**:

   ```bash
   git clone https://github.com/SanthoshS05/Linux_projects.git
   cd Linux_projects/1.Socket_Programming/1_Tic-Tac-Toe
   ```

2. **Compile the code**:

   ```bash
   make
   ```

3. **Run the executable**:

Run:
   ```bash
   cd bin
   ./tictactoe
   ```


   The server will wait for a client to connect.

4. **Choose Mode**:

   ```bash
   1. Run as Server  
   2. Run as Client  
   3. Run Local Game
    ```

5. **Server Side**
      
   Server will Display the ip of its Device automatically
   ```bash
   [SERVER]Interface: wlp2s0       IP: <ipv4 of Server>

   ```

6. **Client Side**

   ```bash
   Enter server IP address: <Enter ipv4 addr of Server>

   ```
## Contributors
**Santhosh Suresh**  
Email: santhoshsuresh150@gmail.com  
Developed the client-server architecture, local gameplay, and documentation.
