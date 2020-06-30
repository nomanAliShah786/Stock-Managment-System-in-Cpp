#include <string>
using namespace std;
class Location{
	public:
		friend class Product;
		Location(int = 0,string = "N/A",int = 0,string = "N/A",int = 0);
		void setLocationID(int);
		int getLocationID();
		void setLocationName( string );
		string getLocationName();
		void setProductStoredID(int);
		int getProductStoredID();
		void setProductStoredCustomLabel( string );
		string getProductStoredCustomLabel();
		void setStoredQty(int);
		int getStoredQty();
	private:
		int locationID;// 
		char locationName[20];// 
		int productStoredID;// 
		char productStoredCustomLabel[10];// 
		int storedQty;
};
//default constructor for class Location ID
Location::Location(int locationIDValue,string locationNameString,int productStoredIDValue,string productStoredCustomLabelString,int storedQty){
	setLocationID(locationIDValue);
	setLocationName(locationNameString);
	setProductStoredID(productStoredIDValue);
	setProductStoredCustomLabel(productStoredCustomLabelString);
	setStoredQty(storedQty);
}
//functions of class Location ID
void Location::setLocationID( int locationIDValue ){
	locationID = locationIDValue;
}
int Location::getLocationID(){
	return locationID;
}
void Location::setLocationName( string locationNameString ){
	// copy at most 10 characters from string
	int length = locationNameString.size();
	if(length>=10){
		length = 9;
	}
	locationNameString.copy(locationName,length);
	locationName[length]='\0'; // append null character to LocationName
}
string Location::getLocationName(){
	return locationName;
}
void Location::setProductStoredID( int productStoredIDValue ){
	productStoredID = productStoredIDValue;
}
int Location::getProductStoredID(){
	return productStoredID;
}
void Location::setProductStoredCustomLabel( string productStoredCustomLabelString ){
	// copy at most 10 characters from string
	int length = productStoredCustomLabelString.size();
	if(length>=10){
		length = 9;
	}
	productStoredCustomLabelString.copy(productStoredCustomLabel,length);
	productStoredCustomLabel[length]='\0'; // append null character to LocationName
}
string Location::getProductStoredCustomLabel(){
	return productStoredCustomLabel;
}
void Location::setStoredQty( int storedQtyValue ){
	storedQty = storedQtyValue;
}
int Location::getStoredQty(){
	return storedQty;
}
//end of functions of class Location ID
