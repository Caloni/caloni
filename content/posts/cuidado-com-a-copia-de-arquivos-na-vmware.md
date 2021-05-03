---
categories:
- code
date: '2009-07-27'
tags:
- draft
title: Cuidado com a cópia de arquivos na VMWare
---

Quebrei a cabeça com uma DLL de hook que não estava funcionando para usuários comuns. No entanto, para qualquer administrador funcionava.

Isso acontece porque quando se arrasta uma DLL recém-compilada para a VMWare ela possui um mecanismo que primeiro cria esse arquivo no temporário do usuário atual e depois move esse arquivo para o lugar onde você de fato arrastou.

Como sabemos, a pasta temporária de um usuário fica em seu perfil, que possui direitos de uso apenas do usuário e dos administradores do sistema. Se eu copio um arquivo de uma pasta restrita para outra pasta os direitos do arquivo permanecem. Isso quer dizer que apenas o usuário atual e os administradores terão acesso ao arquivo, mesmo que se trate de um arquivo para uso de todos.

Resultado: arrastava a nova DLL de hook compilada da pasta de saída direto para a pasta de sistema da máquina virtual e esse caminho através do temporário era seguido, tornando a DLL inacessível para os usuários que eu estava testando.

Solução: após arrastar o arquivo, mude suas permissões. Ou copie-o através do bom e velho copiar/colar. Diferente do arrastar, o Ctrl+C Ctrl+V não gera arquivos temporários.