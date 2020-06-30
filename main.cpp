#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <cstring>
#include <string>
#include <fstream>
#include "Category.h"
#include "Product.h"
#include "Supplier.h"
#include "Location.h"
using namespace std;
void emptyRecords();
int mainMenu();
void goodsReceived(fstream &productFile);
void createPickList(fstream &productFile);
void dispLowStock(fstream &productFile);
void addProduct(fstream &productFile);
void delProduct(fstream &productFile);
void updateProduct(fstream &productFile);
void addSupplier();
void updateSupplier();
void dispStock(fstream &productFile);
void dispSupplier();
void dispLocations();
int getProduct();
int getCategory();
int getSupplier();
int getLocation();
void getNewLocation(Product &productRec);
int findCategory(string categName);
int findLocation(string locationName);
int findSupplier(string supplierName);
string removeSpaces(string productCustomLabelString);
void updateLocationQuantity(Product &productRec,int qty);
void outPutProductLine(Product &productRec);
void outPutLocationLine(Location &locationRec);
void outPutProductDetail(Product &productRec);
void outPutSupplierDetail(Supplier &supplierRec);
int main(){
	emptyRecords();
	fstream inOutProduct("productData.dat",ios::in|ios::out|ios::binary);
	if(!(inOutProduct)){
		cout<<"File could not be created/ opened!!!"<<endl;
		return 0;
	}
	for(;true;){
		int op;
		system("cls");
		op = mainMenu();
		switch (op){
			case 1:
				goodsReceived(inOutProduct);
			break;
			case 2:
				createPickList(inOutProduct);
			break;
			case 3:
				dispLowStock(inOutProduct);
			break;
			case 4:
				addProduct(inOutProduct);
			break;
			case 5:
				delProduct(inOutProduct);
			break;
			case 6:
				updateProduct(inOutProduct);
			break;
			case 7:
				addSupplier();
			break;
			case 8:
				updateSupplier();
			break;
			case 9:
				dispStock(inOutProduct);
			break;
			case 10:
				dispSupplier();
			break;
			case 11:
				dispLocations();
			break;
			case 0:
				return 0;
			break;
			default:
				cout<<"Error: Ivalid Input(please enter a number between 0 - 11 )"<<endl;
				system("pause");	
			break;
		}
	}
	inOutProduct.close();
	return 0;
}
int mainMenu(){
	int value;
	char choice[8];
	cout<<"\t========================================================"<<endl;
	cout<<"\t\t\tSTOCK MANAGMENT SYSTEM"<<endl;
  	cout<<"\t====================> MAIN MENU <======================="<<endl;
	cout<<"\t========================================================"<<endl;
	cout<<"\t\t1\tAdd Goods Received\n\n";
	cout<<"\t\t2\tCreate Pick List\n\n";
	cout<<"\t\t3\tDisplay Low Stock/ Out of Stock Products\n\n";
	cout<<"\t\t4\tAdd New Product\n\n";
	cout<<"\t\t5\tDelete Product\n\n";
	cout<<"\t\t6\tUpdate Product Info\n\n";
	cout<<"\t\t7\tAdd New Supplier\n\n";
	cout<<"\t\t8\tUpdate Supplier info\n\n";
	cout<<"\t\t9\tDisplay All Stock\n\n";
	cout<<"\t\t10\tDisplay All Suppliers\n\n";
	cout<<"\t\t11\tDisplay All Locations\n\n";
	cout<<"\t\t0\tExit\n";
	cout<<"\t========================================================"<<endl;
	cout<<"\tEnter your choice: ";
	cin>>choice;
	if((choice[0] >= '0' && choice[0] <= '9')&&(choice[1]=='\0'||(choice[1] >= '0' &&choice[1] <= '1'))) {
	      value = atoi(choice);
	      return value;
	} else{
		return 12;
	}
}
void goodsReceived(fstream &productFile){
	system("cls");
	char choice;
	cout<<"\t========================================================"<<endl;
  	cout<<"\t===============> GOODS RECEIVED MENU <=================="<<endl;
	cout<<"\t========================================================"<<endl;
	cout<<"\t\t1\tAdd Items Received by Product ID (UPC)\n\n";
	cout<<"\t\t2\tAdd Items Received by Custom Label \n\n";
	cout<<"\t\t0\tGo back to Main Menu \n\n";
	cout<<"\t========================================================"<<endl;
	cout<<"\tEnter your choice:";
	cin>>choice;
	 if(choice=='1'){
	 	int num = 1;
		for(;true;){
			cout<<"------------------------------------------------"<<endl;
			cout<<"Received Product No "<<num<<" :"<<endl;
			char ans;
			int qty;
			string cLabel;
			int ID = getProduct();
			productFile.seekg(0);
			productFile.seekg((ID-1)*sizeof(Product));
			Product productRec;
			productFile.read( reinterpret_cast< char * >( &productRec ),sizeof( Product ) );
			if(productRec.getProductID()!=0){
				cerr<<setw(20)<<"Custom Label of Product ID ( "<< productRec.getProductID() <<" ) : "<<productRec.getProductCustomLabel()<<endl;
				cerr<<setw(20)<<"Title of Product ID ( "<<productRec.getProductID()<<" ) : "<<productRec.getProductTitle()<<endl;
				cin.ignore();
				cout<<"Enter Quantity: ";
				//Input Quantity
				cin>>qty;
				qty = qty + productRec.getProductQuantity();
				productRec.setProductQuantity(qty);
				updateLocationQuantity(productRec,qty);
				//
				productFile.seekp(0);
				productFile.seekp((ID-1)*sizeof(Product));
				productFile.write( reinterpret_cast< char * >( &productRec ),sizeof( Product ) );
				
			}else{
				cout<<"Error: Product ID ("<<ID<<") not found."<<endl;
				cout<<"You can add a new product ID from \"Add New Product\" in Main Menu "<<endl;
			}
			cout<<"Do you want to add another product? (y for yes or any character for No): ";
			cin>>ans;
			if(!(ans=='y'||ans=='Y')){
				return;
			}
			num++;
		}
	 }else if(choice=='2'){
	 	int num = 1;
	 	for(;true;){
		 	cin.ignore();
		 	cout<<"------------------------------------------------"<<endl;
			cout<<"Received Product No "<<num<<" :"<<endl;
			char ans;
			int qty;
			string cLabel;
			int ID;
			bool nfound = true;
			cout<<"Enter Custom Label (e.g S6/D): ";
			getline(cin,cLabel);
			Product productRec;
			productFile.seekg(0);
			while(productFile.read( reinterpret_cast< char * >( &productRec ),sizeof( Product ) )){
				if(productRec.getProductID()!=0){
					if(productRec.getProductCustomLabel()==cLabel){
						ID = productRec.getProductID();
						cerr<<setw(20)<<"Custom Label of Product ID ( "<< productRec.getProductID() <<" ) : "<<productRec.getProductCustomLabel()<<endl;
						cerr<<setw(20)<<"Title of Product ID ( "<<productRec.getProductID()<<" ) : "<<productRec.getProductTitle()<<endl;
						cout<<"Enter Quantity :";
						cin>>qty;
						qty  = qty + productRec.getProductQuantity();
						productRec.setProductQuantity(qty);
						updateLocationQuantity(productRec,qty);
						productFile.seekp(0);
						productFile.seekp((ID-1)*sizeof(Product));
						productFile.write( reinterpret_cast< char * >( &productRec ),sizeof( Product ) );
						nfound = false;
						break;
					}
				}
			}
			if(nfound){
				cout<<"Error: Product with custom Label ("<<cLabel<<") not found."<<endl;
				cout<<"You can add a new product ID from \"Add New Product\" in Main Menu "<<endl;
			}
			cout<<"Do you want to add another product? (y for yes or any character for No): ";
			cin>>ans;
			if(!(ans=='y'||ans=='Y')){
				return;
			}
			num++;
		}
		productFile.clear();
	 }else if(choice=='0'){
	 	return;
	 }else{
	 	cout<<"Error: Ivalid Input(please enter a number 1 or 2 )"<<endl;
		system("pause");
	 }
}

