// THis is an exercise to hack a string that was asked during an online interview.
// Here is the breakdwon of the problem:
// A password detection system for companys account detects a password as similar
// if the number of vowels is equal to the number of consonants
// Password consists of lowercase letters only
// To check the strength of the password and how easily it could be haked, some manipulations
// can be made to the password. In one operation, any character of the string can either be incremented or decremented .
// For example, 'f' can be changed to 'e' or 'g'. Note that 'a' cannot be decremented and 'z' cannot be incremented.
// Find the minimum number of operations required to make the password similar.
//e.g hack -> iack which has two vowels and two consonants and we only change the 'h'
// so our function should return 1
// if this is impossible, return -1


// Lets consider the algorithm

#include <string>
#include <vector>
#include <unordered_map>

bool is_vowel(const char c){
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' );
}

char find_operation(char c )
{
    // this function will take a char and return the next or the previous char based on
    // requirements

        // here is more tricky since there is the situation where a consonant could not have a neighbor vowel
    if ( c == 'z') return 'y'; // edge case
    return (is_vowel(c + 1)  ? (c + 1 )  : (c - 1) );
}

int count_minimum_operations(std::string password)
{
    std::vector<char> vowels;
    std::vector<char> consonants;
    int minimum_operations = 0 ;

    if (password.size() < 1 ) return -1;

    for (const char c : password){
        if (is_vowel(c)) vowels.push_back(c);
        else consonants.push_back(c);
    }

    int num_vowels = vowels.size();
    int num_consonants = consonants.size();

    if (num_vowels == num_consonants) return 0; // case with balance

    else if (! (password.size() % 2 == 0)) return -1; // case with odd chars

    else if ( num_vowels > num_consonants) // we need to check now which vowels we can change
    {
       return (num_vowels - num_consonants) / 2; // since for sure all the vowels can be change to consonants
    }

    else{
        int i = 0; // index of consonants
        while ( !(num_consonants == num_vowels) && i < consonants.size()){
            char cons_change = find_operation(consonants[i]);
            if (is_vowel(cons_change))
            {
                ++minimum_operations;
                ++num_vowels;
                --num_consonants;
            }
            ++ i;
        }
    }
    return (num_consonants == num_vowels ? minimum_operations : -1 );
    
}