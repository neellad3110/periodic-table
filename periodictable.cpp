#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include<process.h>
 
using namespace std;
fstream fin,fout;  
class Elements{

    public:

    // data members
    int at_no;                          // atomic number
    char at_name[50];                   // atomic name of the element
    char at_symbol[30];                 // atomic symbol of the element 
    char at_configuration[50];          // atmoic electronic configuration of the element 
    int at_mass;                        // atomic mass of the element 
    char at_nature[30];                 // atmoic nature of the element 
    char at_block[5];                   // block of the element

    // methods
    void fetchdata_of_element(int n);   // input for various attributes of an element
    void showdata_of_element();         // displaying data of an element
    void add_new_element();             // adding new record
    void display_element();             // fetch record from the file  
    void check_atomic_no();             // fetching record with reference to atomic number
    void check_atomic_name();           // fetching record with reference to atomic name
    void check_atomic_symbol();         // fetching record with reference to atomic symbol
    void update_element();              // update a record
    void delete_element();              // delete a record

    void viewtable();                   // view full periodic table    
    void view_Sblock();                 // view S block
    void view_Pblock();                 // view P block
    void view_Dblock();                 // view D block
    void view_Fblock();                 // view F block

}E,e;                   // objects of class Element               


void Elements::fetchdata_of_element(int n=0){

    cout<<endl;
    
     if(n){
         at_no=n;
     }else{
         cout<<"Enter the Atomic Number : ";
         cin>>at_no;
        
    }
   

   
    cout<<"Enter the Atomic Name : ";
    cin>>at_name;

    cout<<"Enter the Atomic Symbol of "<<at_name<<" : ";
    cin>>at_symbol;

   

    cout<<"Enter the Atomic Mass of "<<at_name<<" : ";
    cin>>at_mass;
    cin.ignore();
    cout<<"Enter the Electronic Configuration of "<<at_name<<" : ";
    cin>>at_configuration;
    cout<<"Enter the Nature of "<<at_name<<" : ";
    cin>>at_nature;
    cout<<"Enter the Representative Block of "<<at_name<<" : ";
    cin>>at_block;

    
}

void Elements::showdata_of_element(){
    
    
        if(at_no!=0){
            cout<<endl<<"Element : "<<at_name<<endl;
            cout<<"Atomic Number of "<<at_name<<" : "<<at_no<<endl;
            cout<<"Atomic Symbol of "<<at_name<<" : "<<at_symbol<<endl;
            cout<<"Atomic Mass of "<<at_name<<" : "<<at_mass<<endl;
            cout<<"Electronic Configuration of "<<at_name<<" : "<<at_configuration<<endl;
            cout<<"Nature of "<<at_name<<" : "<<at_nature<<endl;
            cout<<"Representative Block of "<<at_name<<" : "<<at_block<<endl<<endl;
            cout<<"------------------------------------------------------------------"<<endl;
        }
 
}

void Elements::add_new_element(){

    fout.open("elements.dat",ios::out|ios::binary|ios::app);
    if(!fout){
        cout<<"\nError Encountered.. :(";
        exit(0);
    }
    e.fetchdata_of_element();
    fout.write((char*)&e,sizeof(e));
    fout.close();
}

void Elements::display_element(){

    fin.open("elements.dat",ios::in|ios::binary);
    if(!fin){
        cout<<"\nError Encountered.. :(";
        exit(0);
    }

    while(fin.read((char*)&E,sizeof(E))){
        E.showdata_of_element();
    }
    
    fin.close();
}

void Elements:: check_atomic_no(){

    int atno,flag=0;
    cout<<"\n\nEnter the Atomic Number : ";
    cin>>atno;
    
    fin.open("elements.dat",ios::in|ios::binary);
    
    if(!fin){
        cout<<"\nError Encountered.. :(";
        exit(0);
    }

    while(fin.read((char*)&E,sizeof(E))){
       if(E.at_no==atno){
            cout<<"\nElement found : "<<E.at_name<<" ( "<<E.at_symbol<<" ) ."<<endl;
            cout<<"Element Attributes .."<<endl;
            E.showdata_of_element();
            flag=1;
       }
    }
    if(flag==0){
        cout<<"\nMessage : Element not Found.."<<endl<<endl;;
    }
    fin.close();
}

