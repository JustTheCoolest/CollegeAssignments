#include <iostream>
#include <string>
#include <cctype>
#include <pthread.h>

struct ThreadArgs {
    std::string str;
    bool countVowels;
};

void* countVowelsOrConsonants(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    std::string str = args->str;
    bool countVowels = args->countVowels;
    int count = 0;
    std::string vowels = "aeiouAEIOU";
    for (char c : str) {
        if(!std::isalpha(c)){
            continue;
        }
        bool isVowel = (vowels.find_first_of(c) != std::string::npos);
        count += (isVowel == countVowels);
    }
    int* countPtr = new int(count);
    return (void*)countPtr;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <string>" << std::endl;
        return 1;
    }
    std::string str = argv[1];
    pthread_t vowelThread, consonantThread;
    ThreadArgs vowelArgs = {str, true};
    ThreadArgs consonantArgs = {str, false};
    pthread_create(&vowelThread, NULL, countVowelsOrConsonants, (void*)&vowelArgs);
    pthread_create(&consonantThread, NULL, countVowelsOrConsonants, (void*)&consonantArgs);
    void *vowelCountPtr, *consonantCountPtr;
    pthread_join(vowelThread, &vowelCountPtr);
    pthread_join(consonantThread, &consonantCountPtr);
    int vowelCount = *(int*)vowelCountPtr;
    int consonantCount = *(int*)consonantCountPtr;
    delete (int*)vowelCountPtr;
    delete (int*)consonantCountPtr;
    std::cout << "Vowels: " << vowelCount << std::endl;
    std::cout << "Consonants: " << consonantCount << std::endl;
    return 0;
}
