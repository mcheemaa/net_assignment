#include "bakery.hpp"
#include <fstream>
#include <iostream>

void print_bakery(const Bakery& bakery) {
  std::cout << "Employees: " << std::endl;
  for (auto employee : bakery.employees) {
    std::cout << employee << std::endl;
  }

  std::cout << std::endl;
  std::cout << "Items: " << std::endl;
  for (auto item : bakery.items) {
    std::cout << item.name << ", " << item.price << std::endl;
  }

  std::cout << std::endl;
  std::cout << "Orders: " << std::endl;
  for (auto order : bakery.orders) {
    std::cout << order.employee << ": ";
    auto j = 0;
    for (auto item : order.items) {
      std::cout << item.second << " " << item.first;
      j++;
      if (size_t(j) < order.items.size())
        std::cout << ", ";
    }
    std::cout << std::endl;
  }
}

// You shouldn't need to edit this function (unless you want!)
Bakery text_deserializer(std::string file_path) {
  std::ifstream infile(file_path);
  std::string line;
  Bakery bakery;

  while (!infile.eof()) {
    // Employees section
    if (line.compare("@employees") == 0) {
      std::getline(infile, line);
      while (line.size() > 0) {
        bakery.employees.push_back(line);
        std::getline(infile, line);
      }
    }

    // Items section
    if (line.compare("@items") == 0) {
      std::getline(infile, line);
      while (line.size() > 0) {
        auto end = line.find(", ");
        Item item;
        item.name = line.substr(0, end);
        item.price = line.substr(end + 2);
        bakery.items.push_back(item);
        std::getline(infile, line);
      }
    }

    // Orders section
    if (line.compare("@orders") == 0) {
      std::getline(infile, line);
      auto e = bakery.employees;
      while (line.size() > 0) {
        Order order;
        auto end = line.find(": ");
        order.employee = line.substr(0, end);

        // Find all the orders
        auto rest = line.substr(end + 2);
        size_t pos = 0;
        std::string token;
        while ((pos = rest.find(", ")) != std::string::npos) {
          token = rest.substr(0, pos);
          end = token.find(" ");
          auto quantity = token.substr(0, end);
          auto item_name = token.substr(end + 1);
          order.items.push_back(std::make_pair(item_name, quantity));
          rest.erase(0, pos + 2);
        }
        end = rest.find(" ");
        auto quantity = rest.substr(0, end);
        auto item_name = rest.substr(end + 1);
        order.items.push_back(std::make_pair(item_name, quantity));
        bakery.orders.push_back(order);

        // no more lines to read
        if (infile.eof())
          break;

        std::getline(infile, line);
      }
    }

    std::getline(infile, line);
  }

  return bakery;
}

// Implement these 3 functions!
// Hint: use print_bakery to help think about the text serializer
void text_serializer(const Bakery& bakery, std::string file_path){

  std::ofstream outfile;
  outfile.open(file_path);   


  outfile << "@employees: " << std::endl;
  for (auto employee : bakery.employees) {
    outfile << employee << std::endl;
  }

  outfile << std::endl;

  outfile << "@items: " << std::endl;
  for (auto item : bakery.items) {
    outfile << item.name << ", " << item.price << std::endl;
  }

  outfile << std::endl;
  outfile << "@orders: " << std::endl;
  for (auto order : bakery.orders) {
    outfile << order.employee << ": ";
    auto j = 0;
    for (auto item : order.items) {
      outfile << item.second << " " << item.first;
      j++;
      if (size_t(j) < order.items.size())
        outfile << ", ";
    }
    outfile << std::endl;
  }

  outfile.close();
}

void binary_serializer(const Bakery& bakery, std::string file_path){

  std::ofstream outfile;
  outfile.open(file_path, std::ios::out | std::ios::binary);
  //std::string newLine = "\n";
  unsigned int s = 1;

  
  //std::string t = "@employees: ";
  //outfile.write((char*) &t, t.length());
  for (auto employee : bakery.employees) {
    unsigned int size  = employee.length();
    std::cout << size << std::endl;
    
    //outfile.write( (char*)( &size ), sizeof( size ) );
    outfile.write( employee.c_str(), employee.size() );
    //outfile.write( (char*)( &s ), sizeof( s ) );
   
  }
  
  //outfile.write((char*) &newLine, sizeof(newLine)) ;
  //std::string i = "@items: ";
  //outfile.write((char*) &i, sizeof(i));
  //outfile << "@items: " << std::endl;
  for (auto item : bakery.items) {

    std::string item_name = item.name;
    std::string item_price = item.price;
    std::string fin = item_name + item.price;
    unsigned int size  = fin.length();

      
    //outfile.write((char*) (&size), sizeof(size));
    outfile.write( fin.c_str(), fin.size() );
    //outfile.write( (char*)( &s ), sizeof( s ) );
    //outfile << item.name << ", " << item.price << std::endl;
  }

  //outfile.write((char*) &newLine, sizeof(newLine)) ;
  //std::string o = "@orders: ";
  //outfile.write((char*) &o, sizeof(o));
  for (auto order : bakery.orders) {
    std::string empl =  order.employee;
    unsigned int size  = empl.length();

    //outfile.write((char*) (&size), sizeof(size));
    outfile.write( empl.c_str(), empl.size() );
    //utfile.write( (char*)( &s ), sizeof( s ) );

    //outfile.write((char*) &empl, sizeof(empl));
    //outfile << order.employee << ": ";

    auto j = 0;
    for (auto item : order.items) {
      
      std::string item_first = item.first;
      std::string item_second = item.second;
      std::string fina = item_second + item.first;
      unsigned int size  = fina.length();

      //outfile.write((char*) (&size), sizeof(size));
      outfile.write( fina.c_str(), fina.size() );
      //outfile.write( (char*)( &s ), sizeof( s ) );

      //outfile.write((char*) &fina, sizeof(fina));
      //outfile << item.second << " " << item.first;
      
      //j++;
      //if (size_t(j) < order.items.size()){
        //std::string chia =  ", ";
        //unsigned int size  = chia.length();

        //outfile.write((char*) & chia, sizeof(chia));

        //outfile.write((char*) (&size), sizeof(size));
        //outfile.write( chia.c_str(), chia.length() );
        //outfile.write( (char*)( &s ), sizeof( s ) );
        //outfile << ", ";
      //}
    //outfile.write((char*) &newLine, sizeof(newLine)) ;
    //}
    }
  }
  outfile.close();
}


Bakery binary_deserializer(std::string file_path) {

  std::ifstream infile;
  infile.open(file_path, std::ios::in | std::ios::binary);
  unsigned int s;
  unsigned int size;
  std::string line;
  Bakery bakery;

  std::string ref;

  
  while (!infile.eof()) {
    // Employees sectio
    
    infile.read( (char*)( &size ), sizeof( size ) );
    ref.resize(size);
    infile.read ( (char*) ref.c_str(), size);
    infile.read((char*) (&s), sizeof(s));
    std::cout << ref << std::endl;
  }

  infile.close();

  

}

