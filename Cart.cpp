#include<iostream>
#include<vector>
#include<stdexcept>
using namespace std;
//Lớp sản phẩm
class Product{
public:    
    string name;
    double price;
    int quantity;

    Product(string name,double price,int quantity){
        this->name = name;
        this->price = price;
        this->quantity= quantity;
    }
};
//Lớp giỏ hàng
class Cart {
private:
    vector<Product> products;
    int capacity; //Số lượng tối đa sản phẩm trong giỏ hàng
public:
    Cart(int capacity){
        this->capacity=capacity;
    }
     // Thêm sản phẩm vào giỏ hàng
    void addToCart(const Product& product){
        if(products.size()>=capacity){
            throw overflow_error("Giỏ hàng đã đầy! :_)");
        }
        products.push_back(product);
    }
//Tính tổng tiền trong giỏ hàng
double TotalPrice(){
    double total= 0.0;
    for(const Product& product : products){
         total += product.price * product.quantity;
    }
    return total;
}
// Kiểm tra số mặt hàng trong giỏ hàng
    int getItemCount() {
        return products.size();
    }
    //Xóa rỗng giỏ hàng 
    void emptyCart() {
        products.clear();
    }
    // xóa rỗng bất kỳ một sản phẩm
    void removeProduct(const string& productName){
       for (auto it = products.begin(); it != products.end(); ++it) {
            if (it->name == productName) {
                products.erase(it);
                return;
            }
        }
    }
    //Mua sản phẩm với số lượng xác đinh
    void buyProduct(const string& productName, int quantityToBuy) {
        for (Product& product : products) {
            if (product.name == productName) {
                if (quantityToBuy <= 0 || quantityToBuy > product.quantity) {
                    throw invalid_argument("Số lượng mua không hợp lệ ! ");
                }
                product.quantity -= quantityToBuy;
                return;
            }
        }
        throw invalid_argument("Sản phẩm không tồn tại trong giỏ hàng !");
    
    }
};
int main(){
     Cart cart(100); // Giỏ hàng có sức chứa tối đa là 100 sản phẩm

    try{
       
        Product product1("Sản phẩm 1",10.0,20);
        Product product2("Sản phẩm 2",5.0,10);
        Product product3("Sản phẩm 3",20.0,35);
        cart.addToCart(product1);
        cart.addToCart(product2);
        cart.addToCart(product3);
        cout<<"Tổng số tiền trong giỏ hàng: "<<cart.TotalPrice()<<endl;
        cout << "Số mặt hàng trong giỏ hàng: " << cart.getItemCount() << endl;
         // Nhập số lượng sản phẩm mua
        int quantityToBuy;
        cout << "Nhập số lượng sản phẩm muốn mua cho 'Sản phẩm 1': ";
        cin >> quantityToBuy;
        cart.buyProduct("Sản phẩm 1", quantityToBuy);
        cout << "Tổng tiền sau khi mua: " << cart.TotalPrice() << endl;
        cout << "Số mặt hàng sau khi mua: " << cart.getItemCount() << endl;
        cart.removeProduct("Sản phẩm 2");

        cout << "Số mặt hàng sau khi xóa: " << cart.getItemCount() << endl;

        cart.emptyCart();  
         cout << "Số mặt hàng sau khi xóa rỗng giỏ hàng: " << cart.getItemCount() << endl;  
    } catch (const exception& e) {
        cerr << "Lỗi: " << e.what() << endl;
    } 
    return 0;
}