import tkinter as tk
import os

def Nombre_coeur():
    fichier = open("/proc/cpuinfo", "r")
    compteur = 0
    for ligne in fichier:
        if "processor" in ligne:
            compteur = compteur + 1
    fichier.close()
    return compteur

def Memoire_totale_et_libre():
    fichier = open("/proc/meminfo", "r")
    totale_ko = 0
    libre_ko = 0
    for ligne in fichier:
        if "MemTotal:" in ligne:
            mots = ligne.split()
            totale_ko = int(mots[1])
        if "MemFree:" in ligne:
            mots = ligne.split()
            libre_ko = int(mots[1])
    fichier.close()
    return totale_ko // 1024, libre_ko // 1024

def Taille_disque():
    fichier = open("/sys/block/sda/size", "r")
    secteurs = int(fichier.read().strip())
    fichier.close()
    gigas = (secteurs * 512) // (1024 * 1024 * 1024)
    return gigas

def Architecture():
    fichier = open("/proc/cpuinfo", "r")
    bits = 32
    for ligne in fichier:
        if "flags" in ligne:
            if " lm " in ligne:
                bits = 64
            break
    fichier.close()
    return bits

def Nombre_processus():
    d = os.listdir("/proc")
    compteur = 0
    for entry in d:
        if entry.isdigit():
            compteur = compteur + 1
    return compteur

def Nombre_logiciels():
    fichier = open("/var/lib/dpkg/status", "r")
    compteur = 0
    for ligne in fichier:
        if "Package:" in ligne:
            compteur = compteur + 1
    fichier.close()
    return compteur

def Adresse_ip():
    f = os.popen("hostname -I")
    ip = f.read().strip()
    f.close()
    if " " in ip:
        ip = ip.split()[0]
    return ip

def mettre_a_jour():
    for widget in cadre_interieur.winfo_children():
        widget.destroy()
    
    coeurs = Nombre_coeur()
    totale_mo, libre_mo = Memoire_totale_et_libre()
    utilise_mo = totale_mo - libre_mo
    disque = Taille_disque()
    archi = Architecture()
    processus = Nombre_processus()
    logiciels = Nombre_logiciels()
    ip = Adresse_ip()
    
    # Cadre CPU
    cadre_cpu = tk.Frame(cadre_interieur, bg="white", relief="groove", bd=2)
    cadre_cpu.pack(padx=10, pady=5, fill="x")
    tk.Label(cadre_cpu, text="CPU", bg="white").pack(pady=5)
    tk.Label(cadre_cpu, text=str(coeurs) + " coeurs", bg="white", font=(30)).pack(pady=5)
    
    # Cadre Memoire
    cadre_mem = tk.Frame(cadre_interieur, bg="white", relief="groove", bd=2)
    cadre_mem.pack(padx=10, pady=5, fill="x")
    tk.Label(cadre_mem, text="Memoire RAM", bg="white").pack(pady=5)
    
    # Barre de progression
    pourcentage = (utilise_mo * 100) / totale_mo
    barre = tk.Canvas(cadre_mem, width=200, height=20, bg="white")
    barre.pack(pady=5)
    barre.create_rectangle(2, 2, 2 + (196 * pourcentage // 100), 18, fill="gray", outline="")
    barre.create_rectangle(2, 2, 198, 18, outline="black", width=1, fill="")
    tk.Label(cadre_mem, text=str(utilise_mo) + " Mo / " + str(totale_mo) + " Mo", bg="white").pack(pady=5)
    
    # Cadre Disque
    cadre_disque = tk.Frame(cadre_interieur, bg="white", relief="groove", bd=2)
    cadre_disque.pack(padx=10, pady=5, fill="x")
    tk.Label(cadre_disque, text="Disque dur", bg="white").pack(pady=5)
    tk.Label(cadre_disque, text=str(disque) + " Go", bg="white", font=(30)).pack(pady=5)
    
    # Cadre Architecture
    cadre_arch = tk.Frame(cadre_interieur, bg="white", relief="groove", bd=2)
    cadre_arch.pack(padx=10, pady=5, fill="x")
    tk.Label(cadre_arch, text="Architecture", bg="white").pack(pady=5)
    tk.Label(cadre_arch, text=str(archi) + " bits", bg="white", font=(30)).pack(pady=5)
    
    # Cadre Processus
    cadre_proc = tk.Frame(cadre_interieur, bg="white", relief="groove", bd=2)
    cadre_proc.pack(padx=10, pady=5, fill="x")
    tk.Label(cadre_proc, text="Processus", bg="white").pack(pady=5)
    tk.Label(cadre_proc, text=str(processus), bg="white", font=(30)).pack(pady=5)
    
    # Cadre Logiciels
    cadre_log = tk.Frame(cadre_interieur, bg="white", relief="groove", bd=2)
    cadre_log.pack(padx=10, pady=5, fill="x")
    tk.Label(cadre_log, text="Logiciels installes", bg="white").pack(pady=5)
    tk.Label(cadre_log, text=str(logiciels), bg="white", font=(30)).pack(pady=5)
    
    # Cadre IP
    cadre_ip = tk.Frame(cadre_interieur, bg="white", relief="groove", bd=2)
    cadre_ip.pack(padx=10, pady=5, fill="x")
    tk.Label(cadre_ip, text="Adresse IP", bg="white").pack(pady=5)
    tk.Label(cadre_ip, text=ip, bg="white", font=(30)).pack(pady=5)

# Fenetre principale

fenetre = tk.Tk()
fenetre.title("Info serveur")
fenetre.configure(bg="pink")

cadre_principal = tk.Frame(fenetre, bg="white")
cadre_principal.pack(padx=20, pady=20)

titre = tk.Label(cadre_principal, text="Information sur le serveur", bg="white", fg="red")
titre.pack(pady=10)

cadre_interieur = tk.Frame(cadre_principal, bg="white")
cadre_interieur.pack(pady=10)

bouton = tk.Button(cadre_principal, text="Actualiser", command=mettre_a_jour, bg="pink", fg="gray")
bouton.pack(pady=10)

mettre_a_jour()

fenetre.mainloop()