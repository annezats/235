#include <iostream>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <sys/time.h>
#include <math.h>

int find_min(std::vector<int> a, int start_index, int stop_index){
  int min_index = start_index;
  int i;
  for (i = start_index; i < stop_index; i++){
    if (a[i] < a[min_index])
      min_index = i;
  }
  return min_index;
}

std::vector<int> ssort(std::vector<int> a){

  int i,j;
  int l = a.size();
  int min_index;

  for (i = 0; i < l; ++i) {
    min_index = find_min(a,i,l);
    int tmp = a[i];
    a[i] = a[min_index];
    a[min_index] = tmp;
  } 
  return a;
}

  
void print_vector(std::vector<int> a){
  for (int i = 0; i < a.size(); ++i) {
    std::cout << a[i] << ", ";;
  }
  std::cout << "\n";
}

std::vector<int> merge(std::vector<int> a, std::vector<int> b){
  int ai=0;
  int bi=0;
  std::vector<int> result;
  while(ai<a.size() && bi<b.size()){
    if (a[ai] < b[bi]){
      result.push_back(a[ai]);
      ai++;
    } else {
      result.push_back(b[bi]);
      bi++;
    }
  }
  // we know we finished one list, a or b but the
  // other will still have at least one element on it.

  while (ai < a.size()){
    result.push_back(a[ai]);
    ai++;
  }

  while (bi < b.size()){
    result.push_back(b[bi]);
    bi++;
  }
  return result;
}

std::vector<int> msort(std::vector<int> list){

  // base case
  if (list.size() <= 1 ){
    return list;
  }

  // split
  int mid = list.size() / 2;
  std::vector<int> a,b;
  int i;
  for (i=0;i<mid;i++){
    a.push_back(list[i]);
  }

  for (i=mid;i<list.size();i++){
    b.push_back(list[i]);
  }
  
  // recurse
  a = msort(a);
  b = msort(b);
  // merge
  list = merge(a,b);
  return list;
  
}

int main(int argc, char *argv[])
{
  int i;
  int size=100000;
  std::vector<int> a(size);
  
  srand(time(NULL));
  for (i = 0; i < size; ++i) {
    a[i] = rand()%1000;
  }
  // print_vector(a);

  std::cout << "Start!!\n";
  struct timeval tp;
  gettimeofday(&tp,NULL);
  long start_time = tp.tv_sec * 1000 + tp.tv_usec / 1000;
  
  
  a=msort(a);

  gettimeofday(&tp,NULL);
  long current_time = tp.tv_sec * 1000 + tp.tv_usec / 1000;

  long elapsed = current_time - start_time;
  // print_vector(a);
  std::cout << "time: " << elapsed << "\n";
  return 0;
}
