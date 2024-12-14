# Password Cracker - C++ Implementation

This repository contains a simple C++ script for cracking MD5 hashed passwords using brute force. It is intended for educational purposes only. Unauthorized usage is strictly prohibited.

## Steps to Use

### 1. Prerequisites
Ensure you have the following installed:
- **Visual Studio Code (VS Code)**
- **g++ compiler**
- **OpenSSL library** (for MD5 hash computations)

### 2. Create the Script File
1. Open VS Code.
2. Create a new file with a `.cpp` extension, e.g., `password_cracker.cpp`.
3. Copy the C++ script provided below into the file:

```cpp
#include <iostream>
#include <string>
#include <openssl/md5.h>

using namespace std;

// Function to generate MD5 hash
string md5(const string& str) {
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5((unsigned char*)str.c_str(), str.length(), (unsigned char*)&digest);

    char mdString[33];
    for (int i = 0; i < 16; i++) {
        sprintf(&mdString[i * 2], "%02x", (unsigned int)digest[i]);
    }
    return string(mdString);
}

// Brute force function
void crack_password(const string& hash) {
    string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string attempt = "";

    for (char c1 : charset) {
        for (char c2 : charset) {
            for (char c3 : charset) {
                attempt = {c1, c2, c3};
                if (md5(attempt) == hash) {
                    cout << "Password found: " << attempt << endl;
                    return;
                }
            }
        }
    }
    cout << "Password not found." << endl;
}

int main() {
    string hash;
    cout << "Enter MD5 hash: ";
    cin >> hash;

    crack_password(hash);
    return 0;
}
```

### 3. Replace Placeholder
Replace `Enter MD5 hash:` in the `main()` function with your target hash. For example:

```cpp
string hash = "[ID]"; // Replace [ID] with your MD5 hash.
```

### 4. Save the File
Save the file as `password_cracker.cpp`.

### 5. Compile the Script
Open the VS Code terminal (Ctrl + Shift + `) and navigate to the directory containing the file. Use the following command to compile the program:

```bash
g++ -o password_cracker password_cracker.cpp -lcrypto
```

### 6. Run the Script
Run the compiled executable:

```bash
./password_cracker
```

### 7. Results
Enter the MD5 hash when prompted. The program will attempt to crack the hash by brute-forcing 3-character combinations from a given charset.

## Notes
1. **Performance:** This example brute-forces 3-character passwords. For longer passwords, the script must be extended, significantly increasing runtime.
2. **Legal Disclaimer:** This tool is for educational purposes only. Do not use it for unauthorized activities.

## Contributions
Pull requests to optimize the code or extend functionality are welcome!

## License
This project is licensed under the MIT License. See the `LICENSE` file for details.
