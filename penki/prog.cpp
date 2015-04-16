#include <fstream>
#include <string>

using namespace std;

char buf1[1024];

bool isProtein(string s){
   if (s[0] == '>') return false;
   for(int i=0;i<s.length();i++)
      if ((s[i] != 'a') && (s[i] != 'A') && (s[i] != 'c') && (s[i] != 'C')
          && (s[i] != 'g') && (s[i] != 'G') && (s[i] != 't') && (s[i] != 'T'))
          return  true;
   return false;         
}


int nextSeq(ifstream& fin, string& firstLine, string& content, bool& protein) {

    
    if(buf1[0]=='*')
       do{
         fin.getline(buf1, 1024);
       } while((buf1[0] != '>')&& (!fin.eof()));

    
    if (!fin.eof()) 
        firstLine = string(buf1);
    else return -1;
    
    content = "";
    
    do{
      fin.getline(buf1, 1024);
      if ((buf1[0] != '>') && (!fin.eof())) 
          content = content + string(buf1);
    } while( (buf1[0] != '>') && (!fin.eof()));
    
    protein = isProtein(content);
    return 0;
    

}


void getAllProteins(string nfin, string nfout){
   buf1[0]='*';

   ifstream fin(nfin.c_str());
   ofstream fout(nfout.c_str());
   string title, content;
   bool prot;
   while (nextSeq(fin, title, content, prot) != -1) {
      if(prot){
         fout << title << endl;
         fout << content << endl;
      }   
      
   }
   fin.close();
   fout.close();
}

void getAllHipotProteins(string nfin, string nfout){
   buf1[0]='*';

   ifstream fin(nfin.c_str());
   ofstream fout(nfout.c_str());
   string title, content;
   bool prot;
   while (nextSeq(fin, title, content, prot) != -1) {
      if((prot) && (title.find("hypothetical protein") != string::npos))  {
         fout << title << endl;
         fout << content << endl;
      }   
      
   }
   fin.close();
   fout.close();
}

void getAllFoundEnzymeProteins(string nfin, string nfout){
   buf1[0]='*';

   ifstream fin(nfin.c_str());
   ofstream fout(nfout.c_str());
   string title, content;
   bool prot;
   while (nextSeq(fin, title, content, prot) != -1) {
      if((prot) && (title.find("(EC ") != string::npos))  {
         fout << title << endl;
         fout << content << endl;
      }   
      
   }
   fin.close();
   fout.close();
}


int main(){
   
   getAllProteins("J08-automatine.fa", "J08-hip-proteins.fa");
   getAllProteins("J11-automatine.fa", "J11-hip-proteins.fa");
   getAllProteins("D13-automatine.fa", "D13-hip-proteins.fa");
   
   getAllHipotProteins("J08-automatine.fa", "J08-hip-proteins.fa");
   getAllHipotProteins("J11-automatine.fa", "J11-hip-proteins.fa");
   getAllHipotProteins("D13-automatine.fa", "D13-hip-proteins.fa");
   
   getAllFoundEnzymeProteins("J08-automatine.fa", "J08-enz-proteins.fa");
   getAllFoundEnzymeProteins("J11-automatine.fa", "J11-enz-proteins.fa");
   getAllFoundEnzymeProteins("D13-automatine.fa", "D13-enz-proteins.fa");
   
   
   return 0;   
}

