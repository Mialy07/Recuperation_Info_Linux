#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

void Nombre_coeur()
{
    ifstream fichier("/proc/cpuinfo");
    string ligne;
    int compteur = 0;
    while (getline(fichier, ligne))
    {
        if (ligne.find("processor") != string::npos)
        {
            compteur = compteur + 1;
        }
    }
    fichier.close();
    cout << "nombre de coeurs CPU : " << compteur << endl;
}

void Memoire_totale_et_libre()
{
    ifstream fichier("/proc/meminfo");
    string ligne;
    int totale_ko = 0;
    int libre_ko = 0;
    while (getline(fichier, ligne))
    {
        if (ligne.find("MemTotal:") != string::npos)
        {
            sscanf(ligne.c_str(), "MemTotal: %d kB", &totale_ko);
        }
        if (ligne.find("MemFree:") != string::npos)
        {
            sscanf(ligne.c_str(), "MemFree: %d kB", &libre_ko);
        }
    }
    fichier.close();
    cout << "mémoire totale : " << (totale_ko / 1024) << "M" << endl;
    cout << "mémoire libre : " << (libre_ko / 1024) << " M" << endl;
}

void Taille_disque()
{
    ifstream fichier("/sys/block/sda/size");
    long secteurs = 0;
    if (fichier.is_open())
    {
        fichier >> secteurs;
        fichier.close();
        cout << "taille du disque : " << ((secteurs * 512) / (1024 * 1024 * 1024)) << " G" << endl;
    }
    else
    {
        cout << "taille du disque : pas trouve" << endl;
    }
}

void Architecture()
{
    ifstream fichier("/proc/cpuinfo");
    string ligne;
    int bits = 32;
    while (getline(fichier, ligne))
    {
        if (ligne.find("flags") != string::npos)
        {
            if (ligne.find(" lm ") != string::npos)
            {
                bits = 64;
            }
            break;
        }
    }
    fichier.close();
    cout << "architecture du système : " << bits << endl;
}

void Nombre_processus()
{
    DIR *d = opendir("/proc");
    struct dirent *entry;
    int compteur = 0;
    
    while ((entry = readdir(d)) != NULL)
    {
        int est_un_nombre = 1;
        for (int i = 0; entry->d_name[i] != '\0'; i++)
        {
            if (entry->d_name[i] < '0' || entry->d_name[i] > '9')
            {
                est_un_nombre = 0;
                break;
            }
        }
        if (est_un_nombre == 1)
        {
            compteur = compteur + 1;
        }
    }
    closedir(d);
    cout << "nombre de processus : " << compteur << endl;
}

void Nombre_logiciels()
{
    ifstream fichier("/var/lib/dpkg/status");
    string ligne;
    int compteur = 0;
    if (!fichier.is_open())
    {
        cout << "Erreur: Paquet introuvable" << endl;
        return;
    }
    while (getline(fichier, ligne))
    {
        if (ligne.find("Package:") != string::npos)
        {
            compteur = compteur + 1;
        }
    }
    fichier.close();
    cout << "nombre de logiciels installés : " << compteur << endl;
}

void Adresse_ip()
{
    FILE *f = popen("hostname -I", "r");
    char ip[50];
    fgets(ip, sizeof(ip), f);
    for (int i = 0; ip[i] != '\0'; i++)
    {
        if (ip[i] == ' ')
        {
            ip[i] = '\0';
            break;
        }
    }
    pclose(f);
    cout << "adresse IP : " << ip << endl;
}

int main()
{
    Nombre_coeur();
    Memoire_totale_et_libre();
    Taille_disque();
    Architecture();
    Nombre_processus();
    Nombre_logiciels();
    Adresse_ip();
    return 0;
}