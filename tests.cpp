/// @file tests.cpp
/// @date March 17, 2023

/// 
/// TODO

/// Provided testing file to implement framework based tests in. The examples
/// below demonstrates a basic empty test in each framework with a single
/// assertion. The version uses the supplied catch.hpp file in starter code.
///
/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Spring 2023

// TODO:
// Choose which framework to keep and delete the other.
//


// Catch 1.0 Framework Testing
#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "priorityqueue.h"
#include <map>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;



//fills integer maps
void mapInsert(map<int,vector<int>>& intmap, int key, int value) {
    if(intmap.find(key) == intmap.end()){
        vector<int> temp;
        intmap.insert(pair<int, vector<int>>(key, temp));
    }
    intmap.at(key).push_back(value);
}

//fills char maps
void mapInsert(map<int,vector<char>>& cmap, int key, int value) {
    if(cmap.find(key) == cmap.end()){
        vector<char> temp;
        cmap.insert(pair<int, vector<char>>(key, temp));
    }
    cmap.at(key).push_back(value);
}

//fills string maps
void mapInsert(map<int,vector<string>>& stringmap, int key, string value) {
    if(stringmap.find(key) == stringmap.end()){
        vector<string> temp;
        stringmap.insert(pair<int, vector<string>>(key, temp));
    }
    stringmap.at(key).push_back(value);
}

//creates a string for testing toString functions
string mapToString(map<int,vector<int>> intmap) {
    stringstream ss;
    for(pair<int,vector<int>> values : intmap) {
        for(int v : values.second) {
            ss << values.first << " value: " << v << "\n";
        }
    }
    return ss.str();
}

//creates a string for testing toString functions
string mapToString(map<int,vector<char>> intmap) {
    stringstream ss;
    for(pair<int,vector<char>> values : intmap) {
        for(char v : values.second) {
            ss << values.first << " value: " << v << "\n";
        }
    }
    return ss.str();
}

//creates a string for testing toString functions
string mapToString(map<int,vector<string>> intmap) {
    stringstream ss;
    for(pair<int,vector<string>> values : intmap) {
        for(string v : values.second) {
            ss << values.first << " value: " << v << "\n";
        }
    }
    return ss.str();
}



TEST_CASE("(0) no tests") 
{
    REQUIRE(true);
}

// default constructor, enqueue, size
TEST_CASE("priorityqueue types") {
    priorityqueue<int> intqueue;
    priorityqueue<double> doublequeue;
    priorityqueue<string> stringqueue;
    priorityqueue<char> charqueue;
    priorityqueue<bool> boolqueue;
    intqueue.enqueue(6, 5);
    doublequeue.enqueue(6.77, 5);
    stringqueue.enqueue("hello", 5);
    charqueue.enqueue('c', 5);
    boolqueue.enqueue(1, 5);
    
    REQUIRE(intqueue.Size() == 1);
    REQUIRE(doublequeue.Size() == 1);
    REQUIRE(stringqueue.Size() == 1);
    REQUIRE(charqueue.Size() == 1);
    REQUIRE(boolqueue.Size() == 1);
    intqueue.clear();
    doublequeue.clear();
    stringqueue.clear();
    charqueue.clear();
    boolqueue.clear();
}

//default constructor, enqueue, size, toString, clear
TEST_CASE("duplicate value and priority") {
    priorityqueue<char> cqueue;
    map<int, vector<char>> cmap;
    for (int i = 0; i < 10; i++) {
        cqueue.enqueue('c', 5);
        mapInsert(cmap, 5, 'c');
        REQUIRE(cqueue.Size() == i + 1);
    }
    REQUIRE(mapToString(cmap) == cqueue.toString());
    cqueue.clear();
    REQUIRE(cqueue.Size() == 0);

    priorityqueue<int> iqueue;
    map<int, vector<int>> imap;
    for (int i = 0; i < 10; i++) {
        iqueue.enqueue(20, 5);
        mapInsert(imap, 5, 20);
        REQUIRE(iqueue.Size() == i + 1);
    }
    REQUIRE(mapToString(imap) == iqueue.toString());
    iqueue.clear();
    REQUIRE(iqueue.Size() == 0);

    priorityqueue<string> squeue;
    map<int, vector<string>> smap;
    for (int i = 0; i < 10; i++) {
        squeue.enqueue("apple", 5);
        mapInsert(smap, 5, "apple");
        REQUIRE(squeue.Size() == i + 1);
    }
    REQUIRE(mapToString(smap) == squeue.toString());
    squeue.clear();
    REQUIRE(squeue.Size() == 0);
}

