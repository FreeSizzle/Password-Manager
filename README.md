# Password Manager (C++)

A console-based Password Manager built in C++ that allows users to securely store, manage, and retrieve credentials. The project demonstrates object-oriented programming, file handling, data persistence, random password generation, and basic encryption techniques.

## Features

* Add new credentials
* View stored credentials
* Search credentials by username
* Update existing credentials
* Delete credentials
* Generate strong random passwords
* Master password authentication
* Change master password
* Save credentials to file
* Load credentials from file on startup
* XOR + Hex password encryption before storage

## Technologies Used

* C++
* Object-Oriented Programming (OOP)
* STL Vector
* File Handling
* String Streams
* Random Number Generation
* Basic Encryption (XOR + Hex Encoding)

## Project Structure

```text
project/
│
├── data/
│   ├── passwords.txt
│
├── include/
│   ├── Credentials.h
│   └── PasswordManager.h
│
├── src/
│   ├── main.cpp
│   └── PasswordManager.cpp
│
├── master.txt
├── README.md
└── .gitignore
```

## How It Works

### Authentication

The application requires a master password before granting access.

```text
Enter Master Password:
```

The master password is stored in `master.txt`.

### Credential Storage

Credentials are stored in:

```text
data/passwords.txt
```

Format:

```text
website|username|encrypted_password
```

Example:

```text
github|john|26323b2a38383c24392f
```

Passwords are encrypted using XOR encryption and then converted to hexadecimal before being written to disk.

### Password Generation

The application can generate random passwords using:

* Uppercase letters
* Lowercase letters
* Numbers
* Special characters

Example:

```text
Generated Password: aB7@kP9#xL
```

## Building and Running

### Compile

```bash
g++ src/main.cpp src/PasswordManager.cpp -o passwordmanager
```

### Run

Windows:

```bash
passwordmanager.exe
```

or

```bash
.\passwordmanager.exe
```

Linux/macOS:

```bash
./passwordmanager
```

## Sample Menu

```text
Password Manager

1. Add Credential
2. View Credentials
3. Search Credential
4. Delete Credential
5. Update Credential
6. Generate Password
7. Change Master Password
8. Exit
```

## Learning Outcomes

This project helped me practice:

* C++ Classes and Objects
* Header and Source File Organization
* STL Containers
* File Handling
* Data Serialization
* Encryption Basics
* Random Number Generation
* Project Structuring
* Git and GitHub Workflow

## Future Improvements

* Password Strength Checker
* Password Masking
* Hashing Master Password
* AES Encryption
* Credential Categories
* GUI using Qt or Tkinter
* Export/Import Functionality
* Unit Testing

## Disclaimer

The XOR encryption used in this project is for educational purposes only and should not be considered secure for production use. A real-world password manager should use modern cryptographic algorithms and secure password hashing techniques.
