#include <string>
#include <iostream>

std::string to_camel_case(std::string text) {
    std::string a = "";
    int len = text.size();
    if (len == 0){
        return "";
    }
    a += text[0];
    for(int i = 1;i < len;i++){
        if(text[i] != '_' && text[i] != '-'){
            if(text[i-1] == '_' || text[i-1] == '-'){
                if (text[i] >= 'a' && text[i] <= 'z'){
                    a += (text[i] - 32);
                }
                else{
                    a += text[i];
                }
            }
            else{
                a += text[i];
            }
        }
    }
    return a;
}

int main(){
    std::cout << to_camel_case("The-stealth-warrior");

}