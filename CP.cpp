#include <bits/stdc++.h>
using namespace std;

void tokenize(string s, string del, vector<string> &dtypes)
{
    int start = 0;
    int end = s.find(del);
    while (end != -1)
    {
        dtypes.push_back(s.substr(start, end - start));

        start = end + del.size();
        end = s.find(del, start);
    }

    dtypes.push_back(s.substr(start, end - start));
}

bool isTablePresent(string tname, string &deleteline)
{
    string schema = "schema.txt";
    fstream table;
    table.open("schema.txt", ios::in);
    bool tablepresent = false;
    string currentline;
    while (getline(table, currentline))
    {

        // getline(table, currentline);
        // cout.flush();

        if (currentline.substr(0, tname.length()) == tname)
        {
            tablepresent = true;
            deleteline = currentline;
        }
    }
    table.close();

    return tablepresent;
}

// void insert(vector<string> &querytocons){
//     string schema = "schema.txt";
//     string tname = querytocons[2];
//     string requiredline;
//     if (querytocons.size() < 2){
//         cout << "Incorrect Query" << endl;
//         return;
//     }

//     if (!isTablePresent(tname, requiredline))
//     {
//         cout << "Table does not exists.." << endl;
//     }

//     if (querytocons[3] == "values"){
//         if (querytocons[4] == "("){

//         }
//     }
// }