void Elements:: check_atomic_symbol(){

    int flag=0;
    char symb[10];
    cout<<"\n\nEnter the Atomic Symbol of the element : ";
    cin.ignore();
    gets(symb);
    
    fin.open("elements.dat",ios::in|ios::binary);
    
    if(!fin){
        cout<<"\nError Encountered.. :(";
        exit(0);
    }

    while(fin.read((char*)&E,sizeof(E))){
       if(strcmpi(E.at_symbol,symb)==0){
            cout<<"\nElement found : "<<E.at_name<<" ( "<<E.at_symbol<<" ) ."<<endl;
            cout<<"Element Attributes .."<<endl;
            E.showdata_of_element();
            flag=1;
       }
    }
    if(flag==0){
        cout<<"\nMessage : Element not Found.."<<endl<<endl;;
    }
    fin.close();
}

void Elements:: check_atomic_name(){

    int flag=0;
    char name[50];
    cout<<"\n\nEnter the Atomic Name of the element : ";
    cin.ignore();
    gets(name);
    
    fin.open("elements.dat",ios::in|ios::binary);
    
    if(!fin){
        cout<<"\nError Encountered.. :(";
        exit(0);
    }
    
    while(fin.read((char*)&E,sizeof(E))){
       if(strcmpi(E.at_name,name)==0){
            
            cout<<"\nElement found : "<<E.at_name<<" ( "<<E.at_symbol<<" ) ."<<endl;
            cout<<"Element Attributes .."<<endl;
            E.showdata_of_element();
            flag=1;
            break;
       }
    }
    if(flag==0){
        cout<<"\nMessage : Element not Found.."<<endl<<endl;
    }
    fin.close();
}

void Elements :: update_element(){

    int number,flag=0;
    cout<<"\n\nValid Atomic Number : ";
    cin>>number;
    fin.open("elements.dat",ios::in|ios::out|ios::binary);

    if(!fin){ 
        cout<<"\nError Encountered.. :(";
        exit(0);
    }
    while(fin.read((char*)&E,sizeof(E))){
        if(E.at_no==number){

            cout<<"\nElement found : "<<E.at_name<<" ( "<<E.at_symbol<<" ) ."<<endl;
            cout<<"Update the record .."<<endl<<endl;
           
            
            E.fetchdata_of_element(number);

            cout<<fin.tellg()<<"--"<<sizeof(E);
            int pos=((int)fin.tellg())-((int)sizeof(E));
            fin.seekp(pos);
            fin.write((char*)&E,sizeof(E));
            cout<<"\nRecord updated successfully.."<<endl;
             flag=1;            
        }
    }

    if(flag==0){
        cout<<"\nMessage : Element not Found.."<<endl<<endl;;
    }
    fin.close();
    

}

void Elements :: delete_element(){

    char blankdata[206]={};
    int number,flag=0,pos;
    cout<<"\n\nValid Atomic Number : ";
    cin>>number;
    fin.open("elements.dat",ios::in|ios::out|ios::binary);

    if(!fin){ 
        cout<<"\nError Encountered.. :(";
        exit(0);
    }
    while(fin.read((char*)&E,sizeof(E))){
        if(E.at_no==number){

            cout<<"\nElement found : "<<E.at_name<<" ( "<<E.at_symbol<<" ) ."<<endl;
            cout<<"Deleting the record .."<<endl<<endl;

            
            pos=((int)fin.tellg())-((int)sizeof(E));
            fin.seekp(pos);
            fin.write(blankdata,176);   
            flag=1;        
        }

        
    }

    
    if(flag==0){
        cout<<"\nMessage : Element not Found.."<<endl<<endl;;
    }
    fin.close();
    

}


void Elements::viewtable(){
    system("cls");
    cout<<"                                          PERIODIC TABLE"<<endl;
    cout<<"\t ------                                                                                ------"<<endl;
    cout<<"\t | He |                                                                                | He |"<<endl;
    cout<<"\t -----------                                                  -------------------------------"<<endl;
    cout<<"\t | Li | Be |                                                  | B  | C  | N  | O  | F  | Ne |"<<endl;
    cout<<"\t -----------                                                  -------------------------------"<<endl;
    cout<<"\t | Na | Mg |                                                  | Al | Si | P  | S  | Cl | Ar |"<<endl;
    cout<<"\t -------------------------------------------------------------------------------------------"<<endl;
    cout<<"\t | K  | Ca | Sc  | Ti | V  | Cr | Mn | Fe | Co | Ni | Cu | Zn | Ga | Ge | As | Se | Br | Kr |"<<endl;
    cout<<"\t --------------------------------------------------------------------------------------------"<<endl;
    cout<<"\t | Rb | Sr | Y   | Zr | Nb | Mo | Tc | Ru | Rh | Pd | Ag | Cd | In | Sn | Sb | Te | I  | Xe |"<<endl;
    cout<<"\t --------------------------------------------------------------------------------------------"<<endl;
    cout<<"\t | Cs | Ba | La* | Hf | Ta | W  | Re | Os | Ir | Pt | Au | Hg | Tl | Pb | Bi | Po | At | Rn |"<<endl;
    cout<<"\t --------------------------------------------------------------------------------------------"<<endl;
    cout<<"\t | Fr | Ra | Ac* | Rf | Db | Sg | Bh | Hs | Mt | Ds | Rg | Cn | Nh | Fl | Mc | Lv | Ts | Og |"<<endl;
    cout<<"\t --------------------------------------------------------------------------------------------"<<endl;
    cout<<endl<<endl;
    cout<<"\t           -----------------------------------------------------------------------------"<<endl;
    cout<<"\t           | La* | Ce | Pr | Nd | Pm | Sm | Eu | Gd | Tb | Dy | Ho | Er | Tm | Yb | Lu |"<<endl;
    cout<<"\t           -----------------------------------------------------------------------------"<<endl;
    cout<<"\t           | Ac* | Th | Pa | U  | Np | Pu | Am | Cm | Bk | Cf | Es | Fm | Md | No | Lr |"<<endl;
    cout<<"\t           -----------------------------------------------------------------------------"<<endl<<endl;

}

