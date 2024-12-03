#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "TableEntry.h"

#include "../practica1/PRA_2324_P1/ListLinked.h"

template <typename V>
class HashTable: public Dict<V>{
	private:
		int n;
		int max;
		ListLinked<TableEntry<V>>* table;
		int h(std::string key){
			int sum = 0;
			for (size_t i = 0; i < key.size(); ++i) {
				sum += static_cast<int>(key.at(i));
			}
        		return sum % max; 
		}
	public:
		HashTable(int size): n(0),max(size){
			table = new ListLinked<TableEntry<V>>[max];
		}
		~HashTable(){
			delete[] table;
		}
		int capacity(){
			return max;
		}
		
		void insert(std::string key, V value) override {
			int index = h(key);
			TableEntry<V> entry(key, value);
			if (table[index].contains(entry)) {
				throw std::runtime_error("Key ya existe");
			}
			table[index].insert(entry);
			n++;
		}

		V search(std::string key) override {
			int index = h(key);
			TableEntry<V> searchEntry(key);
			if (!table[index].contains(searchEntry)) {
				throw std::runtime_error("No se ha encontrado key");
			}
			return table[index].find(searchEntry).value;
		}

		V remove(std::string key) override {
			int index = h(key);
			TableEntry<V> searchEntry(key);
			if (!table[index].contains(searchEntry)) {
				throw std::runtime_error("No se ha encontrado key");
			}
			V value = table[index].find(searchEntry).value;
			table[index].remove(searchEntry);
			n--;
			return value;
		}

		int entries() override {
			return n;
		}

		friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th){
			for (int i = 0; i < th.max; ++i) {
            			out << "Cubeta " << i << ": ";
        			out << th.table[i] << "\n";
			}
			return out;
		}
		V operator[](std::string key){
			try {
     				return search(key);
			} catch (const std::runtime_error& e) {
        			throw std::runtime_error("Key no exixte");
    			}
		}




};
#endif
