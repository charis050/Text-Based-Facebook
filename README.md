# Text-Based Facebook

## Overview
This project is a text-based implementation of Facebook, developed in C. It provides core functionalities such as user registration, profile management, post handling, and friend connections. The application leverages fundamental concepts like **structures**, **linked lists**, **stacks**, and **memory allocation** to create a fully functional console-based social network.

---

## Features
### User Management
- **Register New Users**: Add unique usernames and passwords. Usernames are stored in lowercase and arranged in ascending order.
- **Login System**: Authenticate users using their username and password. Logged-in users can access their specific data directly without re-entering their username.

### Profile Management
- **Change Password**: Update a user’s password after verifying the old one.

### Friend Management
- **Add Friends**: Add friends from the registered user list. Only valid usernames can be added as friends.
- **Remove Friends**: Remove existing friends from a user’s friend list.
- **Friend-Post Connection**: Link friends to their respective posts, enabling viewing of friends' posts.

### Post Management
- **Add Posts**: Add posts to a user’s profile. Posts are managed as a stack (last-in, first-out).
- **Remove Posts**: Remove the latest post from a user’s profile.

### Post Viewing
- **View Posts**: Display posts from a user or their friends, with support for paginated viewing.

### User-Friendly Navigation
- **Main Menu**: Intuitive navigation for all features, including user registration, login, and other functionalities.
- **Session-Specific Menus**: Logged-in users can directly manage their profile, posts, and friends without redundant prompts.

### Exit
- Terminates the program with a goodbye message.

---

## Project Structure
The project is organized into the following files:
- **`main.c`**: Manages the application’s flow and user interactions.
- **`a2_functions.c`**: Implements core functions for user, post, and friend management.
- **`a2_functions.h`**: Function declarations and prototypes.
- **`a2_nodes.h`**: Definitions of data structures, including users, friends, and posts.

---

## How to Compile and Run
Follow these steps to compile and execute the program:

### Compilation
#### Windows:
```bash
gcc -g *.c -o TextBasedFacebook.exe
./TextBasedFacebook.exe

