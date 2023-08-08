//Code made by Md. Zunaied Nudar (2107041)

#include <bits/stdc++.h>

using namespace std;

class product
{
public:
    string name;
    int price;
    int quantity;
    product()
    {
        name = "undefined";
        quantity = 0;
        price = 0;
    }
    void set_product(string s, int x, int y)
    {
        name = s;
        quantity = x;
        price = y;
    }
    void display()
    {
        cout << setw(30) << left << name << setw(30) << left << quantity << setw(30) << left << price << endl;
    }
};

class brand
{
    int j, total;
    product p[100];
public:
    string b_name;
    brand()
    {
        b_name = "undefined";
        j = 0;
        total = 0;
    }
    void set_brand(string name)
    {
        b_name = name;
    }
    void add_product(string s, int x, int y)
    {
        int ok;
        for(int l = 0; l < total; l++)
        {
            if(p[l].name == s)
            {
                p[l].quantity += x;
                ok = 1;
            }
        }
        if(ok != 1)
        {
            p[j].set_product(s, x, y);
            j++;
            total++;
        }
        ok = 0;
    }
    int del_product(string s, int x, int type)
    {
        int ok;
        for(int l = 0; l < total; l++)
        {
            if(p[l].name == s)
            {
                if(p[l].quantity >= x)
                {
                    p[l].quantity -= x;
                    ok = 1;
                }
                else if(p[l].quantity < x && type == 0)
                {
                    p[l].quantity = 0;
                    ok = 1;
                }
            }
        }
        if(ok != 1)
        {
            if(type == 0)
                cout << "Product out of stock/insufficient" << endl;
            else cout << "Product quantity exceeded the stock\nCheck the available stock and try again..." << endl;
            return 0;
        }
    }
    int product_search(string name)
    {
        for(int k = 0; k < total; k++)
        {
            if(p[k].name == name)
            {
                return p[k].price;
            }
        }
    }
    int product_search2(string name)
    {
        for(int k = 0; k < total; k++)
        {
            if(p[k].name == name)
            {
                return 1;
            }
        }
        return 0;
    }
    void brand_display()
    {
        cout << endl;
        cout << setw(15) << left << "BRAND NAME: " << b_name << endl;
        cout << setw(15) << left << "-----------" << endl << endl;
        cout << setw(30) << left << "PRODUCT NAME" << setw(30) << left << "QUANTITY" << setw(30) << left <<  "PRICE" << endl;
        cout << setw(30) << left << "=============" << setw(30) << left << "========" << setw(30) << left << "======" << endl;
        for (int i = 0; i < total; i++)
        {
            p[i].display();
        }
    }
};

class customer;

class bill
{
    int i;
    int total;
    int total_spent;
    string brand[1000];
    string product[1000];
    int quantity[1000];
    int price[1000];
public:
    bill()
    {
        i = 0;
        total = 0;
        total_spent = 0;
    }
    void add_to_bill(string b, string p, int q, int a)
    {
        int ok;
        for(int n = 0; n < total; n++)
        {
            if(brand[n] == b && product[n] == p)
            {
                quantity[n] += q;
                ok = 1;
            }
        }
        if(ok != 1)
        {
            brand[i] = b;
            product[i] = p;
            quantity[i] = q;
            price[i] = q * a;
            i++;
            total++;
            total_spent += q * a;
        }
    }
    void show_bill()
    {
        for(int j = 0; j < total; j++)
        {
            cout << setw(30) << left << brand[j] << setw(30) << left << product[j] << setw(30) << left << quantity[j] << setw(30) << right << price[j] << endl << endl;
        }
    }
    friend int shipment(bill b, customer c);
};

class customer_record;

class customer : public bill
{
    string name;
    string address;
    int charge;
    int total_cost;
public:
    customer()
    {
        name = "undefined";
        address = "undefined";
        charge = 0;
        total_cost = 0;
    }
    void set_value(string na, string add, int c)
    {
        name = na;
        address = add;
        charge = c;
    }
    void update_totalcost(int x)
    {
        total_cost = x;
    }
    friend int shipment(bill b, customer c);
    friend void add_customer(customer_record &cu, customer &obj);
};

