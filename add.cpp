#include <iostream>
#include <cstdlib> /* avec atoi, les str sont transformer en 0*/
#include <string> /*avec stoi les str provoque une erreur*/
/*
int str_to_int(char* str)
{
    int result = 0;
    int i = 0;
    for (char c = str[0]; c != '\0'; c = str[++i])
    {
        result = 10 * result + ((int)c - (int)'0');
    }
    return result;
}*/
int is_sign (char str[]) {
    if (str[0]=='-') {
        std::cout<< -1<< std::endl;
        return -1;
    } else {
        std::cout<< 1<< std::endl;
        return 1;
    }
}

int is_digit (char* str) {
    char n=*str;
    if (n=='0'){
        return true;
    } else if (std::atoi(str)==0) {
        return false;
    } else {
        return true;
    }
}


int main(int argc, char* argv []){
    if (argc==1) {
        std::cout <<"error: not enough arguments"<< std::endl;
        return -1;
    } else {
        std::cout <<is_digit(argv[1])<<std::endl;
        int sum = 0;
        for (int i = 1; i < argc; i++){
            sum = sum + std::atoi(argv[i]);
            //std::cout <<std::atoi(argv[i])<<std::endl;
        }
        std::cout <<"La somme totale est: " << sum << std::endl;
    }
    return 0;

    /*int sum = '0' ;
    for (int i=0; i<=argc; i++)
    {
        int nombre= argv[i];
        sum= sum + nombre;
    }
    std::cout <<sum<< std::endl;

    std::cout << str_to_int("12345") << std::endl;

    return 0;*/
}