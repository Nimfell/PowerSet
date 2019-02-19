#include <list>
#include <stdio.h>
#include <string.h>
using namespace std;

class PowerSet
{
 public:
  int Size; 
  list<char*>* slots;   

  PowerSet()
  {
    Size = 5;
    slots = new list<char*>[Size];
  }

  int size()
  {
    int quantity = 0;  // sum of list items  
    for (int i = 0; i < Size; i++)
	    quantity += slots[i].size();			
    return quantity;
  }

  void put(char* value)
  {
    if (get(value)) 
      return;

    int index = hashFun_CHAR(value);
    if (index == -1) 
      return;                           // if value == NULL

    int char_lengh = strlen(value); 	
    char* val = new char[char_lengh];		
    strcpy (val, value);
    slots[index].push_back(val);	    
  }

  bool get(char* value)
  { 
	int index = hashFun_CHAR(value);			//get index	  
    list<char*> List = slots[index];
	for (list<char*>::iterator _list = List.begin(); _list != List.end(); ++_list)
    {			
      char* _val = *_list;
      if ( strcmp(value, _val) == 0)	    // compare			  
		return true;
    }     
	return false;
  }
  
  bool remove(char* value)
  {
    int index = hashFun_CHAR(value);
    
    if (index != -1)
    {      
      char* _value = find(value);
      if (_value != NULL)
      {
        slots[index].remove(_value);
        return true;
      }
    }
    return false;
  }

  PowerSet* intersection(PowerSet* set2)
  {
    PowerSet* new_set = new PowerSet; 
    for (int i = 0; i < Size; i++)
    {
      list<char*> List = slots[i];
	  for (list<char*>::iterator _list = List.begin(); _list != List.end(); ++_list)
      {			
        char* _val = *_list;            // cell contents
        if ( set2->get(_val) )          // if "set2" contains "_val"
          new_set->put(_val);           // put "_val" to new_set
      }
    }    
    return new_set;
  }

  PowerSet* _union(PowerSet* set2)
  {
    PowerSet* new_set = new PowerSet;    
    for (int i = 0; i < Size; i++)        //copy set to new_set
    {
      list<char*> List = slots[i];      
	  for (list<char*>::iterator _list = List.begin(); _list != List.end(); ++_list)
      {			
        char* _val = *_list;              
        new_set->put(_val);            
      }
    } 
    for (int i = 0; i < set2->Size; i++)  //copy set2 to new_set if value is not found
    {
      list<char*> List = set2->slots[i];      
	  for (list<char*>::iterator _list = List.begin(); _list != List.end(); ++_list)
      {			
        char* _val = *_list; 
          new_set->put(_val);         
      }
    }    
    return new_set;
  }

  PowerSet* difference(PowerSet* set2)
  {
    PowerSet* new_set = new PowerSet; 
    for (int i = 0; i < Size; i++)
    {
      list<char*> List = slots[i];
	  for (list<char*>::iterator _list = List.begin(); _list != List.end(); ++_list)
      {			
        char* _val = *_list;            
        if ( !set2->get(_val) )          
          new_set->put(_val);           
      }
    }
    return new_set;
  }

  bool is_subset(PowerSet* set2)
  {     
    for (int i = 0; i < set2->Size; i++)
    {
      list<char*> List = set2->slots[i];
	  for (list<char*>::iterator _list = List.begin(); _list != List.end(); ++_list)
      {			
        char* _val = *_list;            
        if ( !get(_val) )        
         return false;  
      }
    }    
    return true;  
  }

private:
  int hashFun_CHAR(char* value)
  {    
    if (value == NULL)
		return -1;
	int index = 0;	 
    index = (int)value[0];
    for (int i = 1; value[i] != 0; i++)  // adder of sumbols    
      index += (int)value[i];    
    if (index < 0) index *= -1;          // number modulus    
    index = hashFun_INT(index, Size);   
    return index;
  }

  int hashFun_INT(int value, int size)
  {    
	  if (value == -1)
		return -1;
	  int p = 17; // Prime number
	  int a = 9;  // 1 ... ð-1
	  int b = 5;  // 0 ... ð-1
	  int index = ( (a*value + b) % p ) % size;
	  return index;
  }

  int seekSlot(char* value)
  {    
    int index = hashFun_CHAR(value);         
    return index;  
  }

  char* find(char* value)
  { 
	int index = hashFun_CHAR(value);				//get index
    list<char*> List = slots[index];
	for (list<char*>::iterator _list = List.begin(); _list != List.end(); ++_list)
    {			
      char* _val = *_list;
      if ( strcmp(value, _val) == 0)	      // compare			  
		return *_list;
    }
     return NULL;
  }
};

//======================= TEST ======================

int test_hash(PowerSet* Table,PowerSet* Table2)
{
	int test = 0;
	char string[] = "light 0";
	for (int i = 49; i <= 100; i++) // fill the entire array 
	{ 
    string[6] = (char)i;    
    Table->put( string );
	}
	if (Table->get("light 1") != true ) test++;
	if (Table->remove("light 1") != true ) test++;
	if (Table->remove("light 1") != false ) test++; 
	if (Table->get("light 1") != false ) test++;
	if (Table->get("dark") != false ) test++;
  
	PowerSet* Table6 = Table2->_union(Table);
	for (int i = 48; i <= 59; i++) // fill the entire array 
	{ 
		string[6] = (char)i;    
		Table2->put( string );
	}
  PowerSet* Table3 = Table->intersection(Table2);
  if (Table3->get("light 0") != false ) test++;
  if (Table3->get("light 2") != true  ) test++;
  if (Table3->get("light F") != false ) test++;

  PowerSet* Table4 = Table->_union(Table2);
  if (Table4->get("light 2") != true ) test++;
  if (Table4->get("light F") != true ) test++;
  if (Table4->get("light 0") != true ) test++;
  if (Table->is_subset(Table3) != true ) test++; 
  if (Table->is_subset(Table2) != false ) test++; 

	PowerSet* set2 = new PowerSet(); 
	char str[] = "l 0";
	for (int i = 48; i <= 59; i++) // fill the entire array 
	{ 
		str[2] = (char)i;    
		set2->put( str );
	}
  PowerSet* set1 = new PowerSet();
	for (int i = 48; i <= 59; i++) // fill the entire array 
	{ 
		str[2] = (char)i;    
		set1->put( str );
	}
	PowerSet* set7 = set1->intersection(set2);
	PowerSet* set5 = set2->intersection(set1);

	char str2[] = "m 0";
	for (int i = 48; i <= 59; i++) // fill the entire array 
	{ 
		str2[2] = (char)i;    
		set1->put( str2 );
	}
  PowerSet* set6 = set2->intersection(set1);
  PowerSet* set8 = set1->intersection(set2);
  PowerSet* set3 = set1->difference(set2);  
  PowerSet* set4 = set2->difference(set1);   
  return test;
}