void describeTable(vector<string> &querytocons)
{
    string tname = querytocons[1];
    string requiredline = "";
    if (!isTablePresent(tname, requiredline))
    {
        cout << "Table does not exists.." << endl;
        return;
    }

    int i = tname.size() + 1;
    int countHash = 0;

    cout << endl
         << endl;
    cout << "------"
         << "Table " << tname << "-----" << endl;
    while (i < requiredline.size())
    {
        if (requiredline[i] == '#')
        {
            if (countHash % 2 == 0)
            {
                cout << "--";
            }
            else
            {
                cout << endl;
            }
            countHash++;
        }
        else
        {
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
    if (querytocons.size() < 2)
    {
        cout << "Incorrect Query" << endl;
        return;
    }

    if (!isTablePresent(tname, deleteline))
    {
        cout << "Table does not exists.." << endl;
        return;
    }
    else
    {
        fstream table;
        ofstream fout;
        fout.open("tempfile.txt", ios::out);
        table.open("schema.txt", ios::in);
        //  ifstream table(schema);
        string line;
        bool exists = false;
        while (getline(table, line))
        {

            // getline(table, line);
            // cout.flush();
            // cout << line[0] << " ";

            if (line != deleteline && line != "")
            {
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
void truncateTable(vector<string> &querytocons)
{
    string schema = "schema.txt";
    string tname = querytocons[2];
    string deleteline;
    if (querytocons.size() < 2)
    {
        cout << "Incorrect Query" << endl;
        return;
    }

    if (!isTablePresent(tname, deleteline))
    {
        cout << "Table does not exists.." << endl;
        return;
    }
    else
    {
        fstream table;
        ofstream fout;

        string toRemove = tname + ".txt";
        char char_array[toRemove.size() + 1];
        strcpy(char_array, toRemove.c_str());

        int r = remove(char_array);
    }
}
void selectCol(vector<string> &querytocons)
{
    string schema = "schema.txt";
    // string tname = querytocons[querytocons.size() - 2];
    string tname = querytocons[3];

    //  cout<<tname<<endl;

    int fromindex = -99;
    for (int i = 0; i < querytocons.size(); i++)
    {
        if (querytocons[i] == "from")
        {
            fromindex = i;
            break;
        }
    }

    tname = querytocons[fromindex + 1];

    string requiredline;
    vector<string> tableinfo;
    map<string, int> collist;
    vector<string> colnamecheck;
    int whereindex = 0;

    vector<int> st;
    vector<string> selectedcolumns;
    // if (querytocons.size() < 4 or querytocons[querytocons.size() - 3] != "from")
    // {
    //     cout << "Incorrect Query" << endl;
    //     return;
    // }

    if (!isTablePresent(tname, requiredline))
    {
        cout << "Table does not exists.." << endl;
        return;
    }
    else
    {
        tokenize(requiredline, "#", tableinfo);
        // for(auto it:tableinfo)
        // {
        //     cout<<it<<" ";
        // }

        int cnt = 0;
        for (int i = 1; i < tableinfo.size(); i += 2)
        {
            collist[tableinfo[i]] = cnt;
            colnamecheck.push_back(tableinfo[i]);

            cnt++;
        }
        // for(auto it:collist)
        // {
        //     cout<<it.first<<" "<<it.second<<endl;
        // }
        // cout<<endl;
        // cout<<"*************"<<endl;
        // cout<<requiredline<<endl;
        fstream table;
        string line;
        // ofstream fout;
        ifstream myfile(tname + ".txt");

        // check if where present

        for (int i = 0; i < querytocons.size(); i++)
        {
            if (querytocons[i] == "where")
            {
                whereindex = i;
                break;
            }
        }

        //  cout<<whereindex<<endl;
        if (myfile.is_open())
        {
            if (querytocons[1] == "*")
            {
                if (whereindex == 0)
                {
                    while (getline(myfile, line))
                    {
                        for (int i = 0; i < line.length(); i++)
                        {
                            if (line[i] == '#')
                                cout << " ";
                            else
                                cout << line[i];
                        }
                        cout << endl;
                    }
                }
                else if (whereindex == 4)
                { /* string wherecheck="";
                   for(int i = whereindex+1;i<querytocons.size();i++)
                   {
                       wherecheck+=querytocons[i];
                   }*/

                    while (getline(myfile, line))
                    {
                        vector<string> wherecondition;

                        tokenize(line, "#", wherecondition);

                        for (int i = 0; i < querytocons.size(); i++)
                        {

                            if (collist.find(querytocons[i]) != collist.end())
                            {

                                int pos = collist[querytocons[i]];
                                // cout<<pos<<" "<<querytocons[i+2]<<endl;
                                int flag = 0;

                                if (querytocons[i + 1] == "=")
                                {
                                    if (wherecondition[pos + 1] == querytocons[i + 2])
                                        flag = 1;
                                }
                                else if (querytocons[i + 1] == ">")
                                {
                                    if (wherecondition[pos + 1] > querytocons[i + 2])
                                    {

                                        flag = 1;
                                    }
                                }
                                else if (querytocons[i + 1] == ">=")
                                {
                                    if (wherecondition[pos + 1] >= querytocons[i + 2])
                                        flag = 1;
                                }
                                else if (querytocons[i + 1] == "<")
                                {
                                    if (wherecondition[pos + 1] < querytocons[i + 2])
                                        flag = 1;
                                }
                                else if (querytocons[i + 1] == "<=")
                                {
                                    if (wherecondition[pos + 1] <= querytocons[i + 2])
                                        flag = 1;
                                }
                                else if (querytocons[i + 1] == "!=")
                                {
                                    if (wherecondition[pos + 1] != querytocons[i + 2])
                                        flag = 1;
                                }
                                else
                                    cout << "incorrect operator!!!!!!!!!!!" << endl;

                                if (flag)
                                {

                                    for (auto it : wherecondition)
                                    {
                                        cout << it << " ";
                                    }
                                    cout << endl;
                                }
                            }
                        }
                    }
                }
                else
                {
                    cout << "ERROR IN WHERE" << endl;
                }
            }

            else
            {
                // for selected columns
                int ind = 1;
                while (querytocons[ind] != "from")
                {
                    if (querytocons[ind] != ",")
                    {
                        // cout<<querytocons[ind]<<" ";
                        selectedcolumns.push_back(querytocons[ind]);
                        int pos = collist[querytocons[ind]];
                        st.push_back(pos);
                    }

                    ind++;
                }

                for (auto it : collist)
                {
                    cout << it.first << " ";
                }
                cout << endl;
                cout << "****" << endl;
                for (auto it : selectedcolumns)
                {
                    vector<string>::iterator iter;
                    iter = find(colnamecheck.begin(), colnamecheck.end(), it);
                    if (iter == colnamecheck.end())
                    {
                        cout << "please add right col name" << endl;
                        return;
                    }

                    // cout<<it<<" ";
                }

                while (getline(myfile, line))
                {

                    vector<string> data;
                    // cout<<"hello"<<endl;
                    tokenize(line, "#", data);
                    //  for(auto it:data)
                    //  {
                    //      cout<<it<<" ";
                    //  }
                    for (auto it : st)
                    { // cout<<it<<" ";
                        cout << data[it + 1] << " ";
                    }
                    cout << endl;
                }
            }

            myfile.close();
        }

        else
            cout << "Unable to open file";
    }
}

void update(vector<string> &querytocons)
{

    string tname = querytocons[1];
    string requiredline;
    vector<string> tableinfo;
    map<string, int> collist; // maping of colname and its index
    vector<string> colnamecheck;
    int whereindex = -1;
    int setindex = -1;
    map<string, string> mp; // updation required for these column
    string conditioncolumn;
    fstream table; // tablename
    string line;
    // ofstream fout;
    // fstream myfile(tname + ".txt");

    if (!isTablePresent(tname, requiredline))
    {
        cout << "Table does not exists.." << endl;
        return;
    }
    else
    {
        tokenize(requiredline, "#", tableinfo);

        int cnt = 0;
        for (int i = 1; i < tableinfo.size(); i += 2)
        {
            collist[tableinfo[i]] = cnt;
            colnamecheck.push_back(tableinfo[i]);

            cnt++;
        }

        for (int i = 0; i < querytocons.size(); i++)
        {
            if (querytocons[i] == "where")
            {
                whereindex = i;
                break;
            }
            else if (querytocons[i] == "set")
            {
                setindex = i;
            }
        }

        if (whereindex != -1)
        {
            conditioncolumn = querytocons[whereindex + 1];

            int k = setindex + 1;

            while (k < whereindex)
            {
                mp[querytocons[k]] = querytocons[k + 2]; // map<column that needs to be updated , value of new data>
                k += 4;
            }

            int conditioncolpos = collist[conditioncolumn];

            if (querytocons[whereindex + 2] == "=")
            {
                ofstream fout;
                fout.open("tempfile.txt", ios::out);
                table.open(tname + ".txt", ios::in);
                int i = 1;
                string line;
                while (getline(table, line))
                {
                    // cout << "In " << i << endl;
                    // i++;
                    vector<string> data;
                    tokenize(line, "#", data);

                    for (auto m : mp)
                    {
                        int reqpos = collist[m.first];
                        cout << data[reqpos + 1] << ":->" << m.second << endl;
                        data[reqpos + 1] = m.second;
                    }

                    if (data[conditioncolpos + 1] == querytocons[whereindex + 3])
                    {

                        //  cout<<data[conditioncolpos+1]<<" "<<querytocons[whereindex+3]<<endl;

                        string finalline = "";
                        for (auto it : data)
                        {
                            cout << it << " ";
                            finalline += it;
                            finalline += "#";
                        }
                        finalline.pop_back();
                        fout.write(finalline.data(), finalline.size());
                        fout << endl;
                    }
                    else
                    {
                        fout.write(line.data(), line.size());
                        fout << endl;
                    }
                }
                fout.close();
                table.close();

                // first remove original table->rename tempfile to original name of table
                string toRemove = tname + ".txt";
                char char_array[toRemove.size() + 1];
                strcpy(char_array, toRemove.c_str());

                int r = remove(char_array);
                cout << r << endl;

                rename("tempfile.txt", char_array);
            }
            else if (querytocons[whereindex + 2] == ">")
            {
                ofstream fout;
                fout.open("tempfile.txt", ios::out);
                table.open(tname + ".txt", ios::in);
                int i = 1;
                string line;
                while (getline(table, line))
                {
                    // cout << "In " << i << endl;
                    // i++;
                    vector<string> data;
                    tokenize(line, "#", data);

                    for (auto m : mp)
                    {
                        int reqpos = collist[m.first];
                        cout << data[reqpos + 1] << ":->" << m.second << endl;
                        data[reqpos + 1] = m.second;
                    }

                    if (data[conditioncolpos + 1] > querytocons[whereindex + 3])
                    {

                        //  cout<<data[conditioncolpos+1]<<" "<<querytocons[whereindex+3]<<endl;

                        string finalline = "";
                        for (auto it : data)
                        {
                            cout << it << " ";
                            finalline += it;
                            finalline += "#";
                        }
                        finalline.pop_back();
                        fout.write(finalline.data(), finalline.size());
                        fout << endl;
                    }
                    else
                    {
                        fout.write(line.data(), line.size());
                        fout << endl;
                    }
                }
                fout.close();
                table.close();

                // first remove original table->rename tempfile to original name of table
                string toRemove = tname + ".txt";
                char char_array[toRemove.size() + 1];
                strcpy(char_array, toRemove.c_str());

                int r = remove(char_array);
                cout << r << endl;

                rename("tempfile.txt", char_array);
            }
            else if (querytocons[whereindex + 2] == "<")
            {
                ofstream fout;
                fout.open("tempfile.txt", ios::out);
                table.open(tname + ".txt", ios::in);
                int i = 1;
                string line;
                while (getline(table, line))
                {
                    // cout << "In " << i << endl;
                    // i++;
                    vector<string> data;
                    tokenize(line, "#", data);

                    for (auto m : mp)
                    {
                        int reqpos = collist[m.first];
                        cout << data[reqpos + 1] << ":->" << m.second << endl;
                        data[reqpos + 1] = m.second;
                    }

                    if (data[conditioncolpos + 1] < querytocons[whereindex + 3])
                    {

                        //  cout<<data[conditioncolpos+1]<<" "<<querytocons[whereindex+3]<<endl;

                        string finalline = "";
                        for (auto it : data)
                        {
                            cout << it << " ";
                            finalline += it;
                            finalline += "#";
                        }
                        finalline.pop_back();
                        fout.write(finalline.data(), finalline.size());
                        fout << endl;
                    }
                    else
                    {
                        fout.write(line.data(), line.size());
                        fout << endl;
                    }
                }
                fout.close();
                table.close();

                // first remove original table->rename tempfile to original name of table
                string toRemove = tname + ".txt";
                char char_array[toRemove.size() + 1];
                strcpy(char_array, toRemove.c_str());

                int r = remove(char_array);
                cout << r << endl;

                rename("tempfile.txt", char_array);
            }
            //    // if (data[conditioncolpos + 1] == querytocons[whereindex + 3])
            //      if(querytocons[whereindex+2]=="=")
            //     {

            //     }
            // }
        }
       
            else
            {
                // 0        1    2   3   4  5   6
                // UPDATE stud SET name ='Juan';

                int k = 3;
                while (k < querytocons.size())
                {
                    mp[querytocons[k]] = querytocons[k + 2]; // map<column that needs to be updated , value of new data>
                    k += 4;
                }

                ofstream fout;
                fout.open("tempfile.txt", ios::out);
                table.open(tname + ".txt", ios::in);
                int i = 1;
                string line;
                while (getline(table, line))
                {
                    // cout << "In " << i << endl;
                    // i++;
                    vector<string> data;
                    tokenize(line, "#", data);

                    for (auto m : mp)
                    {
                        int reqpos = collist[m.first];
                        cout << data[reqpos + 1] << ":->" << m.second << endl;
                        data[reqpos + 1] = m.second;
                    }

                    //  cout<<data[conditioncolpos+1]<<" "<<querytocons[whereindex+3]<<endl;

                    string finalline = "";
                    for (auto it : data)
                    {
                        cout << it << " ";
                        finalline += it;
                        finalline += "#";
                    }
                    finalline.pop_back();
                    fout.write(finalline.data(), finalline.size());
                    fout << endl;
                }
                fout.close();
                table.close();

                // first remove original table->rename tempfile to original name of table
                string toRemove = tname + ".txt";
                char char_array[toRemove.size() + 1];
                strcpy(char_array, toRemove.c_str());
                
                int size = toRemove.size();
                char newname[size+1];
                strcpy(newname,toRemove.c_str());
                // for(int i = 0;i<=size;i++)
                // {
                //     newname[i] = toRemove[i];
                // }

                int r = remove(char_array);
                cout << r << endl;

                rename("tempfile.txt", newname);
            }
        
    }
}

void create(vector<string> &querytocons)
{
    ofstream fout, foutfortable;

    string schema = "schema.txt";
    ifstream table(schema);
    string table_name = querytocons[2];
    cout << endl;

    bool tablepresent = false;
    string currentline;
    while (getline(table, currentline))
    {

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
        int j;
        for (j = 5; j < querytocons.size(); j += 3)
        {
            // cout << querytocons[j] << " ";
            if (querytocons[j].substr(0, 4) == "char")
            {
                fout << "#" << querytocons[j - 1] << "#" << querytocons[j];
            }
            else
            {
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

bool checkint(string temp)
{
    for (auto it : temp)
    {
        if (isdigit(it) == 0)
        {
            return false;
        }
    }
    return true;
}
bool checkdouble(string temp)
{
    for (auto it : temp)
    {
        if (it == '.')
        {
            continue;
        }
        if (isdigit(it) == 0)
        {
            return false;
        }
    }
    return true;
}

bool checkchar(string temp)
{

    for (auto it : temp)
    {
        if (isdigit(it) == 0)
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}

void insertquery(vector<string> querytocons)
{

    string table_name = querytocons[2];
    string tname = querytocons[2] + ".txt";
    string schema = "schema.txt";
    ifstream table(schema);
    string currline = "";
    bool tablepresent = false;
    string currentline;
    while (getline(table, currentline))
    {

        cout.flush();

        if (currentline.substr(0, table_name.length()) == table_name)
        {
            tablepresent = true;
            currline = currentline;
            break;
        }
    }
    if (tablepresent == false)
    {
        cout << "Table does not exist " << endl;
        return;
    }

    vector<string> dtypes;
    //  char *str = currline.c_str();
    // char *token = strtok(currline.c_str(), "#");

    tokenize(currline, "#", dtypes);
    // for(int i=0;i<dtypes.size();i++)
    // {
    //     cout<<dtypes[i]<<" ";
    // }

    vector<string> dtypetocons;
    for (int i = 2; i < dtypes.size(); i += 2)
    {
        dtypetocons.push_back(dtypes[i]);
    }

    // for(int i = 0;i<dtypetocons.size();i++)
    // {
    //     cout<<dtypetocons[i]<<" ";
    // }
    cout << endl;
    // return;

    vector<string> datatoinsert;

    for (int i = 5; i < querytocons.size() - 2; i++)
    {
        if (querytocons[i] != ",")
        {
            datatoinsert.push_back(querytocons[i]);
        }
    }

    // for(auto it:datatoinsert)
    // {
    //     cout<<it<<" ";
    // }
    if (datatoinsert.size() != dtypetocons.size())
    {
        cout << "Please add the necessary attributes only" << endl;
        return;
    }

    for (int i = 0; i < datatoinsert.size(); i++)
    {
        if (dtypetocons[i] == "char" or dtypetocons[i] == "str")
        {
            if (checkchar(datatoinsert[i]) == false)
            {
                cout << " error!!!!wrong datatype" << endl;
                return;
            }
        }
        else if (dtypetocons[i] == "int")
        {
            if (checkint(datatoinsert[i]) == false)
            {
                cout << " error!!!!wrong datatype" << endl;
                return;
            }
        }
        else if (dtypetocons[i] == "double" or dtypetocons[i] == "number")
        {
            if (checkdouble(datatoinsert[i]) == false)
            {
                cout << " error!!!!wrong datatype" << endl;
                return;
            }
        }
    }

    // return;
    ofstream insert_table;
    insert_table.open(tname, std::ios_base::app);

    if (insert_table)
    {

        for (int i = 5; i < querytocons.size() - 2; i++)
        {
            if (querytocons[i] != ",")
            {
                insert_table << "#" << querytocons[i];
            }
        }
        insert_table << endl;
        cout << "Data Inserted" << endl;
    }

    else
    {
        cout << "Table does not exists" << endl;
    }

    insert_table.close();
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
    else if (querytocons[0] == "drop")
    {
        if (querytocons[1] == "table")
        {
            dropTable(querytocons);
        }
    }
    else if (querytocons[0] == "describe")
    {
        describeTable(querytocons);
    }
    else if (querytocons[0] == "insert")
    {
        if (querytocons[querytocons.size() - 1] != ";")
        {
            cout << "Please provide ; at the end" << endl;
        }
        else
        {
            insertquery(querytocons);
        }
    }
    else if (querytocons[0] == "truncate")
    {
        if (querytocons[1] == "table")
        {
            truncateTable(querytocons);
        }
    }
    else if (querytocons[0] == "select")
    {
        selectCol(querytocons);
    }
    else if (querytocons[0] == "update")
    {
        update(querytocons);
    }

    return 0;
}
