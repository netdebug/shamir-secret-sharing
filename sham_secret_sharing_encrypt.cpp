/*
This is the encryption program for the Shamir's Secret Sharing crypto-system, writes keys to keys.txt
*/

#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <fstream>

std::vector<int> coefficients;
std::vector<std::pair<int,long long>> key_list;
std::ofstream keys_stream("keys.txt");


void generate_coefficients(int threshold)
{
    std::random_device device;
    std::mt19937 generator(device());

    std::uniform_int_distribution<int> range(1,100);

    for (int i = 1 ; i < threshold ; i++)
    {
        coefficients.push_back(range(generator));
        std::cout<<coefficients[i-1]<<' ';
    }
}

void generate_keys(int secret,int split_num)
{
    std::pair<int,long long> temp;

    for(int i = 1 ; i <= split_num ; i++)
    {
        temp.first = i;
        temp.second = secret;

        for(int j = 0 ; j < coefficients.size() ; j++)
        {
            temp.second += coefficients[j] * pow(i,j+1);
        }

        key_list.push_back(temp);
        std::cout<<key_list[i-1].first<<' '<<key_list[i-1].second<<'\n';
        keys_stream <<key_list[i-1].first<<' '<<key_list[i-1].second<<'\n';
    }
}

int main()
{
    int secret;
    std::cout<<"Enter the secret (max. 10^9): ";
    std::cin>>secret;

    int split_num,threshold;
    std::cout<<"\nEnter the number of keys to be made and the minimum number of keys required to get the secret: ";
    std::cin>>split_num>>threshold;

    keys_stream << split_num <<' '<< threshold << '\n';

    generate_coefficients(threshold);
    std::cout<<"\n";
    generate_keys(secret,split_num);

    keys_stream.close();

}
