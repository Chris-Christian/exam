#include <iostream>
#include <vector>
using namespace std;

void receiving(string);
string crc_generator(string equation)
{
	string result = "";
	string store = "";
	int max = 0;
	
	int j=0;
	while(j<equation.length())
	{
		if(equation[j] == 'x')
		{
			int temp3 = equation[j+1] - '0';
			store+=equation[j+1];
			j+=2;
			if(temp3 > max)
			{
				max = temp3;
			}
		}	
		else
		{
			j+=1;
		}
	}

	for(int i=max;i>=0;i--)
	{
		int flag = 0;
		for(int t=0;t<store.length();t++)
		{
			int temp2 = store[t] - '0';
			if(i == temp2)
			{
				result+='1';
				flag = 1;	
			}	
		}
		if(flag == 0)
		{
			result+='0';
			
		}			
	}
	return result;
}

string binary_dev(string s1 , string s2)
{
	string div = "";
	for(int i=0;i<s1.length();i++)
	{
		div+=s2[i];
	}
	vector<string> parts;
	int t=0;
	int flag = 0;
	int cnt=0;
	for(int i=s1.length();i<s2.length();i++)
	{
		string res = "";
		if(flag == 0)
		{
			flag = 1;
			if(div[0] == '1')
			{
				for(int j=1;j<s1.length();j++)
				{
					int n1 = div[j] - '0';
					int n2 = s1[j] - '0';
					int ans = n1^n2;
					res+=ans + '0'; 
				}
				res+=s2[i];
				parts.push_back(res);
			}
			else
			{
				for(int j=1;j<s1.length();j++)
				{
					int n1 = div[j] - '0';
					int n2 = 0;
					int ans = n1^n2;
					res+=ans + '0'; 
				}
				res+=s2[i];	
				parts.push_back(res);		
			}			
		}
		else
		{
			if(parts[t][0] == '1')
			{
				for(int j=1;j<s1.length();j++)
				{
					int n1 = parts[t][j] - '0';
					int n2 = s1[j] - '0';
					int ans = n1^n2;
					res+=ans + '0'; 
				}
				res+=s2[i];
				parts.push_back(res);
				cnt++;
				t++;
			}
			else
			{
				for(int j=1;j<s1.length();j++)
				{
					int n1 = parts[t][j] - '0';
					int n2 = 0;
					int ans = n1^n2;
					res+=ans + '0'; 
				}
				res+=s2[i];	
				parts.push_back(res);
				cnt++;
				t++;		
			}
			
//			if(cnt == 8)
//			{
//				cout << i << endl;
//				cout << s2[i] << endl;
//				cout << res;
//				break;	
//			}		
		}
		
	}
	
	if(parts[parts.size() - 1][0] == '1')
	{
		string res = "";
		for(int j=1;j<s1.length();j++)
		{
			int n1 = parts[parts.size() - 1][j] - '0';
			int n2 = s1[j] - '0';
			int ans = n1^n2;
			res+=ans + '0'; 
		}
		parts.push_back(res);		
	}
	else
	{
		string res = "";
		for(int j=1;j<s1.length();j++)
		{
			int n1 = parts[parts.size() - 1][j] - '0';
			int n2 = 0;
			int ans = n1^n2;
			res+=ans + '0'; 
		}
		parts.push_back(res);		
	}
	
	string final_result = parts[parts.size() - 1];
	return final_result;
}


void sending(string data , string crc_gen)
{
	string new_data = data;
	int append = crc_gen.size() - 1;
	for(int i=1;i<=append;i++)
	{
		new_data+='0';	
	}	
	cout << "Data after appending 0's in it : " << new_data << endl;
	string crc = binary_dev(crc_gen,new_data);
	cout << "CRC obtained after dividing data with crc generator: " << crc << endl;
	data+=crc;	
	cout << "Codeword to be sent : " << data << endl << endl;
	receiving(crc_gen);
}

void receiving(string crc_gen)
{
	cout << "Receiving Side : " << endl;
	string data;
	cout << "Enter the data : ";
	cin >> data;
	cout << "Received Data : " << data << endl;
	cout << "Recieved Crc generator : " << crc_gen << endl;
	string check = binary_dev(crc_gen , data);
	cout << "The remainder after dividing data with crc generator : " << check << endl;
	int flag = 0;
	for(int i=0;i<check.length();i++)
	{
		if(check[i] == '1')
		{
			flag = 1;
			break;
		}
	}
	if(flag == 0)
	{
		cout << "There is no error in the data";
	}
	else
	{
		cout << "There is error in the data";
	}
}

int main()
{
	cout << "Sending Side : " << endl << endl;
	string data;
	string equation = "x4 + x1 + 1x0";
	cout << "Given equation is : " << equation << endl;
	cout << "Enter the data : ";
	cin >> data;
	cout << "Given data is : " << data << endl;
	string crc_gen = crc_generator(equation);
	cout << "Crc generator is : " << crc_gen << endl;
	sending(data,crc_gen);
}
