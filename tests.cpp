#include <gtest/gtest.h>
#include "priorityqueue.h"
//testing for a tree with one node
TEST(priorityqueue,oneNode)
{
    priorityqueue<string> pq;
    pq.enqueue("Mike",1);
    EXPECT_EQ("1 value: Mike\n",pq.toString());
    EXPECT_EQ(1,pq.Size());
}
//testing for tree with two nodes
TEST(priorityqueue,twoNodes)
{
    priorityqueue<string> pq2;
    pq2.enqueue("Mike",2);
    pq2.enqueue("Josh",1);
    EXPECT_EQ(2,pq2.Size());
}
//three nodes
TEST(priorityqueue,threeNodes)
{
    priorityqueue<string> pq3;
    pq3.enqueue("Mike",2);
    pq3.enqueue("Josh",1);
    pq3.enqueue("Sami",3);
    EXPECT_EQ(3,pq3.Size());
}
// four nodes
TEST(priorityqueue,fourNodes)
{
    priorityqueue<string> pq4;
    pq4.enqueue("Mike",2);
    pq4.enqueue("Josh",1);
    pq4.enqueue("Sami",3);
    pq4.enqueue("Carl",5);
    EXPECT_EQ(4,pq4.Size());
}
//testing if to string is working properly
TEST(priorityqueue,toString)
{
    priorityqueue<string> pq5;
    pq5.enqueue("Mike",2);
    pq5.enqueue("Sami",1);
    pq5.enqueue("Josh",3);
    pq5.enqueue("Carl",5);
    EXPECT_EQ("1 value: Sami\n2 value: Mike\n3 value: Josh\n5 value: Carl\n",pq5.toString());
}
// checking if to string is working, in combination with clear
TEST(priorityqueue,clear)
{
    priorityqueue<string> pq6;
    pq6.enqueue("Mike",2);
    pq6.enqueue("Sami",1);
    pq6.enqueue("Josh",3);
    pq6.enqueue("Carl",5);
    EXPECT_EQ(4,pq6.Size());
    EXPECT_EQ("1 value: Sami\n2 value: Mike\n3 value: Josh\n5 value: Carl\n",pq6.toString());
    pq6.clear();
    EXPECT_EQ("",pq6.toString());
    EXPECT_EQ(0,pq6.Size());
    EXPECT_EQ(nullptr,pq6.getRoot());
}
//testing if the equals operator works
TEST(priorityqueue,equalsOperator)
{
    priorityqueue<string> pq7;
    pq7.enqueue("Mike",2);
    pq7.enqueue("Sami",1);
    pq7.enqueue("Josh",3);
    pq7.enqueue("Ayah",5);
    priorityqueue<string> pq8;
    pq8 = pq7;
    EXPECT_EQ("1 value: Sami\n2 value: Mike\n3 value: Josh\n5 value: Ayah\n",pq7.toString()); 
    EXPECT_EQ("1 value: Sami\n2 value: Mike\n3 value: Josh\n5 value: Ayah\n",pq8.toString());
    pq8.clear();
    EXPECT_EQ("",pq8.toString());
    EXPECT_EQ(0,pq8.Size());
}
TEST(priorityqueue,beginFunction)
{
    priorityqueue<string> pq9;
    pq9.enqueue("Matt",12);
    pq9.enqueue("Sami",3);
    pq9.enqueue("Mike",4);
    pq9.enqueue("Josh",2);
    pq9.enqueue("Carl",5);
    string value = "hello";
    int priority = -1;
    pq9.begin();
    pq9.next(value,priority);
    EXPECT_EQ("Josh",value);
    EXPECT_EQ(2,priority);

}
TEST(priorityqueue,dequeueAndPeek)
{
    priorityqueue<string> pq10;
    pq10.enqueue("Michael",2);
    pq10.enqueue("Sami",1);
    pq10.enqueue("Matt",12);
    pq10.enqueue("Josh",3);
    pq10.enqueue("Carl",5);
    EXPECT_EQ("Sami",pq10.dequeue());
    EXPECT_EQ("2 value: Michael\n3 value: Josh\n5 value: Carl\n12 value: Matt\n",pq10.toString());
    EXPECT_EQ("Michael",pq10.peek());
}
TEST(priorityqueue,doubleEqualOperator)
{
    priorityqueue<string> pq11;
    pq11.enqueue("Michael",3);
    pq11.enqueue("Sami",1);
    priorityqueue<string> pq12;
    pq12.enqueue("Michael",3);
    pq12.enqueue("Sami",1); 
    priorityqueue<string> pq13;
    pq13.enqueue("Carl",3);
    pq13.enqueue("Josh",1);
    EXPECT_EQ(true,pq11 == pq12);
    EXPECT_EQ(false,pq11 == pq13);
}
TEST(priorityqueue,dequeueOnDups)
{
    priorityqueue<string> pq;
    pq.enqueue("sami",1);
    pq.enqueue("mike",1);
    pq.enqueue("josh",1);
    pq.enqueue("carl",1);
    EXPECT_EQ("sami",pq.dequeue());
    EXPECT_EQ("mike",pq.dequeue());
    EXPECT_EQ("josh",pq.dequeue());
    EXPECT_EQ("carl",pq.dequeue());

}
TEST(priorityqueue,doubleEqualsWithDups)
{
    priorityqueue<string> pq2;
    pq2.enqueue("sami",1);
    pq2.enqueue("mike",1);
    pq2.enqueue("josh",1);
    pq2.enqueue("carl",1);
    priorityqueue<string> pq;
    pq.enqueue("sami",1);
    pq.enqueue("mike",1);
    pq.enqueue("josh",1);
    pq.enqueue("carl",1);
    EXPECT_EQ(true,pq == pq2);
    priorityqueue<string> pq1;
    pq1.enqueue("sami",1);
    pq1.enqueue("mike",1);
    pq1.enqueue("josh",1);
    pq1.enqueue("ayah",1);
    EXPECT_EQ(false,pq1 == pq2);
}
TEST(priorityqueue,constructorTests)
{
    priorityqueue<string> pq;
    EXPECT_EQ(nullptr,pq.getRoot());
    EXPECT_EQ(0,pq.Size());  
}
TEST(priorityqueue,exampleTests)
{
    map<int, vector<int> > map;
    int n = 9;
    int vals[] = {15, 16, 17, 6, 7, 8, 9, 2, 1};
    int prs[] = {1, 2, 3, 2, 2, 2, 2, 3, 3};
    priorityqueue<int> pq;
    for (int i = 0; i < n; i++) {
        pq.enqueue(vals[i], prs[i]);
        map[prs[i]].push_back(vals[i]);
    }
    EXPECT_EQ(pq.Size(), 9);
    stringstream ss;
    for (auto e: map) {
        int priority = e.first;
        vector <int> values = e.second;
        for (size_t j = 0; j < values.size(); j++){
            ss << priority << " value: " << values[j] << endl;
        }
    }
    EXPECT_EQ(pq.toString(), ss.str());

}
TEST(priorityqueue,charTests)
{
    priorityqueue<char> pq;
    EXPECT_EQ(0,pq.Size());
    vector<char> letters;
    letters.push_back('a');
    letters.push_back('b');
    letters.push_back('c');
    letters.push_back('d');
    letters.push_back('e');
    letters.push_back('f');
    letters.push_back('g');
    letters.push_back('h');
    letters.push_back('i');
    letters.push_back('j');
    for(int i = 0; i< letters.size();i++)
    {
        pq.enqueue(letters[i],i+1);
    }
    EXPECT_EQ("1 value: a\n2 value: b\n3 value: c\n4 value: d\n5 value: e\n6 value: f\n7 value: g\n8 value: h\n9 value: i\n10 value: j\n",pq.toString());
    EXPECT_EQ(10,pq.Size());
    EXPECT_EQ('a',pq.peek());
    EXPECT_EQ('a',pq.dequeue());
    EXPECT_EQ("2 value: b\n3 value: c\n4 value: d\n5 value: e\n6 value: f\n7 value: g\n8 value: h\n9 value: i\n10 value: j\n",pq.toString());
    EXPECT_EQ('b',pq.peek());
    EXPECT_EQ('b',pq.dequeue());
    EXPECT_EQ("3 value: c\n4 value: d\n5 value: e\n6 value: f\n7 value: g\n8 value: h\n9 value: i\n10 value: j\n",pq.toString());
    priorityqueue<char> pq1;
    pq1 = pq;
    EXPECT_EQ(true,pq1==pq);
    EXPECT_EQ("3 value: c\n4 value: d\n5 value: e\n6 value: f\n7 value: g\n8 value: h\n9 value: i\n10 value: j\n",pq1.toString());
    EXPECT_EQ(8,pq1.Size());
    pq.clear();
    EXPECT_EQ("",pq.toString());
    EXPECT_EQ(0,pq.Size());
    EXPECT_EQ(nullptr,pq.getRoot());
}
TEST(priorityqueue,stringTests)
{
    priorityqueue<string> pq;
    vector<string> names;
    names.push_back("sam");
    names.push_back("mike");
    names.push_back("sami");
    names.push_back("josh");
    names.push_back("ayah");
    names.push_back("matt");
    names.push_back("john");
    names.push_back("carl");
    names.push_back("nate");
    for(int i = 0; i < names.size(); i++)
    {
        pq.enqueue(names[i],i+1);
    }
    EXPECT_EQ(9,pq.Size());
    EXPECT_EQ("sam",pq.peek());
    EXPECT_EQ(9,pq.Size());
    EXPECT_EQ("sam",pq.dequeue());
    EXPECT_EQ(8,pq.Size());
    EXPECT_EQ("2 value: mike\n3 value: sami\n4 value: josh\n5 value: ayah\n6 value: matt\n7 value: john\n8 value: carl\n9 value: nate\n",pq.toString());
    priorityqueue<string> pq1;
    pq1 = pq;
    EXPECT_EQ(8,pq1.Size());
    EXPECT_EQ("2 value: mike\n3 value: sami\n4 value: josh\n5 value: ayah\n6 value: matt\n7 value: john\n8 value: carl\n9 value: nate\n",pq.toString());
}
TEST(priorityqueue,duplicateTestsString)
{

    priorityqueue<string> pq;
    pq.enqueue("sami",5);
    pq.enqueue("mike",7);
    pq.enqueue("josh",1);
    pq.enqueue("jeffrey",1);
    pq.enqueue("carl",3);

    EXPECT_EQ(5,pq.Size());
    EXPECT_EQ("josh",pq.peek());
    EXPECT_EQ("josh",pq.dequeue());
     EXPECT_EQ(4,pq.Size());
    EXPECT_EQ("jeffrey",pq.peek());
    EXPECT_EQ("jeffrey",pq.dequeue());
    EXPECT_EQ(3,pq.Size());
    EXPECT_EQ("carl",pq.dequeue());
    EXPECT_EQ(2,pq.Size());
    EXPECT_EQ("sami",pq.dequeue());
    EXPECT_EQ(1,pq.Size());

}


int main()
{

    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
