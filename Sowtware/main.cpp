//
//  main.cpp
//  Sowtware
//
//  Created by Julian Orozco on 11/5/14.
//  Copyright (c) 2014 Julian Orozco. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//Globales
int cont1;
int contID;
int contPass;
vector<string> arrId;
vector<string>arrPass;
vector<string> arrNom;

//Verificar LOG IN
bool idVer(string id, string pass)
{
    contID = -1;
    contPass = -2;
    for (int i=0; i<arrId.size(); i++)
    {
        if (arrId[i]==id)
        {
            contID=i;
        }
    }
    for (int j=0; j<arrPass.size(); j++)
    {
        if (arrPass[j]==pass)
        {
            contPass=j;
        }
    }
    if (contID==contPass)
    {
        return true;
    }
    else
    {
        return false;
    }
}
//Verificacion Password
bool verPass(string pass, string npass)
{
    if (pass==npass) {
        return true;
    }
    else return false;
}
//Verificacion de disponibilidad de Usuario en Sing Up
bool verUsuario(string id)
{
    string sId;
    for (int i=0; i<arrId.size(); i++)
    {
        if (arrId[i]==id) {
            sId=arrId[i];
        }
    }
    if (sId==id) {
        return false;
    }
    else
        return true;
}
int main(int argc, const char * argv[])
{
    char opcion;
    string sId, sNombre, sPass, vPass;
    ifstream archUsuarios;
    ofstream archUsuariosSal;
    bool existe=false, existepass=false, existeid=false;
    
    archUsuarios.open("Usuarios.txt");
    
    while (! archUsuarios.eof())
    {
        archUsuarios>>sId>>sPass;
        archUsuarios.ignore();
        getline(archUsuarios, sNombre);
        arrId.push_back(sId);
        arrPass.push_back(sPass);
        arrNom.push_back(sNombre);
    }
    
   
    do
    {
        cout<<"Menu"<<endl;
        cout<<"a. LOG IN"<<endl;
        cout<<"b. SING UP"<<endl;
        cout<<"c. LOG OUT"<<endl;
        cout<<"d. Salir"<<endl;
        cin>>opcion;
        
        switch (opcion) {
                //LOGIN
            case 'a':
            case 'A':
                do{
                    cout<<"Username: ";
                    cin>>sId;
                    cout<<"Password: ";
                    cin>>sPass;
                    //Verificacion de id y contrasena
                    existe=idVer(sId,sPass); 
                    if (existe==true) {
                        cout<<"Bienvenido "<<arrNom[contID]<<endl;
                    }
                    else
                    {cout<<"Error, favor de ingresar nuevamente los datos."<<endl;}
                }while(existe!=true);
                break;
                
            case 'b':
            case 'B':
                //SIGN UP
                //Verificacion que no exista el ususario
                do{
                cout<<"Ingrese su Mail(nombre de usuario): ";
                cin>>sId;
                existeid=verUsuario(sId);
                if (existeid==true)
                {
                    arrId.push_back(sId);
                }
                else
                {cout<<"El usuario que ingreso ya existe, vuelva a intentar."<<endl;}
                }while(existeid!=true);
                cout<<"Ingrese su nombre completo: ";
                cin>>sNombre;
                arrNom.push_back(sNombre);
                //Verificacion de igualdad de contrasenas
                do{
                    //Verificacion de longitud de contrasena
                    do{
                        cout<<"Ingrese su contrasena(Mayor o igual a 6 caracteres): ";
                        cin>>sPass;
                        if (sPass.length()<6) {
                            cout<<"Favor de ingresar nuevamente la contrasena con una longitud de minimo 6 caracteres."<<endl;}
                    }while(sPass.length()<6);
                        cout<<"Ingrese de nuevo su contrasena: ";
                        cin>>vPass;
                        existepass=verPass(sPass, vPass);
                            if (existepass==true)
                                {
                                    arrPass.push_back(sPass);
                                }
                            else
                            {cout<<"Error, favor de ingresar nuevamente su contrasena."<<endl;}
                }while (existepass!=true);
                
                break;
                
            case 'c':
            case 'C':
                cout<<"Adios "<<arrNom[contID]<<endl;
                sId=" ";
                sPass=" ";
                sNombre=" ";
                vPass=" ";
                existe=false;
                existeid=false;
                existepass=false;
                break;
                
                
            case 'd':
            case 'D':
                //Meter los nuevos datos al archivo
                archUsuariosSal.open("Usuarios.txt");
                for (int i=0; i<arrId.size(); i++)
                {
                    archUsuariosSal<<arrId[i]<<" "<<arrPass[i]<<" "<<arrNom[i]<<endl;
                }

                exit(0);
                break;
        }
        
    }while (opcion!='d' || opcion!='D');
    
    
    
    archUsuarios.close();
    archUsuariosSal.close();
    return 0;
}

