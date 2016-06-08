#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <sstream>
#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <sys/wait.h>
#include <vector>
#include <cstdlib>
#include "execute.h"

using namespace std;

Base* treecreate(vector <vector <string> > cmds, vector <vector <string> > ops, Base *& op, unsigned & count, unsigned & currint, unsigned & level)
{
    cout << "count: " << count << endl;
    cout << "Level: " << level << endl;
    cout << "currint: " << currint<< endl;
    stringstream ss;
    vector <string> Node;
    string temp;
    Base* Ops = NULL;
    Base* Opt = NULL;
    //Base* Br1 = NULL;
    //Base* Br2 = NULL;
    
    ss << cmds[count].at(0);
    if(ss >> temp)
    {
       // cout << "count: " << count << endl;
        cout << "Curr temp left: " << temp << endl;
        if (temp == "Recurse")
        {
            level++;
            currint++;
            count = level;
            Ops = treecreate(cmds, ops, op, count, currint, level);
            cout << "ended recurstion" << endl;
            currint--;
            count = currint;
        }
        else if(temp == " ")
        {
            Ops = NULL;
        }
        else
        {
            Node.push_back(temp);
            while(ss >> temp)
            {
                cout << "Curr temp left: " << temp << endl;
                Node.push_back(temp);
            }
            cout << "creating node" << endl;
            Ops = new Command(Node);
        }
    }
    //cout << "count: " << count << endl;
    //cout << "   got left" << endl;
    ss.str( string() );
    ss.clear();
    Node.clear();
    cout << "count: " << count << endl;
    cout << "   getting right" << endl;
     cout << "size" << cmds[count].size() <<endl;
    if((cmds[count].size())  > 1)
    {
        cout << "entered" << cmds[count].size() <<endl;
        ss << cmds[count].at(1);
        
        cout << "found" << endl;
    while(ss >> temp)
    {
        if(temp == "1")
        {
            ss << cmds[count].at(2);
            ss >> temp;
        }
        cout << "entered while" << endl;
        
        cout << "Curr temp right: " << temp << endl;
        if (temp == "Recurse")
        {
            level++;
            currint++;
            count = level;
            Opt = treecreate(cmds, ops, op, count, currint, level);
            currint--;
            count = currint;
        }
        
        else
        {
            Node.push_back(temp);
            while(ss >> temp)
            {
                cout << "Curr temp right: " << temp << endl;
                Node.push_back(temp);
            }
            Opt = new Command(Node);
        }
    }
    cout << "count: " << count << endl;
    cout << "   got right" << endl;
    ss.str( string() );
    ss.clear();
    Node.clear();
    }
    else
    {
        cout << "   null right" <<endl;
        Opt = NULL;
    }
    cout << "   getting op" << count << endl;
    cout << "ops size" << ops.size() << endl;
    if(!ops[count].empty())
    {
        cout << "entered ops" << endl;
        ss << ops[count].at(0);
    //cout << "Currently at op 0: " << ops[count].at(0) << endl;
    if(ss >> temp)
    {
        cout << "Curr temp: " << temp << endl;
        Node.push_back(temp);
        if(temp == "&&")
        {
            cout << "create link &&" << endl;
            op = new ANND(Ops, Opt);
        }
        else if(temp == "||")
        {
            op = new ORR(Ops, Opt);
        }
        else
        {
            op = new Scolon(Ops, Opt);
        }
        
    }
    else
    {
        cout << "create default scolon link" << endl;
        op = new Scolon(Ops, Opt);
    }
    }
    else
    {
        cout << "standardizing op scolon" << endl;
        op = new Scolon(Ops, Opt);
        //cout << "returning" << endl;
        //return op;
    }
    //cout << "count: " << count << endl;
    //cout << "   got op" << endl;
    Ops = NULL;
    Opt = NULL;
    ss.str( string() );
    ss.clear();
    Node.clear();
    //cout << "count: " << count << endl;
    //cout << "entering loop" << endl;
    
    for(unsigned i = 1; i < ops[count].size(); i++)
    {
        //cout << "for loop" << endl;
        if((cmds[count].size() - 1) != i)
        {
            ss << cmds[count].at(i);
            //cout << "if statment" << endl;
            ss << cmds[count].at(i + 1);
            if(ss >> temp)
            {
                cout << "Curr temp left: " << temp << endl;
                if (temp == "Recurse")
                {
                    level++;
                    currint++;
                    count = level;
                    //cout << "recursing" << endl;
                    Opt = treecreate(cmds, ops, op, count, currint, level);
                    currint--;
                    count = currint;
                }
                else if(temp == " ")
                {
                    Opt = NULL;
                }
                else
                {
                    Node.push_back(temp);
                    while(ss >> temp)
                    {
                        cout << "Curr temp left: " << temp << endl;
                        Node.push_back(temp);
                    }
                    Opt = new Command(Node);
                }
            }        
            ss.str( string() );
            ss.clear();
            Node.clear();
           // cout << "   got leftg" << endl;
        }
        
        if(!ops[count].empty())
        {
            ss << ops[count].at(i);
        //cout << "Currently at op" << i << ": " << ops[count].at(i) << endl;
        if(ss >> temp)
        {
            cout << "Curr temp right: " << temp << endl;
            Node.push_back(temp);
            if(temp == "&&")
            {
                Opt = new ANND(Ops, op);
                op = Opt;
            }
            else if(temp == "||")
            {
                Opt = new ORR(Ops, op);
                op = Opt;
            }
            else
            {
                Opt = new Scolon(Ops, op);
                op = Opt;
            }
        
        }
        else
        {
            Opt = new Scolon(Ops, op);
            op = Opt;
        }
        }
        else
        {
            //cout << "standardizing op scolon" << endl;
            op = new Scolon(Ops, Opt);
        }
       // cout << "   got op" << endl;
    }
        ss.str( string() );
        ss.clear();
        Node.clear();
        Ops = NULL;
        Opt = NULL;
    
    
    
    return op;
}