class customer_record
{
    static int p;
    string c_name[100];
    string c_address[100];
    int total_cost[100];
public:
    friend void add_customer(customer_record &cu, customer &obj)
    {
        cu.c_name[p] = obj.name;
        cu.c_address[p] = obj.address;
        cu.total_cost[p] = obj.total_cost;
        p++;
    }
    void display()
    {
        for(int k = 0; k < p; k++)
        {
            cout << setw(30) << left << c_name[k] << setw(30) << left << c_address[k] << setw(30) << left << total_cost[k] << endl;
        }
    }
};

int customer_record :: p = 0;

class payment
{
    static int order_no;
public:
    int set_value()
    {
        order_no++;
        return order_no;
    }
    int set_value(int mobile, int password)
    {
        order_no++;
        if(mobile != 0 && password != 0)
            return order_no;
    }
};

int payment :: order_no = 0;

int shipment(bill b, customer c)
{
    string a;
    a = c.address;
    a[0] -= 32;
    cout << "CUSTOMER NAME: " << c.name << endl;
    cout << "BILLING ADDRESS: " << a << endl << "\n";
    cout << setw(30) << left << "BRAND" << setw(30) << left << "PRODUCT" << setw(30) << left << "QUANTITY" << setw(30) << right << "PRICE" << endl << endl;
    cout << setw(30) << left << "=====" << setw(30) << left << "=======" << setw(30) << left << "========" << setw(30) << right << "=====" << endl << endl;
    b.show_bill();
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;
    cout << setw(30) << left << "TOTAL COST:" << setw(90) << right << b.total_spent << endl << endl;
    cout << setw(30) << left << "DELIVERY CHARGE:" << setw(90) << right << c.charge << endl << endl;
    c.total_cost = c.charge + b.total_spent;
    cout << endl;
    cout << setw(30) << left << "FINAL COST:" << setw(90) << right << c.total_cost << endl;
    return c.total_cost;
}

