#include <bits/stdc++.h>

using namespace std;


bool isTablePresent(string tname, string &deleteline){
    string schema = "schema.txt";
    fstream table;
    table.open("schema.txt", ios::in);
    bool tablepresent = false;
    while (table){
        string currentline;
        getline(table, currentline);
        cout.flush();

        if (currentline.substr(0, tname.length()) == tname){
            tablepresent = true;
            deleteline = currentline;
        }
    }
    table.close();

    return tablepresent;
}


void insert(vector<string> &querytocons){
    string schema = "schema.txt";
    string tname = querytocons[2];
    string requiredline;
    if (querytocons.size() < 2){
        cout << "Incorrect Query" << endl;
        return;
    }

    if (!isTablePresent(tname, requiredline))
    {
        cout << "Table does not exists.." << endl;
    }

    if (querytocons[3] == "values"){
        if (querytocons[4] == "("){
            
        }
    }
}


void describeTable(vector<string> &querytocons){
    string tname = querytocons[1];
    string requiredline = "";
    if (!isTablePresent(tname, requiredline)){
        cout << "Table does not exists.." << endl;
        return;
    }

    int i = tname.size() + 1;
    int countHash = 0;

    cout << endl << endl;
    cout << "------" << "Table " << tname << "-----" << endl;
    while(i < requiredline.size()){
        if (requiredline[i] == '#'){
            if (countHash % 2 == 0){
                cout << "--";
            }
            else{
                cout << endl;
            }
            countHash++;
        }
        else{
            cout << requiredline[i];
        }
        i++;
    }

    return;
}


void dropTable(vector<string> &querytocons)
{
    string schema = "schema.txt";
    string tname = querytocons[2];
    string deleteline;
    if (querytocons.size() < 2){
        cout << "Incorrect Query" << endl;
        return;
    }

    if (!isTablePresent(tname, deleteline)){
        cout << "Table does not exists.." << endl;
        return;
    }
    else{
        fstream table;
        ofstream fout;
        fout.open("tempfile.txt", ios::out);
        table.open("schema.txt", ios::in);
        //  ifstream table(schema);

        bool exists = false;
        while (table)
        {
            string line;
            getline(table, line);
            cout.flush();
            //cout << line[0] << " ";

            if (line != deleteline && line != ""){
                fout.write(line.data(), line.size());
                fout << endl;
            }
        }
        table.close();
        fout.close();
        int res = remove("schema.txt");
        cout << res << endl;

        string toRemove = tname + ".txt";
        char char_array[toRemove.size() + 1];
        strcpy(char_array, toRemove.c_str());

        int r = remove(char_array);

        rename("tempfile.txt", "schema.txt");
    }
}


void create(vector<string> &querytocons){
    ofstream fout, foutfortable;

    string schema = "schema.txt";
    ifstream table(schema);
    string table_name = querytocons[2];
    cout << endl;

    bool tablepresent = false;

    while (table)
    {
        string currentline;
        getline(table, currentline);
        cout.flush();

        if (currentline.substr(0, table_name.length()) == table_name){
            tablepresent = true;
        }
    }

    if (tablepresent == true){
        cout << "Table already exists!" << endl;
    }
    else{
        vector<string> query;
        query = querytocons;

        fout.open("schema.txt", ios_base::app);
        cout << endl;

        string table_name = querytocons[2] + ".txt";
        foutfortable.open(table_name, ios_base::app);

        fout << querytocons[2];
        int j;
        for (j = 5; j < querytocons.size(); j += 3){
            // cout << querytocons[j] << " ";
            if (querytocons[j].substr(0, 4) == "char"){
                fout << "#" << querytocons[j - 1] << "#" << querytocons[j];
            }
            else {
                fout << "#" << querytocons[j - 1] << "#" << querytocons[j];
            }
            // if (querytocons[j] == "primary"){
            //     break;
            // }
        }

        // if (j != querytocons.size()-1){
        //     if (querytocons[j] == "primary" && querytocons[j+1] == "key"){
        //         j += 2; //to get in the brackets
        //         while(j < querytocons.size()){
        //             fout << "#" << querytocons[j] << "#pkey";
        //             j += 2;

        //             if (querytocons[j] == ","){
        //                 j++;
        //                 break;
        //             }
        //         }
        //     }
        // }

        // if (j != querytocons.size()-1){
        //     if (querytocons[j] == "foreigh" && querytocons[j+1] == "key"){
                
        //     }
        // }

        fout << endl;

        fout.close();
        foutfortable.close();
        cout << "Table created successfully" << endl;
        cout << endl;
    }
}

int main()
{
    string s;
    getline(cin, s);

    stringstream ss(s);
    string temp;
    vector<string> querytocons;
    while (ss >> temp){
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        querytocons.push_back(temp);
    }

    if (querytocons[0] == "create"){
        if (querytocons[1] == "table"){

            if (querytocons[3] == "(" and querytocons[querytocons.size() - 1] == ";" and querytocons[querytocons.size() - 2] == ")"){
                bool corr = true;
                for (int i = 6; i < querytocons.size() - 2; i += 3){
                    if (querytocons[i] != ","){
                        corr = false;
                        break;
                    }
                }
                if (corr){
                    create(querytocons);
                }

                else{
                    cout << "Incorrect Query" << endl;
                }
            }
            else{
                if (querytocons[querytocons.size() - 1] != ";")
                    cout << "Please provide ; at the end" << endl;
                else
                    cout << "Incorrect Query!!" << endl;
            }
        }
        else{
            cout << "Incorrect syntax!!!" << endl;
        }
    }
    else if (querytocons[0] == "drop"){
        if (querytocons[1] == "table"){
            dropTable(querytocons);
        }
    }
    else if (querytocons[0] == "describe"){
        describeTable(querytocons);
    }
    else if (querytocons[0] == "insert"){
        if (querytocons[1] == "into"){
            insert(querytocons);
        }
    }


    return 0;
}