void breakup(string test, vector <vector <string> > & cmds, vector <vector <string> > & ops, unsigned & rct, unsigned & nbc)
{
    cmds.push_back(vector <string>());
    ops.push_back(vector <string>());
    string curr;
    string temp;
    string recur;
    stringstream ss;
    stringstream testss;
    stringstream cmd;
    string wholecmd;
    string check = "Recurse";
    ss << test;
    cout << "       current rct/nbc: " << endl;
    cout << rct << " / " << nbc << endl;


    
    while(ss >> curr)
    {
        cout << "           Global curr: " << curr << endl;
        if((curr != "||") && (curr != "&&") && (curr != ";") )
        {
            cout << "found no op" << endl;
            
            for(unsigned i = 0; i < curr.size(); i++)
            {
                cout << "Current i is: " << curr.at(i) << endl; 
                if(curr.at(i) == '(') //start parenth check -
                {
                    if(curr.size() == 1) //parenth organizers --start
                    {
                        ss >> curr;
                        i = 0;
                    }
                    else if( i == curr.size() - 1)
                    {
                        curr = curr.substr(0, i);
                        cmd << curr;
                        cmd << " ";
                        ss >> curr;
                        i = 0;
                    }
                    else if (i == 0)
                    {
                        curr = curr.substr(1, curr.size() - 1);
                        i = 0;
                    }
                    else
                    {
                        temp = curr.substr(0, i);
                        cmd << temp;
                        cmd << " ";
                        curr = curr.substr(i + 1, (i - (curr.size() - 1)));
                        i = 0;
                    }                   //parenth organizers --end
                    unsigned numparent = 1; //find ending parenth ---start
                    while(numparent != 0)
                    {
                        if (curr.at(i) == ')')
                        {
                            numparent--;
                            i++;
                        }
                        else if (curr.at(i) == '(')
                        {
                            numparent++;
                            i++;
                        }
                        else if( i == curr.size() - 1)
                        {
                            testss << curr;
                            testss << " ";
                            ss >> curr;
                            i = 0;
                        }
                        else
                        {
                            i++;
                        }
                    }
                    if( i != 0)
                    {
                        //cout << "end parent is in last word" << endl;
                        //cout << "current curr: " << curr << endl;
                        curr = curr.substr(0, i - 1);
                        //cout << "new curr: " << curr << endl;
                        testss << curr;
                    }
                    recur = testss.str(); //find ennding parenth ---end
                    testss.str( string() );
                    testss.clear();
                    cout << "       current rct/nbc: " << endl;
                    cout << rct << " / " << nbc << endl;                    
                    
                    rct++;
                    nbc++;
                    cout << "       String to be sent: " << endl;
                    cout << recur << endl;
                    cout << "       current rct/nbc: " << endl;
                    cout << rct << " / " << nbc << endl;
                    cmd << check;
                    cmd << " ";
                    cmd << nbc;                    
                    breakup(recur, cmds, ops, rct, nbc);
                    rct--;
                    cout << "       new rct/nbc: " << endl;
                    cout << rct << " / " << nbc << endl;

                    wholecmd = cmd.str();
                    cout << "current rct before pushback: " << rct << endl;
                    cmds[rct].push_back(wholecmd);
                    cmd.str( string() );
                    cmd.clear();
                    curr = "1 ";
                    i = curr.size();              // end recurstion part --
                    
                }
                else if(curr.at(i) == '"')
                {
                cout << "encountered quote in " << curr <<  endl;
                    if(curr.size() == 1)
                    {
                        ss >> curr;
                    }
                    else
                    {
                        curr = curr.substr(1, curr.size() - 1);
                    }
                    if(i < curr.size() - 1)
                    {
                        i++;
                    }
                    else
                    {
                        i = 0;
                        cmd << " ";
                        ss >> curr;
                        cout << "New curr: (space) " << curr << endl;
                    }
                    while(curr.at(i) != '"')
                    {
                        cout << "while looping" << endl;
                        cout << "found: " << curr.at(i) << endl;
                        if(i == (curr.size() - 1))
                        {
                            i = 0;
                            cmd << curr;
                            cmd << " ";
                            ss >> curr;
                            cout << "New curr: (std) " << curr << endl;
                            //cout << "switched to next curr" << endl;
                        }
                        if(i < curr.size() - 1)
                        {
                            cout << "increased" << endl;
                            cout << "at i: " << curr.at(i) << endl;
                            i++;
                        }
                    }
                    if(curr.at(i) == '"')
                    {
                        cout << "Deleted parent" << endl;
                        curr.at(i) = '\0';
                    }
                }
                else if(curr.at(i) == '#')
                {
                    cout << "   found pound in " << curr <<endl;
                    if(i == 0)
                    {
                        return;
                    }
                    else
                    {
                    curr = curr.substr(0, i);
                    cmd << curr;
                    cout << "   curr before pound " << curr <<endl;
                    wholecmd = cmd.str();
                    cmds[rct].push_back(wholecmd);
                    cmd.str( string() );
                    cmd.clear();
                    
                    return;
                    }
                }
                else if(curr.at(i) == ';')
                {
                    cout << "   found embeded op" << endl;
                    if(i == 0)
                    {
                        cout << "   Found something after" << endl;
                        temp = curr.at(i);
                        //cout << "Temp is now: " << temp << endl; 
                        curr = curr.substr(1, curr.size() -1);
                        wholecmd = cmd.str();
                        cmds[rct].push_back(wholecmd);
                        ops[rct].push_back(temp);
                        cmd.str( string() );
                        cmd.clear();
                        i = 0;
                        
                    }
                    else
                    {
                        if(i != curr.size() - 1)
                        {
                            cout << "   Found things before and after" << endl;
                            temp = curr.substr(i, i - curr.size() - 1);
                            curr = curr.substr(0, i);
                            cmd << curr;
                            wholecmd = cmd.str();
                            cmds[rct].push_back(wholecmd);
                            cmd.str( string() );
                            cmd.clear();
                            curr = temp.substr(1, temp.size() - 1);
                            temp = temp.substr(0, 1);
                            ops[rct].push_back(temp);
                            i = 0;
                            
                            
                        }
                        else
                        {
                            cout << "   Found something before" << endl;
                            temp = curr.at(i);
                            curr = curr.substr(0, i);
                            cmd << curr;
                            wholecmd = cmd.str();
                            cmds[rct].push_back(wholecmd);
                            cmd.str( string() );
                            cmd.clear();
                            ops[rct].push_back(temp);
                                cout << "continuing" << endl;
                                curr = " ";
                                i = curr.size();
                        }
                        
                    }
                }
                else if(curr.at(i) == '|')
                {
                    cout << "   found embeded op" << endl;
                    if(i == 0)
                    {
                        cout << "   Found something after" << endl;
                        temp = curr.substr(0, 2);
                        //cout << "Temp is now: " << temp << endl; 
                        curr = curr.substr(2, curr.size() -1);
                        wholecmd = cmd.str();
                        cmds[rct].push_back(wholecmd);
                        ops[rct].push_back(temp);
                        cmd.str( string() );
                        cmd.clear();
                        i = 0;
                        
                    }
                    else
                    {
                        if(i != curr.size() - 2)
                        {
                            cout << "   Found things before and after" << endl;
                            temp = curr.substr(i, i - curr.size() - 1);
                            curr = curr.substr(0, i);
                            cmd << curr;
                            wholecmd = cmd.str();
                            cmds[rct].push_back(wholecmd);
                            cmd.str( string() );
                            cmd.clear();
                            curr = temp.substr(2, temp.size() - 1);
                            temp = temp.substr(0, 2);
                            ops[rct].push_back(temp);
                            i = 0;
                            
                            
                        }
                        else
                        {
                            cout << "   Found something before" << endl;
                            temp = curr.substr(i, 2);
                            curr = curr.substr(0, i);
                            cmd << curr;
                            wholecmd = cmd.str();
                            cmds[rct].push_back(wholecmd);
                            cmd.str( string() );
                            cmd.clear();
                            ops[rct].push_back(temp);

                                curr = " ";
                                i = curr.size();

                        }
                        
                    }
                }
                else if(curr.at(i) == '&')
                {
                    cout << "   found embeded op" << endl;
                    if(i == 0)
                    {
                        cout << "   Found something after" << endl;
                        temp = curr.substr(0, 2);
                        //cout << "Temp is now: " << temp << endl; 
                        curr = curr.substr(2, curr.size() -1);
                        wholecmd = cmd.str();
                        cmds[rct].push_back(wholecmd);
                        ops[rct].push_back(temp);
                        cmd.str( string() );
                        cmd.clear();
                        i = 0;
                        
                    }
                    else
                    {
                        if(i != curr.size() - 2)
                        {
                            cout << "   Found things before and after" << endl;
                            temp = curr.substr(i, i - curr.size() - 1);
                            curr = curr.substr(0, i);
                            cmd << curr;
                            wholecmd = cmd.str();
                            cmds[rct].push_back(wholecmd);
                            cmd.str( string() );
                            cmd.clear();
                            curr = temp.substr(2, temp.size() - 1);
                            temp = temp.substr(0, 2);
                            ops[rct].push_back(temp);
                            i = 0;
                            
                            
                        }
                        else
                        {
                            cout << "   Found something before" << endl;
                            temp = curr.substr(i, 2);
                            curr = curr.substr(0, i);
                            cmd << curr;
                            wholecmd = cmd.str();
                            cmds[rct].push_back(wholecmd);
                            cmd.str( string() );
                            cmd.clear();
                            ops[rct].push_back(temp);

                                curr = " ";
                                i = curr.size();
      
                        }
                        
                    }
                }
                
            }
            if(curr.at(curr.size() - 1) == '"')
            {
            curr.at(curr.size() - 1) = '\0';
            }

            cout << "New curr: (end) " << curr << endl;
            cmd << curr;
            cmd << " ";
        }
        else
        {
            cout << "found op" << endl;
            wholecmd = cmd.str();
            cmds[rct].push_back(wholecmd);
            
            ops[rct].push_back(curr);
            cmd.str( string() );
            cmd.clear();
        }
        cout << " curr: " << curr << endl;
    }
    cout << "finalizing" << endl;
    cout << "Cmd: " << cmd.str() << endl;
    wholecmd = cmd.str();
    cout << "current rct: " << rct << endl;
    cmds[rct].push_back(wholecmd);
    cmd.str( string() );
    cmd.clear();
    
    return;
}
    


