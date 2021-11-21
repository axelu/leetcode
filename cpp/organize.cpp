#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

using namespace std;

int main() {

    string path = ".";
    for(const auto & entry : filesystem::directory_iterator(path)) {

        string fname = entry.path().filename();
        int n = -1;

        if( fname.size() > 4 && fname.substr(fname.size()-4) == ".cpp" ) {
            // cout << fname << endl;

            ifstream file(fname);

            string line;
            while(getline(file,line)) {
                // cout << "line " << line << endl;

                if( line.size() >= 7 && line.substr(0,3) == "// " ) {
                    string n_str = "";
                    int i = 3;
                    for(; i < line.size(); ++i) {
                        if( isdigit(line[i]) )
                            n_str.push_back(line[i]);
                        else
                            break;
                    }
                    if( !n_str.empty() &&
                        i < line.size() && line[i] == '.'  &&
                        i+1 < line.size() && line[i+1] == ' ' &&
                        i+2 < line.size() && isalnum(line[i+2]) )

                        n = stoi(n_str);
                }
                if( n != -1 )
                    break;
            }
        }
        if( n != -1 ) {
            
            // github only lists up to 1000 files in a folder
            // so we will splitt at 500
            int t = n / 500;
            string a = to_string(t*500);
            while( a.size() < 5)
                a = '0' + a;
            string b = to_string((t+1)*500-1);
            while( b.size() < 5)
                b = '0' + b;
            string target = a + '-' + b;

            // create target directory if not exist
            if( !filesystem::exists(target) ) {
                cout << "mkdir " << target << endl;
                filesystem::create_directory(target);
            }

            cout << "mv " << fname << " " << target << "/" << endl;
            filesystem::rename(fname,target+'/'+fname);
            
        } else
            cout << "# " << fname << endl;

    }

    return 0;
}
