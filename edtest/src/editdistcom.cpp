#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <chrono> //c++ clock
//#pragma GCC diagnostic ignored "-Wc++11-extensions"
#define DEBUG 0
//#define endl "\n"
#define all(v) v.begin(),v.end()
using namespace std;
#define gamma gama
int r = 34;
const int INF = 1e9;


int edit_distance(const string &s1, const string &s2){
  int len1 = s1.length();
  int len2 = s2.length();
  int dp[2][len1+1]; 
  for(int i = 0;i <= len1 ; ++i){
    dp[0][i] = i;
    dp[1][i] = INF;
  }
  for(int i = 1;i <= len2 ; ++i){
    int curr = (i&1), prev = (curr^1);
    dp[curr][0] = i;
    for(int j = 1; j <= len1 ; ++j){
      if(s2[i-1] == s1[j-1]) dp[curr][j] = dp[prev][j-1]; 
      else{
        dp[curr][j] = min(1+dp[prev][j] , 1+dp[prev][j-1]);
        dp[curr][j] = min(dp[curr][j] , 1+dp[curr][j-1]);
      }
    }
  }
  return dp[len2&1][len1];
}

bool compute_distance(const string &s1, const string &s2, string type, int len, int rad){
  if(type == "edit1"){
    //if(DEBUG) assert(dis <= strand_length);
    int ra = edit_distance(s1, s2);
    return ra <= rad;
  }
  else if(type == "edit2"){ // returns 0 if both substr edit dist c1, c2 <= r, else return 1
    // comparing front and back substrings
    int c1 = edit_distance(s1.substr(0, len) , s2.substr(0, len));
    int c2 = edit_distance(s1.substr((s1.size() - len), len), s2.substr((s2.size() - len), len));
    return (c1 <= rad && c2 <= rad); //if match return < r, else return > r: makeshift clustering
  }
  else {
    assert(0);
  }
}

int main() {
  string control = "CCGTCTCCCCAGTCTCGTTGAAGTGTCAGGCGTATACTGAGTTTAGCGTGCGGGAAACATTAGGATGTCCTTGAAAGACGAGGGTCAGCTGCACCTACTTTGAGCGGCGTTTGGGCAGTGGATTG";
  string match = "CCGTCTCCCATTCTTGCACTGTCCGGATATATATTTAGCGGTGCGGAAAATTAGGATGTCCCTGGAAGTAGAGTCCAGTCACCTACTTTGTAAGCGGCGTATGGGCAGTTGATTG";
  string mismatch = "GGGCGGTAAGGAGGTGACAGGAGTTATGAAGTGAGTACTTCACTGCGATAGAGATCCGTAACGTAGTCACGGGGCGGTTGAACGCTCCTGTGCAAGATTTGAGGCCTGATTTTGAACGGCCGT";

  int len = 24;
  cout << "frag length: " << len << endl;
  int radlow = 7;
  int radhigh = 17;

  for(int i = radlow; i <= radhigh; i++){
    cout << "rad = " << i << endl;

    auto t0 = std::chrono::high_resolution_clock::now();
    cout << "buffer: " << (compute_distance(control,match,"edit1",len,r) == true) << endl;
    auto c0 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - t0);
    cout << "buffer: " << c0.count() << "us" << endl;

    auto t1 = std::chrono::high_resolution_clock::now();
    cout << "ED match: " << (compute_distance(control,match,"edit1",len,r) == true) << endl;
    auto c1 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - t1);
    cout << "ED match: " << c1.count() << "us" << endl;

    auto t2 = std::chrono::high_resolution_clock::now();
    cout << "ED mismatch: " << (compute_distance(control,mismatch,"edit1",len,r) == false) << endl;
    auto c2 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - t2);
    cout << "ED mismatch: " << c2.count() << "us" << endl;

    auto t3 = std::chrono::high_resolution_clock::now();
    cout << "Frag match: " << (compute_distance(control,match,"edit2",len,i) == true) << endl;
    auto c3 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - t3);
    cout << "Frag match: " << c3.count() << "us" << endl;

    auto t4 = std::chrono::high_resolution_clock::now();
    cout << "Frag mismatch: " << (compute_distance(control,mismatch,"edit2",len,i) == false) << endl;
    auto c4 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - t4);
    cout << "Frag mismatch: " << c4.count() << "us" << endl;
  }

  return 0;
}