void createPickList(fstream &productFile){
	char choice;
	for(;true;){
		system("cls");
		cout<<"\t========================================================"<<endl;
  		cout<<"\t===============> CREATE PICK LIST MENU <================"<<endl;
		cout<<"\t========================================================"<<endl;
		cout<<"\t\t1\tCreate Pick List by Product ID (UPC)\n\n";
		cout<<"\t\t2\tCreate Pick List by Custom Label \n\n";
		cout<<"\t\t0\tGo back to Main Menu \n\n";
		cout<<"\t========================================================"<<endl;
		cout<<"\tEnter your choice:";
		cin>>choice;
		if(choice=='1'||choice=='2'||choice=='0'){
			break;
		}else{
			cout<<"Error: Wrong Input Entered!!!"<<endl;
			cout<<"(Enter a number between 0-2)";
			system("pause");
		}
	}
	 if(choice=='1'){
	 	Product pickList[500];
	 	int num = 0;
		for(;true;){
			cout<<"------------------------------------------------------------------"<<endl;
			cout<<"List's Product No "<<num+1<<" :"<<endl;
			char ans;
			int qty;
			int qtyF;
			string cLabel;
			int ID = getProduct();
			productFile.seekg(0);
			productFile.seekg((ID-1)*sizeof(Product));
			Product productRec;
			productFile.read( reinterpret_cast< char * >( &productRec ),sizeof( Product ) );
			if(productRec.getProductID()!=0){
				cerr<<setw(20)<<"Custom Label of Product ID ( "<< productRec.getProductID() <<" ) : "<<productRec.getProductCustomLabel()<<endl;
				cerr<<setw(20)<<"Title of Product ID ( "<<productRec.getProductID()<<" ) : "<<productRec.getProductTitle()<<endl;
				cout<<"Avliable quantity: "<<productRec.getProductQuantity()<<endl;	
				pickList[num] = productRec;	
				do{
					cout<<"Enter Quantity: ";
					//Input Quantity
					cin>>qty;
					qtyF =  productRec.getProductQuantity() - qty;
					if(qtyF<0){
						cout<<"Error: Not enough stock!!!"<<endl;
						system("pause");
					}
				}while(qty<0);
				pickList[num].setProductQuantity(qty);
				cout<<"Remaining quantity will be: "<<qtyF<<endl;
				productRec.setProductQuantity(qtyF);
				updateLocationQuantity(productRec,qtyF);
				//
				productFile.seekp(0);
				productFile.seekp((ID-1)*sizeof(Product));
				productFile.write( reinterpret_cast< char * >( &productRec ),sizeof( Product ) );
				
			}else{
				cout<<"Error: Product ID ("<<ID<<") not found."<<endl;
				cout<<"You can add a new product from \"Add New Product\" in Main Menu "<<endl;
			}
			cout<<"Do you want to enter another product? (y for yes or any character for No): ";
			cin>>ans;
			if(!(ans=='y'||ans=='Y')){
				break;
			}
			num++;
		}
		 int pCount  =  1;
		 cout<<"\n\n====================================================================================================================="<<endl<<endl;
		 cout<<"---------------------------------------------Created Pick List-------------------------------------------------------"<<endl<<endl;
   		 cout<<endl<<"---------------------------------------------------------------------------------------------------------------------"<<endl;
		 cerr<<left<<setw(14)<<"|Product No";cerr<<setw(10)<<"|ProductID";cerr <<setw(50)<<"|Product Title"; cerr <<setw(20)<<"|CustomLabel"; cerr <<setw(10)<<"|Quantity"; cerr <<setw(12)<<"|Location   ";cerr<<'|'; cerr <<endl;
		 cout<<"---------------------------------------------------------------------------------------------------------------------"<<endl;
			
		 for(int count=0;count<=num;count++){
		 	if(pickList[count].getProductCategID()!=0){
		 		cerr<<'|';cerr<<left<<setw(13)<<pCount;
				outPutProductLine(pickList[count]);
				pCount++;
		 	}
		 }
		 cout<<"---------------------------------------------------------------------------------------------------------------------"<<endl<<endl;	
		 char ans;
		 cout<<"Do you want to create printable file of pick list? (y for yes or any charcter for no)";
		 cin>>ans;
		 if(ans=='y'||ans=='Y'){
		 	fstream printFile("pickList.txt",ios::out);
		 	if(!printFile){
		 		cout<<"Error: File could not be created!!!"<<endl;
		 		system("pause");
		 		return;
		 	}
		 	 int pCount  =  1;
			 printFile<<"\n\n====================================================================================================================="<<endl<<endl;
			 printFile<<"---------------------------------------------Created Pick List-------------------------------------------------------"<<endl<<endl;
			 printFile<<endl<<"---------------------------------------------------------------------------------------------------------------------"<<endl;
			 printFile<<left<<setw(14)<<"|Product No";printFile<<setw(10)<<"|ProductID";printFile <<setw(50)<<"|Product Title"; printFile <<setw(20)<<"|CustomLabel"; printFile <<setw(10)<<"|Quantity"; printFile <<setw(12)<<"|Location   ";printFile<<'|'; printFile <<endl;
			 printFile<<"---------------------------------------------------------------------------------------------------------------------"<<endl;
				
			 for(int count=0;count<=num;count++){
			 	if(pickList[count].getProductCategID()!=0){
			 		printFile<<'|';printFile<<left<<setw(13)<<pCount;printFile<<'|';printFile << left << setw( 9 ) << pickList[count].getProductID();printFile<<'|'; printFile << setw( 49 );printFile << pickList[count].getProductTitle();printFile<<'|'; printFile << setw( 19 ); printFile << pickList[count].getProductCustomLabel();printFile<<'|'; printFile << setw( 9 ); printFile << pickList[count].getProductQuantity();printFile<<'|'; printFile << setw( 11 ); printFile << pickList[count].getProductLocationName(); printFile << '|'; printFile << endl;
					pCount++;
			 	}
			 }
			 printFile<<"---------------------------------------------------------------------------------------------------------------------"<<endl<<endl;	
			 cout<<"A printable file with the name \"pickList.txt\" has been created in the same folder."<<endl;
		 }
	 }else if(choice=='2'){
	 	int num = 0;
	 	Product pickList[500];
	 	for(;true;){
		 	cin.ignore();
		 	cout<<"------------------------------------------------"<<endl;
			cout<<"List's Product No "<<num+1<<" :"<<endl;
			char ans;
			int qty;
			int qtyF;
			string cLabel;
			int ID;
			bool nfound = true;
			cout<<"Enter Custom Label (e.g S6/D): ";
			getline(cin,cLabel);
			Product productRec;
			productFile.seekg(0);
			while(productFile.read( reinterpret_cast< char * >( &productRec ),sizeof( Product ) )){
				if(productRec.getProductID()!=0){
					if(productRec.getProductCustomLabel()==cLabel){
						ID = productRec.getProductID();
						cerr<<setw(20)<<"Custom Label of Product ID ( "<< productRec.getProductID() <<" ) : "<<productRec.getProductCustomLabel()<<endl;
						cerr<<setw(20)<<"Title of Product ID ( "<<productRec.getProductID()<<" ) : "<<productRec.getProductTitle()<<endl;
						cout<<"Avliable quantity: "<<productRec.getProductQuantity()<<endl;	
						pickList[num] = productRec;	
						do{
							cout<<"Enter Quantity: ";
							//Input Quantity
							cin>>qty;
							qtyF =  productRec.getProductQuantity() - qty;
							if(qtyF<0){
								cout<<"Error: Not enough stock!!!"<<endl;
								system("pause");
							}
						}while(qty<0);
						pickList[num].setProductQuantity(qty);
						cout<<"Remaining quantity will be: "<<qtyF<<endl;
						productRec.setProductQuantity(qtyF);
						updateLocationQuantity(productRec,qtyF);
						productFile.seekp(0);
						productFile.seekp((ID-1)*sizeof(Product));
						productFile.write( reinterpret_cast< char * >( &productRec ),sizeof( Product ) );
						nfound = false;
						break;
					}
				}
			}
			if(nfound){
				cout<<"Error: Product with custom Label ("<<cLabel<<") not found."<<endl;
				cout<<"You can add a new product from \"Add New Product\" in Main Menu "<<endl;
			}
			cout<<"Do you want to enter another product? (y for yes or any character for No): ";
			cin>>ans;
			if(!(ans=='y'||ans=='Y')){
				break;
			}
			num++;
		}
		int pCount  =  1;
		 cout<<"\n\n====================================================================================================================="<<endl<<endl;
		 cout<<"---------------------------------------------Created Pick List-------------------------------------------------------"<<endl<<endl;
   		 cout<<endl<<"---------------------------------------------------------------------------------------------------------------------"<<endl;
		 cerr<<left<<setw(14)<<"|Product No";cerr<<setw(10)<<"|ProductID";cerr <<setw(50)<<"|Product Title"; cerr <<setw(20)<<"|CustomLabel"; cerr <<setw(10)<<"|Quantity"; cerr <<setw(12)<<"|Location   ";cerr<<'|'; cerr <<endl;
		 cout<<"---------------------------------------------------------------------------------------------------------------------"<<endl;
			
		 for(int count=0;count<=num;count++){
		 	if(pickList[count].getProductCategID()!=0){
		 		cerr<<'|';cerr<<left<<setw(13)<<pCount;
				outPutProductLine(pickList[count]);
				pCount++;
		 	}
		 }
		 cout<<"---------------------------------------------------------------------------------------------------------------------"<<endl<<endl;	
		 char ans;
		 cout<<"Do you want to create printable file of pick list? (y for yes or any charcter for no)";
		 cin>>ans;
		 if(ans=='y'||ans=='Y'){
		 	fstream printFile("pickList.txt",ios::out);
		 	if(!printFile){
		 		cout<<"Error: File could not be created!!!"<<endl;
		 		system("pause");
		 		return;
		 	}
		 	 int pCount  =  1;
			 printFile<<"\n\n====================================================================================================================="<<endl<<endl;
			 printFile<<"---------------------------------------------Created Pick List-------------------------------------------------------"<<endl<<endl;
			 printFile<<endl<<"---------------------------------------------------------------------------------------------------------------------"<<endl;
			 printFile<<left<<setw(14)<<"|Product No";printFile<<setw(10)<<"|ProductID";printFile <<setw(50)<<"|Product Title"; printFile <<setw(20)<<"|CustomLabel"; printFile <<setw(10)<<"|Quantity"; printFile <<setw(12)<<"|Location   ";printFile<<'|'; printFile <<endl;
			 printFile<<"---------------------------------------------------------------------------------------------------------------------"<<endl;
				
			 for(int count=0;count<=num;count++){
			 	if(pickList[count].getProductCategID()!=0){
			 		printFile<<'|';printFile<<left<<setw(13)<<pCount;printFile<<'|';printFile << left << setw( 9 ) << pickList[count].getProductID();printFile<<'|'; printFile << setw( 49 );printFile << pickList[count].getProductTitle();printFile<<'|'; printFile << setw( 19 ); printFile << pickList[count].getProductCustomLabel();printFile<<'|'; printFile << setw( 9 ); printFile << pickList[count].getProductQuantity();printFile<<'|'; printFile << setw( 11 ); printFile << pickList[count].getProductLocationName(); printFile << '|'; printFile << endl;
					pCount++;
			 	}
			 }
			 printFile<<"---------------------------------------------------------------------------------------------------------------------"<<endl<<endl;	
			 cout<<"A printable file with the name \"pickList.txt\" has been created in the same folder."<<endl;
		 }
		productFile.clear();
	 }else if(choice=='0'){
	 	return;
	 }else{
	 	cout<<"Error: Ivalid Input(please enter a number 1 or 2 )"<<endl;
	 }
	system("pause");
}
void dispLowStock(fstream &productFile){
	bool nOFound = true;
	bool nLFound = true;
	Product productRec;
	Product productRec2;
	productFile.seekg(0);
	system("cls");
	cout<<"\n\n===================================================================================================="<<endl<<endl;
	cout<<"-----------------------------------------Out Of Stock Items-----------------------------------------"<<endl<<endl;
	cerr<<left<<setw(10)<<"ProductID";cerr <<setw(50)<<"Product Title"; cerr <<setw(20)<<"CustomLabel"; cerr <<setw(10)<<"Quantity"; cerr <<setw(12)<<"Location"; cerr <<endl;
	while(productFile.read( reinterpret_cast< char * >( &productRec ),sizeof( Product ) )){
			if(productRec.getProductID()!=0){
				if(productRec.getProductQuantity()==0){
					outPutProductLine(productRec);
					nOFound = false;
				}
			}
	}
	if(nOFound){
		cout<<"No out of Stock Product found"<<endl;
	}
	productFile.clear();
	productFile.seekg(0);
	cout<<"-----------------------------------------Low Stock Items--------------------------------------------"<<endl<<endl;
	cerr<<left<<setw(10)<<"ProductID";cerr <<setw(50)<<"Product Title"; cerr <<setw(20)<<"CustomLabel"; cerr <<setw(10)<<"Quantity"; cerr <<setw(12)<<"Location"; cerr <<endl;
	while(productFile.read( reinterpret_cast< char * >( &productRec2 ),sizeof( Product ) )){
			if(productRec2.getProductID()!=0){
				if(productRec2.getProductQuantity()>0&&productRec2.getProductQuantity()<=5){
					outPutProductLine(productRec2);
					nLFound = false;
				}
			}
	}
	if(nLFound){
		cout<<"No Low Stock Product found"<<endl;
	}
	cout<<"\n===================================================================================================="<<endl<<endl;
	productFile.clear();
	system("pause");
}
void addProduct(fstream &productFile){	
	for(;true;){
		system("cls");
		cout<<"========================================================"<<endl;
  		cout<<"\t   ========> Add New Product <======="<<endl;
		cout<<"========================================================"<<endl;
		char ans;
		bool noCateg = false;
		int categID;
		string categ;
		string title;
		string cLabel;
		int supplierID;
		string supplier;
		string specs;
		int ID = getProduct();
		productFile.seekg((ID-1)*sizeof(Product));
		Product productRec;
		productFile.read( reinterpret_cast< char * >( &productRec ),sizeof( Product ) );
		if(productRec.getProductID()==0){
			cin.ignore();
			cout<<"Enter Product Title: ";
			getline(cin,title);
			for(;true;){
				cout<<"Enter Product Category: ";
				getline(cin,categ);
				categID = findCategory(categ);
				if(categID!=0){
					break;
				}else{
					cout<<"Category not found!!!"<<endl;
					cout<<"Do you want to create new Category? (y for yes or any character for No): ";
					cin>>ans;
					Category categRec;
					fstream categFile("categData.dat",ios::in|ios::out|ios::binary);
					if(!categFile){
						cout<<"File \"categData.dat\" could not be created"<<endl;
						system("pause");
						continue;
					}
					if(ans=='y'||ans=='Y'){
						for(;true;){
							categID = getCategory();
							categFile.seekg(0);
							categFile.seekg((categID-1)*sizeof(Category));
							categFile.read( reinterpret_cast< char * >( &categRec ),sizeof( Category ) );
							if(categRec.getCategID()==0){
								cin.ignore();
								cout<<"Enter Category Name: ";
								getline(cin,categ);
								categRec.setCategID(categID);
								categRec.setCategName(categ);
								categFile.seekp(0);
								categFile.seekp((categID-1)*sizeof(Category));
								categFile.write( reinterpret_cast< char * >( &categRec ),sizeof( Category ) );
								cout<<"New Category is saved successfully to \"categData.dat\"."<<endl;
								break;
								break;
							}else{
								cout<<"Error: Category ID("<<categID<<") already has data."<<endl;
								cout<<"Do you want to add another new category to this product? (y for yes or any character for No): ";
								cin>>ans;
								if(!(ans=='y'||ans=='Y')){
									noCateg = true;
									cin.ignore();
									break;
								}
							}
						}
						if(noCateg){
							continue;
						}
						break;
					}else{
						cin.ignore();
					}
				categFile.clear();
				categFile.close();	
				}
			}
			cout<<"Enter Custom Label without space (e.g S6/D): ";
			getline(cin,cLabel);
			cLabel = removeSpaces(cLabel);
			cout<<"You can not Add Quantity here (Quantity is 0 by default)."<<endl;
			for(;true;){
				cout<<"Enter Supplier Name: ";
				getline(cin,supplier);
				supplierID = findSupplier(supplier);
				if(supplierID!=0){
					break;
				}else{
					cout<<"Supplier not found!!!"<<endl;
					cout<<"You can add a new supplier from \"Add New Supplier\" in Main Menu.";
					cout<<"\n===================================================================================================="<<endl<<endl;
					cout<<"Do you want to go back to Main menu? (y for yes or any charcter for no)(keep in mind this product will not be added to data)";
					cin>>ans;
					if(ans=='y'||ans=='Y'){
						return;
					}
					cin.ignore();
				}
			}
			
			cout<<"Enter Product Specifications: "<<endl;
			getline(cin,specs);
			//
			productRec.setProductID(ID);
			productRec.setProductTitle(title);
			productRec.setProductCategID(categID);
			productRec.setProductCategName(categ);
			productRec.setProductCustomLabel(cLabel);
			productRec.setProductSupplierID(supplierID);
			productRec.setProductSupplierName(supplier);
			productRec.setProductSpecs(specs);
			getNewLocation(productRec);
			//
			productFile.seekp((ID-1)*sizeof(Product));
			productFile.write( reinterpret_cast< char * >( &productRec ),sizeof( Product ) );
			
		}else{
			cout<<"Product ID ("<<ID<<") Already has data."<<endl;
		}
		cout<<"Do you want to add another product? (y for yes or any character for No): ";
		cin>>ans;
		if(!(ans=='y'||ans=='Y')){
			break;
		}
	}
}
void delProduct(fstream &productFile){
	char choice;
	for(;true;){
		system("cls");
		cout<<"\t========================================================"<<endl;
	  	cout<<"\t===============> DELETE PRODUCT MENU <=================="<<endl;
		cout<<"\t========================================================"<<endl;
		cout<<"\t\t1\tDelete Product by Product ID (UPC)\n\n";
		cout<<"\t\t2\tDelete Product by Custom Label \n\n";
		cout<<"\t\t0\tGo back to Main Menu \n\n";
		cout<<"\t========================================================"<<endl;
		cout<<"\tEnter your choice: ";
		cin>>choice;
		if(choice=='1'||choice=='2'||choice=='0'){
			break;
		}else{
			cout<<"Error: Wrong Input Entered!!!"<<endl;
			cout<<"(Enter a number between 0-2)";
		}
	}
	 if(choice=='1'){
	 	int num = 1;
		for(;true;){
			cout<<"------------------------------------------------"<<endl;
			char ans;
			char sAns;
			string cLabel;
			int ID = getProduct();
			productFile.seekg(0);
			productFile.seekg((ID-1)*sizeof(Product));
			Product productRec;
			Product emptyRec;
			productFile.read( reinterpret_cast< char * >( &productRec ),sizeof( Product ) );
			if(productRec.getProductID()!=0){
				cout<<"\n===================================================================================================="<<endl<<endl;
				cout<<"Found Product:"<<endl;
				cerr<<left<<setw(10)<<"ProductID";cerr <<setw(50)<<"Product Title"; cerr <<setw(20)<<"CustomLabel"; cerr <<setw(10)<<"Quantity"; cerr <<setw(12)<<"Location"; cerr <<endl;
				outPutProductLine(productRec);
				cout<<"\n===================================================================================================="<<endl<<endl;
				cin.ignore();
				cout<<"Are you sure you want to delete above product? (y for yes or any charcter for no): ";
				cin>>sAns;
				if(sAns=='y'||sAns=='Y'){
					productFile.seekp(0);
					productFile.seekp((ID-1)*sizeof(Product));
					productFile.write( reinterpret_cast< char * >( &emptyRec ),sizeof( Product ) );
					cout<<"Product deleted sucessfully."<<endl;
				}else{
					cout<<"Product will not be deleted."<<endl;
				}
				//
				
			}else{
				cout<<"Error: Product ID ("<<ID<<") not found."<<endl;
			}
			cout<<"Do you want to delete another product? (y for yes or any character for No): ";
			cin>>ans;
			if(!(ans=='y'||ans=='Y')){
				return;
			}
			num++;
		}
	 productFile.clear();
	 }else if(choice=='2'){
	 	int num = 1;
	 	for(;true;){
		 	cin.ignore();
		 	cout<<"------------------------------------------------"<<endl;
			char ans;
			char sAns;
			int qty;
			string cLabel;
			int ID;
			bool nfound = true;
			cout<<"Enter Custom Label (e.g S6/D): ";
			getline(cin,cLabel);
			Product productRec;
			Product emptyRec;
			productFile.seekg(0);
			while(productFile.read( reinterpret_cast< char * >( &productRec ),sizeof( Product ) )){
				if(productRec.getProductID()!=0){
					if(productRec.getProductCustomLabel()==cLabel){
						ID = productRec.getProductID();
						cout<<"\n===================================================================================================="<<endl<<endl;
						cout<<"Found Product:"<<endl;
						cerr<<left<<setw(10)<<"ProductID";cerr <<setw(50)<<"Product Title"; cerr <<setw(20)<<"CustomLabel"; cerr <<setw(10)<<"Quantity"; cerr <<setw(12)<<"Location"; cerr <<endl;
						outPutProductLine(productRec);
						cout<<"\n===================================================================================================="<<endl<<endl;
						cout<<"Are you sure you want to delete above product? (y for yes or any charcter for no): ";
						cin>>sAns;
						if(sAns=='y'||sAns=='Y'){
							productFile.seekp(0);
							productFile.seekp((ID-1)*sizeof(Product));
							productFile.write( reinterpret_cast< char * >( &emptyRec ),sizeof( Product ) );
							cout<<"Product deleted sucessfully."<<endl;
						}else{
							cout<<"Product will not be deleted."<<endl;
						}
						nfound = false;
						break;
					}
				}
			}
			if(nfound){
				cout<<"Error: Product with custom Label ("<<cLabel<<") not found."<<endl;
			}
			cout<<"Do you want to delete another product? (y for yes or any character for No): ";
			cin>>ans;
			if(!(ans=='y'||ans=='Y')){
				return;
			}
			num++;
		}
		productFile.clear();
	 }else if(choice=='0'){
	 	return;
	 }else{
	 	cout<<"Error: Ivalid Input(please enter a number 1 or 2 )"<<endl;
	 }
	system("pause");
}
void updateProduct(fstream &productFile){
	char choice;
	for(;true;){
		system("cls");
		cout<<"\t========================================================"<<endl;
	  	cout<<"\t===============> UPDATE PRODUCT MENU <=================="<<endl;
		cout<<"\t========================================================"<<endl;
		cout<<"\t\t1\tFind Product to Update by Product ID (UPC)\n\n";
		cout<<"\t\t2\tFind Product to Update by Custom Label \n\n";
		cout<<"\t\t0\tGo back to Main Menu \n\n";
		cout<<"\t========================================================"<<endl;
		cout<<"\tEnter your choice: ";
		cin>>choice;
		if(choice=='1'||choice=='2'||choice=='0'){
			break;
		}else{
			cout<<"Error: Wrong Input Entered!!!"<<endl;
			cout<<"(Enter a number between 0-2)";
			system("pause");
		}
	}
	 if(choice=='1'){
	 	int num = 1;
	 	
		for(;true;){
			system("cls");
			cout<<"\n======================================FIND AND UPDATE PRODUCT BY ID================================="<<endl<<endl;
			char ans;
			int categID = 0;
			string title;
			string cLabel;
			string categ;
			string supplier;
			string specs;
			int qty;
			int supplierID;
			int ID = getProduct();
			productFile.seekg(0);
			productFile.seekg((ID-1)*sizeof(Product));
			Product productRec;
			productFile.read( reinterpret_cast< char * >( &productRec ),sizeof( Product ) );
			if(productRec.getProductID()!=0){
				cout<<"\n===================================================================================================="<<endl<<endl;
				cout<<"Found Product:"<<endl;
				outPutProductDetail(productRec);
				cout<<"\n===================================================================================================="<<endl<<endl;
				system("pause");
				cin.ignore();
				char uChoice;
				for(;true;){
					system("cls");
					cout<<"\t========================================================"<<endl;
	  				cout<<"\t===================> CHOSE OPTION <====================="<<endl;
					cout<<"\t========================================================"<<endl;
					cout<<"\t\t1\tUpdate Product Title\n\n";
					cout<<"\t\t2\tUpdate Product Category\n\n";
					cout<<"\t\t3\tUpdate Custom Label\n\n";
					cout<<"\t\t4\tUpdate Product Quantity\n\n";
					cout<<"\t\t5\tUpdate Product Supplier\n\n";
					cout<<"\t\t6\tUpdate Product Location\n\n";
					cout<<"\t\t7\tUpdate Product Specifications\n\n";
					cout<<"\t\t0\tUpdate Nothing\n\n";
					cout<<"\t========================================================"<<endl;
					cout<<"\tEnter your choice: ";
					cin>>uChoice;
					cout<<"\t========================================================"<<endl<<endl;
					if(uChoice=='1'||uChoice=='2'||uChoice=='3'||uChoice=='4'||uChoice=='5'||uChoice=='6'||uChoice=='7'||uChoice=='8'||uChoice=='0'){
						break;
					}else{
						cout<<"Error: Wrong Input Entered!!!"<<endl;
						cout<<"(Enter a number between 0-8)";
						system("pause");
					}
				}
				switch(uChoice){
					case '1':
						cin.ignore();
						cout<<"Previous Product Title: "<<productRec.getProductTitle()<<endl;
						cout<<"Enter New Product Title: ";
						getline(cin,title);
						productRec.setProductTitle(title);	
						productFile.seekp(0);
						productFile.seekp((ID-1)*sizeof(Product));
						productFile.write( reinterpret_cast< char * >( &productRec ),sizeof( Product ) );
						cout<<"\n===================================================================================================="<<endl<<endl;
						cout<<"Product Information Updated Successfully:"<<endl;
						outPutProductDetail(productRec);
						cout<<"\n===================================================================================================="<<endl<<endl;
					break;
					case '2':
						cin.ignore();
						cout<<"Previous Product Category: "<<productRec.getProductCategName()<<endl;
						cout<<"Enter New Product Category: ";
						getline(cin,categ);
						categID = findCategory(categ);
						if(categID!=0){
							productRec.setProductCategID(categID);
							productRec.setProductCategName(categ);
							productFile.seekp(0);
							productFile.seekp((ID-1)*sizeof(Product));
							productFile.write( reinterpret_cast< char * >( &productRec ),sizeof( Product ) );
							cout<<"\n===================================================================================================="<<endl<<endl;
							cout<<"Product Information Updated Successfully:"<<endl;
							outPutProductDetail(productRec);
							cout<<"\n===================================================================================================="<<endl<<endl;
						}else{
							cout<<"Category not found!!!"<<endl;
							cout<<"Do you want to create new Category? (y for yes or any character for No): ";
							cin>>ans;
							Category categRec;
							fstream categFile("categData.dat",ios::in|ios::out|ios::binary);
							if(!categFile){
								cout<<"File \"categData.dat\" could not be created"<<endl;
								system("pause");
								return;
							}
							if(ans=='y'||ans=='Y'){
								for(;true;){
									categID = getCategory();
									categFile.seekg(0);
									categFile.seekg((categID-1)*sizeof(Category));
									categFile.read( reinterpret_cast< char * >( &categRec ),sizeof( Category ) );
									if(categRec.getCategID()==0){
										cin.ignore();
										cout<<"Enter Category Name: ";
										getline(cin,categ);
										categRec.setCategID(categID);
										categRec.setCategName(categ);
										categFile.seekp(0);
										categFile.seekp((categID-1)*sizeof(Category));
										categFile.write( reinterpret_cast< char * >( &categRec ),sizeof( Category ) );
										cout<<"New Category is saved successfully to \"categData.dat\"."<<endl;
										productRec.setProductCategID(categID);
										productRec.setProductCategName(categ);
										productFile.seekp(0);
										productFile.seekp((ID-1)*sizeof(Product));
										productFile.write( reinterpret_cast< char * >( &productRec ),sizeof( Product ) );
										cout<<"\n===================================================================================================="<<endl<<endl;
										cout<<"Product Information Updated Successfully:"<<endl;
										outPutProductDetail(productRec);
										cout<<"\n===================================================================================================="<<endl<<endl;
										break;
									}else{
										cout<<"Error: Category ID("<<categID<<") already has data."<<endl;
										cout<<"Do you want to add another new category to this product? (y for yes or any character for No): ";
										cin>>ans;
										if(!(ans=='y'||ans=='Y')){
											break;
										}
									}
								}
								
							}
						categFile.clear();
						categFile.close();	
						}
						
					break;
					case '3':
						cin.ignore();
						cout<<"Previous Custom Label: "<<productRec.getProductCustomLabel()<<endl;
						cout<<"Enter New Custom Label: ";
						getline(cin,cLabel);
						cLabel = removeSpaces(cLabel);
						productRec.setProductCustomLabel(cLabel);	
						productFile.seekp(0);
						productFile.seekp((ID-1)*sizeof(Product));
						productFile.write( reinterpret_cast< char * >( &productRec ),sizeof( Product ) );
						cout<<"\n===================================================================================================="<<endl<<endl;
						cout<<"Product Information Updated Successfully:"<<endl;
						outPutProductDetail(productRec);
						cout<<"\n===================================================================================================="<<endl<<endl;
					break;
					case '4':
						cin.ignore();
						cout<<"Previous Quantity: "<<productRec.getProductQuantity()<<endl;
						do{
							cout<<"Enter Quantity (Quantity must by 0 or greater): ";
							cin>>qty;
						}while(qty<0);
						productRec.setProductQuantity(qty);
						updateLocationQuantity(productRec,qty);
						productFile.seekp(0);
						productFile.seekp((ID-1)*sizeof(Product));
						productFile.write( reinterpret_cast< char * >( &productRec ),sizeof( Product ) );
						cout<<"\n===================================================================================================="<<endl<<endl;
						cout<<"Product Information Updated Successfully:"<<endl;
						outPutProductDetail(productRec);
						cout<<"\n===================================================================================================="<<endl<<endl;
					break;
					case '5':
						cin.ignore();
						cout<<"Previous Supplier Name: "<<productRec.getProductCategName()<<endl;
						cout<<"Enter New Supplier Name: ";
						getline(cin,supplier);
						supplierID = findSupplier(supplier);
						if(supplierID!=0){
							productRec.setProductSupplierID(supplierID);
							productRec.setProductSupplierName(supplier);
							productFile.seekp(0);
							productFile.seekp((ID-1)*sizeof(Product));
							productFile.write( reinterpret_cast< char * >( &productRec ),sizeof( Product ) );
							cout<<"\n===================================================================================================="<<endl<<endl;
							cout<<"Product Information Updated Successfully:"<<endl;
							outPutProductDetail(productRec);
							cout<<"\n===================================================================================================="<<endl<<endl;
						}else{
							cout<<"Supplier not found!!!"<<endl;
							cout<<"You can add a new supplier from \"Add New Supplier\" in Main Menu.";
							cout<<"\n===================================================================================================="<<endl<<endl;
						}
					break;
					case '6':
						getNewLocation(productRec);
						productFile.seekp(0);
						productFile.seekp((ID-1)*sizeof(Product));
						productFile.write( reinterpret_cast< char * >( &productRec ),sizeof( Product ) );
						cout<<"\n===================================================================================================="<<endl<<endl;
						cout<<"Product Information Updated Successfully:"<<endl;
						outPutProductDetail(productRec);
						cout<<"\n===================================================================================================="<<endl<<endl;
					break;
					case '7':
						cout<<"Enter Product Specifications: "<<endl;
						getline(cin,specs);
						productRec.setProductSpecs(specs);
						productFile.seekp(0);
						productFile.seekp((ID-1)*sizeof(Product));
						productFile.write( reinterpret_cast< char * >( &productRec ),sizeof( Product ) );
						cout<<"\n===================================================================================================="<<endl<<endl;
						cout<<"Product Information Updated Successfully:"<<endl;
						outPutProductDetail(productRec);
						cout<<"\n===================================================================================================="<<endl<<endl;
					break;
					//case '8':
					//break;
					case '0':
						cout<<"Nothing will be updated!!!"<<endl;
					break;
					default:
					break;	
				}
				
			}else{
				cout<<"Error: Product ID ("<<ID<<") not found."<<endl;
				cout<<"You can add a new product from \"Add New Product\" in Main Menu "<<endl;
			}
			cout<<"Do you want to update another product? (y for yes or any character for No): ";
			cin>>ans;
			if(!(ans=='y'||ans=='Y')){
				return;
			}
			num++;
		}
	 }else if(choice=='2'){
	 	int num = 1;
		for(;true;){
			system("cls");
			cout<<"\n=================================FIND AND UPDATE PRODUCT BY CUSTOM LABEL============================"<<endl<<endl;
			char ans;
			int categID = 0;
			string title;
			string cLabel;
			string categ;
			string supplier;
			string specs;
			int qty;
			int supplierID;
			int ID;
			///////////////////////////
			bool nfound = true;
			cin.ignore();
			cout<<"Enter Custom Label (e.g S6/D): ";
			getline(cin,cLabel);
			Product productRec;
			productFile.seekg(0);
			while(productFile.read( reinterpret_cast< char * >( &productRec ),sizeof( Product ) )){
				if(productRec.getProductID()!=0){
					if(productRec.getProductCustomLabel()==cLabel){
						ID = productRec.getProductID();
						nfound = false;
						break;
					}
				}
			}
			/*if(nfound){
				cout<<"Error: Product with custom Label ("<<cLabel<<") not found."<<endl;
				cout<<"You can add a new product from \"Add New Product\" in Main Menu "<<endl;
			}*/
			if(!nfound){
				cout<<"\n===================================================================================================="<<endl<<endl;
				cout<<"Found Product:"<<endl;
				outPutProductDetail(productRec);
				cout<<"\n===================================================================================================="<<endl<<endl;
				system("pause");
				char uChoice;
				for(;true;){
					system("cls");
					cout<<"\t========================================================"<<endl;
	  				cout<<"\t===================> CHOSE OPTION <====================="<<endl;
					cout<<"\t========================================================"<<endl;
					cout<<"\t\t1\tUpdate Product Title\n\n";
					cout<<"\t\t2\tUpdate Product Category\n\n";
					cout<<"\t\t3\tUpdate Custom Label\n\n";
					cout<<"\t\t4\tUpdate Product Quantity\n\n";
					cout<<"\t\t5\tUpdate Product Supplier\n\n";
					cout<<"\t\t6\tUpdate Product Location\n\n";
					cout<<"\t\t7\tUpdate Product Specifications\n\n";
					cout<<"\t\t0\tUpdate Nothing\n\n";
					cout<<"\t========================================================"<<endl;
					cout<<"\tEnter your choice: ";
					cin>>uChoice;
					cout<<"\t========================================================"<<endl<<endl;
					if(uChoice=='1'||uChoice=='2'||uChoice=='3'||uChoice=='4'||uChoice=='5'||uChoice=='6'||uChoice=='7'||uChoice=='8'||uChoice=='0'){
						break;
					}else{
						cout<<"Error: Wrong Input Entered!!!"<<endl;
						cout<<"(Enter a number between 0-8)";
						system("pause");
					}
				}
				switch(uChoice){
					case '1':
						cin.ignore();
						cout<<"Previous Product Title: "<<productRec.getProductTitle()<<endl;
						cout<<"Enter New Product Title: ";
						getline(cin,title);
						productRec.setProductTitle(title);	
						productFile.seekp(0);
						productFile.seekp((ID-1)*sizeof(Product));
						productFile.write( reinterpret_cast< char * >( &productRec ),sizeof( Product ) );
						cout<<"\n===================================================================================================="<<endl<<endl;
						cout<<"Product Information Updated Successfully:"<<endl;
						outPutProductDetail(productRec);
						cout<<"\n===================================================================================================="<<endl<<endl;
					break;
					case '2':
						cin.ignore();
						cout<<"Previous Product Category: "<<productRec.getProductCategName()<<endl;
						cout<<"Enter New Product Category: ";
						getline(cin,categ);
						categID = findCategory(categ);
						if(categID!=0){
							productRec.setProductCategID(categID);
							productRec.setProductCategName(categ);
							productFile.seekp(0);
							productFile.seekp((ID-1)*sizeof(Product));
							productFile.write( reinterpret_cast< char * >( &productRec ),sizeof( Product ) );
							cout<<"\n===================================================================================================="<<endl<<endl;
							cout<<"Product Information Updated Successfully:"<<endl;
							outPutProductDetail(productRec);
							cout<<"\n===================================================================================================="<<endl<<endl;
						}else{
							cout<<"Category not found!!!"<<endl;
							cout<<"Do you want to create new Category? (y for yes or any character for No): ";
							cin>>ans;
							Category categRec;
							fstream categFile("categData.dat",ios::in|ios::out|ios::binary);
							if(!categFile){
								cout<<"File \"categData.dat\" could not be created"<<endl;
								system("pause");
								return;
							}
							if(ans=='y'||ans=='Y'){
								for(;true;){
									categID = getCategory();
									categFile.seekg(0);
									categFile.seekg((categID-1)*sizeof(Category));
									categFile.read( reinterpret_cast< char * >( &categRec ),sizeof( Category ) );
									if(categRec.getCategID()==0){
										cin.ignore();
										cout<<"Enter Category Name: ";
										getline(cin,categ);
										categRec.setCategID(categID);
										categRec.setCategName(categ);
										categFile.seekp(0);
										categFile.seekp((categID-1)*sizeof(Category));
										categFile.write( reinterpret_cast< char * >( &categRec ),sizeof( Category ) );
										cout<<"New Category is saved successfully to \"categData.dat\"."<<endl;
										productRec.setProductCategID(categID);
										productRec.setProductCategName(categ);
										productFile.seekp(0);
										productFile.seekp((ID-1)*sizeof(Product));
										productFile.write( reinterpret_cast< char * >( &productRec ),sizeof( Product ) );
										cout<<"\n===================================================================================================="<<endl<<endl;
										cout<<"Product Information Updated Successfully:"<<endl;
										outPutProductDetail(productRec);
										cout<<"\n===================================================================================================="<<endl<<endl;
										break;
									}else{
										cout<<"Error: Category ID("<<categID<<") already has data."<<endl;
										cout<<"Do you want to add another new category to this product? (y for yes or any character for No): ";
										cin>>ans;
										if(!(ans=='y'||ans=='Y')){
											break;
										}
									}
								}
								
							}
						categFile.clear();
						categFile.close();	
						}
						
					break;
					case '3':
						cin.ignore();
						cout<<"Previous Custom Label: "<<productRec.getProductCustomLabel()<<endl;
						cout<<"Enter New Custom Label: ";
						getline(cin,cLabel);
						cLabel = removeSpaces(cLabel);
						productRec.setProductCustomLabel(cLabel);	
						productFile.seekp(0);
						productFile.seekp((ID-1)*sizeof(Product));
						productFile.write( reinterpret_cast< char * >( &productRec ),sizeof( Product ) );
						cout<<"\n===================================================================================================="<<endl<<endl;
						cout<<"Product Information Updated Successfully:"<<endl;
						outPutProductDetail(productRec);
						cout<<"\n===================================================================================================="<<endl<<endl;
					break;
					case '4':
						cin.ignore();
						cout<<"Previous Quantity: "<<productRec.getProductQuantity()<<endl;
						do{
							cout<<"Enter Quantity (Quantity must by 0 or greater): ";
							cin>>qty;
						}while(qty<0);
						productRec.setProductQuantity(qty);
						updateLocationQuantity(productRec,qty);
						productFile.seekp(0);
						productFile.seekp((ID-1)*sizeof(Product));
						productFile.write( reinterpret_cast< char * >( &productRec ),sizeof( Product ) );
						cout<<"\n===================================================================================================="<<endl<<endl;
						cout<<"Product Information Updated Successfully:"<<endl;
						outPutProductDetail(productRec);
						cout<<"\n===================================================================================================="<<endl<<endl;
					break;
					case '5':
						cin.ignore();
						cout<<"Previous Supplier Name: "<<productRec.getProductCategName()<<endl;
						cout<<"Enter New Supplier Name: ";
						getline(cin,supplier);
						supplierID = findSupplier(supplier);
						if(supplierID!=0){
							productRec.setProductSupplierID(supplierID);
							productRec.setProductSupplierName(supplier);
							productFile.seekp(0);
							productFile.seekp((ID-1)*sizeof(Product));
							productFile.write( reinterpret_cast< char * >( &productRec ),sizeof( Product ) );
							cout<<"\n===================================================================================================="<<endl<<endl;
							cout<<"Product Information Updated Successfully:"<<endl;
							outPutProductDetail(productRec);
							cout<<"\n===================================================================================================="<<endl<<endl;
						}else{
							cout<<"Supplier not found!!!"<<endl;
							cout<<"You can add a new supplier from \"Add New Supplier\" in Main Menu.";
							cout<<"\n===================================================================================================="<<endl<<endl;
						}
					break;
					case '6':
						getNewLocation(productRec);
					break;
					case '7':
						cout<<"Enter Product Specifications: "<<endl;
						getline(cin,specs);
						productRec.setProductSpecs(specs);
						productFile.seekp(0);
						productFile.seekp((ID-1)*sizeof(Product));
						productFile.write( reinterpret_cast< char * >( &productRec ),sizeof( Product ) );
						cout<<"\n===================================================================================================="<<endl<<endl;
						cout<<"Product Information Updated Successfully:"<<endl;
						outPutProductDetail(productRec);
						cout<<"\n===================================================================================================="<<endl<<endl;
					break;
					//case '8':
					//break;
					case '0':
						cout<<"Nothing will be updated!!!"<<endl;
					break;
					default:
					break;	
				}
				
			}else{
				cout<<"Error: Product with custom Label ("<<cLabel<<") not found."<<endl;
				cout<<"You can add a new product from \"Add New Product\" in Main Menu "<<endl;
			}
			cout<<"Do you want to update another product? (y for yes or any character for No): ";
			cin>>ans;
			if(!(ans=='y'||ans=='Y')){
				return;
			}
			num++;
		}
	 }else if(choice=='0'){
	 	return;
	 }else{
	 	cout<<"Error: Ivalid Input(please enter a number 1 or 2 )"<<endl;
	 }
	system("pause");
}
void addSupplier(){
	fstream supplierFile("supplierData.dat",ios::in|ios::out|ios::binary);
	if(!supplierFile){
		cout<<"File could not be created/ opened!!!"<<endl;
		system("pause");
		return;
	}
	char ans;
	for(;true;){
		system("cls");
		cout<<"============================================================="<<endl;
	  	cout<<"======================> ADD NEW SUPPLIER <==================="<<endl;
		cout<<"============================================================="<<endl<<endl;
		string supplierName;
		string supplierMail;
		string supplierPhone;
		string supplierAddress;
		int supplierID = getSupplier();
		supplierFile.seekg(0);
		supplierFile.seekg((supplierID-1)*sizeof(Supplier));
		Supplier supplierRec;
		supplierFile.read( reinterpret_cast< char * >( &supplierRec ),sizeof( Supplier ) );
		if(supplierRec.getSupplierID()==0){
			cin.ignore();
			cout<<"Enter Supplier Name / Business Name(e.g KARNI TRADERS LTD ): ";
			getline(cin,supplierName);
			cout<<"Enter Supplier email Address: ";
			getline(cin,supplierMail);
			cout<<"Enter Supplier Contact Number : ";
			getline(cin,supplierPhone);
			cout<<"Enter Supplier Address: ";
			getline(cin,supplierAddress);
			//
			supplierRec.setSupplierID(supplierID);
			supplierRec.setSupplierName(supplierName);
			supplierRec.setSupplierMail(supplierMail);
			supplierRec.setSupplierPhone(supplierPhone);
			supplierRec.setSupplierAddress(supplierAddress);
			//
			supplierFile.seekp(0);
			supplierFile.seekp((supplierID-1)*sizeof(Supplier));
			supplierFile.write( reinterpret_cast< char * >( &supplierRec ),sizeof( Supplier ) );
			cout<<"\n===================================================================================================="<<endl<<endl;
			cout<<"Supplier saved Successfully:"<<endl;
			outPutSupplierDetail(supplierRec);
			cout<<"\n===================================================================================================="<<endl<<endl;
			
		}else{
			cout<<"Supplier ID ("<<supplierID<<") Already has data."<<endl;
		}
		cout<<"Do you want to add another Supplier? (y for yes or any character for No): ";
		cin>>ans;
		if(!(ans=='y'||ans=='Y')){
			break;
		}
	}
	supplierFile.clear();
	supplierFile.close();
}
void updateSupplier(){
	fstream supplierFile("supplierData.dat",ios::in|ios::out|ios::binary);
	if(!supplierFile){
		cout<<"File could not be created/ opened!!!"<<endl;
		system("pause");
		return;
	}
	char choice;
	for(;true;){
		system("cls");
		cout<<"\t========================================================"<<endl;
	  	cout<<"\t==================> UPDATE SUPPLIER <==================="<<endl;
		cout<<"\t========================================================"<<endl;
		cout<<"\t\t1\tFind Supplier to Update by Supplier ID \n\n";
		cout<<"\t\t2\tFind Supplier to Update by Supplier Name \n\n";
		cout<<"\t\t0\tGo back to Main Menu \n\n";
		cout<<"\t========================================================"<<endl;
		cout<<"\tEnter your choice: ";
		cin>>choice;
		if(choice=='1'||choice=='2'||choice=='0'){
			break;
		}else{
			cout<<"Error: Wrong Input Entered!!!"<<endl;
			cout<<"(Enter a number between 0-2)";
			system("pause");
		}
	}
	 if(choice=='1'){
	 	int num = 1;
	 	
		for(;true;){
			system("cls");
			cout<<"\n======================================FIND AND UPDATE SUPPLIER BY ID================================="<<endl<<endl;
			char ans;
			string supplierName;
			string supplierMail;
			string supplierPhone;
			string supplierAddress;
			int supplierID = getSupplier();
			supplierFile.seekg(0);
			supplierFile.seekg((supplierID-1)*sizeof(Supplier));
			Supplier supplierRec;
			supplierFile.read( reinterpret_cast< char * >( &supplierRec ),sizeof( Supplier ) );
			if(supplierRec.getSupplierID()!=0){
				cout<<"\n===================================================================================================="<<endl<<endl;
				cout<<"Found Supplier:"<<endl;
				outPutSupplierDetail(supplierRec);
				cout<<"\n===================================================================================================="<<endl<<endl;
				system("pause");
				cin.ignore();
				char uChoice;
				for(;true;){
					system("cls");
					cout<<"\t========================================================"<<endl;
				  	cout<<"\t==================> UPDATE SUPPLIER <==================="<<endl;
					cout<<"\t========================================================"<<endl;
					cout<<"\t\t1\tUpdate Supplier Name\n\n";
					cout<<"\t\t2\tUpdate Supplier email address\n\n";
					cout<<"\t\t3\tUpdate Supplier Contact Number\n\n";
					cout<<"\t\t4\tUpdate Supplier Address\n\n";
					cout<<"\t\t0\tUpdate Nothing\n\n";
					cout<<"\t========================================================"<<endl;
					cout<<"\tEnter your choice: ";
					cin>>uChoice;
					cout<<"\t========================================================"<<endl;
					if(uChoice=='1'||uChoice=='2'||uChoice=='3'||uChoice=='4'||uChoice=='0'){
						break;
					}else{
						cout<<"Error: Wrong Input Entered!!!"<<endl;
						cout<<"(Enter a number between 0-4)";
						system("pause");
					}
				}
				switch(uChoice){
					case '1':
						cin.ignore();
						cout<<"Previous Supplier Name: "<<supplierRec.getSupplierName()<<endl;
						cout<<"Enter New Supplier Name: ";
						getline(cin,supplierName);
						supplierRec.setSupplierName(supplierName);
						supplierFile.seekp(0);
						supplierFile.seekp((supplierID-1)*sizeof(Supplier));
						supplierFile.write( reinterpret_cast< char * >( &supplierRec ),sizeof( Supplier ) );
						cout<<"\n===================================================================================================="<<endl<<endl;
						cout<<"Product Information Updated Successfully:"<<endl;
						outPutSupplierDetail(supplierRec);
						cout<<"\n===================================================================================================="<<endl<<endl;
					break;
					case '2':
						cin.ignore();
						cout<<"Previous Supplier email address: "<<supplierRec.getSupplierMail()<<endl;
						cout<<"Enter New Supplier Name: ";
						getline(cin,supplierMail);
						supplierRec.setSupplierMail(supplierMail);
						supplierFile.seekp(0);
						supplierFile.seekp((supplierID-1)*sizeof(Supplier));
						supplierFile.write( reinterpret_cast< char * >( &supplierRec ),sizeof( Supplier ) );
						cout<<"\n===================================================================================================="<<endl<<endl;
						cout<<"Product Information Updated Successfully:"<<endl;
						outPutSupplierDetail(supplierRec);
						cout<<"\n===================================================================================================="<<endl<<endl;
					break;
					case '3':
						cin.ignore();
						cout<<"Previous Supplier Contact Number: "<<supplierRec.getSupplierPhone()<<endl;
						cout<<"Enter New Supplier Contact Number: ";
						getline(cin,supplierPhone);
						supplierRec.setSupplierPhone(supplierPhone);
						supplierFile.seekp(0);
						supplierFile.seekp((supplierID-1)*sizeof(Supplier));
						supplierFile.write( reinterpret_cast< char * >( &supplierRec ),sizeof( Supplier ) );
						cout<<"\n===================================================================================================="<<endl<<endl;
						cout<<"Product Information Updated Successfully:"<<endl;
						outPutSupplierDetail(supplierRec);
						cout<<"\n===================================================================================================="<<endl<<endl;
					break;
					case '4':
						cin.ignore();
						cout<<"Previous Address: "<<supplierRec.getSupplierAddress()<<endl;
						cout<<"Enter New Supplier Address: ";
						getline(cin,supplierAddress);
						supplierRec.setSupplierAddress(supplierAddress);
						supplierFile.seekp(0);
						supplierFile.seekp((supplierID-1)*sizeof(Supplier));
						supplierFile.write( reinterpret_cast< char * >( &supplierRec ),sizeof( Supplier ) );
						cout<<"\n===================================================================================================="<<endl<<endl;
						cout<<"Product Information Updated Successfully:"<<endl;
						outPutSupplierDetail(supplierRec);
						cout<<"\n===================================================================================================="<<endl<<endl;
					break;
					//case '8':
					//break;
					case '0':
						cout<<"Nothing will be updated!!!"<<endl;
					break;
					default:
					break;	
				}
				
			}else{
				cout<<"Error: Supplier ID ("<<supplierID<<") not found."<<endl;
				cout<<"You can add a new supplier from \"Add New Supplier\" in Main Menu "<<endl;
			}
			cout<<"Do you want to update another supplier? (y for yes or any character for No): ";
			cin>>ans;
			if(!(ans=='y'||ans=='Y')){
				return;
			}
			num++;
		}
	 }else if(choice=='2'){
	 	int num = 1;
		for(;true;){
			system("cls");
			cout<<"\n=================================FIND AND UPDATE SUPPLIER BY NAME============================"<<endl<<endl;
			char ans;
			string supplierName;
			string supplierMail;
			string supplierPhone;
			string supplierAddress;
			int supplierID;
			bool nfound = true;
			cin.ignore();
			cout<<"Enter Supplier Name: ";
			getline(cin,supplierName);
			Supplier supplierRec;
			supplierFile.seekg(0);
			while(supplierFile.read( reinterpret_cast< char * >( &supplierRec ),sizeof( Supplier ) )){
				if(supplierRec.getSupplierID()!=0){
					if(supplierRec.getSupplierName()==supplierName){
						supplierID = supplierRec.getSupplierID();
						nfound = false;
						break;
					}
				}
			}
			/*if(nfound){
				cout<<"Error: Product with custom Label ("<<cLabel<<") not found."<<endl;
				cout<<"You can add a new product from \"Add New Product\" in Main Menu "<<endl;
			}*/
			if(!nfound){
				cout<<"\n===================================================================================================="<<endl<<endl;
				cout<<"Found Supplier:"<<endl;
				outPutSupplierDetail(supplierRec);
				cout<<"\n===================================================================================================="<<endl<<endl;
				system("pause");
				char uChoice;
				for(;true;){
					system("cls");
					cout<<"\t========================================================"<<endl;
				  	cout<<"\t==================> UPDATE SUPPLIER <==================="<<endl;
					cout<<"\t========================================================"<<endl;
					cout<<"\t\t1\tUpdate Supplier Name\n\n";
					cout<<"\t\t2\tUpdate Supplier email address\n\n";
					cout<<"\t\t3\tUpdate Supplier Contact Number\n\n";
					cout<<"\t\t4\tUpdate Supplier Address\n\n";
					cout<<"\t\t0\tUpdate Nothing\n\n";
					cout<<"\t========================================================"<<endl;
					cout<<"\tEnter your choice: ";
					cin>>uChoice;
					cout<<"\t========================================================"<<endl;
					if(uChoice=='1'||uChoice=='2'||uChoice=='3'||uChoice=='4'||uChoice=='0'){
						break;
					}else{
						cout<<"Error: Wrong Input Entered!!!"<<endl;
						cout<<"(Enter a number between 0-4)";
						system("pause");
					}
				}
				switch(uChoice){
					case '1':
						cin.ignore();
						cout<<"Previous Supplier Name: "<<supplierRec.getSupplierName()<<endl;
						cout<<"Enter New Supplier Name: ";
						getline(cin,supplierName);
						supplierRec.setSupplierName(supplierName);
						supplierFile.seekp(0);
						supplierFile.seekp((supplierID-1)*sizeof(Supplier));
						supplierFile.write( reinterpret_cast< char * >( &supplierRec ),sizeof( Supplier ) );
						cout<<"\n===================================================================================================="<<endl<<endl;
						cout<<"Product Information Updated Successfully:"<<endl;
						outPutSupplierDetail(supplierRec);
						cout<<"\n===================================================================================================="<<endl<<endl;
					break;
					case '2':
						cin.ignore();
						cout<<"Previous Supplier email address: "<<supplierRec.getSupplierMail()<<endl;
						cout<<"Enter New Supplier Name: ";
						getline(cin,supplierMail);
						supplierRec.setSupplierMail(supplierMail);
						supplierFile.seekp(0);
						supplierFile.seekp((supplierID-1)*sizeof(Supplier));
						supplierFile.write( reinterpret_cast< char * >( &supplierRec ),sizeof( Supplier ) );
						cout<<"\n===================================================================================================="<<endl<<endl;
						cout<<"Product Information Updated Successfully:"<<endl;
						outPutSupplierDetail(supplierRec);
						cout<<"\n===================================================================================================="<<endl<<endl;
					break;
					case '3':
						cin.ignore();
						cout<<"Previous Supplier Contact Number: "<<supplierRec.getSupplierPhone()<<endl;
						cout<<"Enter New Supplier Contact Number: ";
						getline(cin,supplierPhone);
						supplierRec.setSupplierPhone(supplierPhone);
						supplierFile.seekp(0);
						supplierFile.seekp((supplierID-1)*sizeof(Supplier));
						supplierFile.write( reinterpret_cast< char * >( &supplierRec ),sizeof( Supplier ) );
						cout<<"\n===================================================================================================="<<endl<<endl;
						cout<<"Product Information Updated Successfully:"<<endl;
						outPutSupplierDetail(supplierRec);
						cout<<"\n===================================================================================================="<<endl<<endl;
					break;
					case '4':
						cin.ignore();
						cout<<"Previous Address: "<<supplierRec.getSupplierAddress()<<endl;
						cout<<"Enter New Supplier Address: ";
						getline(cin,supplierAddress);
						supplierRec.setSupplierAddress(supplierAddress);
						supplierFile.seekp(0);
						supplierFile.seekp((supplierID-1)*sizeof(Supplier));
						supplierFile.write( reinterpret_cast< char * >( &supplierRec ),sizeof( Supplier ) );
						cout<<"\n===================================================================================================="<<endl<<endl;
						cout<<"Product Information Updated Successfully:"<<endl;
						outPutSupplierDetail(supplierRec);
						cout<<"\n===================================================================================================="<<endl<<endl;
					break;
					//case '8':
					//break;
					case '0':
						cout<<"Nothing will be updated!!!"<<endl;
					break;
					default:
					break;	
				}
				
			}else{
				cout<<"Error: Supplier with Name ("<<supplierName<<") not found."<<endl;
				cout<<"You can add a new Supplier from \"Add New Supplier\" in Main Menu "<<endl;
			}
			cout<<"Do you want to update another supplier? (y for yes or any character for No): ";
			cin>>ans;
			if(!(ans=='y'||ans=='Y')){
				return;
			}
			num++;
		}
	 }else if(choice=='0'){
	 	return;
	 }else{
	 	cout<<"Error: Ivalid Input(please enter a number 1 or 2 )"<<endl;
	 }
	supplierFile.clear();
	supplierFile.close();
	system("pause");
}
void dispStock(fstream &productFile){
	Product productRec;
	int ans;
	bool noFound = true;
	do{
		system("cls");
		cout<<"\t============================================================="<<endl;
		cout<<"\t========================> PRODUCTS DATA <===================="<<endl;
		cout<<"\t============================================================="<<endl;
		cout<<"\t\t1\tBrief view of stock (in the form of table)\n\n";
		cout<<"\t\t2\tDetailed view of stock\n\n";
		cout<<"\t\t0\tGo back to Main Menu\n\n";
		cout<<"\tEnter your choice: ";
		cin.clear();
		cin>>ans;
		cout<<"\t========================================================"<<endl;
		
	}while(ans < 0 || ans > 2);
	
	if(ans==1){
		system("cls");
		cout<<"======================================================================================================="<<endl;
		cout<<"===============================================> PRODUCTS DATA <======================================="<<endl;
		cout<<"======================================================================================================="<<endl;
  		cout<<endl<<"-------------------------------------------------------------------------------------------------------"<<endl;
		cerr<<left<<setw(10)<<"|ProductID";cerr <<setw(50)<<"|Product Title"; cerr <<setw(20)<<"|CustomLabel"; cerr <<setw(10)<<"|Quantity"; cerr <<setw(12)<<"|Location   ";cerr<<'|'; cerr <<endl;
		cout<<"-------------------------------------------------------------------------------------------------------"<<endl;
		productFile.seekg(0);
		while(!productFile.eof()){
			productFile.read( reinterpret_cast< char * >( &productRec ),sizeof( Product ) );
			if(productFile.eof()){break;}
			if(productRec.getProductID()!=0){
				outPutProductLine(productRec);
				noFound = false;
			}
		}
	}else if(ans==2){
		system("cls");
		cout<<"============================================================="<<endl;
		cout<<"========================> PRODUCTS DATA <===================="<<endl;
		cout<<"============================================================="<<endl;
		productFile.seekg(0);
		while(!productFile.eof()){
			productFile.read( reinterpret_cast< char * >( &productRec ),sizeof( Product ) );
			if(productFile.eof()){break;}
			if(productRec.getProductID()!=0){
				outPutProductDetail(productRec);
				noFound = false;
			}
		}
	}else{
		return;
	}
	if(noFound){
		cout<<"No Product found"<<endl;
	}
	system("pause");
	productFile.clear();
}
void dispSupplier(){
	bool noFound = true;
	system("cls");
	Supplier supplierRec;
	fstream supplierFile("supplierData.dat",ios::in|ios::binary);
	if(!supplierFile){
		cout<<"File could not be created/ opened!!!"<<endl;
		system("pause");
		return;
	}
	cout<<"==================================================================================================="<<endl;
	cout<<"===============================================> SUPPLIER DATA <==================================="<<endl;
	cout<<"==================================================================================================="<<endl;
	supplierFile.seekg(0);
	while(supplierFile.read( reinterpret_cast< char * >( &supplierRec ),sizeof( Supplier ) )){
		if(supplierRec.getSupplierID()!=0){
			outPutSupplierDetail(supplierRec);
			noFound = false;
		}
	}
	if(noFound){
		cout<<"No Supplier found."<<endl;
	}
	supplierFile.clear();
	supplierFile.close();
	system("pause");
}
void dispLocations(){
	bool noFound = true;
	system("cls");
	Location locationRec;
	fstream locationFile("locationData.dat",ios::in|ios::binary);
	if(!locationFile){
		cout<<"File could not be created/ opened!!!"<<endl;
		system("pause");
		return;
	}
	cout<<"==========================================================================================================="<<endl;
	cout<<"===============================================> LOCATION DATA <==========================================="<<endl;
	cout<<"==========================================================================================================="<<endl;
	cout<<endl<<"-----------------------------------------------------------------------------------------------------------"<<endl;
	cerr<<left<<setw(20)<<"|LocationID";cerr <<setw(20)<<"|Location Name"; cerr <<setw(20)<<"|Product Stored ID"; cerr <<setw(30)<<"|Product Stored Custom Label"; cerr <<setw(17)<<"|Stored Quantity|"; cerr <<endl;
	cout<<"-----------------------------------------------------------------------------------------------------------"<<endl;
	locationFile.seekg(0);
	while(locationFile.read( reinterpret_cast< char * >( &locationRec ),sizeof( Location ) )){
		if(locationRec.getLocationID()!=0){
			outPutLocationLine(locationRec);
			noFound = false;
		}
	}
	if(noFound){
		cout<<"No location found."<<endl;
	}
	locationFile.clear();
	locationFile.close();
	system("pause");
}
void emptyRecords(){
	char ans;
	cout<<"\n\n\n================================================================================================================"<<endl<<endl;
	cout<<"Have you opened this programe for the first time?(y for yes or any character for no) :";
	cin>>ans; //creates a blank records in ".dat" files
	if(ans=='y'||ans=='Y'){
		char res;
		cout<<"\n\n\n================================================================================================================"<<endl<<endl;
		cout<<"Are you sure?(Empty records will be created and previous will be delated)(y for yes or any character for no) : ";
		cin>>res;
		if(res=='y'||res=='Y'){
			fstream categFile("categData.dat",ios::out|ios::binary);
			if(!categFile){
				cout<<"File \"categData.dat\" could not be created"<<endl;
				system("pause");
				exit(1);
			}
			Category categRec;
			// creating 100 empty records
			for(int count=0;count<100;count++){
			categFile.write(reinterpret_cast<char*>(&categRec),sizeof(Category));
			//WriteFile<<"\n"; //not compulsory, was done to see whether the file contains a 100 records or not
			}
			categFile.close();

			fstream productFile("productData.dat",ios::out|ios::binary);
			if(!productFile){
				cout<<"File \"productData.dat\" could not be created"<<endl;
				system("pause");
				exit(1);
			}
			Product productRec;
			// creating 100 empty records
			for(int count=0;count<100;count++){
			productFile.write(reinterpret_cast<char*>(&productRec),sizeof(Product));
			//WriteFile<<"\n"; //not compulsory, was done to see whether the file contains a 100 records or not
			}
			categFile.close();
			
			fstream supplierFile("supplierData.dat",ios::out|ios::binary);
			if(!supplierFile){
				cout<<"File \"supplierData.dat\" could not be created"<<endl;
				system("pause");
				exit(1);
			}
			Supplier supplierRec;
			// creating 100 empty records
			for(int count=0;count<100;count++){
			supplierFile.write(reinterpret_cast<char*>(&supplierRec),sizeof(Supplier));
			//WriteFile<<"\n"; //not compulsory, was done to see whether the file contains a 100 records or not
			}
			supplierFile.close();
			//////////////////
			fstream locationFile("locationData.dat",ios::out|ios::binary);
			if(!locationFile){
				cout<<"File \"locationData.dat\" could not be created"<<endl;
				system("pause");
				exit(1);
			}
			Location locationRec;
			// creating 100 empty records
			for(int count=0;count<1000;count++){
			locationFile.write(reinterpret_cast<char*>(&locationRec),sizeof(Location));
			//WriteFile<<"\n"; //not compulsory, was done to see whether the file contains a 100 records or not
			}
			locationFile.close();
		}
	}
}

