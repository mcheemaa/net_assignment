#include <chrono>
#include <iostream>
#include "../include/bakery.hpp"
using namespace std::chrono;

int main() {
  auto start = high_resolution_clock::now();
  auto bakery = text_deserializer("../data/small.txt");
  auto deser_time = high_resolution_clock::now() - start;
  std::cout << "Text deserializer took: "
            << duration_cast<milliseconds>(deser_time).count() << "ms"
            << std::endl
            << std::endl;
  print_bakery(bakery);

  start = high_resolution_clock::now();
  text_serializer(bakery, "../data/t_s_c.txt");
  deser_time = high_resolution_clock::now() - start;
  std::cout << "Text serializer took: "
            << duration_cast<milliseconds>(deser_time).count() << "ms"
            << std::endl
            << std::endl;



  start = high_resolution_clock::now();
  binary_serializer(bakery, "../data/b_s_c.bin");
  deser_time = high_resolution_clock::now() - start;
  std::cout << "Binary serializer took: "
            << duration_cast<milliseconds>(deser_time).count() << "ms"
            << std::endl
            << std::endl;


  bakery = binary_deserializer("../data/b_s_c.bin");




  return 0;
}