void Elements :: view_Sblock(){
    system("cls");
    cout<<"\t       S Block"<<endl<<endl;
    cout<<"\t ------     "<<endl; 
    cout<<"\t | He |     "<<endl;
    cout<<"\t -----------"<<endl;
    cout<<"\t | Li | Be |"<<endl;
    cout<<"\t -----------"<<endl;
    cout<<"\t | Na | Mg |"<<endl;
    cout<<"\t -----------"<<endl;
    cout<<"\t | K  | Ca |"<<endl;
    cout<<"\t -----------"<<endl;
    cout<<"\t | Rb | Sr |"<<endl;
    cout<<"\t -----------"<<endl;
    cout<<"\t | Cs | Ba |"<<endl;
    cout<<"\t -----------"<<endl;
    cout<<"\t | Fr | Ra |"<<endl;
    cout<<"\t -----------"<<endl<<endl;   
}

void Elements::view_Pblock(){
    system("cls");
    cout<<"\t           P Block"<<endl<<endl;
    cout<<"\t                         ------"<<endl;
    cout<<"\t                         | He |"<<endl;
    cout<<"\t-------------------------------"<<endl;
    cout<<"\t| B  | C  | N  | O  | F  | Ne |"<<endl;
    cout<<"\t-------------------------------"<<endl;
    cout<<"\t| Al | Si | P  | S  | Cl | Ar |"<<endl;
    cout<<"\t-------------------------------"<<endl;
    cout<<"\t| Ga | Ge | As | Se | Br | Kr |"<<endl;
    cout<<"\t-------------------------------"<<endl;
    cout<<"\t| In | Sn | Sb | Te | I  | Xe |"<<endl;
    cout<<"\t-------------------------------"<<endl;
    cout<<"\t| Tl | Pb | Bi | Po | At | Rn |"<<endl;
    cout<<"\t-------------------------------"<<endl;
    cout<<"\t| Nh | Fl | Mc | Lv | Ts | Og |"<<endl;
    cout<<"\t-------------------------------"<<endl<<endl;

}

void Elements :: view_Dblock(){
    system("cls");
    cout<<"\t                   D Block"<<endl<<endl;
    cout<<"\t----------------------------------------------------"<<endl;
    cout<<"\t| Sc  | Ti | V  | Cr | Mn | Fe | Co | Ni | Cu | Zn |"<<endl;
    cout<<"\t----------------------------------------------------"<<endl;
    cout<<"\t| Y   | Zr | Nb | Mo | Tc | Ru | Rh | Pd | Ag | Cd |"<<endl;
    cout<<"\t----------------------------------------------------"<<endl;
    cout<<"\t| La* | Hf | Ta | W  | Re | Os | Ir | Pt | Au | Hg |"<<endl;
    cout<<"\t----------------------------------------------------"<<endl;
    cout<<"\t| Ac* | Rf | Db | Sg | Bh | Hs | Mt | Ds | Rg | Cn |"<<endl;
    cout<<"\t----------------------------------------------------"<<endl<<endl;
}

void Elements:: view_Fblock(){
    system("cls");
    cout<<"\t                                   F Block"<<endl<<endl;
    cout<<"\t-----------------------------------------------------------------------------"<<endl;
    cout<<"\t| La* | Ce | Pr | Nd | Pm | Sm | Eu | Gd | Tb | Dy | Ho | Er | Tm | Yb | Lu |"<<endl;
    cout<<"\t-----------------------------------------------------------------------------"<<endl;
    cout<<"\t| Ac* | Th | Pa | U  | Np | Pu | Am | Cm | Bk | Cf | Es | Fm | Md | No | Lr |"<<endl;
    cout<<"\t-----------------------------------------------------------------------------"<<endl<<endl;

}

