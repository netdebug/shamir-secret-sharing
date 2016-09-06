/*
Decryption program for Shamir's Secret Sharing crypto-system, reads keys from keys.txt
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <random>

std::vector<int> coefficients;
std::vector<std::pair<int,long long>> key_list;

void fisher_yates_shuffle()
{
    std::random_device device;
    std::mt19937 generator(device());
    std::pair<int,long long> temp;

    for(int i = key_list.size()-1 ; i>0 ; i--)
    {
        std::uniform_int_distribution<int> range(1,i);
        int random_index = range(generator);

        temp = key_list[i];
        key_list[i] = key_list[random_index];
        key_list[random_index] = temp;
    }

    std::uniform_int_distribution<int> range(1,key_list.size()-1);
    int random_index = range(generator);

    temp = key_list[0];
    key_list[0] = key_list[random_index];
    key_list[random_index] = temp;

}

int main()
{
    std::ifstream keys_stream("keys.txt");
    std::pair<int,long long> temp_key;

    int split_num, threshold;
    keys_stream >> split_num >> threshold;

    while(true)
    {
        keys_stream >> temp_key.first >> temp_key.second;

        if (keys_stream.eof())
            break;

        key_list.push_back(temp_key);

        if (keys_stream.eof())
            break;
    }

    fisher_yates_shuffle();

    std::cout<<"The random "<<threshold<<" keys selected are\n";
    for(int i = 0 ; i<threshold ; i++)
    {
        std::cout<<'('<<key_list[i].first<<','<<key_list[i].second<<')';
        if (i != threshold-1)
            std::cout<<",\n";
    }

    std::cout<<"\n\n";

    long double secret = 0, mult = 1;

    for(int i = 0 ; i < threshold ; i++)
    {
        std::cout<<"FIRST: "<<key_list[i].first<<"\nSECOND: "<<key_list[i].second<<'\n';
        mult = 1;
        for(int j = 0 ; j < threshold ; j++)
        {
            if(j != i)
            mult *= float((0 - key_list[j].first))/float((key_list[i].first - key_list[j].first));
        }
        std::cout<<"MULT: "<<mult<<'\n';
        secret += mult * key_list[i].second;
        std::cout<<"TEMPSECRET: "<<secret<<"\n\n";
    }

    std::cout<<"\nThe secret is: "<<secret;
}
