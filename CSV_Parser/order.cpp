#pragma once
#include "order.h"
#include "util.h"
#include <iostream>


Order::Order(vector<string>& row) { //default slot

	try {

		if (row.size() < 3) {
			throw string("expected 4 or 5 fields, found ") + to_string(row.size());
		}

		//   string orderCustomer, orderProduct;
		if (OrderNameValid(row[0])) { orderCustomer = row[0]; }
		else { throw string("Invalid Order Name: ") + (row[0]); }

		if (OrderNameValid(row[1])) { orderProduct = row[1]; }
		else { throw string("Invalid Order Product: ") + (row[1]); }

		// Rest of fields append to orderlist.
		for (size_t i = 2; i < row.size(); i++) {
		   if (OrderNameValid(row[i])) { OrderItems.push_back(row[i]); }
         else { throw string("Invalid Item Name: ") + (row[i]); }
		}
		
	}
	catch (string& error) {
		cout << "Error: " << error << endl;
	}

}//Task Constructor


void Order::OrderPrint() {
   cout << "Customer: " << orderCustomer << " > ";
   cout << "Product: " << orderProduct << " > ";
}

//could add colors also function is written differently for Order
void Order::OrderGraph(fstream& os) {

   if (!orderCustomer.empty()) {
      os << orderCustomer << "->" << orderProduct << "[color=green];\n";
   }
   //add more ordergraph logic? needs visual testing

}

void Order::validOrder(ItemManager& IM) {
   //Loop through every item in an order and confirm that it exits in item manager csv data

   for (size_t i = 0; i < OrderItems.size(); i++) { //iterator for order item index
      if( !IM.ItemExists(OrderItems[i]) ){ //if an item in order is not in item list, report an error
         cout << "Order referenced Item: " << OrderItems[i] << " but it is not in Item Manager \n";
      }
   }

}


//Task manager

OrderManager::OrderManager(std::vector <std::vector<std::string> >& csv) {
   int lineNumber = 0;

   for (auto row : csv) { //copy over over csv data
      try {
         lineNumber++; // to detect errors
         OrderList.push_back(move(Order(row)));
      }
      catch (string& e) {
         cerr << e << "error in line " << lineNumber << "\n";
      }
   }
}

OrderManager::~OrderManager() {}

void OrderManager::OrderPrint() {
   int taskNumber = 0;
   for (auto t : OrderList) {
      taskNumber++;
      cout << "Order " << taskNumber << " ";
      t.OrderPrint(); // Runs t auto type of [order] vector, so runs order print here not order manager's print 
      cout << "\n"; //Not placed here intially, more readable
   }
}

void OrderManager::OrderGraph(string& filename) {
	fstream os(filename + ".gv", ios::out);
	os << "digraph DG {\n";

	for (auto o : OrderList) {
		o.OrderGraph(os);
	}

	os << "};\n";
	os.close();
   //string cmd = string("dot - Tpng ") + filename + ".gv >" + filename + ".gv.png";
   //system(cmd.c_str); // for graph wizz api your using later
}

void OrderManager::IntegrityCheck(ItemManager& IM) {
   try { // For every OrderItems[i] in a order, compare if duplicate itemname exists within IM itemlist vector [ IN STOCK? ]
      for (size_t i = 0; i < OrderList.size(); i++) {
         OrderList[i].validOrder(IM); //if an ordered item is not found in item manager, report an error
      }
   }
   catch(string& e) { cout << "Error: " << e << "\n"; }
   

}//CustomerOrder data - ensure all of the items ordered exist.
