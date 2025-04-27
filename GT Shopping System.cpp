#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int totalOrderCount;
string append = to_string(totalOrderCount);
string receipt = "receipt";

bool isValidName(const string& name) {		
    for (char ch : name) {
        if (!isalpha(ch) && ch != ' ') {
            return false;
        }
    }
    return !name.empty(); 
}


bool noSpace(const string& str) {
	for(char ch : str){
		if(ch == ' '){
			return false;
		}
	}
	return true;
}

bool isDigits(const string& str) {
    for (char ch : str) {
        if (!isdigit(ch) || ch == ' ') {
            return false;
        }
    }
    return true;
}

string capital(string input){
	
    for (int i = 0; i < input.length(); i++)
        input[i] = toupper(input[i]);

	return input;
}




// Product Class
class Product {
public:
    string productId;
    const char* name;
    double price;
    int stockQuantity;

    Product(string id, const char* n, double p, int stock) : productId(id), name(n), price(p), stockQuantity(stock) {}
};

// ShoppingCart Class
class ShoppingCart {
private:
    Product* items[10];
    int quantities[10];
    int itemCount;
    double amount;
    double totalAmount;

public:
    ShoppingCart() : itemCount(0) {}

    bool addProduct(Product* product, int quantity) {
        if (product->stockQuantity < quantity) {
            return false;
        }
        for (int i = 0; i < itemCount; i++) {
            if (items[i]->productId == product->productId) {
                quantities[i] += quantity;
                amount = quantity * product->price;
            	totalAmount += amount;
                cout << "\n[+] Product quantity updated successfully!\n";
                return true;
            }
        }
        items[itemCount] = product;
        quantities[itemCount++] = quantity;
        amount = quantity * product->price;
        totalAmount += amount;
        cout << "\n[+] Product added to cart successfully!\n";
        return true;
    }

    void displayCart() const {
        if (itemCount == 0) {
            return;
        }
        cout << "\nShopping Cart:\nID| Name          | Price | Quantity\n------------------------------------\n";
        for (int i = 0; i < itemCount; i++) {
            cout << items[i]->productId << " | " << items[i]->name << " | $"
                 << items[i]->price << "   | " << quantities[i] << "\n";
        }
        
    }

    double calculateTotal() const {
        double total = 0;
        for (int i = 0; i < itemCount; i++) {
            total += items[i]->price * quantities[i];
        }
        return total;
    }

    void clearCart() { itemCount = 0; amount = 0; totalAmount = 0;}

    int getItemCount() { 
	   	 if(itemCount == 0){   	 	
			throw "No Items On Cart.";
			}
	return itemCount; }
	
    void printTotalAmount(){
    	if(itemCount == 0) {
    		return;
		}
    	cout<<endl<<"----------------------------------------"<<endl;
    	cout<<"Total: $"<<totalAmount<<endl;
	}
	
	double getTotal(){
		return totalAmount;
	}	
	
};

// Order Class
class Order {
private:
    static int orderCounter;
    int orderId;
    double totalAmount;
    ShoppingCart cart;
    string paymentMethod;

public:
    Order() : orderId(0), totalAmount(0) {}

    Order(const ShoppingCart& c) : orderId(++orderCounter), totalAmount(c.calculateTotal()), cart(c) {}

    void displayOrderDetails() const {
        cout << "\n=====================================";
        cout << "\n Order Summary ";
        cout << "\n=====================================";
        cout << "\nOrder ID: " << orderId;
        cout << "\nTotal Amount: $" << totalAmount << "\n";
        cart.displayCart();
        cout << "=====================================\n";
    }    
    
 	int getCounter(){
 		return orderCounter;
		}
		
	void virtual checkout(){
	}	
		
};
int Order::orderCounter = 0;

// Display Products
void displayProducts(Product* products[], int size) {
    cout << "\nAvailable Products:\n";
    cout << "ID| Name          | Price\n";
    cout << "------------------------------\n";
    for (int i = 0; i < size; i++) {
        cout << products[i]->productId << " | " << products[i]->name << " | $" << products[i]->price << "\n";
    }
}

class Credit: public Order{
	public:
	void checkout() override{
		receipt.insert(7,append);
		string file = receipt + ".txt";
		ofstream myFile(file);
		 myFile << "ORDER ID: " <<totalOrderCount<<" Has Been successfully checked out and paid using Credit Card."<<std::endl;
    	myFile.close();

                    cout << "\n[+] Checkout successful!\n";
}
	
};

class Debit: public Order {
	public: 
	void checkout() override{
		receipt.insert(7,append);
		string file = receipt + ".txt";
		ofstream myFile(file);
		 myFile << "ORDER ID: " <<totalOrderCount<<" Has Been successfully checked out and paid using Debit Card."<<std::endl;

    	myFile.close();
                    cout << "\n[+] Checkout successful!\n";
                }
};

class GCash: public Order {
	public: 
	void checkout() override{
		receipt.insert(7,append);
		string file = receipt + ".txt";
		ofstream myFile(file);
		 myFile << "ORDER ID: " <<totalOrderCount<<" Has Been successfully checked out and paid using GCash."<<std::endl;

    	myFile.close();
                    cout << "\n[+] Checkout successful!\n";
                }
};

