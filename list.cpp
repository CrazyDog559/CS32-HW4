//
//  list.cpp
//  HW4
//
//  Created by Drew Wan on 5/26/23.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class MenuItem
{
  public:
    MenuItem(string nm) : m_name(nm) {}
    virtual ~MenuItem() {}
    string name() const { return m_name; }
    virtual bool add(MenuItem* m) = 0;
    virtual const vector<MenuItem*>* menuItems() const = 0;
  private:
    string m_name;
};

class PlainMenuItem : public MenuItem   // PlainMenuItem allows no submenus
{
  public:
    PlainMenuItem(string nm) : MenuItem(nm) {}
    virtual bool add(MenuItem* m) { return false; }
    virtual const vector<MenuItem*>* menuItems() const { return nullptr; }
};

class CompoundMenuItem : public MenuItem  // CompoundMenuItem allows submenus
{
  public:
    CompoundMenuItem(string nm) : MenuItem(nm) {}
    virtual ~CompoundMenuItem();
    virtual bool add(MenuItem* m) { m_menuItems.push_back(m); return true; }
    virtual const vector<MenuItem*>* menuItems() const { return &m_menuItems; }
  private:
    vector<MenuItem*> m_menuItems;
};

CompoundMenuItem::~CompoundMenuItem()
{
    for (int k = 0; k < m_menuItems.size(); k++)
        delete m_menuItems[k];
}

void listAll(const MenuItem* m, string path) // two-parameter overload
{
    
//    if ( m == nullptr) {
//        return;
//    }
//    if(!path.empty()) {
//        cout << path << endl;
//    }
//    if (m -> menuItems() == nullptr) {
//        return;
//    }
//
//    const vector <MenuItem*>* menu = m->menuItems();
//    for (const MenuItem* it: *menu) {
//        listAll(it , path + "/" + it -> name());
//    }
    
//    if (!path.empty()) // Output the complete path if the path is not empty
//           cout << path << "/" << m->name() << endl;
//       else
//           cout << m->name() << endl;
//
//       if (m->menuItems() == nullptr) // If the menu item has no submenus, return
//           return;
//
//       const vector<MenuItem*>* items = m->menuItems(); // Get the submenus
//
//       for (size_t i = 0; i < items->size(); i++)
//       {
//           if (!path.empty()) // Append the current menu item's name to the path
//               listAll((*items)[i], path + "/" + m->name());
//           else
//               listAll((*items)[i], m->name());
//       }
    
    
    // If the menu item has no submenus, output the path and return
        if (m->menuItems() == nullptr) {
                cout << path << m->name() << endl;
                return;
        }

//        if (!path.empty()) // Output the path if it is not empty
//            path += "/";
    
        path += m->name();
        
        if (!path.empty())
            cout << path << endl; // Output the current path

        const vector<MenuItem*>* items = m->menuItems(); // Get the submenus

        for (size_t i = 0; i < items->size(); i++) {
            
            // Pass the current path to the recursive call
            if (!path.empty()) {
                listAll((*items)[i], path + "/");
            } else {
                listAll((*items)[i], path);
            }
        }
        
  
    
    
  
   
}

void listAll(const MenuItem* m)  // one-parameter overload
{
    if (m != nullptr)
        listAll(m, "");
}

int main()
{
    CompoundMenuItem* cm0 = new CompoundMenuItem("New");
    cm0->add(new PlainMenuItem("Window"));
    CompoundMenuItem* cm1 = new CompoundMenuItem("File");
    cm1->add(cm0);
    cm1->add(new PlainMenuItem("Open"));
    cm1->add(new PlainMenuItem("Exit"));
    CompoundMenuItem* cm2 = new CompoundMenuItem("Help");
    cm2->add(new PlainMenuItem("Index"));
    cm2->add(new PlainMenuItem("About"));
    CompoundMenuItem* cm3 = new CompoundMenuItem("");  // main menu bar
    cm3->add(cm1);
    cm3->add(new PlainMenuItem("Refresh"));  // no submenu
    cm3->add(new CompoundMenuItem("Under Development")); // no submenus yet
    cm3->add(cm2);
    listAll(cm3);
    delete cm3;
}