void viewsubtable(){
    
    char ch;
    int choice;
    do{
        system("cls");
        cout<<"\n\t        View Periodic Table"<<endl<<endl;
        cout<<"\t\t\t  ________________________________"<<endl;
        cout<<"\t\t\t |             Menu               |"<<endl;
        cout<<"\t\t\t |                                |"<<endl;
        cout<<"\t\t\t |  1. View Full Periodic Table.  |"<<endl;    
        cout<<"\t\t\t |  2. View S Block.              |"<<endl;    
        cout<<"\t\t\t |  3. View P Block.              |"<<endl;    
        cout<<"\t\t\t |  4. View D Block.              |"<<endl;    
        cout<<"\t\t\t |  5. View F Block.              |"<<endl;    
        cout<<"\t\t\t |  6. Back to Previous Menu.     |"<<endl;    
        cout<<"\t\t\t |________________________________|"<<endl<<endl;
        cout<<"\tSelect your choice : ";
        cin>>choice;
        
        switch(choice){

            case 1: e.viewtable();
                    break;
            case 2: e.view_Sblock();
                    break;
            case 3: e.view_Pblock();
                    break;
            case 4: e.view_Dblock();
                    break;
            case 5: e.view_Fblock();
                    break;
            case 6: break;

            default : cout<<"Invalid choice.."<<endl;        

        }
        if(choice==6) break;


        cout<<"Want to enter more ? (y/n) : ";
        cin>>ch;

    }while(ch=='y'|| ch=='Y');
 
}

void viewsubfetch(){
    
    char ch;
    int choice;
    do{
        system("cls");
        cout<<"\n\t        Choose Parameters"<<endl<<endl;
        cout<<"\t\t\t  ________________________________"<<endl;
        cout<<"\t\t\t |             Parameters         |"<<endl;
        cout<<"\t\t\t |                                |"<<endl;
        cout<<"\t\t\t |  1. Search by Atomic Number.   |"<<endl;    
        cout<<"\t\t\t |  2. Search by Atomic Name.     |"<<endl;    
        cout<<"\t\t\t |  3. Search by Atomic Symbol    |"<<endl;    
        cout<<"\t\t\t |  4. Back to Previous Menu.     |"<<endl;    
        cout<<"\t\t\t |________________________________|"<<endl<<endl;
        cout<<"\tSelect your choice : ";
        cin>>choice;

        switch(choice){

            case 1: e.check_atomic_no();
                    break;
            case 2: e.check_atomic_name();
                    break;
            case 3: e.check_atomic_symbol();
                    break;
            case 4: break;

            default : cout<<"Invalid choice.."<<endl;        

        }
        if(choice==4) break;


        cout<<"Want to enter more ? (y/n) : ";
        cin>>ch;

    }while(ch=='y'|| ch=='Y');
 
}
int main(){

    // system("cls");
    // e.delete_element();
   
    char ch;
    int choice,pass;
    do{ 
        system("cls");
        pass=0;
        cout<<"\n\t\t\t             Main Menu"<<endl<<endl;
        cout<<"\t\t\t  _______________________________"<<endl;
        cout<<"\t\t\t |             Menu              |"<<endl;
        cout<<"\t\t\t |                               |"<<endl;
        cout<<"\t\t\t |  1. Display Periodic Table.   |"<<endl;    
        cout<<"\t\t\t |  2. Add New Element.          |"<<endl;    
        cout<<"\t\t\t |  3. Display All Elements.     |"<<endl;    
        cout<<"\t\t\t |  4. Find Element.             |"<<endl;    
        cout<<"\t\t\t |  5. Update Element.           |"<<endl;    
        cout<<"\t\t\t |  6. Delete a Element.         |"<<endl;    
        cout<<"\t\t\t |  6. Exit.                     |"<<endl;    
        cout<<"\t\t\t |_______________________________|"<<endl<<endl;
        cout<<"\tSelect your choice : ";
        cin>>choice;

        switch(choice){

            case 1: viewsubtable(); pass=1; break;
                    
            case 2: e.add_new_element();
                    break;
            case 3: e.display_element();  
                    break;
                    
            case 4: viewsubfetch(); pass=1; break;
                    break;
            case 5: e.update_element();
                    break;
            case 6: e.delete_element();
                    break;
            case 7: exit(0);

            default : cout<<"Invalid choice.."<<endl;        

        }

        if(pass==0){
            cout<<"Want to enter more ? (y/n) : ";
            cin>>ch;
        }else{
            ch='y';
        }
        

    }while(ch=='y'|| ch=='Y');
    
    getch();


}