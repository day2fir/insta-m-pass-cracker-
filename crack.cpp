#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstring>
#include <openssl/md5.h>

std::string generate_hash(const std::string &password)
{
    unsigned char result[MD5_DIGEST_LENGTH];
    MD5((unsigned char *)password.c_str(), password.length(), result);

    std::string hash;
    char buf[3];
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
    {
        sprintf(buf, "%02x", result[i]);
        hash += buf;
    }
    return hash;
}

bool crack_password(const std::string &target_hash, int max_length, std::string &cracked_password)
{
    std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+-=[]{};':\",./<>?";
    std::vector<std::string> combinations;

    for (int length = 1; length <= max_length; length++)
    {
        std::string combination(length, ' ');
        std::vector<bool> used(characters.length(), false);

        do
        {
            for (int i = 0; i < length; i++)
            {
                combination[i] = characters[i];
            }
            std::string hash = generate_hash(combination);
            if (hash == target_hash)
            {
                cracked_password = combination;
                return true;
            }
            std::reverse(combination.begin(), combination.end());
        } while (std::next_permutation(combination.begin(), combination.end()));
    }
    return false;
}

int main()
{
    std::string target_hash = "[ID]"; // MD5 hash of the password
    int max_length = 00;              // Maximum length of the password
    std::string cracked_password;

    if (crack_password(target_hash, max_length, cracked_password))
    {
        std::cout << "Password cracked: " << cracked_password << std::endl;
    }
    else
    {
        std::cout << "Password not found." << std::endl;
    }

    return 0;
}