//default constructor, enqueue, size, toString, clear
TEST_CASE("duplicate priority only") {
    priorityqueue<char> cqueue;
    string cvals = "abcdefghijk";
    map<int, vector<char>> cmap;
    for (int i = 0; i < 10; i++) {
        cqueue.enqueue(cvals[i], 5);
        mapInsert(cmap, 5, cvals[i]);
        REQUIRE(cqueue.Size() == i + 1);
    }
    REQUIRE(mapToString(cmap) == cqueue.toString());
    cqueue.clear();
    REQUIRE(cqueue.Size() == 0);

    priorityqueue<int> iqueue;
    map<int, vector<int>> imap;
    for (int i = 0; i < 10; i++) {
        iqueue.enqueue(i, 5);
        mapInsert(imap, 5, i);
        REQUIRE(iqueue.Size() == i + 1);
    }
    REQUIRE(mapToString(imap) == iqueue.toString());
    iqueue.clear();
    REQUIRE(iqueue.Size() == 0);

    priorityqueue<string> squeue;
    map<int, vector<string>> smap;
    string words[] = {"apple","banana","cherry","tomato","pumpkin","rhubarb", "orange", "lemon", "eggplant", "watermelon"};
    for (int i = 0; i < 10; i++) {
        squeue.enqueue(words[i], 5);
        mapInsert(smap, 5, words[i]);
        REQUIRE(squeue.Size() == i + 1);
    }
    REQUIRE(mapToString(smap) == squeue.toString());
    squeue.clear();
    REQUIRE(squeue.Size() == 0);
}

//default constructor, enqueue, size, toString, clear
TEST_CASE("duplicate value only") {
    priorityqueue<char> cqueue;
    map<int, vector<char>> cmap;
    for (int i = 0; i < 10; i++) {
        cqueue.enqueue('c', i);
        mapInsert(cmap, i, 'c');
        REQUIRE(cqueue.Size() == i + 1);
    }
    REQUIRE(mapToString(cmap) == cqueue.toString());
    cqueue.clear();
    REQUIRE(cqueue.Size() == 0);

    priorityqueue<int> iqueue;
    map<int, vector<int>> imap;
    for (int i = 0; i < 10; i++) {
        iqueue.enqueue(20, i);
        mapInsert(imap, i, 20);
        REQUIRE(iqueue.Size() == i + 1);
    }
    REQUIRE(mapToString(imap) == iqueue.toString());
    iqueue.clear();
    REQUIRE(iqueue.Size() == 0);

    priorityqueue<string> squeue;
    map<int, vector<string>> smap;
    for (int i = 0; i < 10; i++) {
        squeue.enqueue("apple", i);
        mapInsert(smap, i, "apple");
        REQUIRE(squeue.Size() == i + 1);
    }
    REQUIRE(mapToString(smap) == squeue.toString());
    squeue.clear();
    REQUIRE(squeue.Size() == 0);
}