int getProduct(){
		int inpt;
		do{
			cout<<"Enter Product ID (1-1000): ";
			cin>>inpt;
		} while ( inpt < 1 || inpt > 1000 );
	return inpt;
}
int getCategory(){
		int inpt;
		do{
			cout<<"Enter Category ID (1-100): ";
			cin>>inpt;
		} while ( inpt < 1 || inpt > 100 );
	return inpt;
}
int getLocation(){
		int inpt;
		do{
			cout<<"Enter Location ID (1-100): ";
			cin>>inpt;
		} while ( inpt < 1 || inpt > 100 );
	return inpt;
}
void getNewLocation(Product &productRec){
	fstream locationFile("locationData.dat",ios::in|ios::out|ios::binary);
	if(!locationFile){
		cout<<"Error: File could not be opened/ created ;"<<endl;
		system("pause");
		return;
	}
	
	if(productRec.getProductLocationID()!=0){
		locationFile.seekp(0);
		locationFile.seekp((productRec.getProductLocationID()-1)*sizeof(Location));
		Location emptyLocation;
		locationFile.write(reinterpret_cast<char*>(&emptyLocation),sizeof(Location));
	}
	for(;true;){
		string locationName;
		int locationID = getLocation();
		locationFile.seekg(0);
		locationFile.seekg((locationID-1)*sizeof(Location));
		Location locationRec;
		locationFile.read( reinterpret_cast< char * >( &locationRec ),sizeof( Location ) );
		if(locationRec.getLocationID()==0){
			for(;true;){
				cin.ignore();
				cout<<"Enter Location Name with out space (e.g A-1/R2/S3): ";
				getline(cin,locationName);
				locationName = removeSpaces(locationName);
				if(findLocation(locationName)==0){
					break;
				}else{
					cout<<"Error: Location already occupied by another product."<<endl;
					system("pause");
				}
			}
			locationRec.setLocationID(locationID);
			locationRec.setLocationName(locationName);
			locationRec.setProductStoredID(productRec.getProductID());
			locationRec.setProductStoredCustomLabel(productRec.getProductCustomLabel());
			locationRec.setStoredQty(productRec.getProductQuantity());
			locationFile.seekg(0);
		    locationFile.seekg((locationID-1)*sizeof(Location));
			locationFile.write( reinterpret_cast< char * >( &locationRec ),sizeof( Location ) );
			productRec.setProductLocationID(locationID);
			productRec.setProductLocationName(locationName);
			break;
		}else{
			cout<<"Error: Location ID "<<locationID<<" already has data."<<endl;
			system("pause");
		}
	}
	
	locationFile.clear();
	locationFile.close();
}
int getSupplier(){
		int inpt;
		do{
			cout<<"Enter Supplier ID (1-100): ";
			cin>>inpt;
		} while ( inpt < 1 || inpt > 100 );
	return inpt;
}
int findCategory(string categName){
	fstream categFile("categData.dat",ios::in|ios::out|ios::binary);
	if(!categFile){
		cout<<"File could not be created/ opened!!!"<<endl;
		return 0;
	}
	Category categRec;
	categFile.seekg(0);
	while(categFile.read(reinterpret_cast<char*>(&categRec),sizeof(Category))){
		if(categRec.getCategID()!=0){
			if(categRec.getCategName()==categName){
				return categRec.getCategID();
			}
		}
	}
	return 0;
	categFile.clear();
	categFile.close();
}
int findLocation(string locationName){
	fstream locationFile("locationData.dat",ios::in|ios::out|ios::binary);
	if(!locationFile){
		cout<<"File could not be created/ opened!!!"<<endl;
		return 1;
	}
	Location locationRec;
	locationFile.seekg(0);
	while(locationFile.read(reinterpret_cast<char*>(&locationRec),sizeof(Location))){
		if(locationRec.getLocationID()!=0){
			if(locationRec.getLocationName()==locationName){
				return locationRec.getLocationID();
			}
		}
	}
	return 0;
	locationFile.clear();
	locationFile.close();
}
int findSupplier(string supplierName){
	fstream supplierFile("supplierData.dat",ios::in|ios::out|ios::binary);
	if(!supplierFile){
		cout<<"File could not be created/ opened!!!"<<endl;
		return 0;
	}
	Supplier supplierRec;
	supplierFile.seekg(0);
	while(supplierFile.read(reinterpret_cast<char*>(&supplierRec),sizeof(Supplier))){
		if(supplierRec.getSupplierID()!=0){
			if(supplierRec.getSupplierName()==supplierName){
				return supplierRec.getSupplierID();
			}
		}
	}
	return 0;
	supplierFile.clear();
	supplierFile.close();
}
string removeSpaces(string productCustomLabelString){
	  int length = productCustomLabelString.length();
	  for (int i = 0; i < length; i++) {
	     if(productCustomLabelString[i] == ' '){
	        productCustomLabelString.erase(i, 1);
	         length--;
	         i--;
	     }
	  }
	  return productCustomLabelString;
}
void updateLocationQuantity(Product &productRec,int qty){
	fstream locationFile("locationData.dat",ios::in|ios::out|ios::binary);
	if(!locationFile){
		cout<<"Error: File could not be opened/ created ;"<<endl;
		system("pause");
		return;
	}
	Location locationRec;
	int locationID = productRec.getProductLocationID();
	locationFile.seekg(0);
	locationFile.seekg((locationID-1)*sizeof(Location));
	locationFile.read( reinterpret_cast< char * >( &locationRec ),sizeof( Location ) );
	locationRec.setStoredQty(qty);
	locationFile.seekp(0);
	locationFile.seekp((locationID-1)*sizeof(Location));
	locationFile.write( reinterpret_cast< char * >( &locationRec ),sizeof( Location ) );
	locationFile.close();
}
void outPutProductLine(Product &productRec){
	
	cerr<<'|';cerr << left << setw( 9 ) << productRec.getProductID();cerr<<'|'; cerr << setw( 49 );cerr << productRec.getProductTitle();cerr<<'|'; cerr << setw( 19 ); cerr << productRec.getProductCustomLabel();cerr<<'|'; cerr << setw( 9 ); cerr << productRec.getProductQuantity();cerr<<'|'; cerr << setw( 11 ); cerr << productRec.getProductLocationName(); cerr << '|'; cerr << endl;
}
void outPutLocationLine(Location &locationtRec){
	
	cerr<<'|'; cerr << left << setw( 19 ) << locationtRec.getLocationID(); cerr<<'|'; cerr << setw( 19 );cerr << locationtRec.getLocationName(); cerr<<'|'; cerr << setw( 19 ); cerr << locationtRec.getProductStoredID();cerr<<'|';  cerr << setw( 29 ); cerr << locationtRec.getProductStoredCustomLabel(); cerr<<'|'; cerr << setw( 15 ); cerr << locationtRec.getStoredQty(); cerr<<'|'; cerr << endl;
}
void outPutProductDetail(Product &productRec){
	cerr << "\n---------------------------------------------------------------------------------------------------"<<endl;
	cerr << left <<setw(25) <<"Product ID: "<< productRec.getProductID()<<endl;
	cerr << left <<setw(25) <<"Category ID: "<< productRec.getProductCategID()<<endl;
	cerr << left <<setw(25) <<"Product Title: "<< productRec.getProductTitle()<<endl;
	cerr << left <<setw(25) <<"Category: "<<productRec.getProductCategName()<<endl;
	cerr << left <<setw(25) <<"Product Custom Label: " << productRec.getProductCustomLabel()<<endl;
	cerr << left <<setw(25) <<"Product Quantity: " << productRec.getProductQuantity()<<endl;
	cerr << left <<setw(25) <<"Supplier ID: " << productRec.getProductSupplierID()<<endl;
	cerr << left <<setw(25) <<"Supplier: " << productRec.getProductSupplierName()<<endl;
	cerr << left <<setw(25) <<"Product Location ID: "<< productRec.getProductLocationID()<<endl;
	cerr << left <<setw(25) <<"Product Location: " << productRec.getProductLocationName() << endl;
	cerr << left <<setw(25) <<"Product Specifications: " <<endl<<"\t"<< productRec.getProductSpecs() << endl;
}
void outPutSupplierDetail(Supplier &supplierRec){
	cerr << "\n---------------------------------------------------------------------------------------------------"<<endl;
	cerr << left <<setw(30) <<"Supplier ID: "<< supplierRec.getSupplierID()<<endl;
	cerr << left <<setw(30) <<"Supplier Name: "<< supplierRec.getSupplierName()<<endl;
	cerr << left <<setw(30) <<"Supplier e-mail: "<<supplierRec.getSupplierMail()<<endl;
	cerr << left <<setw(30) <<"Supplier Contact Number: " << supplierRec.getSupplierPhone()<<endl;
	cerr << left <<setw(30) <<"Supplier Address: " << supplierRec.getSupplierAddress()<<endl;
}

