
#include <Common.h>

int main ()
{
  size_t nelem (5);

  std::cout << "\n[1] Testing operator<<(std::vector<T>)\n" << std::endl;
  {
    std::vector<bool> vec_bool (nelem);
    std::vector<int> vec_int (nelem);
    std::vector<long> vec_long (nelem);
    std::vector<short> vec_short (nelem);
    std::vector<float> vec_float (nelem);
    std::vector<double> vec_double (nelem);
    
    std::cout << "-- vector<bool>   = " << vec_bool   << std::endl;
    std::cout << "-- vector<int>    = " << vec_int    << std::endl;
    std::cout << "-- vector<long>   = " << vec_long   << std::endl;
    std::cout << "-- vector<short>  = " << vec_short  << std::endl;
    std::cout << "-- vector<float>  = " << vec_float  << std::endl;
    std::cout << "-- vector<double> = " << vec_double << std::endl;
  }
  
  std::cout << "\n[2] Testing operator<<(std::set<T>)\n" << std::endl;
  {
    bool array_bool[] = {true,false,true,false,true};
    std::set<bool> set_bool (&array_bool[0], &array_bool[5]);
    //
    int array_int[] = {0,1,2,3,4};
    std::set<int> set_int (&array_int[0], &array_int[5]);
    //
    long array_long[] = {0,1,2,3,4};
    std::set<long> set_long (&array_long[0], &array_long[5]);
    //
    short array_short[] = {0,1,2,3,4};
    std::set<short> set_short (&array_short[0], &array_short[5]);
    //
    float array_float[] = {0.0,0.1,0.2,0.3,0.4};
    std::set<float> set_float (&array_float[0], &array_float[5]);
    //
    double array_double[] = {0.1,0.12,0.123,0.1234,0.12345};
    std::set<double> set_double (&array_double[0], &array_double[5]);
    //
    std::string array_string[] = {"a","b","c","d","e"};
    std::set<std::string> set_string (&array_string[0], &array_string[5]);
    
    std::cout << "-- set<bool>   = " << set_bool   << std::endl;
    std::cout << "-- set<int>    = " << set_int    << std::endl;
    std::cout << "-- set<long>   = " << set_long   << std::endl;
    std::cout << "-- set<short>  = " << set_short  << std::endl;
    std::cout << "-- set<float>  = " << set_float  << std::endl;
    std::cout << "-- set<double> = " << set_double << std::endl;
    std::cout << "-- set<string> = " << set_string << std::endl;
  }

  // std::cout << "\n[3] Testing operator<<(std::map<T,S>)\n" << std::endl;
  // {
  //   std::map<int,std::string> mapIntString;
  //   mapIntString[0] = "Hello";
  //   mapIntString[1] = "World";

  //   std::cout << "-- map<int,string> = " << mapIntString << std::endl;
  // }
  
  return 0;
}
