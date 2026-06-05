#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>

void Nombre_coeur() 
{
    FILE *f = fopen("/proc/cpuinfo", "r");
    char ligne[300];
    int compteur = 0;
    
    while (fgets(ligne, sizeof(ligne), f)) 
    {
        if (strstr(ligne, "processor") != NULL) {
            compteur++;
        }
    }
    fclose(f);
    printf("nombre de coeurs CPU : %d\n", compteur);
}

void Memoire_totale_et_libre()
{
    FILE *f = fopen("/proc/meminfo", "r");
    char ligne[300];
    int totale_ko = 0;
    int libre_ko = 0;
    
    while (fgets(ligne, sizeof(ligne), f))
    {
        if (strstr(ligne, "MemTotal:") != NULL) 
        {
            sscanf(ligne, "MemTotal: %d kB", &totale_ko);
        }
        if (strstr(ligne, "MemFree:") != NULL) 
        {
            sscanf(ligne, "MemFree: %d kB", &libre_ko);
        }
    }
    fclose(f);
    
    printf("mémoire totale : %dM\n", totale_ko / 1024);
    printf("mémoire libre : %d M\n", libre_ko / 1024);
}

void Taille_disque()
{
    char chemin[100];
    FILE *f;
    long secteurs;
    f = fopen("/sys/block/sda/size", "r");
    if (f != NULL)
    {
        fscanf(f, "%ld", &secteurs);
        fclose(f);
        printf("taille du disque : %ld G\n", (secteurs * 512) / (1024 * 1024 * 1024));
        return;
    }
    printf("taille du disque : pas trouve\n");
}

void Architecture()
{
    FILE *f = fopen("/proc/cpuinfo", "r");
    char ligne[300];
    int bits = 32;
    while (fgets(ligne, sizeof(ligne), f))
    {
        if (strstr(ligne, "flags") != NULL)
        {
            if (strstr(ligne, " lm ") != NULL) {
                bits = 64;
            }
            break;
        }
    }
    fclose(f);
    printf("architecture du système : %d\n", bits);
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
        if (est_un_nombre == 1) {
            compteur++;
        }
    }
    closedir(d);
    printf("nombre de processus : %d\n", compteur);
}

void Nombre_logiciels()
{
    FILE *f = fopen("/var/lib/dpkg/status", "r");
    char ligne[500];
    int compteur = 0;
    if (f == NULL) {
        printf("Erreur: Paquet introuvable\n");
        return;
    }
    while (fgets(ligne, sizeof(ligne), f))
    {
        if (strstr(ligne, "Package:") != NULL) {
            compteur++;
        }
    }
    fclose(f);
    printf("nombre de logiciels installés : %d\n", compteur);
}

void Adresse_ip()
{
    FILE *f = popen("hostname -I", "r");
    char ip[50];
    fgets(ip, sizeof(ip), f);
    ip[strcspn(ip, " ")] = '\0';
    pclose(f);
    printf("adresse IP : %s\n", ip);
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