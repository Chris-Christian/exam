#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void receiving(string , int );
string addbinary(string s1, string s2) {
    int i = s1.size() - 1;
    int j = s2.size() - 1;
    int carry = 0;
    string result = "";
    while (i >= 0 || j >= 0 || carry) {
        int n1 = 0, n2 = 0;
        if (i >= 0) {
            n1 = s1[i] - '0';
        }
        if (j >= 0) {
            n2 = s2[j] - '0';
        }

        int sum = n1 + n2 + carry;

        if (sum == 0) {
            carry = 0;
            result += '0';
        } else if (sum == 1) {
            carry = 0;
            result += '1';
        } else if (sum == 2) {
            carry = 1;
            result += '0';
        } else if (sum == 3) {
            carry = 1;
            result += '1';
        }
        i--;
        j--;
    }
    reverse(result.begin(), result.end());
    return result;
}

string onecompliment(string temp)
{
	string result = "";
	for(int i=0;i<temp.size();i++)
	{
		if(temp[i] == '0')
		{
			result+='1';	
		}
		else
		{
			result+='0';	
		}	
	}
	return result;
}

string sumdata(vector<string> arr , int temp)
{
	int size = arr.size();
	vector<string> summation = arr;

	while(summation.size() > 1)
	{
		string push = addbinary(summation[0] , summation[1]);
		summation[0] = push;
		summation.erase(summation.begin() + 1);	
	}	
	
	string final = summation[0];
	if(final.size() > temp)
	{
		int cut = final.size() - temp;
		string s1 = "";
		for(int i=0;i<cut;i++)
		{
			s1+=final[i];
		}
		string new_final = "";
		for(int i= cut;i<final.length();i++)
		{
			new_final+=final[i];
		}
		
		string temp2 = addbinary(s1 , new_final);
		return temp2;
	}
	else
	{
		return final;	
	}	

}


void sending(string data, int temp) {
    int size = data.size();
    int parts = size / temp; 
    vector<string> arr;
    
    for (int i = 0; i < parts; ++i) {
        string result = "";
        for (int j = i * temp; j < (i + 1) * temp;j++) {
            result += data[j];
        }
        arr.push_back(result);
    }
    
    cout << "The data after dividing in into " << temp << " bits : " << endl;
    for(int i=0;i<arr.size();i++)
    {
    	cout << arr[i] << endl;
	}

    string sum = sumdata(arr , temp);
    cout << "The sum of the data is : " << sum << endl;
	string checksum = onecompliment(sum);
	cout << "The value of checksum is : " << checksum << endl;
	receiving(checksum , temp);    
}

void receiving(string checksum , int temp)
{
	cout << endl << "Receiver Side : " << endl;
    string data = "10011001111000100010010010000100";
    cout << "Data : " << data << endl;
    int size = data.size();
    int parts = size / temp; 
    vector<string> arr;
    
    for (int i = 0; i < parts; ++i) {
        string result = "";
        for (int j = i * temp; j < (i + 1) * temp;j++) {
            result += data[j];
        }
        arr.push_back(result);
    }
    cout << "The data after dividing in into " << temp << " bits : " << endl;
    for(int i=0;i<arr.size();i++)
    {
    	cout << arr[i] << endl;
	}

    string sum = sumdata(arr , temp);
    cout << "The sum of the data is : " << sum << endl;
	string temp2 = addbinary(sum , checksum);
	cout << "After adding the checksum value in the sum of the data : " << temp2 << endl;
	string check = onecompliment(temp2);
	cout << "Complemented Value : " << check << endl;
	int flag = 0;
	for(int i=0;i<check.size();i++)
	{
		if(check[i] == '1')
		{
			flag = 1;
			break;
		}
	}
	
	if(flag == 0)
	{
		cout << "There is no error in the data" << endl;
	}
	else
	{
		cout << "There is error in the data" << endl;
	}
}

int main() {
    int temp;
    string data = "10011001111000100010010010000100";
    cout << "Sender Side : " << endl;
    cout << "Data : " << data << endl;
    cout << "Enter the m bit: ";
    cin >> temp;
    sending(data, temp);
    return 0;
}
