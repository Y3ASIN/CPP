#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <cstdlib> 
using namespace std;

// Global variable for alphabets
std::string alphabets = "ZYXWVUTSRQPONMLKJIHGFEDCBA";

// Function prototype to check duplicate elements in a list
bool isDuplicate(const std::vector<int>& lst);

// Function prototype to encrypt plaintext
void encode(const std::string& plaintext, const std::vector<int>& key);

// Function prototype to decrypt ciphertext
void decode(const std::string& ciphertext, const std::vector<int>& key);

int main() {
    while (true) {
        std::string choice;
        std::cout << "Type 'encode' to encrypt\nType 'decode' to decrypt\n==> ";
        std::cin >> choice;

        if (choice == "encode" || choice == "decode") {
            std::string text;
            std::cout << "Type your message: ";
            std::cin >> text;

            int k;
            std::cout << "Type the key (Only unique integer): ";
            std::cin >> k;

            std::vector<int> key;
            while (k > 0) {
                key.push_back(k % 10);
                k /= 10;
            }
            std::reverse(key.begin(), key.end());

            // Check if list has duplicate value or not
            while (isDuplicate(key)) {
                std::cout << "\n\n!Sorry This encryption could not possible\nYou must have to enter Only unique integer as Key\n\n";
                std::cout << "Type the key (Only unique integer): ";
                std::cin >> k;

                key.clear();
                while (k > 0) {
                    key.push_back(k % 10);
                    k /= 10;
                }
                std::reverse(key.begin(), key.end());
            }

            if (choice == "encode") {
                encode(text, key);
            } else {
                decode(text, key);
            }
        } else {
            std::cout << "\nWrong Selection\nYou need to type 'encode' to encrypt or 'decode' to decrypt\n";
        }

        char isContinue;
        std::cout << "Do you want to continue? (Y/N): ";
        std::cin >> isContinue;

        if (isContinue == 'n' || isContinue == 'N') break;
    }

    std::cout << "\n\n---------------------------------------------------\n";
    std::cout << "Goodbye\nThanks for using....\n";
    std::cout << "---------------------------------------------------\n";

    return 0;
}

// Function to check duplicate elements in a list
bool isDuplicate(const std::vector<int>& lst) {
    std::set<int> seen;
    for (int item : lst) {
        if (seen.find(item) != seen.end()) {
            return true;
        }
        seen.insert(item);
    }
    return false;
}

// Function to encrypt plaintext
void encode(const std::string& plaintext, const std::vector<int>& key) {
    std::vector<std::string> ciphertext_list(key.size(), "");

    // Fill empty cells with extra characters from alphabets
    int total_characters = plaintext.size();
    int num_rows = (total_characters + key.size() - 1) / key.size();

    for (int i = total_characters; i < num_rows * key.size(); ++i) {
        plaintext += alphabets[i];
    }

    // Seperate string by column
    for (int column = 0; column < key.size(); ++column) {
        int pointer = column;

        while (pointer < plaintext.size()) {
            ciphertext_list[column] += plaintext[pointer];
            pointer += key.size();
        }
    }

    // Create a dictionary using two lists
    std::unordered_map<int, std::string> ciphered_dict;
    for (int i = 0; i < key.size(); ++i) {
        ciphered_dict[key[i]] = ciphertext_list[i];
    }

    // Sort the key
    std::vector<int> sorted_key = key;
    std::sort(sorted_key.begin(), sorted_key.end());

    // Create Encrypted String
    std::string ciphertext;
    for (int i : sorted_key) {
        ciphertext += ciphered_dict[i];
    }

    std::cout << "Encrypted Text is: " << ciphertext << std::endl;
}

// Function to decrypt ciphertext
void decode(const std::string& ciphertext, const std::vector<int>& key) {
    std::vector<int> sorted_key = key;
    std::sort(sorted_key.begin(), sorted_key.end());

    int num_columns = key.size();
    int num_rows = (ciphertext.size() + num_columns - 1) / num_columns;

    std::vector<std::string> cipher_text(num_columns);
    for (int i = 0; i < num_columns; ++i) {
        cipher_text[i] = ciphertext.substr(i * num_rows, num_rows);
    }

    std::unordered_map<int, std::string> cipher_text_dict;
    for (int i = 0; i < num_columns; ++i) {
        cipher_text_dict[sorted_key[i]] = cipher_text[i];
    }

    std::vector<std::string> cipher_text_key_sorted(num_columns);
    for (int num : key) {
        cipher_text_key_sorted.push_back(cipher_text_dict[num]);
    }

    std::string plain_text = "";
    while (cipher_text_key_sorted[0].size() > 0) {
        for (const std::string& strings : cipher_text_key_sorted) {
            plain_text += strings[0];
            cipher_text_key_sorted[0] = strings.substr(1);
        }
    }

    // Reverse plain text
    std::reverse(plain_text.begin(), plain_text.end());

    // Remove extra characters from the beginning
    std::string alphabets = "ZYXWVUTSRQPONMLKJIHGFEDCBA";
    while (true) {
        if (plain_text[0] == alphabets[0]) {
            plain_text = plain_text.substr(1);
            alphabets = alphabets.substr(1);
        } else {
            break;
        }
    }

    std::cout << "Your Decrypted Text is: \"" << plain_text << "\"" << std::endl;
}
