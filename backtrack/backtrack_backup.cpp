#include <iostream>
#include <string>
using namespace std;
int solutions = 0 ;
bool isAssigned(string str,int counter,int lettermap[])
{
	if(counter >= str.length())
		return true;
	else
	{
		if(lettermap[ str[counter] - 'a'] == -1)		//letter maps to the number they denote
			return false;
		else
			return true;
	}
}

void initialise(int &a, int &b, char numbermap[],string str1, string str2, int counter,int lettermap[])
{
	bool s1 = isAssigned(str1,counter,lettermap);
	bool s2 = isAssigned(str2,counter,lettermap);

	int ai,bi;
	if(counter >= str1.length()-1 and !s1)
		ai = 1;
	else
		ai = 0;
	if(counter >= str2.length()-1 and !s2)
		bi = 1;
	else
		bi = 0;

	if(!s1 and !s2)		//none are assigned
	{
		for(int i=ai;i<10;i++)
		{
			if(numbermap[i] == '\0')
			{
				a = i;
				break;
			}
		}
		for(int i=bi;i<10;i++)
		{
			if(numbermap[i] == '\0' and i!=a)
			{
				b = i;
				break;
			}
		}
	}
	else if(s1 and !s2)	//s1 is assigned
	{
		a = 10;
		b = bi;
		while(b<10)
		{
			if(numbermap[b] == '\0')
				break;
			b++;
		}
	}
	else if(!s1 and s2)	//s2 is assigned
	{
		b = 10;
		a = ai;
		while(a<10)
		{
			if(numbermap[a] == '\0')
				break;
			a++;
		}
	}
	else 
		s1 = s2 = 10;
}

void assignValue(string str,int counter,int lettermap[],char numbermap[],int a)
{
	lettermap[ str[counter] - 'a' ] = a;
	numbermap[a] = str[counter];
}

int numberSum(string str1, string str2, int counter, int lettermap[],int carry, int& carryHere)
{
	int sum = 0,a1,a2;
	if(counter >= str1.length())
		a1 = 0;
	else
	{
		a1 = lettermap[ str1[counter] - 'a'];
	}
	if(counter >= str2.length())
		a2 = 0;
	else
	{
		a2 = lettermap[ str2[counter] - 'a'];
	}
	sum = (a1 + a2 + carry)%10;
	carryHere  = (a1+a2+carry)/10;
	return sum;
}

int valueOf(string str, int counter, int lettermap[])
{
	if(counter >= str.length())
		return 0;
	else
		{
			int k = lettermap[ str[counter] -'a'];
			return k;
		} 
}

void iterateValues(int &a, int &b, char numbermap[],bool k1, bool k2)
{
		if(a==10 and b==10)
			return;

		if(k1 and k2)		//none were assigned before
		{
			b++;
			while(b<10)
			{
				if(numbermap[b] == '\0' and b!=a)
					break;
				b++;
			}
			if(b>=10)
			{
				a++;
				while(a<10)
				{
					if(numbermap[a] == '\0')
						break;
					a++;
				}

				if(a!=10)
				{
					b = 0;
					while(true)
					{
						if(numbermap[b] == '\0' and a!=b)
							break;
						b++;
					}

				}
			}
		}
		else if(k1 and !k2)  		//k2 is assigned before
		{
			b = 10;
			a++;
			while(a<10)
			{
				if(numbermap[a] == '\0')
					break;
				a++;
			}
		}
		else if(!k1 and k2)			//k1 is assigned before
		{
			a = 10;
			b++;
			while(b<10)
			{
				if(numbermap[b] == '\0')
					break;
				b++;
			}
		}
		else
		{
			a = b = 10;
		}
}

void resetValues(bool &s1, bool &s2, bool &s3, string str1, string str2, string str3, int lettermap[], char numbermap[], int &a, int &b, int counter)
{
	bool k1,k2;
	k1 = s1;
	k2 = s2;

	if(s1 and s2)		//both were unassigned
	{
		if(b==9)
		{
			numbermap[ lettermap[ str1[counter] -'a' ] ] = '\0';			//modify str1
			lettermap[str1[counter] - 'a'] = -1;
			s1 = false;
		}

		numbermap[ lettermap[ str2[counter] - 'a' ] ] = '\0';				//str2
		lettermap[str2[counter]-'a'] = -1;
		s2 = false;
	}
	else if(s1 and !s2)				//str2 is already defined
	{
		numbermap[ lettermap[ str1[counter] -'a' ] ] = '\0';
		lettermap[str1[counter] - 'a'] = -1;
		s1 = false;
	}
	else if(!s1 and s2)				//str1 is given a value
	{
		numbermap[ lettermap[ str2[counter] - 'a' ] ] = '\0';
		lettermap[str2[counter]-'a'] = -1;
		s2 = false;
	}
	if(s3)
	{
		numbermap[ lettermap[ str3[counter] - 'a' ] ] = '\0';
		lettermap[str3[counter]-'a'] = -1;
		s3 = false;
	}
	iterateValues(a,b,numbermap,k1,k2);
}