Credit credit;
Debit debit;
GCash gcash;





int main() {

    Product p1("AAA", "Hammer       ", 25, 100);
    Product p2("BBB", "Screwdriver  ", 15, 100);
    Product p3("CCC", "Wrench       ", 30, 100);
    Product p4("DDD", "Pliers       ", 20, 100);
    Product p5("EEE", "Drill        ", 50, 100);
    Product* products[] = { &p1, &p2, &p3, &p4, &p5 };
    int productCount = 5;

    ShoppingCart cart;
    Order orderHistory[10];
    int orderCount = 0;
    bool running = true;
	string input;
	bool condition = false;
    while (running) {
        cout << "\n===================";
        cout << "\n Main Menu ";
        cout << "\n===================";
        cout << "\n1. View Products\n2. View Shopping Cart\n3. View Orders\n4. Exit\nEnter choice: ";

        int choice;
         while(!condition){
                	getline(cin, input);
                	if(isDigits(input) == false || input.empty()){
                		cout<<"Error: Invalid Input. Try Again"<<endl;
                		cout<<"Input: ";
                		getline(cin,input);
					}
					else {
						condition = true;
						choice = stoi(input);
						break;
					}
					
				}
					condition = false;
        if (choice == 1) {
            displayProducts(products, productCount);
            int id, qty;
            bool addingProduct = true;
            while (addingProduct) {
                cout << "\nEnter Product ID to add to the Shopping Cart (press 0 to go back): ";
				getline(cin, input);
				input = capital(input);

                if (input == "0") {
				addingProduct = false;
                break;
                		
					}

                Product* selectedProduct = nullptr;
                for (int i = 0; i < productCount; i++) {
                    if (products[i]->productId == input) {
                        selectedProduct = products[i];
                        break;
                    }
                }

                if (!selectedProduct) {
                    cout << "\n[!] Invalid Product ID!\n";
                    continue;
                }

                cout << "Enter quantity: ";
                         while(!condition){
                	getline(cin, input);
                	if(isDigits(input) == false || input.empty()){
                		cout<<"Error: Invalid Input. Try Again"<<endl;
                		cout<<"Input: ";
                		getline(cin,input);
					}
					else {
						condition = true;
						qty = stoi(input);
						break;
					}
					
				}
					condition = false;
                
                //cin >> qty;

                if (qty <= 0 || selectedProduct->stockQuantity < qty) {
                    cout << "Error: Quantity must not exceed "<<selectedProduct->stockQuantity<<" or be below 1";
                    continue;
                }



                cart.addProduct(selectedProduct, qty);
            }
        }
        else if (choice == 2) {
            cart.displayCart();
        	cart.printTotalAmount();
            try {
            	cart.getItemCount();
			}
			catch (const char* msg){
				cout<<msg<<endl;
				continue;
			}
            
            
            if (cart.getItemCount() > 0) {
                string confirm;
                bool checkingOut = true;
                while (checkingOut) {
                    cout << "\nProceed to checkout? (Y/N): ";
                    getline(cin, confirm);
                    if (confirm == "Y" || confirm == "y" || confirm == "N" || confirm == "n") checkingOut = false;
                    else cout << "[!] Invalid input! Please enter 'Y' or 'N'.\n";
                }
                if (confirm == "Y" || confirm == "y") {
					
                	cout<<"Choose Payment Method"<<endl;
                	cout<<"[1] Credit Card"<<endl;
                	cout<<"[2] Debit Card"<<endl;
                	cout<<"[3] GCash"<<endl;
                	
                	while(!condition){
	cout<<"Input: ";
	getline(cin, input);
	if(isDigits(input) || input.empty()){
		choice = stoi(input);
		condition = true;
		break;
	}
	else{
		cout<<"Invalid Input. Input Must only be digits [1] [2] [3]"<<endl;
	}
}
	condition = false;
                	switch(choice){
                		
                		case 1: 
                		orderCount++;
                		totalOrderCount++;
                		receipt = "receipt";
                		append = to_string(totalOrderCount);
                		orderHistory[orderCount] = Order(cart);
                		cart.clearCart();
                		credit.checkout();
                		break;
                		
                		case 2: 
                		orderCount++;
                		totalOrderCount++;
                		receipt = "receipt";
                		append = to_string(totalOrderCount);
                		orderHistory[orderCount] = Order(cart);
                		cart.clearCart();
                		debit.checkout();
                		break;
                		
                		case 3:
                		orderCount++;
                		totalOrderCount++;
                		receipt = "receipt";
                		append = to_string(totalOrderCount);
                		orderHistory[orderCount] = Order(cart);
                		cart.clearCart();
                		gcash.checkout();
                		break;
					}
                	

                }
            }
        }
        else if (choice == 3) {
        	if (orderCount == 0) cout << "\n[!] No orders placed yet.\n";
            else for (int i = 1; i <= orderCount; i++) orderHistory[i].displayOrderDetails();
        }
        else if (choice == 4) {
            cout << "\nExiting Program . . .\n";
            running = false;
        }
        else cout << "\n[!] Invalid choice!\n";
    }
    return 0;
}