int main()
{
    map <string, int> m;
    m["mym"] = 100;
    m["dha"] = 50;
    m["bar"] = 70;
    m["cha"] = 80;
    m["khu"] = 60;
    m["raj"] = 90;
    m["ran"] = 65;
    m["syl"] = 75;
    string password, owner_password = "owner123";
    brand b[100];
    customer c[20];
    payment bikash, nagad, cod, due;
    customer_record cu;
    int i, n, k = 0, password_check = 0, total = 0;
    while(k < 100)
    {
        bill bi;
        bool choice;
        string decision, addproduct, buyproduct,delproduct;
        cout << "Please select: " << endl;
        cout << "0. Owner\n1. Buyer" << endl;
        cin >> choice;

        i = 0;
        n = 0;
        while (!choice)
        {
            string brand, product;
            int quantity, price;
            if(i == 0 || password_check != 1)
            {
                cout << "Enter your password: ";
                cin >> password;
            }
            if(password != owner_password)
            {
                cout << "Password invalid!" << endl;
                cout << "Please select again: " << endl;
                cout << "0. Owner\n1. Buyer" << endl;
                cin >> choice;
                continue;
            }
            else password_check = 1;
            if (i == 0) cout << "Do you want to store products?(y/n)" << endl;
            else cout << "Do you want to store more products?(y/n)" << endl;
            cin >> decision;
            if (decision == "y")
            {
                cout << "State brand name: ";
                cin >> brand;
                b[i].set_brand(brand);
                addproduct = "y";
                while (addproduct == "y")
                {
                    int availability = 0;
                    cout << "State product name: ";
                    cin >> product;
                    availability = b[i].product_search2(product);
                    if(availability == 0)
                    {
                        cout << "State the standard price of this product: ";
                        cin >> price;
                    }
                    cout << "State quantity: ";
                    cin >> quantity;
                    b[i].add_product(product, quantity, price);
                    cout << "Do you want to add more products of this brand?(y/n)" << endl;
                    cin >> addproduct;
                }
                i++;
                total++;
            }
            else
            {
                int in;
                if (n == 0) cout << "Do you want to delete products?(y/n)" << endl;
                else cout << "Do you want to delete more products?(y/n)" << endl;
                cin >> decision;
                if(decision == "y")
                {
                    cout << "Which brand of product do you want to delete?" << endl;
                    cin >> brand;
                    for(int m = 0; m < 100; m++)
                    {
                        if(b[m].b_name == brand)
                        {
                            in = m;
                            break;
                        }
                    }
                    delproduct = "y";
                    while(delproduct == "y")
                    {
                        cout << "State product name: " << endl;
                        cin >> product;
                        cout << "State quantity: " << endl;
                        cin >> quantity;
                        b[in].del_product(product, quantity, 0);
                        cout << "Do you want to delete more products from the same brand?(y/n)" << endl;
                        cin >> delproduct;
                    }
                    n++;
                }
                else
                {
                    cout << "Please select again: " << endl;
                    cout << "0. Owner\n1. Buyer" << endl;
                    cin >> choice;
                }
            }

        }
        string name, address, substring;
        int charge, method = 0, mobile, password, order_no;
        cout << setw(120) << "___Products available for purchase___" << endl << endl;
        cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
        for (int k = 0; k < total; k++)
        {
            b[k].brand_display();
        }
        cout << endl << endl;
        i = 0;
        decision = "y";
        while(decision == "y")
        {
            int index, availability;
            string brand, product;
            int quantity, price;
            cout << "State the brand of product that you want to buy: " << endl;
            cin >> brand;
            for(int m = 0; m < 100; m++)
            {
                if(b[m].b_name == brand)
                {
                    index = m;
                    break;
                }
            }
            buyproduct = "y";
            while(buyproduct == "y")
            {
                cout << "State the product name: " << endl;
                cin >> product;
                cout << "State the quantity: " << endl;
                cin >> quantity;
                price = b[i].product_search(product);
                availability = b[index].del_product(product, quantity, 1);
                if(availability) bi.add_to_bill(brand, product, quantity, price);
                cout << "Do you want to buy more products from this brand?(y/n)" << endl;
                cin >> buyproduct;
            }
            cout << "Do you want to buy more?(y/n)" << endl;
            cin >> decision;
        }
        cout << endl;
        cout << "Please enter your information below: " << endl;
        cout << "Name: " << endl;
        cin >> name;
        cout << "Location(small letters only): ";
        cin >> address;
        string payment;
        while(!method)
        {
            cout << endl;
            cout << "Select payment method:\n1.Bikash\n2.Nagad\n3.Cash On Delivery\n4.Exit" << endl;
            cin >> method;
            if(method == 1)
            {
                cout << "Enter you Bikash mobile number: " << endl;
                cin >> mobile;
                cout << "Enter the password: " << endl;
                cin >> password;
                order_no = bikash.set_value(mobile, password);
                payment = "Bikash";
            }
            else if(method == 2)
            {
                cout << "Enter you Nagad mobile number: " << endl;
                cin >> mobile;
                cout << "Enter the password: " << endl;
                cin >> password;
                order_no = nagad.set_value(mobile, password);
                payment = "Nagad";
            }
            else if(method == 3)
            {
                order_no = cod.set_value();
                payment = "Cash On Delivery";
            }
            else if(method == 4)
            {
                order_no = due.set_value();
                payment = "Due";
            }
            else
            {
                method = 0;
                cout << "Try again!" << endl;
            }
        }
        substring = address.substr(0, 3);
        charge = m[substring];
        c[k].set_value(name, address, charge);
        cout << endl << endl << endl;
        cout << "Your Bill" << endl;
        cout << "-------------------" << endl;
        int y = shipment(bi, c[k]);
        c[k].update_totalcost(y);
        cout << endl;
        cout << "Payment method: " << payment << endl;
        cout << "Order No: " << order_no << endl;
        add_customer(cu, c[k]);
        k++;
        cout << endl << endl;
        cout << "Customer " << k << " is leaving..." << endl;
        cout << endl;
    }
    cout << "Customer record: " << endl << endl;
    cout << setw(30) << left << "Name" << setw(30) << left << "Address" << setw(30) << left << "Total" << endl;
    cout << setw(30) << left << "====" << setw(30) << left << "========" << setw(30) << left << "=====" << endl;
    cu.display();
    return 0;
}
