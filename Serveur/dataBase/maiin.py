import sqlite3

# Créer le fichier de base de données
db = sqlite3.connect("mdp.db")

# Créer un cursor pour executer des requetes
cursor = db.cursor()

# Créer une requete pour générer une table
cursor.execute("""
CREATE TABLE IF NOT EXISTS users(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    login TEXT UNIQUE NOT NULL,
    password TEXT NOT NULL,
    date_creation TEXT DEFAULT (datetime('now', 'localtime'))            
)
""")

# Ajouter users dans la table "users"
cursor.execute("INSERT INTO users (login, password) VALUES (?, ?)", ('Lucas', '/tsukA?'))
cursor.execute("INSERT INTO users (login, password) VALUES (?, ?)", ('Fred', '@GaNg.ct'))

# Executer les requetes
db.commit()

# Lire les données
cursor.execute("SELECT * FROM users")
for row in cursor.fetchall():
    print(row)


# Recupere Password de l'id 1
cursor.execute("SELECT password FROM users WHERE id = ?", (1, ))
result = cursor.fetchone()
if result:
    print("Password: ", result[0])
else:
    print("Aucun utilisateur n'a été trouvé !")

# Modifié un élément 
cursor.execute("UPDATE users SET password = ? WHERE id = ?", ('!Prime!', 1))
print("Password modifié !")
db.commit()

# Suprimé un élément 
cursor.execute("DELETE FROM users WHERE password = ?", ('!Prime!', ))
print("Utilisateur suprimé")
db.commit()

db.close()