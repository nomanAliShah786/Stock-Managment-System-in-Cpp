#include <string>
using namespace std;
class Supplier{
	public:
		friend class Product;
		Supplier(int = 0,string = "N/A",string = "N/A",string = "N/A",string = "N/A");
		void setSupplierID(int);
		int getSupplierID();
		void setSupplierName( string );
		string getSupplierName();
		void setSupplierAddress( string );
		string getSupplierAddress();
		void setSupplierMail( string );
		string getSupplierMail();
		void setSupplierPhone( string );
		string getSupplierPhone();
	private:
		int supplierID;
		char supplierName[20];
		char supplierAddress[50];
		char supplierMail[40];
		char supplierPhone[15];
};
//default constructor for class Category ID
Supplier::Supplier(int supplierIDValue,string supplierNameString,string supplierAddressString,string supplierMailString,string supplierPhoneString){
	setSupplierID( supplierIDValue);
	setSupplierName( supplierNameString );
	setSupplierAddress( supplierAddressString );
	setSupplierMail( supplierMailString );
	setSupplierPhone( supplierPhoneString );
}
//functions of class Category ID
void Supplier::setSupplierID( int supplierIDValue ){
	supplierID = supplierIDValue;
}
int Supplier::getSupplierID(){
	return supplierID;
}
void Supplier::setSupplierName( string supplierNameString ){
	// copy at most 20 characters from string
	int length =  supplierNameString.size();
	if(length>=20){
		length = 19;
	}
	 supplierNameString.copy(supplierName,length);
	supplierName[length]='\0'; // append null character 
}
string Supplier::getSupplierName(){
	return supplierName;
}
void Supplier::setSupplierAddress( string supplierAddressString ){
	// copy at most 50 characters from string
	int length =  supplierAddressString.size();
	if(length>=50){
		length = 49;
	}
	supplierAddressString.copy(supplierAddress,length);
	supplierAddress[length]='\0'; // append null character 
}
string Supplier::getSupplierAddress(){
	return supplierAddress;
}
void Supplier::setSupplierMail( string supplierMailString ){
	// copy at most 20 characters from string
	int length =  supplierMailString.size();
	if(length>=40){
		length = 39;
	}
	supplierMailString.copy(supplierMail,length);
	supplierMail[length]='\0'; // append null character 
}
string Supplier::getSupplierMail(){
	return supplierMail;
}
void Supplier::setSupplierPhone( string supplierPhoneString ){
	// copy at most 15 characters from string
	int length =  supplierPhoneString.size();
	if(length>=15){
		length = 14;
	}
	 supplierPhoneString.copy(supplierPhone,length);
	supplierPhone[length]='\0'; // append null character 
}
string Supplier::getSupplierPhone(){
	return supplierPhone;
}
//end of functions of Class