bool isTaken(int num, char numbermap[])
{
	num%=10;
	if(numbermap[num] == '\0')
		return false;
	else
		return true;
}

void reverse(string &s)
{
	int n = s.length();
	char c;

	for(int i = 0;i<n/2;i++)
	{
		c = s[i];
		s[i] = s[n-i-1];
		s[n-i-1] = c;
	}
}

void printArray(int lettermap[],char numbermap[],string str1,string str2,string str3)
{
	cout<<"Solution: ";
	string t[3] = {str1,str2,str3};
	int len[3];

	for (int i = 0; i < 3; ++i)
	{
		reverse(t[i]);
		len[i] = t[i].length();
	}


	for(int i = 0 ; i<len[0];i++)
		cout<<lettermap[ t[0][i] - 'a' ];
	cout<<" + ";
	for(int i = 0 ; i<len[1];i++)
		cout<<lettermap[ t[1][i] - 'a'];
	cout<<" = ";
	for(int i=0;i<len[2];i++)
		cout<<lettermap[ t[2][i] - 'a'];
	cout<<endl;
}
void backtrack(string str1, string str2, string str3, int counter, int lettermap[], char numbermap[], int carry = 0)
{
	int a = 0, b = 0;
	bool s2,s3;
	bool s1 = s2 = s3 = false;
	int carryHere = 0;
	bool temps1 = false,temps2 = false;

	if(counter == str3.length() and carry == 0)	//end case
	{
		printArray(lettermap,numbermap,str1,str2,str3);
		::solutions++;
	}
	else if(counter == str3.length() and carry == 1)
	{
		return;
	}

	else								//not the end case
	{
		initialise(a,b,numbermap,str1,str2,counter,lettermap);

		while(true)
		{
			if(a>=10 and b>=10)
			{
					resetValues(s1,s2,s3,str1,str2,str3,lettermap,numbermap,a,b,counter);
					return;
			}

			if(!isAssigned(str1,counter,lettermap))
			{
				assignValue(str1,counter,lettermap,numbermap,a);
				s1 = true;
				temps1 = s1;
			}

			if(!isAssigned(str2,counter,lettermap))
			{
				assignValue(str2,counter,lettermap,numbermap,b);
				s2 = true;
				temps2 = s2;
			}

			if(isAssigned(str3,counter,lettermap))	//if str3 is assigned
			{
				
				if(valueOf(str3,counter,lettermap)==0 and counter == (str3.length()-1))
				{
					resetValues(s1,s2,s3,str1,str2,str3,lettermap,numbermap,a,b,counter);
					return;
				}

				if(numberSum(str1,str2,counter,lettermap,carry,carryHere)==valueOf(str3,counter,lettermap))		//exact match
				{
						backtrack(str1,str2,str3,counter+1,lettermap,numbermap,carryHere);
						resetValues(s1,s2,s3,str1,str2,str3,lettermap,numbermap,a,b,counter);
						if(!temps1 and !temps2)
							return;	
				}
				else
				{
					resetValues(s1,s2,s3,str1,str2,str3,lettermap,numbermap,a,b,counter);
					if(!temps1 and !temps2)
						return;	
				}
			}	
			else	//if str3 isnt assigned
			{
				if( !isTaken(numberSum(str1,str2,counter,lettermap,carry,carryHere) , numbermap ))	//if the sum is NOT given to some other letter
				{
					assignValue(str3,counter,lettermap,numbermap,numberSum(str1,str2,counter,lettermap,carry,carryHere));
					s3 = true;


					if(valueOf(str3,counter,lettermap)==0 and counter == (str3.length()-1))
					{
						resetValues(s1,s2,s3,str1,str2,str3,lettermap,numbermap,a,b,counter);
						return;
					}

					backtrack(str1,str2,str3,counter+1,lettermap,numbermap,carryHere);	
					resetValues(s1,s2,s3,str1,str2,str3,lettermap,numbermap,a,b,counter);
					if(!temps1 and !temps2)
						return;					//change this later
				}
				else
				{
					resetValues(s1,s2,s3,str1,str2,str3,lettermap,numbermap,a,b,counter);
					if(!temps1 and !temps2)
						return;
				}
			}
		}
		
	}
}

int main()
{
	string str1,str2,str3;

	int lettermap[26];
	for(int i=0;i<26;i++)
		lettermap[i] = -1;

	char numbermap[10];
	for(int i=0;i<10;i++)
		numbermap[i] = '\0';

	cin>>str1>>str2>>str3;
	reverse(str1);
	reverse(str2);
	reverse(str3);
	backtrack(str1,str2,str3,0,lettermap,numbermap);
	cout<<"Total number of solutions - "<<::solutions<<endl;
}