//default constructor, enqueue, size, toString, clear
TEST_CASE("mixed duplicates") {
    priorityqueue<char> cqueue;
    string cvals = "abcdefghijk";
    map<int, vector<char>> cmap;
    for (int i = 0; i < 10; i++) {
        cqueue.enqueue(cvals[i % 3], i / 2);
        mapInsert(cmap, i / 2, cvals[i % 3]);
        REQUIRE(cqueue.Size() == i + 1);
    }
    REQUIRE(mapToString(cmap) == cqueue.toString());
    cqueue.clear();
    REQUIRE(cqueue.Size() == 0);

    priorityqueue<int> iqueue;
    map<int, vector<int>> imap;
    for (int i = 0; i < 10; i++) {
        iqueue.enqueue(i % 3, i / 2);
        mapInsert(imap, i / 2, i % 3);
        REQUIRE(iqueue.Size() == i + 1);
    }
    REQUIRE(mapToString(imap) == iqueue.toString());
    iqueue.clear();
    REQUIRE(iqueue.Size() == 0);

    priorityqueue<string> squeue;
    map<int, vector<string>> smap;
    string words[] = {"apple","banana","cherry","tomato","pumpkin","rhubarb", "orange", "lemon", "eggplant", "watermelon"};
    for (int i = 0; i < 10; i++) {
        squeue.enqueue(words[i % 3], i / 2);
        mapInsert(smap, i / 2, words[i % 3]);
        REQUIRE(squeue.Size() == i + 1);
    }
    REQUIRE(mapToString(smap) == squeue.toString());
    squeue.clear();
    REQUIRE(squeue.Size() == 0);
}


//default constructor, enqueue, toString, size, clear
TEST_CASE("clearing") {
    string words[] = {"apple","banana","cherry","tomato","pumpkin","rhubarb", "orange", "lemon", "eggplant", "watermelon"};
    map<int,vector<string>> stringmap;
    priorityqueue<string> stringqueue;

    REQUIRE(stringqueue.Size() == 0);
    stringqueue.clear(); 
    REQUIRE(stringqueue.Size() == 0);

    //duplicate values
    for (int i = 0; i < 10; i++) {
        stringqueue.enqueue(words[i], i/2);
        mapInsert(stringmap, i/2 , words[i]);
        REQUIRE(stringqueue.Size() == i + 1);
    }
    REQUIRE(mapToString(stringmap) == stringqueue.toString());
    stringqueue.clear();
    REQUIRE(stringqueue.Size() == 0); 
    stringqueue.clear();
    REQUIRE(stringqueue.Size() == 0); 
    stringmap.clear();

    int priorities[] = {5,2,10,11,7,6,8,9,2,1,3,4};
    for (int i = 0; i < 11; i++) {
        stringqueue.enqueue(words[i % 10], priorities[i]);
        mapInsert(stringmap, priorities[i] , words[i % 10]);
        REQUIRE(stringqueue.Size() == i + 1);
    }
    REQUIRE(mapToString(stringmap) == stringqueue.toString());
    stringqueue.clear();
    REQUIRE(stringqueue.Size() == 0);
}

TEST_CASE("dequeue") {
    priorityqueue<int> iqueue;
    map<int, vector<int>> imap;

    int priorities[] = {5,2,10,11,7,6,8,9,2,1,3,4};

    for (int i = 0; i < 11; i++) {
        iqueue.enqueue(i % 10, priorities[i]);
        mapInsert(imap, priorities[i] , i % 10);
        REQUIRE(iqueue.Size() == i + 1);
    }
    for (int i = 0; i < 11; i++) {
        iqueue.dequeue();
        REQUIRE(iqueue.Size() == 10-i);
    }
    REQUIRE(iqueue.Size() == 0);
    iqueue.clear();
    REQUIRE(iqueue.Size() == 0);

}

