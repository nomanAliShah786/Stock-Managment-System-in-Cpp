#include <string>
using namespace std;
class Product{
	public:
		Product(int = 0,int = 0,string = "N/A",string = "N/A",string = "N/A",int = 0,int = 0,string = "N/A",int = 0,string = "",string = "N/A");
		void setProductID(int);
		int getProductID();
		
		void setProductCategID(int);
		int getProductCategID();
		
		void setProductTitle( string );
		string getProductTitle();
		
		void setProductCategName( string );
		string getProductCategName();
		
		void setProductCustomLabel( string );
		string getProductCustomLabel();
		
		void setProductQuantity(int);
		int getProductQuantity();
		
		void setProductSupplierID(int);
		int getProductSupplierID();
		
		void setProductSupplierName( string );
		string getProductSupplierName();
		
		void setProductLocationID(int);
		int getProductLocationID();
		
		void setProductLocationName( string );
		string getProductLocationName();
		
		void setProductSpecs( string );
		string getProductSpecs();
	private:
		int productID;//Product ID
		int productCategID;//Product Category ID 
		char productTitle[50];//Product Title
		char productCategName[20];//Product Category
		char productCustomLabel[10];//Product Custom Labe
		int productQuantity;//Product Quantity
		int productSupplierID;//Product Supplier ID
		char productSupplierName[20];//Product Supplier Name
		int productLocationID;//Product ID
		char productLocationName[10];//Porduct Location Name
		char productSpecs[500];//Product Specifications
		
};
//default constructor for class Category ID
Product::Product(int productIDValue,int productCategIDValue,string productTitleString,string productCategNameString,string productCustomLabelString,int productQuantityValue,int productSupplierIDValue,string productSupplierNameString,int productLocationIDValue,string productLocationNameString,string productSpecsString){
	setProductID(productIDValue);
	setProductCategID(productCategIDValue);
	setProductTitle(productTitleString);
	setProductCategName(productCategNameString);
	setProductCustomLabel(productCustomLabelString);
	setProductQuantity(productQuantityValue);
	setProductSupplierID(productSupplierIDValue);
	setProductSupplierName(productSupplierNameString);
	setProductLocationID(productLocationIDValue);
	string array = "N/A ";
	setProductLocationName(array);
	setProductSpecs(productSpecsString);
}
//functions of class Category ID
void Product::setProductID(int productIDValue){
	productID = productIDValue;
}
int Product::getProductID(){
	return productID;
}
void Product::setProductCategID(int productCategIDValue){
	productCategID = productCategIDValue;
}
int Product::getProductCategID(){
	return productCategID;
}
void Product::setProductTitle(string productTitleString){
	// copy at most 500 characters from string to categName
	int length = productTitleString.size();
	if(length>=500){
		length = 499;
	}
	productTitleString.copy(productTitle,length);
	productTitle[length]='\0'; // append null character to Product Title
}
string Product::getProductTitle(){
	return productTitle;
}

void Product::setProductCategName(string productCategNameString){
	int length = productCategNameString.size();
	if(length>=20){
		length = 19;
	}
	productCategNameString.copy(productCategName,length);
	productCategName[length]='\0';	
}
string Product::getProductCategName(){
	return productCategName;
}

void Product::setProductCustomLabel(string productCustomLabelString){
	// copy at most 10 characters from string to productCustomeLabel
	int length = productCustomLabelString.size();
	if(length>=10){
		length = 9;
	}
	productCustomLabelString.copy(productCustomLabel,length);
	productCustomLabel[length]='\0'; // append null character to Product Custome Label
}
string Product::getProductCustomLabel(){
	return productCustomLabel;
}

void Product::setProductQuantity(int productQuantityValue){
	productQuantity = productQuantityValue;
}
int Product::getProductQuantity(){
	return productQuantity;
}

void Product::setProductSupplierID(int productSupplierIDValue){
	productSupplierID = productSupplierIDValue;
}
int Product::getProductSupplierID(){
	return productSupplierID;
}

void Product::setProductSupplierName(string productSupplierNameString){
	int length = productSupplierNameString.size();
	if(length>=20){
		length = 19;
	}
	productSupplierNameString.copy(productSupplierName,length);
	productSupplierName[length]='\0';
}
string Product::getProductSupplierName(){
	return productSupplierName;
}
void Product::setProductLocationID(int productLocationIDValue){
	productLocationID = productLocationIDValue;
}
int Product::getProductLocationID(){
	return productLocationID;
}
void Product::setProductLocationName(string productLocationNameString){
	int length = productLocationNameString.size();
	if(length>=10){
		length = 9;
	}
	productLocationNameString.copy(productLocationName,length);
	productLocationName[length]='\0';
}
string Product::getProductLocationName(){
	return productLocationName;
}

void Product::setProductSpecs(string productSpecsString){
	int length = productSpecsString.size();
	if(length>=500){
		length = 499;
	}
	productSpecsString.copy(productSpecs,length);
	productSpecs[length]='\0';
}
string Product::getProductSpecs(){
	return productSpecs;
}
//end of functions of class Category ID