int main()
{
    string testcmd = "(echo \"True\" && echo \"false\") && echo \"false\"";
    vector <vector <string> > cmds;
    vector <vector <string> > ops;
    Base* op;
    unsigned recurstrack = 0;
    unsigned numbcalls = 0;
    unsigned count = 0;
    unsigned currint = 0;
    unsigned level = 0;
    
    breakup(testcmd, cmds, ops,  recurstrack, numbcalls);
    
    cout << "cmds list:" << endl;
    
    for(unsigned i = 0; i < cmds.size(); i++)
    {
        for(unsigned j = 0; j < cmds[i].size(); j++)
        {
            cout << "for cmd: " << i << " , " << j << " it is:" << endl;
            cout << cmds[i][j] << endl;
        }
        cout << endl;
    }
    
    cout << "ops list:" << endl;
    
    for(unsigned a = 0; a < ops.size(); a++)
    {
        for(unsigned b = 0; b < ops[a].size(); b++)
        {
            cout << "for op: " << a << " , " << b << " it is:" << endl;
            cout << ops[a][b] << endl;
        }
        cout << endl;
    }
    
     cout << "opsize" << ops.size() <<endl;
     cout << "cmdsize" << cmds.size() <<endl;
    
    cout << endl;
    cout << "Beginning organizing and tree creation" << endl;
    
    op = treecreate(cmds, ops, op, count, currint, level);
    
    cout << "Executing tree" << endl;
    cout << endl;
    
    op->execution();
    
    cout << endl;
    cout << "Execution finished" << endl;
    
    return 0;
}