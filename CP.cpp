#include <bits/stdc++.h>
using namespace std;

void create(vector<string> &querytocons)
{

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

        if (currentline.substr(0, table_name.length()) == table_name)
        {
            tablepresent = true;
        }
    }

    if (tablepresent == true)
    {
        cout << "Table already exists!" << endl;
    }
    else
    {
        vector<string> query;
        query = querytocons;

        fout.open("schema.txt", ios_base::app);
        cout << endl;

        string table_name = querytocons[2] + ".txt";
        foutfortable.open(table_name, ios_base::app);

        fout << querytocons[2];
        for (int j = 5; j < querytocons.size(); j+=3)
        {
            if (querytocons[j] == "int")
            {
                fout << "#" << querytocons[j - 1] << "#" << querytocons[j];
                
            }

            if (querytocons[j] == "decimal")
            {
                fout << "#" << querytocons[j - 1] << "#" << querytocons[j];
               
            }

            if (querytocons[j].substr(0, 4) == "char")
            {
                fout << "#" << querytocons[j - 1] << "#" << querytocons[j];
               
            }
        }
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
    while (ss >> temp)
    {
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        cout << temp << endl;
        querytocons.push_back(temp);
    }

    if (querytocons[0] == "create")
    {
        if (querytocons[1] == "table")
        {

            if (querytocons[3] == "(" and querytocons[querytocons.size() - 1] == ";" and querytocons[querytocons.size() - 2] == ")")
            {
                bool corr = true;
                for (int i = 6; i < querytocons.size() - 2; i += 3)
                {
                    if (querytocons[i] != ",")
                    {
                        corr = false;
                        break;
                    }
                }
                if (corr)
                {
                    create(querytocons);
                }

                else
                {
                    cout << "Incorrect Query" << endl;
                }
            }
            else
            {
                if (querytocons[querytocons.size() - 1] != ";")
                    cout << "Please provide ; at the end" << endl;
                else
                    cout << "Incorrect Query!!" << endl;
            }
        }
        else
        {
            cout << "Incorrect syntax!!!" << endl;
        }
    }
}