//default constructor, enqueue, size, toString, clear, next
TEST_CASE("random") {
    string words[] = {"apple","banana","cherry","tomato","pumpkin","rhubarb", "orange", "lemon", "eggplant", "watermelon"};
    map<int,vector<string>> stringmap;
    vector<string> scheck;
    vector<int> icheck, pcheck;
    priorityqueue<string> stringqueue;
    int pval, ival, index;
    string sval;

    srand(0);
    for (int i = 0; i < 100; i++) {
        int rand1 = rand() % 10, rand2 = rand() % 10;
        stringqueue.enqueue(words[rand1], rand2);
        REQUIRE(stringqueue.Size() == i + 1);
        mapInsert(stringmap, rand2 , words[rand1]);
        scheck.push_back(words[rand1]);
        pcheck.push_back(rand2);
    }
    REQUIRE(mapToString(stringmap) == stringqueue.toString());

    index = 0;
    while (stringqueue.next(sval, pval)) {
        REQUIRE(sval == scheck[index]);
        REQUIRE(pval == pcheck[index]);
        index++;
    }
    
    stringqueue.clear();
    stringmap.clear();
    pcheck.clear();
    REQUIRE(stringqueue.Size() == 0);

    map<int,vector<int>> intmap;
    priorityqueue<int> intqueue;

    for (int i = 0; i < 100; i++) {
        int rand1 = rand() % 10, rand2 = rand() % 10;
        intqueue.enqueue(rand1, rand2);
        REQUIRE(intqueue.Size() == i + 1);
        mapInsert(intmap, rand2 , rand1);
        icheck.push_back(rand1);
        pcheck.push_back(rand2);
    }
    REQUIRE(mapToString(intmap) == intqueue.toString());

    index = 0;
    while (intqueue.next(ival, pval)) {
        REQUIRE(ival == icheck[index]);
        REQUIRE(pval == pcheck[index]);
        index++;
    }

    for(int i = 0; i < 100; i++) {
        intqueue.dequeue();
        REQUIRE(intqueue.Size() == 99 - i);
    }

    intqueue.clear();
    intmap.clear();
    REQUIRE(intqueue.Size() == 0);
}

//tests = and == operator for multiple types
TEST_CASE("Equals") {
    priorityqueue<int> iq, niq;
    priorityqueue<char> cq, ncq;
    priorityqueue<string> sq, nsq;
    map<int, vector<int>> imap;
    map<int, vector<char>> cmap;
    map<int, vector<string>> smap;
    int priorities[] = {5,2,10,11,7,6,8,9,2,1,3,4};
    string words[] = {"apple","banana","cherry","tomato","pumpkin","rhubarb", "orange", "lemon", "eggplant", "watermelon"};
    string letters = "abcdefghijkl";
    srand(0);

    for(int i = 0; i < 10; i++) {
        iq.enqueue(i, priorities[i]);
        mapInsert(imap, priorities[i], i);
    }
    for(int i = 0; i < 10; i++) {
        cq.enqueue(letters[i], priorities[i]);
        mapInsert(cmap, priorities[i], letters[i]);
    }
    for(int i = 0; i < 10; i++) {
        sq.enqueue(words[i], priorities[i]);
        mapInsert(smap, priorities[i], words[i]);
    }
    REQUIRE(mapToString(imap) == iq.toString());
    REQUIRE(mapToString(cmap) == cq.toString());
    REQUIRE(mapToString(smap) == sq.toString());

    niq = iq;
    ncq = cq;
    nsq = sq;

    REQUIRE(iq.Size() == niq.Size());
    REQUIRE(cq.Size() == ncq.Size());
    REQUIRE(sq.Size() == nsq.Size());
    REQUIRE(niq == iq);
    REQUIRE(ncq == cq);
    REQUIRE(nsq == sq);
    REQUIRE(niq.toString() == iq.toString());
    REQUIRE(ncq.toString() == cq.toString());
    REQUIRE(nsq.toString() == sq.toString());

    for(int i = 0; i < 100; i++) {
        int rand1 = rand() % 10, rand2 = rand() % 10;
        iq.enqueue(rand1, priorities[rand2]);
        mapInsert(imap, priorities[rand2], rand1);
        cq.enqueue(letters[rand2], priorities[rand1]);
        mapInsert(cmap, priorities[rand1], letters[rand2]);
        sq.enqueue(words[rand1], priorities[rand2]);
        mapInsert(smap, priorities[rand2], words[rand1]);
    }

    REQUIRE(!(niq == iq));
    REQUIRE(!(ncq == cq));
    REQUIRE(!(nsq == sq));

    niq = iq;
    ncq = cq;
    nsq = sq;

    REQUIRE(niq == iq);
    REQUIRE(ncq == cq);
    REQUIRE(nsq == sq);
}