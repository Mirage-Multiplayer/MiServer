import shutil
import os
import argparse

def cpfolder(origem, destino):
    try:
        if os.path.exists(destino):
            print(f"A pasta de destino '{destino}' já existe.")
            return
        
        shutil.copytree(origem, destino)
        print(f"Pasta '{origem}' copiada para '{destino}' com sucesso!")
    except Exception as e:
        print(f"Erro ao copiar a pasta: {e}")

def create_release(platform):
    if not os.path.exists(f"./release/{platform}"):
        os.makedirs(f"./release/{platform}")
    cpfolder("./include", f"./release/{platform}/include")
    cpfolder("./docs", f"./release/{platform}/docs")
    cpfolder("./install/lib", f"./release/{platform}/lib")

def main():
    parser = argparse.ArgumentParser(description="Script para criar releases.")
    parser.add_argument("--platform", type=str, help="Nome da plataforma para a qual criar a release.")
    args = parser.parse_args()
    if args.platform:
        create_release(args.platform)
    else:
        print("Nenhuma plataforma especificada.")

if __name__ == "__main__":
    main()
