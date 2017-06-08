#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include "item.h"
using namespace std;

class Order {

   string orderCustomer, orderProduct;
   
   vector<std::string>OrderItems; //stores items being ordered per customer

public:

   Order(vector<string>& row);

   Order() {};

   ~Order() {};

   void OrderPrint();

   void OrderGraph(fstream& os);

   //put getters here for order find and integrity
   string& getOrderName(){ return orderCustomer; };
   std::string& getOrderProduct() { return orderProduct; };

   void validOrder(ItemManager& IM); //Like TaskFind but moved to Order instead of manager

   size_t getSize() { return OrderItems.size(); };
   string& getItem(size_t i) { return OrderItems[i]; }

};

class OrderManager {

   vector<Order>OrderList;//Holds vector of customer names and their products 
  

public:

   OrderManager(std::vector <std::vector<std::string> >& csv);

   ~OrderManager();

   void OrderPrint();

   void OrderGraph(string& filename);

   void IntegrityCheck(ItemManager& IM);

   size_t getSize() { return OrderList.size(); };
   Order* getOrder(size_t i) { return &OrderList[i]; }

}; //Order manager
