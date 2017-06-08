#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include "task.h"

using namespace std;

class Item {

   string itemName, itemInstaller, itemRemover, itemDescription, itemSequence;

public:

   Item(vector<string>& row);
   ~Item() {};
   void ItemPrint();
   void ItemGraph(fstream& os);

   //getters for find/integrity
   string& getItemName(){ return itemName; };
   string& getItemInstaller() { return itemInstaller; };
   string& getItemRemover() { return itemRemover; };

};

class ItemManager {

   vector<Item> ItemList;

public:

   ItemManager(); 
   ItemManager(std::vector <std::vector<std::string> >& csv);
   ~ItemManager();

   void ItemPrint();

   void ItemGraph(string& filename);

   Item* ItemFind(std::string name);

   void IntegrityCheck(TaskManager& TM, bool& ok);

   bool ItemExists(string& Item);

   size_t getSize() { return ItemList.size(); }

   Item* getItem(int index) {
      return &ItemList[index];
   }

}; //Item manager

