
// 1600. Throne Inheritance
// https://leetcode.com/problems/throne-inheritance/


struct Person {
    string name;
    bool isAlive;
    vector<Person*> children;
    Person(string nm) : name(nm), isAlive(true), children({}) {}
};

class ThroneInheritance {
private:
    Person * king;
    bool done;
    unordered_map<string,Person*> um;

    void insert(string& parentName, string& childName, Person * person) {
        if( done ) return;
        if( person->name == parentName) {
            Person * child = new Person(childName);
            person->children.push_back(child);
            done = true;
            return;
        }
        for(auto it = begin(person->children); it != end(person->children); ++it) {
            insert(parentName,childName,*it);
            if( done ) break;
        }
    }

    void insert2(string& parentName, string& childName) {
        Person * child = new Person(childName);
        um.insert({childName,child});
        auto find = um.find(parentName);
        find->second->children.push_back(child);
    }

    void markDead(string& name, Person * person) {
        if( done ) return;
        if( person->name == name) {
            person->isAlive = false;
            done = true;
            return;
        }
        for(auto it = begin(person->children); it != end(person->children); ++it) {
            markDead(name,*it);
            if( done ) break;
        }
    }

    void markDead2(string& name) {
        auto find = um.find(name);
        find->second->isAlive = false;
    }

    void successor(Person * person, vector<string>& r) {
        if( person->isAlive) r.push_back(person->name);
        for(auto it = begin(person->children); it != end(person->children); ++it)
            successor(*it,r);
    }
public:
    ThroneInheritance(string kingName) {
        king = new Person(kingName);
        um.insert({kingName,king});
    }

    void birth(string parentName, string childName) {
        // done = false;
        // insert(parentName,childName,king);
        insert2(parentName,childName);
    }

    void death(string name) {
        // done = false;
        // markDead(name,king);
        markDead2(name);
    }

    vector<string> getInheritanceOrder() {
        vector<string> r;
        successor(king,r);
        return r;
    }
};

/**
 * Your ThroneInheritance object will be instantiated and called as such:
 * ThroneInheritance* obj = new ThroneInheritance(kingName);
 * obj->birth(parentName,childName);
 * obj->death(name);
 * vector<string> param_3 = obj->getInheritanceOrder();
 */
