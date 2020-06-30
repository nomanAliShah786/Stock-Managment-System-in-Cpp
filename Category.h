#include <string>
using namespace std;
class Category{
	public:
		friend class Product;
		Category(int = 0,string = "");
		void setCategID(int);
		int getCategID();
		void setCategName( string );
		string getCategName();
	private:
		int categID;// Category ID
		char categName[20];// Category Name
};
//default constructor for class Category ID
Category::Category(int categIDValue,string categNameString){
	setCategID(categIDValue);
	setCategName(categNameString);
}
//functions of class Category ID
void Category::setCategID( int categIDValue ){
	categID = categIDValue;
}
int Category::getCategID(){
	return categID;
}
void Category::setCategName( string categNameString ){
	// copy at most 20 characters from string to categName
	int length = categNameString.size();
	if(length>=20){
		length = 19;
	}
	categNameString.copy(categName,length);
	categName[length]='\0'; // append null character to categName
}
string Category::getCategName(){
	return categName;
}
//end of functions of class Category ID
