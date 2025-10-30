🧱 Ambiente C/C++ com OpenGL no Windows (VS Code + CMake + vcpkg)

Este projeto usa um setup moderno para C/C++ com OpenGL no Windows.
Abaixo está a explicação de cada componente envolvido.

1) Editor
✅ Extensão C/C++ (Microsoft)

O que é: suporte a C/C++ no VS Code

Pra que serve: autocompletar, “ir para definição”, debug, IntelliSense

✅ Extensão CMake Tools

O que é: integração entre CMake e VS Code

Pra que serve: rodar Configure / Build / Run, selecionar compilador (kits), presets etc.

2) Compilador e Ambiente do Windows
✅ Visual Studio Build Tools (MSVC)

O que é: compilador C/C++ + ferramentas do Visual Studio

Pra que serve: compilar (cl) e linkar seu código em .exe

Inclui o Windows SDK (headers/libs do sistema)

✅ x64 Native Tools Command Prompt for VS 2022

O que é: terminal com variáveis do MSVC configuradas

Pra que serve: garante que cl e libs estejam no PATH

Dica: abrir o VS Code a partir dele:

code .

3) Sistema de Build
✅ CMake

O que é: gerador de projetos de compilação

Pra que serve: lê CMakeLists.txt e gera arquivos para build (Ninja, Visual Studio, etc.)

Motivo: portabilidade e automação entre Windows/Linux/macOS

(Opcional) ✅ Ninja

O que é: sistema de build super rápido

Pra que serve: usado pelo CMake para builds eficientes

4) Gerenciador de Dependências
✅ vcpkg

O que é: gerenciador de pacotes C/C++ da Microsoft

Pra que serve: instala libs como GLFW, GLAD, GLM…

Integração: via CMAKE_TOOLCHAIN_FILE
-> CMake passa a encontrar libs automaticamente

5) Bibliotecas Usadas
✅ GLFW

O que é: cria janela e contexto OpenGL

Pra que serve: entrada de teclado/mouse e criação da janela

✅ GLAD (loader OpenGL moderno)

O que é: carrega funções OpenGL em runtime

Pra que serve: acesso a funções modernas gl*

✅ GLM

O que é: matemática (vetores, matrizes, transformações)

Pra que serve: operações de câmera, transformações etc.

🔜 OpenGL 4.3+

O que é: API gráfica (4.3 libera compute shaders)

Pra que serve: renderização e futuros cálculos de geodésica na GPU

Requer: GPU + drivers atualizados

6) Arquivos do Projeto
Arquivo	Função
CMakeLists.txt	receita do projeto: fontes, flags, dependências
CMakeUserPresets.json (opcional)	presets locais: Ninja, MSVC, vcpkg, build dir
src/main.cpp	cria janela OpenGL, inicializa GLAD/GLFW, loop básico
7) Como Tudo Conversa

Visão geral do pipeline:

VS Code (CMake Tools)
   → chama CMake (MSVC + vcpkg toolchain)
      → encontra GLFW/GLAD/GLM
         → compila main.cpp
            → linka libs
               → executável abre janela OpenGL ✅