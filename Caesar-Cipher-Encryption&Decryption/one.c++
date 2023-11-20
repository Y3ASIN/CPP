#include <iostream>
using namespace std;
int main(){
    int key,cal1,cal2,number;
	string str;
	char plainText,cipherText;

	do {
		cout<<"\n\nCaeser Cipher Encryption & Decryption!"<<endl;
		cout<<"Enter 1 for encryption and 2 for decryption: ";
		cin>>number;

		switch (number) {
		case 1:
		cout<<"Enter plain text: ";
		cin>>str;
		cout<<"\nEnter key for cncryption: ";
		cin>>key;

		if(key>26){
			cal1=(key/26);
			cal2= 26*cal1;
			key=key-cal2;
		}
		transform(str.begin(), str.end(), str.begin(), ::toupper);

		for(int i=0;i<str.length();i++){
			int ch = int(str[i])+key-26;
			if(ch<65){
				ch=int(str[i])+key;
			}
			cipherText=char(ch);

			cout<<cipherText;
			
		}
		cout<<"\n\n You can enter 3 to execute the program."<<endl;
			break;


		case 2:
		cout<<"Enter cipher text: ";
		cin>>str;
		cout<<"\nEnter decryption key: ";
		cin>>key;

		transform(str.begin(), str.end(), str.begin(), ::toupper);

		for(int i=0;i<str.length();i++){
			int ch = int(str[i])-key+(26*(key/26));
			if(ch<65){
				ch=int(str[i])-key+(26*(key/26))+26;
			}
			plainText=char(ch);

			cout<<plainText;
			
		}
		cout<<"\n\n You can enter 3 to execute the program."<<endl;
			break;
		case 3:
		cout<<"\nExcellent! Isn't it!!\n"<<endl;
		break;	
		
		default:
		cout<<"It's not a valid input! Try again."<<endl;
			break;
		}
		} while(number!=3);
	
	return 0;

}