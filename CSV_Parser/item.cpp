
#pragma once
#include <iostream>
#include "item.h"
#include "util.h"
#include "task.h"

Item::Item(vector<string>& row) { //default slot

	try {
		switch ( row.size()) {

		case 5:
			itemDescription = row[4]; //Some items might come with a description - OPTIONAL

		case 4: //if 4 fields are in a row, the 4th is the Itemfail 
			if (ItemSlotValid(row[3]))
				itemSequence = row[3];
			else
				throw string("expected fail Item name, found ") + row[3];

			//case 3: //if name valid repeat same func
			if (ItemNameValid(row[2]))
				itemRemover = row[2];
			else
				throw string("expected Accept Item name, found ") + row[3];

			//case 2: //if Item slot valid, else throw
			if (ItemNameValid(row[1]))
				itemInstaller = row[1];
			else
				throw string("expected slot Item number, found ") + row[3];

			//case 1: // if name valid, else throw string
			if (ItemNameValid(row[0]))
				itemName = row[0];
			else
				throw string("expected Item name, found ") + row[3];

			break;

		default:

			throw string("expected 5 fields, found") + to_string(row.size());
		}//switch

	}

	catch (string& error) {
		cout << "Error: " << error << endl;
	}

}//Item Constructor


void Item::ItemPrint() {
   cout << "ItemName: " << itemName << " > ";
   cout << "ItemInstaller: " << itemInstaller << " > ";
   cout << "ItemRemover: " << itemRemover << " > ";
   cout << "ItemSequence: " << itemSequence << " > ";
   cout << "ItemDescription: " << itemDescription << " >";
}


//could add colors also function is written differently for item
void Item::ItemGraph(fstream& os) {

   if (!itemSequence.empty()) {
      os << itemName << "->" << itemInstaller << "[color=green];\n";
   }

   if (!itemRemover.empty()) {
      os << itemName << "->" << itemRemover << "[color=red];\n";
   }

   if (itemSequence.empty() && itemRemover.empty()) {
      os << itemName << "[shape=box];\n";
   }
}

//Item manager

ItemManager::ItemManager(){//to initiliaze item manager object in order before feeding it csvitem
};

ItemManager::ItemManager(std::vector <std::vector<std::string> >& csv) {
   int lineNumber = 0;
   for (auto row : csv) {
      try {
         lineNumber++; // to detect errors
         ItemList.push_back(move(Item(row)));
      }
      catch (string& e) {
         cerr << e << "error in line " << lineNumber << "\n";
      }
   }
}

ItemManager::~ItemManager() {}

void ItemManager::ItemPrint() {
   int ItemNumber = 0;
   for (auto t : ItemList) {
      ItemNumber++;
      cout << "Item " << ItemNumber << " ";
      t.ItemPrint();
      cout << "\n"; //Not placed here intially, more readable
   }
}

void ItemManager::ItemGraph(string& filename) {
	fstream os(filename + ".gv", ios::out);
	os << "digraph DG {\n";

	for (auto i : ItemList) {
		i.ItemGraph(os);
	}

	os << "};\n";
	os.close();
   //string cmd = string("dot - Tpng ") + filename + ".gv >" + filename + ".gv.png";
   //system(cmd.c_str); // for graph wizz api your using later
}

Item* ItemManager::ItemFind(std::string name) { 
   for (size_t i = 0; i < ItemList.size(); i++) {
      if (ItemList[i].getItemName() == name) {
         return &ItemList[i]; //if something matches the first field of item name, it will return an address
      }
   }
   return nullptr; //not found
};

void ItemManager::IntegrityCheck(TaskManager& TM , bool& ok) {
   for (auto t : ItemList) {
      
      try { //if an item references an installer/remover - cross reference tasklist that it exists
         if (!t.getItemInstaller().empty() && TM.TaskFind(t.getItemInstaller()) == nullptr) {
            ok = false;
            throw string("Item '") + t.getItemName() + "' referenced Item Installer '" + t.getItemInstaller() + "' but it does not exist";
         }

         if (!t.getItemRemover().empty() && TM.TaskFind(t.getItemRemover()) == nullptr) {
            ok = false;
            throw string("Item ") + t.getItemName() + "' referenced Item Remover '" + t.getItemRemover() + "' but it does not exist";
         }
      }
      catch (string& e) { cout << "Error: " << e << "\n"; }
   }
}//Item data - ensure all install and remove task references exist.

//Takes a string and sees if such item is listed in itemslist
bool ItemManager::ItemExists(string& Item) {
   for (size_t i = 0; i < ItemList.size(); i++) {
      if (Item == ItemList[i].getItemName()) {
         return true;
      }
   }
   return false;
}